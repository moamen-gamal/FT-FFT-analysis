#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include<array>
#include<complex.h>
#include<ccomplex>
#include<cmath>
#define I _Complex_I // can be used to redefine I
using namespace std;

// Trick to allow type promotion below
template <typename T>
struct identity_t { typedef T type; };

/// Make working with std::complex<> nubmers suck less... allow promotion.
#define COMPLEX_OPS(OP)                                                 \
  template <typename _Tp>                                               \
  std::complex<_Tp>                                                     \
  operator OP(std::complex<_Tp> lhs, const typename identity_t<_Tp>::type & rhs) \
  {                                                                     \
    return lhs OP rhs;                                                  \
  }                                                                     \
  template <typename _Tp>                                               \
  std::complex<_Tp>                                                     \
  operator OP(const typename identity_t<_Tp>::type & lhs, const std::complex<_Tp> & rhs) \
  {                                                                     \
    return lhs OP rhs;                                                  \
  }
COMPLEX_OPS(+)
COMPLEX_OPS(-)
COMPLEX_OPS(*)
COMPLEX_OPS(/ )
#undef COMPLEX_OPS

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
double t_real;
double t_imag;

void fft(int* x, double* X_real, double* X_imag, unsigned int N, unsigned int s) {
    unsigned int k;
   
    // At the lowest level pass through (delta T=0 means no phase).
    if (N == 1) {
        X_real[0] = x[0];
      //  cout << endl << X_real[0] << "    " << X_imag[0]  << endl;
        return;
    }

    // Cooley-Tukey: recursively split in two, then combine beneath.
    fft(x, X_real, X_imag, N / 2, 2 * s);
    fft(x + s, X_real + N / 2, X_imag + N / 2, N / 2, 2 * s);

    for (k = 0; k < N / 2; k++) {
        t_real = X_real[k];
        t_imag = X_imag[k];
        X_real[k] = t_real + cos(-2 * M_PI * k / N) * X_real[k + N/2];
        X_imag[k] = t_imag + sin(-2 * M_PI * k / N) * X_imag[k + N/2];
        X_real[k + N / 2] = t_real + cos(-2 * M_PI * k / N) * X_real[k + N / 2];
        X_imag[k + N / 2] = t_imag + sin(-2 * M_PI * k / N) * X_imag[k + N / 2];
      //  cout << endl << X_real[k] << "    " << X_imag[k] << "   " << k << endl;
      //  cout << endl << X_real[k + N / 2] << "    " << X_imag[k + N / 2] << "   " << k << endl;
    }

}
void fft_process(int* x,complex<double>* X, unsigned int N, unsigned int s) {
    unsigned int k;
    complex<double> t;
    complex<double> J(0, 1);
    // At the lowest level pass through (delta T=0 means no phase).
    if (N == 1) {
        X[0] = x[0];
        return;
    }

    // Cooley-Tukey: recursively split in two, then combine beneath.
    fft_process(x, X, N / 2, 2 * s);
    fft_process(x + s, X + N / 2, N / 2, 2 * s);

    for (k = 0; k < N / 2; k++) {
        t = X[k];
        X[k] = t + exp(-2 * M_PI  *J* k / N) * X[k + N / 2];
        X[k + N / 2] = t - exp(-2 * M_PI * J * k / N) * X[k + N / 2];
    }
}
void fft(int* x, complex<double>* X, unsigned int N)
{
    fft_process( x, X, N, 1);
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
    complex<double>i(1, 1);
    complex<double>i2(2, 2);
    int in[8] = { 1,2,3,4,5,6,7,8 };
    complex<double> out[8];
    fft(in, out, 8);
    cout << out[0] << endl << out[3]<<endl;
    return 0;
}