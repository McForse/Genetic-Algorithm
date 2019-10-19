#pragma once
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>

class Chromosome {
public:
	double x = 0.0;
	double y = 0.0;
	double fitness = 0.0;
};

const double PI = 3.141592653589793238463;

class GeneticAlgorithm {
public:
	GeneticAlgorithm();
	GeneticAlgorithm(bool isMaximization, unsigned int population, unsigned int generations, bool isTwoChild, double mutationProb, double crossoverProb, unsigned int randomLimit);

	double getFitness(double x, double y) {
		double function = (x * x * x - 6 * x * y + 8 * y * y * y + 5);
		return (!maximization) ? -1 * function : function;
	}

	void start();
	void outputPopulation();

	Chromosome getResult() {
		Chromosome g = population[populationSize - 1];
		if (!maximization) g.fitness *= -1;

		return g;
	}

	unsigned getGenerationsCount() { return generationsCount; }
	bool getIsMaximization() { return maximization; }

private:
	bool maximization = false;
	bool genMode = false;
	unsigned int populationSize = 100;
	unsigned int generationsCount = 2000;
	bool twoChild = true;
	double mutationRate = 0.05;
	double crossoverRate = 0.8;
	unsigned int randLimit = 10;
	double totalFitness = 0.0;

	std::vector<Chromosome> population;
	std::vector<Chromosome> nextPopulation;
	std::vector<double> fitnessList;

	double random();

	void createPopulation();
	void rankPopulation();
	void fitnessChromosomes();
	void sortChromosomes();
	void createNextGeneration();
	unsigned int rouletteSelection();
	void crossover(Chromosome parent1, Chromosome parent2);
	void mutation(Chromosome& g);

	bool checkPopulation();
};