import ctypes
from numpy.ctypeslib import ndpointer
from ctypes import *
import numpy as np
import time
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error

class fourir:

    def __init__(self):
        self.library =ctypes.CDLL('./bin/fourir.so')
        self.fourir_transform= self.library.fourir
        self.fft=self.library.fft
        self.fft.restype=None
        self.fourir_transform.restype = None
        self.fourir_transform.argtypes= [ndpointer(ctypes.c_int32),ndpointer(ctypes.c_double),ndpointer(ctypes.c_double),c_int32]
        self.fft.argtypes= [ndpointer(ctypes.c_int32),ndpointer(ctypes.c_double),ndpointer(ctypes.c_double),c_int32]

    def ft_fft_time_comparison(self):
        self.arr_sizes =np.array([2**0],dtype=c_int32)
        for i in range(1,15):
            self.arr_sizes=np.append(self.arr_sizes,2**i)

        self.fourir_slow_time =np.array(0)
        self.fft_time =np.array(0)

        for i in range(0,14):
            self.a=np.random.randint(0,10, size=(self.arr_sizes[i]),dtype=c_int32)
            self.size =self.arr_sizes[i]

            self.out_real =np.zeros(self.size,dtype=c_double)
            self.out_im =np.zeros(self.size,dtype=c_double)
            self.time_start =time.time()
            self.fourir_transform(self.a,self.out_real,self.out_im,self.size)
            self.time_end=time.time()
            self.time_excution = (self.time_end - self.time_start)
            self.fourir_slow_time=np.append(self.fourir_slow_time,self.time_excution)
                
            
            self.outfft_real =np.zeros(self.size,dtype=c_double)
            self.outfft_im =np.zeros(self.size,dtype=c_double)
            self.time_start =time.time()
            self.fft(self.a,self.outfft_real,self.outfft_im,self.size)
            self.time_end =time.time()
            self.time_excution=self.time_end-self.time_start
            self.fft_time=np.append(self.fft_time,self.time_excution)


        plt.plot(self.arr_sizes, self.fourir_slow_time)
        plt.plot(self.arr_sizes, self.fft_time)
        plt.show()
    
    def fourir_transformation(self,input_data):
        self.out_real =np.zeros(len(input_data),dtype=c_double)
        self.out_im =np.zeros(len(input_data),dtype=c_double)
        self.out_complex =np.zeros(len(input_data),dtype=complex)
        self.fourir_transform(np.array(input_data),self.out_real,self.out_im,len(input_data))
        for i in range(len(input)):
            self.out_complex[i]=self.out_real[i] + 1*complex(0,1) *self.out_im[i]
        return self.out_complex,self.out_real,self.out_im

    def fft_transformation(self,input_data):
        self.outfft_real =np.zeros(len(input_data),dtype=c_double)
        self.outfft_im =np.zeros(len(input_data),dtype=c_double)
        self.outfft_complex =np.zeros(len(input_data),dtype=complex)
        self.fft(np.array(input_data),self.outfft_real,self.outfft_im,len(input_data))
        for i in range(0,len(input)):
             self.outfft_complex[i]=self.outfft_real[i] + 1*complex(0,1) *self.outfft_im[i]

        return self.outfft_complex,self.outfft_real,self.outfft_im

def mean_square_error(input1,input2)->float:
        MSE = np.square(np.subtract(input1,input2)).mean()
        #to graphically show the diffrence
        #plt.plot(input1)
        #plt.plot(input2)
        #plt.show()
        return abs(MSE)
        

if (__name__ =="__main__") :
    fou=fourir()
    #fou.ft_fft_time_comparison()
    input=[1,2,3,4,5,6,7,8]
    fourir_out,_,_=fou.fourir_transformation(input)
    fft_out,_,_= fou.fft_transformation(input)
    error= mean_square_error(fourir_out,fft_out)
    print (error)

    