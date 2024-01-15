#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
using namespace std; 

double f(double x) {
	return pow((sin(5 * x) + cos(30 * x)), 2);
}

void partb1(double N) {
	srand(time(0));
	double x = 0;
	double y;
	double summation = 0;
	ofstream xdatafile("xdata.csv");
	ofstream ydatafile("ydata.csv");

	for (double i = 0; i < N; i++) {
		x = (double)rand() / (double)RAND_MAX;
		y = f(x);
		xdatafile << x << ",";
		ydatafile << y << ",";
		summation += y * (1 / N);
	}
	cout << summation;
}

void partb2(double N) {
	srand(time(0));
	double x;
	double y;
	ofstream xdatafile("xdata.csv");
	ofstream ydatafile("ydata.csv");
	double Nunder = 0;
	for (double i = 0; i < N; i++) {
		x = ((double)rand() / RAND_MAX);
		y = ((double)rand() / RAND_MAX) * 4;
		if (y <= f(x)) {
			Nunder++;
			xdatafile << x << ",";
			ydatafile << y << ",";
		}
	}
	cout << (Nunder / N) * 4 << endl;
}

int main() {
	return 0;
}