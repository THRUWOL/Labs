#include <iostream>
#include <cmath>

using namespace std;

double log_ab(double a, double b) {
	return log(b) / log(a);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	double a = 0.7, b = 1.2, x_start = 0.5, x_end = 1.5, dx = 0.05, y, min = INFINITY, max = -INFINITY;

	double eps = 1e-9;

	x_end += 0.05;

	if (dx ==0 || x_start > x_end && dx > 0 || x_start < x_end && dx < 0) cout << "С таким шагом никуда не прийти";

	for (; x_start <= x_end + eps; x_start += dx) {
		if (x_start <= a || abs(a-x_start)< eps) y = cos(x_start);
		else if (x_start > a && x_start < b) y = log(x_start) * sin(x_start);
		else if (x_start >= b) y = log_ab(5, 5*x_start);
		if (y > max) max = y;
		if (y < min) min = y;

		cout << "x = " << x_start << ", y = " << y << endl;
	}
	cout << "min = " << min << ", max = " << max << endl;
}

