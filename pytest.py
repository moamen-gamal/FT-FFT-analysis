import ctypes 
from ctypes import c_void_p, c_double, c_int, cdll
from numpy.ctypeslib import ndpointer
import numpy as np
from numpy import random
import time
library =ctypes.CDLL('./outputFile.so')
a = np.array([1,2,3,4,5,6,7,8])
fou= library.fourir
fou.restype = None
arr_sizes =np.array([2**0])
for i in range(1,15):
    arr_sizes=np.append(arr_sizes,2**i)
fourir_slow_time =np.array(0)
fft_time =np.array(0)
for i in range(0,16):
    a=random.randint(5, size=(arr_sizes[i]))
    time1 =time.time()
    size =arr_sizes[i]
    fou(c_void_p(a.ctypes.data),ctypes.c_int(size))
    time2=time.time()
    time3 = tim2 - time1
    fourir_slow_time=np.append(fourir_slow_time,time3)
print(fourir_slow_time)
