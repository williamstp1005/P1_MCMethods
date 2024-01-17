#include <iostream>
#include <random>
using namespace std;

int main() {
	srand(time(0));
	int N = 10;
	int steps = 320;
	int** row = new int* [N];
	for (int i = 0; i < N; i++) {
		row[i] = new int[N];
		for (int j = 0; j < N; j++) {
			row[i][j] = NULL;
		}
	}
	int state;
	int numneg = 0;
	int numpos = 0;
	int x;
	int y;
	double J = 1.0;
	double k = 1.0;
	double T = 0.8;
	double deltE = 0;
	default_random_engine gen(time(0));
	uniform_real_distribution<double> distribution(0.0,1.0);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (distribution(gen) <= 0.5) {
				state = 1;
				cout << '#';
				numneg++;
			}
			else {
				state = -1;
				cout << ' ';
				numpos++;
			}

			row[i][j] = state;
		}
		cout << endl;
	}
	//cout << numneg << "    " << numpos << endl;
	int stepLimit = 10;

	for (int i = 0; i < steps; i++) {
		cout << "\n\n--------------------------------------------------------------------------------------------------------------------\n" << "Steps taken: " << stepLimit << "\n\n" << endl;
		while (i < stepLimit) 
		{
			x = rand() % N;
			y = rand() % N;
			//cout << "\n\n\n\n\nx: " << x << "    y: " << y << "\n\n\n\n";
			int summation = 0;

			if (x == 0 && y == 0) {
				summation = row[x][y + 1] + row[x + 1][y];
			}
			else if (x == 0 && y == N - 1) {
				summation = row[x + 1][y] + row[x][y - 1];
			}
			else if (x == N - 1 && y == 0) {
				summation = row[x - 1][y] + row[x][y + 1];
			}
			else if (x == N - 1 && y == N - 1) {
				summation = row[x - 1][y] + row[x][y - 1];
			}
			else if (x == 0) {
				summation = row[x][y + 1] + row[x][y - 1] + row[x + 1][y];
			}
			else if (x == N - 1) {
				summation = row[x][y + 1] + row[x][y - 1] + row[x - 1][y];
			}
			else if (y == 0) {
				summation = row[x][y + 1] + row[x - 1][y] + row[x + 1][y];
			}
			else if (y == N - 1) {
				summation = row[x - 1][y] + row[x][y - 1] + row[x + 1][y];
			}
			else {
				summation = row[x - 1][y] + row[x][y - 1] + row[x + 1][y] + row[x][y + 1];
			}

			deltE = J * row[x][y] * summation;
			double prob = exp(deltE / (k * T));
			int change = ((((float)rand() / RAND_MAX) <= prob) * -2 + 1);
			row[x][y] *= change;
			i++;
			//cout << change << endl;
		}
		//cout << "Steps taken: " << stepLimit << endl;
		stepLimit *= 2;
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				if (row[j][k] == -1) {
					cout << ' ';
				}
				else {
					cout << '#';
				}
			}
			cout << endl;
		}
	}

	


	return 0;
}