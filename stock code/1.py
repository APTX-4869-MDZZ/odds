import xlwings as xw
wb = xw.Book('1.xlsx')
sht = wb.sheets['Sheet1']
ARange = sht.range("A2").expand("down")
BRange = sht.range("B2").expand("down")
DRange = sht.range("D2").expand("down")
FRange = sht.range("F2").expand("down")
GRange = sht.range("G2").expand("down")
codelist = [A.value for A in ARange]
name = [B.value for B in BRange]
direction = [ 1 if D.value=="卖出" else -1 for D in DRange]

num = [int(F.value) for F in FRange]
price = [float(G.value) for G in GRange]
allCode = list()
for i in range(len(codelist)):
    allCode.append({
        'code': codelist[i],
        'name': name[i],
        'direction': direction[i],
        'num': num[i],
        'price': price[i]
    })

allCode = sorted(allCode, key=lambda x: x['code'])

result = 0
i = 0
result_list = list()
while i < len(allCode)-1:
    while i < len(allCode)-1 and allCode[i]['code'] != allCode[i+1]['code']:
        i = i + 1
    if i < len(allCode)-1:
        numi = allCode[i]['num'] if allCode[i]['num'] < allCode[i+1]['num'] else allCode[i+1]['num']
        profit = (allCode[i]['price']*allCode[i]['direction'] + allCode[i+1]['price']*allCode[i+1]['direction'])*numi
        if allCode[i]['direction'] == -1:
            profit = profit - 0.00025*allCode[i]['price']*allCode[i]['num']
        else:
            profit = profit - 0.00125*allCode[i]['price']*allCode[i]['num']
        if allCode[i+1]['direction'] == -1:
            profit = profit - 0.00025*allCode[i+1]['price']*allCode[i+1]['num']
        else:
            profit = profit - 0.00125*allCode[i+1]['price']*allCode[i+1]['num']
        result = result + profit
        result_list.append({
            'code': allCode[i]['code'],
            'name': allCode[i]['name'],
            'profit': profit
        })
        i = i + 2
result_list = sorted(result_list, key=lambda x:-x['profit'])
print(result)

sht2 = wb.sheets['Sheet2']
sht2.range('A1:C1').value = ['合约代码', '合约名称', '盈利']
for i in range(len(result_list)):
    sht2.range('A{}'.format(i+2)).api.WrapText = True
    sht2.range('A{}:C{}'.format(i+2, i+2)).value = [result_list[i]['code'], result_list[i]['name'], result_list[i]['profit']]
sht2.range('C{}'.format(len(result_list)+2)).value = result
wb.save('1.xlsx')
wb.close()