import ctypes 
from ctypes import c_void_p, c_double, c_int, cdll
from numpy.ctypeslib import ndpointer
from ctypes import *
import numpy as np
from numpy import random
import time
import matplotlib.pyplot as plt

library =ctypes.CDLL('./outputFile.so')
fourir= library.fourir
fft=library.fft
fft.restype=None
fourir.restype = None
fourir.argtypes= [ndpointer(ctypes.c_int32),c_int32]
fft.argtypes= [ndpointer(ctypes.c_int32),c_int32]


arr_sizes =np.array([2**0],dtype=c_int32)
for i in range(1,16):
    arr_sizes=np.append(arr_sizes,2**i)

fourir_slow_time =np.array(0)
fft_time =np.array(0)


for i in range(0,15):
    a=np.random.randint(0,10, size=(arr_sizes[i]),dtype=c_int32)
    size =arr_sizes[i]

    time1 =time.time()
    fourir(a,size)
    time2=time.time()
    time3 = (time2 - time1)
    fourir_slow_time=np.append(fourir_slow_time,time3)
    
    time11 =time.time()
    fft(a,size)
    time22 =time.time()
    time33=time22-time11
    fft_time=np.append(fft_time,time33)

#print(fft_time)
#print(fourir_slow_time)
plt.plot(arr_sizes, fourir_slow_time)
#plt.show()
plt.plot(arr_sizes, fft_time)
plt.show()