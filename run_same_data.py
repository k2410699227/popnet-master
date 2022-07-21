import os
import re

import matplotlib.pyplot as plt

round = 80

def drawcompare(_rate, _delay1, _delay2, _figname):
   plt.plot(_rate, _delay1, label='XY', color='blue', linewidth=1.0)
   plt.plot(_rate, _delay2, label='Adaptive', color='red', linewidth=1.0)
   plt.axis([0, 2.1, 30, 45])
   plt.xticks(fontsize=12, fontstyle='italic', weight='normal')
   plt.yticks(fontsize=12, fontstyle='italic', weight='normal')
   plt.ylabel('Average delay(ms)', fontsize=14, weight='heavy', fontstyle='italic')
   plt.xlabel('Injection rate (packet/cycle)', fontsize=14, weight='heavy', fontstyle='italic')
   plt.title('Average delay - Injection rate',
          fontdict={'style': 'normal', 'size': 20, 'weight': 'heavy'})
   plt.legend(loc='upper left')
   plt.savefig(_figname)
   

def drawfig(_rate, _delay, _loss, fname):
    plt.plot(_rate, _delay, linewidth=2.0)
    plt.xticks(fontsize=12, fontstyle='italic', weight='normal')
    plt.yticks(fontsize=12, fontstyle='italic', weight='normal')
    plt.ylabel('Average delay(ms)', fontsize=14, weight='heavy', fontstyle='italic')
    plt.xlabel('Injection rate (packet/cycle)', fontsize=14, weight='heavy', fontstyle='italic')
    plt.title('Average delay - Injection rate',
              fontdict={'style': 'normal', 'size': 20, 'weight': 'heavy'})
    plt.savefig(fname + 'delay.png')

    plt.clf()

    plt.plot(_rate, _loss, linewidth=2.0, color='red')
    plt.xticks(fontsize=12, fontstyle='italic', weight='normal')
    plt.yticks(fontsize=12, fontstyle='italic', weight='normal')
    plt.ylabel('Packet loss(%)', fontsize=14, weight='heavy', fontstyle='italic')
    plt.xlabel('Injection rate (packet/cycle)', fontsize=14, weight='heavy', fontstyle='italic')
    plt.title('Packet loss - Injection rate',
              fontdict={'style': 'normal', 'size': 20, 'weight': 'heavy'})
    plt.savefig(fname + 'loss.png')
    plt.clf()


rates = [0]
delays = [0]
losses = [0]
rates_a = [0]
delays_a = [0]
losses_a = [0]


for i in range(1, round + 1):
    packets = i * 500

    os.system('python bench.py ' + str(packets))  # 利用编写的的脚本生成指定数目的trace文件

    res = os.popen(
        './popnet -A 9 -c 2 -V 1 -B 12 -O 12 -F 4 -L 1000 -T 20000 -r 1 -I ./mybench/bench -R 0 ')  # 用XY路由算法运行popnet
    mess = res.readlines()
    finished = eval(re.findall(r"\d+\.?\d*", mess[-8])[0])  # 从popnet打印的信息中获取完成数据包的量
    loss = (packets - finished) / packets  # 计算丢包率
    # rate = eval(re.findall(r"\d+\.?\d*", mess[-8])[0])
    rate = packets / 20000  # 注入率
    delay = eval(re.findall(r"\d+\.?\d*", mess[-7])[0])  # 从popnet打印的信息中获取平均延迟

    rates.append(rate)
    delays.append(delay)
    losses.append(loss * 100)

    res = os.popen(
        './popnet -A 9 -c 2 -V 1 -B 12 -O 12 -F 4 -L 1000 -T 20000 -r 1 -I ./mybench/bench -R 3 ')  # 用TXY路由算法运行popnet
    mess = res.readlines()
    finished = eval(re.findall(r"\d+\.?\d*", mess[-8])[0])  # 从popnet打印的信息中获取完成数据包的量
    loss = (packets - finished) / packets  # 计算丢包率
    # rate = eval(re.findall(r"\d+\.?\d*", mess[-8])[0])
    rate = packets / 20000  # 注入率
    delay = eval(re.findall(r"\d+\.?\d*", mess[-7])[0])  # 从popnet打印的信息中获取平均延迟

    rates_a.append(rate)
    delays_a.append(delay)
    losses_a.append(loss * 100)

print("XY Routing Algorithm:")
for i in range(0, round+1):
    print('Round {:<3}'.format(i),
          'Injection Rate：{:<10}'.format(rates[i]),
          'Average Delay:{:<8}'.format(delays[i]), 'Packet Loss: {:<8.2%}'.format(losses[i]/100))

print(rates, '\n' + str(delays), '\n' + str(losses))

print("Adaptive Routing Algorithm:")
for i in range(0, round+1):
    print('Round {:<3}'.format(i),
          'Injection Rate：{:<10}'.format(rates_a[i]),
          'Average Delay:{:<8}'.format(delays_a[i]), 'Packet Loss: {:<8.2%}'.format(losses_a[i]/100))

print(rates, '\n' + str(delays_a), '\n' + str(losses_a))

drawcompare(rates, delays, delays_a, 'exp3-500_TM.png')

#drawfig(rates, delays, losses, 'XY3_')
#drawfig(rates_t, delays_t, losses_t, 'Adaptive3_')


