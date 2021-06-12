#include <iostream>
#include <cmath>

using namespace std;

class DF
{
private:
    double (*f) (double);
    double dx;
public:
    DF(double (*f) (double), double dx)
    {
        this->f = f;
        this->dx = dx;
    }
    
    double operator() (double x) { return (f(x + this->dx) - f(x)) / this->dx; }
};

DF diff(double (*f) (double), double dx)
{
    DF obj(f, dx);
    return obj;
}

double G(double x) { return exp(x * x / 2); }

double g(double x) { return x * exp(x * x / 2); }

int main()
{
    setlocale(LC_ALL, "Russian");
    DF df(G, .001);
    cout << "Производная для функции y(x)=exp(x*x/2):\n";
    for (double z = 0.; z <= 2.; z += .5)
        cout << df(z) << " vs. " << g(z) << endl;
    cout << "Производная для функции y(x)=x*(1-x):\n";
    df = diff([](double x)->double { return x * (1 - x); }, 0.001);
    for (double z = 0; z <= 1; z += 0.25)
        cout << df(z) << " vs. " << [](double x)->double {return 1 - 2 * x; }(z) << endl;
    return 0;
}