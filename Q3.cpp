#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
using namespace std;

void partab(int _size, int timeConst) {
	srand(timeConst);
	rand();
	int x = 0;
	int y = 0;
	int xmovement;
	int ymovement;
	int negative;
	int size = _size;
	int* xlist = new int[size];
	int* ylist = new int[size];
	ofstream xdatafile("xdata.csv");
	ofstream ydatafile("ydata.csv");

	for (int j = 0; j < size; j++) {
		for (int i = 0; i < 100; i++) {
			xmovement = (rand() % 2);
			ymovement = 1;
			negative = (rand() % 2);

			if (negative) {
				xmovement *= -1;
				ymovement *= -1;
			}
			x += (xmovement);

			if (xmovement == 1 || xmovement == -1) {
				continue;
			}
			y += ymovement;
		}
		xlist[j] = x;
		ylist[j] = y;
		xdatafile << x << ",";
		ydatafile << y << ",";
		x = 0;
		y = 0;
	}
	xdatafile.close();
	ydatafile.close();
}


float partc(int _size) {
	float calculateSD(float data[]);
	ifstream xdata("xdata.csv");
	ifstream ydata("ydata.csv");
	string xline;
	string yline;
	getline(xdata, xline);
	getline(ydata, yline);
	istringstream xstream(xline);
	istringstream ystream(yline);
	string xtoken;
	string ytoken;
	int size = _size;
	float* x = new float[size];
	float* y = new float[size];
	float* distance = new float[size];
	int i = 0;
	float mean = 0;
	float stddev = 0;
	float summation = 0;

	while (getline(xstream, xtoken, ',')) {
		x[i] = stoi(xtoken);
		i++;
	}
	i = 0;
	while (getline(ystream, ytoken, ',')) {
		y[i] = stoi(ytoken);
		i++;
	}

	for (int i = 0; i < size; i++) {
		distance[i] = sqrt(pow(x[i], 2) + pow(y[i], 2));
		summation += distance[i];
	}

	mean = summation / size;
	summation = 0;

	for (int i = 0; i < size; i++) {
		distance[i] -= mean;
		distance[i] = pow(distance[i], 2);
		summation += distance[i];
	}

	stddev = sqrt(summation / size);
	cout << "Mean: " << mean << endl << "Standard Deviation: " << stddev << endl;
	xdata.close();
	ydata.close();
	return mean;
}


void partde(int batches, int size) {
	srand(time(NULL));
	float trueMean = 0;
	float sum = 0;
	float* means = new float[batches];
	for (int i = 0; i < batches; i++) {
		partab(size, rand());
		means[i] = partc(size);
		trueMean += means[i];
	}
	cout << "Mean of all: " << trueMean / batches << endl;
	for (int i = 0; i < batches; i++) {
		means[i] -= (trueMean/batches);
		means[i] = pow(means[i], 2);
		sum += means[i];
	}
	cout << "Standard Error: " << (sqrt(sum / batches)/sqrt(batches)) << endl;
}

void partf(int _size, int batches) {
	srand(time(0));
	rand();
	int x = 0;
	int y = 0;
	int xmovement;
	int ymovement;
	int negative;
	int size = _size;
	int* xlist = new int[size];
	int* ylist = new int[size];
	int* movesList = new int[size];
	float* avgList = new float[batches];
	ofstream xdatafile("xdata.csv");
	ofstream ydatafile("ydata.csv");
	ofstream moves("moves.csv");
	int numMoves = 0;
	bool edgeHit = false;
	float meanMoves = 0;
	float stddev = 0;
	float trueMean = 0;
	float stdError = 0;


	for (int k = 0; k < batches; k++)
	{
		for (int j = 0; j < size; j++) {
			while (!edgeHit) {
				//cout << x << "    " << y << "    " << numMoves << endl;
				if (abs(y) == 5 || abs(x) == 5) {
					edgeHit = true;
					continue;
				}
				numMoves++;
				xmovement = (rand() % 2);
				ymovement = 1;
				negative = (rand() % 2);

				if (negative) {
					xmovement *= -1;
					ymovement *= -1;
				}
				x += (xmovement);

				if (xmovement == 1 || xmovement == -1) {
					continue;
				}
				y += ymovement;


			}
			xlist[j] = x;
			ylist[j] = y;
			movesList[j] = numMoves;
			xdatafile << x << ",";
			ydatafile << y << ",";
			moves << numMoves << ",";
			//cout << "x " << x << "    y " << y << "     numMoves " << numMoves << endl;
			x = 0;
			y = 0;
			numMoves = 0;
			edgeHit = false;
		}
		xdatafile.close();
		ydatafile.close();
		moves.close();

		for (int i = 0; i < size; i++) {
			meanMoves += movesList[i];
		}


		meanMoves /= size;
		//cout << meanMoves << endl;
		avgList[k] = meanMoves;
		trueMean += meanMoves;

		for (int i = 0; i < size; i++) {
			movesList[i] -= meanMoves;
			movesList[i] = pow(movesList[i], 2);
			stddev += movesList[i];
		}

		stddev = sqrt(stddev / size);
		//cout << stddev << endl;
	}

	trueMean /= batches;
	for (int i = 0; i < batches; i++) {
		avgList[i] -= (trueMean);
		avgList[i] = pow(avgList[i], 2);
		stdError += avgList[i];
	}
	stdError = ((sqrt(stdError / batches)) / sqrt(batches));
	cout << "Mean of all: " << trueMean << "\nStandard Error: " << stdError << endl;
}

int main() {
	partf(1000, 100);

	cout << "done" << endl;
	return 0;
}