#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include<array>
using namespace std;
template<size_t T>

void fourir(array<double, T> input_data, array<double, T>& real, array<double, T>& imag)
{
    int size = input_data.size();
    
    for (int k = 0; k < size; k++)
    {
        double re= 0;
        double im = 0;
        for (int n = 0; n < size; n++)
        {
            double t = double(n) / size;
            double W = 2 * M_PI * k;
            re += input_data[n] * cos(-W * t);
            im += input_data[n] * sin(-W * t);
            //cout << endl << re << "    " << im << endl;
            
        }
        real[k] = re;
        imag[k] = im;
        cout << endl << real[k] << "    " << imag[k] << "   " <<k<<endl;
        
    }
    
    return;
}

void fft(int* x, double* X_real, double* X_imag, unsigned int N, unsigned int s) {
    unsigned int k;
    double t_real;
    double t_imag;
   
    // At the lowest level pass through (delta T=0 means no phase).
    if (N == 1) {
        X_real[0] = x[0];
        X_imag[0] = x[0];
        return;
    }

    // Cooley-Tukey: recursively split in two, then combine beneath.
    fft(x, X_real, X_imag, N / 2, 2 * s);
    fft(x + s, X_real + N / 2, X_imag + N / 2, N / 2, 2 * s);

    for (k = 0; k < N / 2; k++) {
        t_real = X_real[k];
        t_imag = X_imag[k];
        X_real[k] = t_real + cos(-2 * M_PI * k / N) * X_real[k + N / 2];
        X_imag[k] = t_imag + sin(-2 * M_PI * k / N) * X_imag[k + N / 2];
        X_real[k + N / 2] = t_real - cos(-2 * M_PI * k / N) * X_real[k + N / 2];
        X_imag[k + N / 2] = t_imag - sin(-2 * M_PI * k / N) * X_imag[k + N / 2];

    }

}

void reverseBits(int* n)
{
    int size = sizeof(n) / sizeof(n[0]);
    size = 8;
    int bit_number = 3;
    int temp = 0;
    for (int i = 0; i < size; i++)
    {
        int x = i;
         x= (x<< bit_number) | i;
         cout << endl <<i << "    "  << x << endl;
    }
}

int main() {
    array<double, 8> input = {1,2,3,4,5,6,7,8};
    array<double, 8> real;
    array<double, 8> imag;
    /*for (int i = 0; i < 100; i++)
    {

        int j = (float(rand() % 4))/2;
        input[i] = j; //I believe this should be array[j]=i

    }*/
    fourir<8>(input,real,imag);
    
    int in[8] = { 1,2,3,4,5,6,7,8 };
    double re[8];
    reverseBits(in);
    double im[8];
    fft(in, re, im,8,1 );
    cout << endl << re[5] << "    " << im[5] << "   " << endl;
    reverseBits(in);
    return 0;
}