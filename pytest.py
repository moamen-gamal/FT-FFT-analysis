import ctypes 
import numpy as np
import time
from numpy.ctypeslib import ndpointer
library =ctypes.CDLL('./outputFile.so')
library.connect()
a = np.array([1,2,3,4,5,6,7,8,9,10])
ft = library.fourir
ft.restype=None
time1=time.time()
ft(ctypes.c_void_p(a.ctypes.data))
time2=time.time()-time1
print(time2)