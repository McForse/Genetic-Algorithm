#include <iostream>
#include <iomanip>
#include "GeneticAlgorithm.h"

using namespace std;

int main() {
	// Инициализация со стандартыми параметрами
	GeneticAlgorithm optimization;
	optimization.start();
	Chromosome g = optimization.getResult();

	if (optimization.getIsMaximization()) cout << "Maximization function" << endl;
	else cout << "Minimization function" << endl;
	cout << "z = x * x * x - 6 * x * y + 8 * y * y * y + 5" << endl << endl;
	cout << "X = " << g.x << endl << "Y = " << g.y << endl << "Z = " << g.fitness << endl << endl;
	cout << "Rounded:" << endl << "X = " << setprecision(1) <<  g.x << endl << "Y = " << setprecision(1) << g.y << endl << "Z = " << setprecision(1) << g.fitness << endl << endl;

	return 0;
}