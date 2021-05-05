#define _USE_MATH_DEFINES
#include<iostream>
#include<array>
#include<complex.h>
#include<cmath>
using namespace std;

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

extern "C"
{
    void connect();
    void fourir( double* input_data,int size);
    void fft( int* x, complex<double>* X, unsigned int N);
    void fft_process( int* x,complex<double>* X, unsigned int N, unsigned int s);
}
void connect()
{
    printf("connect\n");
}

void fourir(double* input_data,int size)
{
    if (input_data[0]==1)
        cout<<"right"<<endl;
    const int s=size;
    double real[s];
    double imag[s];
    for (int k = 0; k < 10; k++)
    {
        double re= 0;
        double im = 0;
        for (int n = 0; n < 10; n++)
        {
            double t = double(n) / 10;
            double W = 2 * M_PI * k;
            re += input_data[n] * cos(W * t);
            im += -input_data[n] * sin(W * t);
            //cout << endl << re << "    " << im << endl;
            
        }
        cout << endl << re << "    " << im << "   " <<k<<endl;
        real[k] = re;
        imag[k] = im/10;
    }
    
}
void fft( int* x, complex<double>* X, unsigned int N)
{
    fft_process( x, X, N, 1);
}
void fft_process( int* x,complex<double>* X, unsigned int N, unsigned int s) {
    unsigned int k;
    complex<double> t;
    complex<double> J(0, 1);
    if (N == 1) {
        X[0] = x[0];
        return;
    }

    fft_process(x, X, N / 2, 2 * s);
    fft_process(x + s, X + N / 2, N / 2, 2 * s);

    for (k = 0; k < N / 2; k++) {
        t = X[k];
        X[k] = t + exp(-2 * M_PI  *J* k / N) * X[k + N / 2];
        X[k + N / 2] = t - exp(-2 * M_PI * J * k / N) * X[k + N / 2];
    }
}