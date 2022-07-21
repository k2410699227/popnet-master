import os
import re

import matplotlib.pyplot as plt

round = 30


def drawcompare(_rate, _delay1, _delay2, _figname):
   plt.plot(_rate, _delay1, label='XY_8x8', color='blue', linewidth=1.0)
   plt.plot(_rate, _delay2, label='XYZ_4x4x4', color='red', linewidth=1.0)
   #plt.axis([0, 2.1, 30, 45])
   plt.xticks(fontsize=12, fontstyle='italic', weight='normal')
   plt.yticks(fontsize=12, fontstyle='italic', weight='normal')
   plt.ylabel('Average delay(ms)', fontsize=14, weight='heavy', fontstyle='italic')
   plt.xlabel('Injection rate (packet/cycle)', fontsize=14, weight='heavy', fontstyle='italic')
   plt.title('Average delay - Injection rate',
          fontdict={'style': 'normal', 'size': 20, 'weight': 'heavy'})
   plt.legend(loc='lower right')
   plt.savefig(_figname)


rates = []
delays = []
losses = []

print("XY Routing Algorithm:")
for i in range(1, round + 1):
    packets = i * 2000

    os.system('python bench_2d.py ' + str(packets) + ' 8')  # 利用编写的的脚本生成指定数目的trace文件

    res = os.popen(
        './popnet -A 8 -c 2 -V 4 -B 12 -O 12 -F 4 -L 1000 -T 20000 -r 1 -I ./mybench_2D/bench -R 0 ')  # 运行popnet
    mess = res.readlines()
    finished = eval(re.findall(r"\d+\.?\d*", mess[-8])[0])  # 从popnet打印的信息中获取完成数据包的量
    loss = (packets - finished) / packets  # 计算丢包率
    # rate = eval(re.findall(r"\d+\.?\d*", mess[-8])[0])
    rate = packets / 20000  # 注入率
    delay = eval(re.findall(r"\d+\.?\d*", mess[-7])[0])  # 从popnet打印的信息中获取平均延迟
    # print(mess[-8],rate,'\n',mess[-7] ,delay)
    print('Round {:<3}'.format(i), 'Total Packets:{:<8}'.format(packets),
          'Finished Packet:{:<8}'.format(finished),
          'Injection Rate：{:<10}'.format(rate),
          'Average Delay:{:<8}'.format(delay), 'Packet Loss: {:<8.2%}'.format(loss))
    rates.append(rate)
    delays.append(delay)
    losses.append(loss * 100)

print(rates, '\n' + str(delays), '\n' + str(losses))


rates_z = []
delays_z = []
losses_z = []

print("XYZ Routing Algorithm:")
for i in range(1, round + 1):
    packets = i * 2000

    os.system('python bench_3d.py ' + str(packets) + ' 4')  # 利用编写的的脚本生成指定数目的trace文件

    res = os.popen(
        './popnet -A 4 -c 3 -V 4 -B 12 -O 12 -F 4 -L 1000 -T 20000 -r 1 -I ./mybench_3D/bench -R 4 ')  # 运行popnet
    mess = res.readlines()
    finished = eval(re.findall(r"\d+\.?\d*", mess[-8])[0])  # 从popnet打印的信息中获取完成数据包的量
    loss = (packets - finished) / packets  # 计算丢包率
    # rate = eval(re.findall(r"\d+\.?\d*", mess[-8])[0])
    rate = packets / 20000  # 注入率
    delay = eval(re.findall(r"\d+\.?\d*", mess[-7])[0])  # 从popnet打印的信息中获取平均延迟
    # print(mess[-8],rate,'\n',mess[-7] ,delay)
    print('Round {:<3}'.format(i), 'Total Packets:{:<8}'.format(packets),
          'Finished Packet:{:<8}'.format(finished),
          'Injection Rate：{:<10}'.format(rate),
          'Average Delay:{:<8}'.format(delay), 'Packet Loss: {:<8.2%}'.format(loss))
    rates_z.append(rate)
    delays_z.append(delay)
    losses_z.append(loss * 100)

print(rates_z, '\n' + str(delays_z), '\n' + str(losses_z))
drawcompare(rates,delays,delays_z,"exp4.png")
