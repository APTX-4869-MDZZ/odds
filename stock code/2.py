import threading
import xlwings as xw
import sys
import datetime

x = 99999999
filename = '2.xlsx'

def timer_func():
    global timer
    print('.', end="")
    sys.stdout.flush()
    timer = threading.Timer(1, timer_func)
    timer.start()

def sumItem(tempItem, amount):
    sumProfit = 0
    profitList = list()
    days = 0
    for key in tempItem.keys():
        if key != 'code' and key != 'name':
            if tempItem[key] > 0:
                days = days + 1
            profitList.append(tempItem[key])
    sumProfit = sum(profitList)
    profitListLen = len(profitList)
    avg = sumProfit / profitListLen
    variant = sum([(profit-avg)*(profit-avg) for profit in profitList])/profitListLen
    win = days / profitListLen
    return sumProfit, variant, win, amount/profitListLen

def getPosition(numPosition):
    numPosition = numPosition - 1
    position = ''
    if numPosition>25:
        positionX = int(numPosition / 26)
        positionY = numPosition % 26
        position = '{}{}'.format(chr(positionX+65), chr(positionY+65))
    else:
        position = chr(numPosition+65)
    return position

print('reading...', end="")
sys.stdout.flush()
timer_func()

wb = xw.Book(filename)
sht = wb.sheets['Sheet1']
LRange = sht.range("L2").expand("down")
MRange = sht.range("M2").expand("down")
NRange = sht.range("N2").expand("down")
RRange = sht.range("R2").expand("down")
SRange = sht.range("S2").expand("down")
VRange = sht.range("V2").expand("down")
codelist = [L.value for L in LRange]
name = [M.value for M in MRange]
direction = [ 1 if R.value=="卖出" else -1 for R in RRange]
dateList = [N.value for N in NRange]
dateSet = set(dateList)
dates = [datetime.datetime.strptime(date,'%Y-%m-%d') for date in dateSet]
dates.sort()
dates = [date.strftime('%Y-%m-%d') for date in dates]

num = [int(S.value) for S in SRange]
price = [float(V.value) for V in VRange]

print(' ')
print('sorting...', end='')
sys.stdout.flush()

final_result = list()
allCode = list()
for i in range(len(codelist)):
    allCode.append({
        'code': codelist[i],
        'name': name[i],
        'direction': direction[i],
        'num': num[i],
        'price': price[i],
        'date': dateList[i]
    })
allCode = sorted(allCode, key=lambda x: (x['code'], x['date']))

print(' ')
print('calculating...', end='')
sys.stdout.flush()

i = 0
result_list = list()
addItem = dict()
amount = 0
while i < len(allCode)-1:
    j = i
    sell = 0
    sellCount = 0
    buy = 0
    buyCount = 0
    profit = 0
    while j < len(allCode) and allCode[j]['code'] == allCode[i]['code'] and allCode[j]['date'] == allCode[i]['date']:
        if allCode[j]['direction'] == -1:
            buy = buy + allCode[j]['num']
            buyCount = buyCount + allCode[j]['num']*allCode[j]['price']
        else:
            sell = sell + allCode[j]['num']
            sellCount = sellCount + allCode[j]['num']*allCode[j]['price']
        j = j + 1
    if abs(sell - buy) > x:
        profit = sellCount - buyCount
        profit = profit - sellCount * 0.00125 - buyCount * 0.00025
    else:
        if sell != 0 and buy != 0:
            avgSell = sellCount / sell
            avgBuy = buyCount / buy
            if sell < buy:
                numCount = sell
            else:
                numCount = buy
            profit = avgSell * numCount - avgBuy * numCount
            profit = profit - avgSell * numCount * 0.00125 - avgBuy * numCount * 0.00025
            amount = amount + profit/(avgSell * numCount + avgBuy * numCount)*2

    addItem['code'] = allCode[i]['code']
    addItem['name'] = allCode[i]['name']
    addItem[allCode[i]['date']] = profit     
    if j > len(allCode)-1 or allCode[j-1]['code'] != allCode[j]['code']:
        addItem['profit'], addItem['variance'], addItem['win-ratio'], addItem['profit-ratio'] = sumItem(addItem, amount)
        amount = 0
        result_list.append(addItem)
        addItem = dict()
    i = j
# result_list = sorted(result_list, key=lambda x:-x['profit'])
print(' ')
print('writing...', end='')

sht2 = wb.sheets['Sheet2']
headers = ['证券代码', '证券名称']
headers.extend(list(dates))
headers.append('绝对收益')
headers.append('收益率百分比')
headers.append('方差')
headers.append('胜率')

sht2.range('A1:{}1'.format(getPosition(6+len(dates)))).value = headers
for i in range(len(result_list)):
    sht2.range('A{}:B{}'.format(i+2, i+2)).value = [result_list[i]['code'], result_list[i]['name']]
    dayPosition = 3
    for date in dates:
        sht2.range('{}{}'.format(getPosition(dayPosition), i+2)).value = result_list[i].get(date, '')
        dayPosition = dayPosition + 1
    sht2.range('{}{}:{}{}'.format(getPosition(dayPosition), i+2, getPosition(6+len(dates)), i+2)).value = [result_list[i]['profit'], result_list[i]['profit-ratio'], result_list[i]['variance'], result_list[i]['win-ratio']]
wb.save(filename)
wb.close()
timer.cancel()