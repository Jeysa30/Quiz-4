#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <random>
#include <sys/time.h>

using namespace std;

// Función para tomar el tiempo de ejecución.
double step() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double)tp.tv_sec + (double)tp.tv_usec * 1e-6);
}

bool found = false;
int find_index  = 0;

// Función de P_BSA para encontrar un valor en el arreglo.
bool P_BSA(const vector<int>& arr, int value) {
	int lower = 0, higher = arr.size() - 1;

	#pragma omp parallel
	{
		while (lower <= higher && !found) {
			int middle = lower + (higher - lower) / 2;

			#pragma omp critical
			{
				if (arr[middle] == value) {
					found = true;
					find_index  = middle;
				}
				(arr[middle] < value) ? lower = middle + 1 : higher = middle - 1;
			}
		}
	}
	return found;
}

int main() {
	srand(time(0));
	int size = 16;
	vector<int> array(size);
	int target = rand() % 100;

	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution(0, 99);

	double start = step();
	for (int i = 0; i < size; ++i) {
		array[i] = distribution(generator);
	}

	sort(array.begin(), array.end());

	cout << "Arreglo ordenado: ";
	for (int i = 0; i < min(size, 99); ++i) {
		cout << array[i] << " ";
	}
	cout << "\n";

	bool find_value = P_BSA(array, target);
	double end = step();

	if (find_value) cout << "El valor "<< target <<" se encontro en la posición: " << find_index  << "\n";
	else cout << "El valor "<< target <<" no se encontro en el arreglo.\n";
	printf("Tiempo de ejecución : %f\n", end - start);

	return 0;
}
