#include <iostream>
#include <math.h>

using namespace std;

/*
	y' = f(x, y)
	y(x0) = y0
*/

double const h = 0.05;

double f(double x, double y) {
	return x * exp(-pow(x, 2)) - 2 * x *y;
}

void eyler(double *x, double *y, double m, double a) {
	for (int i = 0; i < m; i++) {
		x[i] = a + i * h;
		y[i + 1] = y[i] + h * f(x[i], y[i]);
	}

	cout << "Method Eylera:\n";
	for (int i = 0; i < m; i++) {
		cout << "x["<< i << "] = " << x[i] << " y[" << i << "] = " << y[i] << endl;
	}
}

double K1(double x, double y) {
	return h * f(x, y);
}

double K2(double x, double y) {
	return h * f(x + 0.5 * h, y + K1(x, y) / 2);
}

double K3(double x, double y) {
	return h * f(x + 0.5 * h, y +  K2(x, y) / 2);
}

double K4(double x, double y) {
	return h * f(x + h, y + K3(x, y));
}

void ryngeKytte(double* x, double* y, double m, double a) {
	for (int i = 0; i < m; i++) {
		x[i] = a + i * h;
		y[i + 1] = y[i] + (K1(x[i], y[i]) + 2 * K2(x[i], y[i]) + 2 * K3(x[i], y[i]) + K4(x[i], y[i])) / 6;
	}

	cout << " Method Rynge-Kytta:\n";
	for (int i = 0; i < m; i++) {
		cout << "x[" << i << "] = " << x[i] << " y[" << i << "] = " << y[i] << endl;
	}
}

int main() {
	double const a = 0, b = 1, h = 0.05;

	double m = (b - a) / h + 1; //размер массива
	double *x = new double[m];
	double *y = new double[m];
	x[0] = a;
	y[0] = b;

	eyler(x, y, m, a);
	ryngeKytte(x, y, m, a);
	return 0;
}