// f(x) = ln(x^2) + (x-12) ^ 2 + x
#include <iostream>
#include <cmath>
using namespace std;
double f(double x);
double derivative(double x);
double GradientDescentMomentum(double startPoint, double alpha, double beta, double epsilon);
int main()
{
    double startPoint;
    double alpha = 0.01; //learning rate
    double beta = 0.9;
    cout << "start point: ";
    cin >> startPoint;
    cout << fixed << GradientDescentMomentum(startPoint, alpha, beta, pow(10, -5)) << endl;
}
double f(double x)
{
    return pow(exp(x*x - 1) + x + 1, 2) + 2*pow(2*x - 4, 2);
}
double derivative(double x)
{
    return 2 * (2 * x * exp(x * x - 1) + 1) * (exp(x * x - 1) + x + 1) + 8 * (2 * x - 4);
}

bool has_converged(double theta_new, double epsilon) {
    return abs(derivative(theta_new)) < epsilon;
}

double GradientDescentMomentum(double startPoint, double alpha, double beta, double epsilon)
{
    double points[1000];
    double deltaX = 0;
    double newDeltaX;
    points[0] = startPoint;
    int i;
    for (i = 1; i < 1000; i++)
    {
        newDeltaX = deltaX * alpha - derivative(points[i - 1]) * beta;
        points[i] = points[i - 1] + alpha * newDeltaX - beta * derivative(points[i - 1]);
        deltaX = newDeltaX; 
        if (fabs(derivative(points[i])) < epsilon) 
        {
            break;
        }
        cout << i << ": "<< points[i] << endl;
    }
    return points[i];
}