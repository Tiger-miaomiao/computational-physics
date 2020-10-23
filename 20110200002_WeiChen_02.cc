////////////////////////////////////////////////////////////////////////////////////
/// 使用Romberg求积法计算被积函数的Simpson积分                           
/// 被积函数为f(x)=x/(4+x^2) 求积区间为(0,1) h^6近似                     
/// 此处就不考虑写成小程序了，直接用主函数进行计算
/// 每一级积分使用Simpson方法求积分
/// version 01                                                         
/// 我怎么写成C了啊喂？？？！！！
/// version 02 修改计划：将function和梯形还有Simpson积分以及Romberg方法都写作模块
////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x)
{
    double f = 0;
    f = x/(4 + x*x);
    return f;
}

double sumf(int n, double a, double h)
{
    double sum = 0;
    int k = pow(2, n - 1);
    for (int i = 0; i < k; i++)
    {
        sum =sum + f(a + double(2*i + 1)*h);
    }
    return sum;
}

int main()
{
    double a = 0, b = 1; //定义区间
    double h = (b - a); //定义区间长度
    double eps = 1e-6; //定义误差范围
    double d[20][20] = {0}; //不同级数的Romberg积分,20为最大级数

    d[0][0] = h*(f(a)+f(b))/(double) 2; //第一项计算

    for (int i = 1; i < 20; i++)
    {
        h = h/(double) 2;
        d[i][0] = d[i-1][0]/((double) 2) + h*sumf(i, a, h); //使用梯形积分计算第一级积分，h^2近似
        for (int j = 1; j < i+1; j++)
        {
            d[i][j] = (((double) pow (2, 2*j))*d[i][j-1] - d[i-1][j-1])/((double) pow (2, 2*j) - 1); //Richardson外推公式，h^(2*(j + 1))近似

            if (fabs(d[i][j-1] - d[i-1][j-1]) < eps)
            {
                cout << "\nRomberg integral f(" << a << " ~ " << b << ") = " << scientific << setprecision(15) << d[i][j-1] << endl;
                cout << "\n级数是：" << i << " " << j << endl;
                j = 20; i = 20;
            }
        }
        if (i == 19) //定义了最大计算级数，如果达到最大计算级数仍未达到相应精度，则提示增大计算级数上限
        {
            cout << "\nCan't get " << eps << " accuracy！Please increase the maxstep" << endl;
            cout << "\nThe last Romberg integral is D[" << i << "][" << i << "] = " << d[i][i] << endl;
        }
    }
    return 0;
}