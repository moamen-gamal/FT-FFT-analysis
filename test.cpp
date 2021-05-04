#define _USE_MATH_DEFINES
#include <cmath>
#include<iostream>
#include<array>
using namespace std;
extern "C"
{
    void connect();
    //int* add (int a[5],int b[5]);
    void fourir(double input_data[],double output[]);
    
}
void connect()
{
    printf("connect\n");
}
/*int* add(int* a,int* ,int sum)
{
    int*c =new int[5];
    for(int i =0;i<5;i++)
    {
        cout<<a[i]<<"   "<<b[i]<<endl;
        c[i]=a[i]+b[i];
    }
    c=sum
    return c;
}*/
void fourir(int input_data[],int output[])
{
    int size =sizeof(input_data)/sizeof(input_data[0]);
    double real[];
    double imag[];
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
        output[k]=real[k];
    }
    
    return;
}