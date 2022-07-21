import matplotlib.pyplot as plt



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


rate = [0,0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0] 


delay = [0,30.8035, 31.1046, 31.3871, 31.3754, 31.5446, 31.6981, 32.0281, 32.1695, 32.3982, 32.487, 32.5218, 32.7038, 32.9855, 33.1569, 33.2566, 33.5843, 33.7659, 34.0733, 34.4165, 34.5427, 34.8735, 35.1301, 35.4601, 35.8428, 36.0988, 36.6041, 36.8943, 37.2558, 37.9335, 38.1527] 


delay_z = [0,23.2067, 23.3249, 23.5452, 23.4525, 23.5441, 23.9762, 23.9286, 24.0565, 24.0965, 24.2825, 24.2457, 24.4431, 24.5967, 24.7245, 24.8171, 24.8951, 24.9233, 25.0049, 25.2065, 25.2749, 25.3635, 25.6042, 25.6593, 25.7773, 25.8013, 25.9641, 26.0874, 26.1607, 26.3835, 26.5054] 

drawcompare(rate, delay, delay_z, "exp4_0.png")