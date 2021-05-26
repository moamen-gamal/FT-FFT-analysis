import ctypes
from numpy.ctypeslib import ndpointer
from ctypes import *
import numpy as np
import time
import matplotlib.pyplot as plt


library =ctypes.CDLL('./bin/fourir.so')
fourir= library.fourir
fft=library.fft
fft.restype=None
fourir.restype = None
fourir.argtypes= [ndpointer(ctypes.c_int32),ndpointer(ctypes.c_double),ndpointer(ctypes.c_double),c_int32]
fft.argtypes= [ndpointer(ctypes.c_int32),ndpointer(ctypes.c_double),ndpointer(ctypes.c_double),c_int32]


arr_sizes =np.array([2**0],dtype=c_int32)
for i in range(1,12):
    arr_sizes=np.append(arr_sizes,2**i)

fourir_slow_time =np.array(0)
fft_time =np.array(0)


for i in range(0,11):
   a=np.random.randint(0,10, size=(arr_sizes[i]),dtype=c_int32)
   size =arr_sizes[i]

   out_real =np.zeros(size,dtype=c_double)
   out_im =np.zeros(size,dtype=c_double)
   time1 =time.time()
   fourir(a,out_real,out_im,size)
   time2=time.time()
   time3 = (time2 - time1)
   fourir_slow_time=np.append(fourir_slow_time,time3)
    
   
   outfft_real =np.zeros(size,dtype=c_double)
   outfft_im =np.zeros(size,dtype=c_double)
   time11 =time.time()
   fft(a,outfft_real,outfft_im,size)
   time22 =time.time()
   time33=time22-time11
   fft_time=np.append(fft_time,time33)


plt.plot(arr_sizes, fourir_slow_time)
plt.plot(arr_sizes, fft_time)
plt.show()

a=np.random.randint(0,10, size=(2**5),dtype=c_int32)
a =np.array([1,2,3,4,5,6,7,8],dtype=c_int32)
out_real =np.zeros(2**5,dtype=c_double)
out_im =np.zeros(2**5,dtype=c_double)
fourir(a,out_real,out_im,2**5)

outfft_real =np.zeros(2**5,dtype=c_double)
outfft_im =np.zeros(2**5,dtype=c_double)
fft(a,outfft_real,outfft_im,2**5)

plt.plot(out_real,out_im)
plt.plot(outfft_real,outfft_im)
plt.show()