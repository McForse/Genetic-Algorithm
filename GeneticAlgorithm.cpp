#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm() {
	srand(time(nullptr));
}

GeneticAlgorithm::GeneticAlgorithm(bool isMaximization, unsigned int population, unsigned int generations, bool isTwoChild, double mutationProb, double crossoverProb, unsigned int randomLimit) {
	maximization = isMaximization;
	populationSize = population;
	generationsCount = generations;
	twoChild = isTwoChild;
	mutationRate = mutationProb;
	crossoverRate = crossoverProb;
	randLimit = randomLimit;
}

double GeneticAlgorithm::random() {
	return rand() / (RAND_MAX + 1.0);
}

void GeneticAlgorithm::start() {
	createPopulation();
	rankPopulation();

	if (genMode) {
		generationsCount = 0;

		do {
			createNextGeneration();
			rankPopulation();
			generationsCount++;
		} while (!checkPopulation());
	} else {
		for (unsigned int i = 0; i < generationsCount; i++) {
			createNextGeneration();
			rankPopulation();
		}
	}


}

void GeneticAlgorithm::createPopulation() {
	for (unsigned int i = 0; i < populationSize; i++) {
		Chromosome g;
		g.x = pow(-1, rand() % 2) + rand() % randLimit + random();
		g.y = pow(-1, rand() % 2) + rand() % randLimit + random();

		population.push_back(g);
	}
}

void GeneticAlgorithm::rankPopulation() {
	fitnessChromosomes();
	sortChromosomes();

	fitnessList.clear();
	double fitness = 0.0;

	for (unsigned int i = 0; i < populationSize; i++) {
		fitness += population[i].fitness;
		fitnessList.push_back(fitness);
	}
}

void GeneticAlgorithm::fitnessChromosomes() {
	totalFitness = 0.0;

	for (unsigned int i = 0; i < populationSize; i++) {
		population[i].fitness = getFitness(population[i].x, population[i].y);
		totalFitness += population[i].fitness;
	}
}

void GeneticAlgorithm::sortChromosomes() {
	unsigned int ind;
	double min;

	for (unsigned int i = 0; i < populationSize; i++) {
		min = INT64_MAX;
		ind = 0;

		for (unsigned int j = i; j < populationSize; j++) {
			if (population[j].fitness < min) {
				min = population[j].fitness;
				ind = j;
			}
		}

		std::swap(population[ind], population[i]);
	}
}

void GeneticAlgorithm::createNextGeneration() {
	nextPopulation.clear();

	for (unsigned int i = 0; i < populationSize; i += 1 + (int)twoChild) {
		unsigned int parent1 = rouletteSelection();
		unsigned int parent2 = rouletteSelection();

		crossover(population[parent1], population[parent2]);
	}

	population.clear();
	nextPopulation.swap(population);
}

unsigned int GeneticAlgorithm::rouletteSelection() {
	double randomFitness = random() * totalFitness;
	unsigned int id = populationSize;
	unsigned int first = 0;
	unsigned int last = populationSize - 1;
	unsigned int mid = (last - first) / 2;

	while (id == populationSize && first <= last) {
		if (randomFitness <= fitnessList[mid]) last = mid;
		else if (randomFitness > fitnessList[mid]) first = mid;

		mid = (first + last) / 2;

		if ((last - first) == 1) id = last;
	}

	return id;
}

void GeneticAlgorithm::crossover(Chromosome parent1, Chromosome parent2) {
	Chromosome child1;

	if (twoChild) {
		Chromosome child2;
		if (random() < crossoverRate) {
			child1.x = parent1.x;
			child2.x = parent2.x;
			child1.y = parent2.y;
			child2.y = parent1.y;
		} else {
			child1 = parent1;
			child2 = parent2;
		}

		mutation(child2);
		nextPopulation.push_back(child2);
	} else {
		if (random() < crossoverRate) {
			child1.x = parent1.x;
			child1.y = parent2.y;
		} else {
			if (random() < 0.5) {
				child1 = parent1;
			} else {
				child1 = parent2;
			}
		}
	}

	mutation(child1);
	nextPopulation.push_back(child1);
}

void GeneticAlgorithm::mutation(Chromosome& g) {
	if (random() < mutationRate) {
		g.x = (g.x + random()) / 2.0;
	}

	if (random() < mutationRate) {
		g.y = (g.x + random()) / 2.0;
	}
}

bool GeneticAlgorithm::checkPopulation() {
	double sum = 0.0;

	for (unsigned int i = populationSize / 2; i < populationSize; i++) {
		sum += population[i].fitness - population[populationSize - 1].fitness;
	}

	return (sum == 0) || ((sum > 0) && (sum < 1.0));
}

void GeneticAlgorithm::outputPopulation() {
	std::cout << std::endl;
	std::cout << "X:\t";
	for (unsigned int i = 0; i < populationSize; i++) {
		std::cout << population[i].x << "\t";
	}
	std::cout << std::endl;
	std::cout << "Y:\t";
	for (unsigned int i = 0; i < populationSize; i++) {
		std::cout << population[i].y << "\t";
	}
	std::cout << std::endl;
	std::cout << "Z:\t";
	for (unsigned int i = 0; i < populationSize; i++) {
		std::cout << population[i].fitness << "\t";
	}
	std::cout << std::endl;
}