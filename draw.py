import os
import re
from scipy.interpolate import make_interp_spline
import matplotlib.pyplot as plt



def drawcompare(_rate, _delay1, _delay2, _figname):
   plt.plot(_rate, _delay1, label='XY', color='blue', linewidth=1.0)
   plt.plot(_rate, _delay2, label='Adaptive', color='red', linewidth=1.0)
   plt.axis([0, 2.1, 30, 40])
   plt.xticks(fontsize=12, fontstyle='italic', weight='normal')
   plt.yticks(fontsize=12, fontstyle='italic', weight='normal')
   plt.ylabel('Average delay(ms)', fontsize=14, weight='heavy', fontstyle='italic')
   plt.xlabel('Injection rate (packet/cycle)', fontsize=14, weight='heavy', fontstyle='italic')
   plt.title('Average delay - Injection rate',
          fontdict={'style': 'normal', 'size': 20, 'weight': 'heavy'})
   plt.legend(loc='upper left')
   plt.savefig(_figname)

rate  =[0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45, 1.5, 1.55, 1.6, 1.65, 1.7, 1.75, 1.8, 1.85, 1.9, 1.95, 2.0] 

delay = [0, 34.1742, 34.5001, 34.2663, 34.8625, 34.5984, 34.982, 35.1542, 35.0552, 35.2364, 35.4279, 35.2436, 35.6527, 35.5087, 35.9683, 35.9058, 35.9246, 36.1047, 36.2402, 36.4501, 36.5886, 36.707, 36.8263, 37.1341, 37.1425, 37.4247, 37.3934, 37.5402, 37.7231, 38.0361, 38.0666, 38.2934, 38.4889, 38.5956, 39.0759, 39.2529, 39.2905, 39.5565, 39.9757, 40.0177, 40.2954] 

delay_a = [0, 34.1391, 34.4411, 34.1326, 34.7749, 34.5058, 34.8453, 35.0263, 34.9189, 35.152, 35.27, 35.135, 35.5613, 35.3741, 35.8456, 35.8309, 35.9018, 36.0646, 36.2658, 36.4589, 36.622, 36.742, 36.9534, 37.2313, 37.3858, 37.7155, 37.6048, 37.8561, 37.9958, 38.2863, 38.5076, 38.7407, 39.0241, 39.2801, 39.7387, 40.0565, 40.1786, 40.4242, 40.9385, 41.0969, 41.4783] 

drawcompare(rate, delay, delay_a, 'exp3.png')
