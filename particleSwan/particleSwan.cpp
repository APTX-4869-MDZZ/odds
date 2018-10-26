#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>
#include<map>
#include<limits>
#include<time.h>
#include<iomanip>
#include<stdlib.h>
#include<cstdio>

// 参数设置
#define S 40
#define c1 2
#define c2 2
#define maxgen 10000000
#define w_start 0.9
#define w_end 0.4
#define vmax 20
#define MAXD 50 // 最大任务数量

using namespace std;

typedef map<int, vector<int> > Meantime;

struct Task {
    int number;
    int time;
};
int d, conflictD, meantimeD, rejectStart, rejectEnd;
int remainNumber;
vector<Task> tasks;
Meantime meantime;
int conflicts[MAXD][2];
double x[S][MAXD];
double v[S][MAXD];
double M[S][MAXD];
double flist[S];
double bestf[S];
double minf;
double minx[MAXD];
double timeSum;
double minTime[7];
double minMiddleTime[MAXD][7];
double timePerDay[7];

// 计算均方差
double getVariance(int k) {
    memset(timePerDay, 0, sizeof(timePerDay));

    // 统计每日检修时间
    for (int i = 0; i < d; i++) {
        int day = floor(x[k][i] / 24);
        int endDay = floor((x[k][i]+tasks.at(i).time)/24);
        if (endDay != day) {
            // 跨日
            double thisDay = 24-(x[k][i]-day*24);
            timePerDay[day] += thisDay;
            timePerDay[endDay] += tasks.at(i).time-thisDay;
        } else {
            // 不跨日
            timePerDay[day] += tasks.at(i).time *1.0;
        }
    }

    // 计算均方差
    double timeAvg = timeSum / 7.0;
    double variance = 0.0;
    for (int i = 0; i < 7; i++) {
        variance = variance+(timePerDay[i]-timeAvg)*(timePerDay[i]-timeAvg);
    }
    double answer = sqrt(variance/7.0);
    return answer;
}

bool checkRestrain(int k) {
    // 检查互斥约束
    for (int i = 0; i < conflictD; i++) {
        int p = conflicts[i][0];
        int q = conflicts[i][1];
        if (!((x[k][p]>x[k][q]+tasks.at(q).time)||(x[k][q]>x[k][p]+tasks.at(p).time))) {
            return false;
        }
    }

    // 检查同时性约束
    Meantime::iterator iter;
    for (iter = meantime.begin(); iter != meantime.end(); iter++) {
        double startTime = x[k][iter->second.front()];
        double endTime = startTime+tasks.at(iter->second.front()).time;
        for (int i = 1; i < iter->second.size(); i++) {
            int j = iter->second.at(i);
            if (x[k][j] < startTime || x[k][j]+tasks.at(j).time > endTime) {
                return false;
            }
        }
    }

    // 检查保供电约束
    for (int i = 0; i < d; i++) {
        if (tasks.at(i).number == remainNumber && !(x[k][i] > rejectEnd|| x[k][i]+tasks.at(i).time<rejectStart)) {
            return false;
        }
    }
    return true;
}

// 计算目标函数
double f(int k) {
    // 检查当前位置是否符合限制条件
    if (checkRestrain(k)) {
        return getVariance(k);
    } else {
        return numeric_limits<double>::max();
    }
}

// 读入
void input() {
/*
读入格式：
    第一行：检修任务总数d
    第二行开始的d行每行输入检修任务编号，所需时间，用一个空格间隔
    第d+2行：冲突线路数量conflictD
    第d+3行开始的conflictD行每行输入冲突的两条任务
    第d+conflictD+4行：需要同时进行的任务组数meantimeD
    之后开始的meantimeD行：每组需要同时进行的任务编号，用一个空格间隔
    最后一行为保修线路相关的任务编号，与保修的开始时间与结束时间，均转化成【0，168】的小时数
*/
    cin >> d;
    timeSum = 0;
    int number;
    int time;
    for (int i = 0; i < d; i++) {
        cin >> number;
        cin >> time;
        tasks.push_back(Task{number-1, time});
        timeSum += time;
    }

    // 读入互斥约束的任务
    cin >> conflictD;
    int conflictx, conflicty;
    for (int i = 0; i < conflictD; i++) {
        cin >> conflictx >> conflicty;
        conflicts[i][0] = conflictx - 1;
        conflicts[i][1] = conflicty - 1;
    }

    // 读入同时约束的任务
    cin >> meantimeD;
    int taskNo;
    char c;
    for (int i = 0; i < meantimeD; i++) {
        vector<int> meantimeQueue;
        meantime.insert(pair<int, vector<int> >(i, meantimeQueue));
        Meantime::iterator iter = meantime.find(i);
        while(true)
        {
            scanf("%d", &taskNo);
            taskNo --;
            if (iter->second.size() > 0) {
                if (tasks.at(taskNo).time > tasks.at(iter->second.front()).time) {
                    iter->second.insert(iter->second.begin(), taskNo);
                } else {
                    iter->second.push_back(taskNo);
                }
            } else {
                iter->second.push_back(taskNo);
            }
            scanf("%c", &c);
            if (c == '\n') {
                break;
            }
        }
    }
    cin >> remainNumber >> rejectStart >> rejectEnd;
}

// 初始化粒子参数
void initialize() {
    while (true) {
        for(int i=0; i<S; i++)
        {
            for(int j=0; j<d; j++)
            {
                x[i][j] = (((double)rand())/RAND_MAX)*165;  //获得小于165的各维位置初始值
                v[i][j] = (((double)rand())/RAND_MAX-0.5)*vmax*2;   // 获得小于±vmax的速度初始值
                M[i][j] = x[i][j];
            }
        }

        // 检查有否存在合理的初始值，否则继续初始化
        int bestN = 0;
        for (int i = 0; i < S; i++) {
            flist[i] = f(i);
            if (flist[i] < flist[bestN]) {
                bestN = i;
            }
        }
        if (flist[bestN] < 1.7e300) {
            break;
        }
    }
}

// 粒子迭代
void PSOfunc() {
    int pp = 0;
    int bestN = 0;
    minf = numeric_limits<double>::max();
    double w = w_start;
    for (int t = 0; t >= 0; t++) {

        w = w_end + (w_start-w_end)*(maxgen-t)/maxgen;
//        w = w_start + (w_start- w_end)*(t/maxgen)*(t/maxgen);
//        w = w_start - (w_start-w_end)*(2*t/maxgen-(t/maxgen)*(t/maxgen));
//        w = w_end*(pow((w_start/w_end),(1/(1+10*t/maxgen))));

    //  找到粒子群最优解
        for (int i = 0; i < S; i++) {
            if (flist[i] < flist[bestN]) {
                bestN = i;
            }
        }
    // 记录迭代中找到的最优解
        if (flist[bestN] < minf) {
            pp = t;
            minf = flist[bestN];
            for (int i = 0; i < d; i++) {
                minx[i] = x[bestN][i];
            }
            for (int i = 0; i < 7; i++) {
                minTime[i] = minMiddleTime[bestN][i];
            }
        }
        if (minf < 0.378) {
            break;
        }
        cout << flist[bestN] << ' ' << t << endl;
        double r1 = (double)rand()/RAND_MAX; //0到1之间的随机数
        double r2 = (double)rand()/RAND_MAX;
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < d; j++) {
                v[i][j] = w*v[i][j] + c1*r1*(M[i][j]-x[i][j]) + c2*r2*(minx[j]-x[i][j]);    // 速度迭代方程
                // 限制速度边界值
                if (v[i][j] > vmax) {
                    v[i][j] = vmax;
                }
                if (v[i][j] < -vmax) {
                    v[i][j] = -vmax;
                }
                x[i][j] = x[i][j] + v[i][j];     // 位置迭代方程
                if (x[i][j] < 0) {
                    x[i][j] = 0;
                }
                if (x[i][j] > 165) {
                    x[i][j] = 165;
                }
            }
            double variance = f(i);
            flist[i] = variance;
            // 更新每个粒子的历史最优解
            if (flist[i] < bestf[i]) {
                bestf[i] = flist[i];
            }
            for (int j = 0; j < 7; j++) {
                minMiddleTime[i][j] = timePerDay[j];
            }
        }
    }
    for (int i = 0; i < S; i++) {
        if (flist[i] < flist[bestN]) {
            bestN = i;
        }
    }

    if (flist[bestN] < minf) {
        minf = flist[bestN];
        for (int i = 0; i < d; i++) {
            minx[i] = x[bestN][i];
        }
    }

    // 输出最优解
    cout << "generation: " << pp << endl;
    cout << "min(f): " << setprecision(8) << minf << endl;
    cout << "x(i): ";
    for (int i = 0; i < d; i++) {
        cout << minx[i] << ' ';
    }
    cout << endl;
    cout << "per day: ";
    for (int i = 0; i < 7; i++) {
        cout << minTime[i] << ' ';
    }
}

int main() {
    srand((unsigned)time(NULL));
    input();
    initialize();
    PSOfunc();
    return 0;
}
