#include "mlisp.h"

double fun(double x);
double golden__section__search(double a, double b);
double golden__start(double a, double b);
double __klv__try(double a, double b, double xa, double ya, double xb, double yb);
bool close__enough_Q(double x, double y);

double a = 2.;
double b = 4.;
double total__iterations = 0;
double mphi = (3. - sqrt(5.)) * (1. / 2.);
double tolerance = 0.001;
double xmin = 0;

double fun(double x){
    x = x - 102./103.;
    return 2 * sin(x) * cos(x) - 0.5;
}

double golden__section__search(double a, double b){
    double xmin(a < b ? golden__start(a, b) : golden__start(b,a));
    newline();
    return xmin;
}

double golden__start(double a, double b){
    total__iterations = 0;
    {
        double xa(a + (mphi * (b - a)));
        double xb(b - (mphi * (b - a)));
        return __klv__try(a, b, xa, fun(xa), xb, fun(xb));
    }
}

bool close__enough_Q(double x, double y) {
    return abs(x - y) < tolerance;
}

 double __klv__try(double a, double b, double xa, double ya, double xb, double yb){
    return (
        close__enough_Q(a, b) ?
            ((a + b) * 0.5) :
            (display("+"), total__iterations += 1, (ya < yb ?
                    (b = xb, xb = xa, yb = ya, xa = a + mphi * (b - a), __klv__try(a, b, xa, fun(xa), xb, yb)) :
                    (a = xa, xa = xb, ya = yb, xb = b - mphi * (b - a), __klv__try(a, b, xa, ya, xb, fun(xb)))
                                                    )
            )
        );
}

int main(){
    xmin = golden__section__search(a, b);
    display("Interval = ["); display(a);  display(", "); display(b); display("]"); newline();
    display("Total number of iterations = "); display(total__iterations); newline();
    display("xmin = "); display(xmin);newline();
    display("f(xmin) = "); display(fun(xmin)); newline();
}
