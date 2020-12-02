#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "Chromosome.h"

/**
 * Константное значение числа PI.
 */
const double PI = 3.141592653589793238463;

/**
 * Типы экстремумов для поиска.
 */
enum SearchType {
	MINIMIZATION, /**< enum value MINIMIZATION */
	MAXIMIZATION /**< enum value MAXIMIZATION */
};

/**
 * Класс, реализующий генетический алгоритм поиска экстремумов функции от двух переменных.
 */
class GeneticAlgorithm {
public:
	/**
	 * Конструктор без параметров.
	 * Используются параметры поиска по умолчанию.
	 */
	GeneticAlgorithm();

	/**
	 * Конструктор с установкой всех параметров поиска.
	 */
	GeneticAlgorithm(SearchType searchType, bool genMode, unsigned int populationSize, unsigned int generationsCount,
					 bool twoChild, double mutationRate, double crossoverRate, unsigned int randLimit);

	/**
	 * Функция для вычисления значения
	 * приспособленности особи по её координатам.
	 * @param x координата X особи.
	 * @param y координата Y особи.
	 * @return значение функции поиска.
	 * @callergraph
	 */
	double getFitness(double x, double y) {
		double function = (x * x * x - 6 * x * y + 8 * y * y * y + 5);
		return (!searchType) ? -1 * function : function;
	}

	/**
	 * Функция для начала поиска.
	 */
	void start();

	/**
	 * Вывод данных о популяции в консоль.
	 */
	void outputPopulation();

	/**
	 * Функция получения результата работы алгоритма.
	 * @return координаты экстремума функции.
	 */
	Chromosome getResult() {
		Chromosome g = population[populationSize - 1];
		if (!searchType) g.fitness *= -1;

		return g;
	}

	/**
	 * Функция, возвращающая установленный тип экстремума для поиска.
	 * @return тип экстремума.
	 */
	SearchType getSearchType() const { return searchType; };

	/**
	 * Функция установки типа экстремума для поиска.
	 * @param searchType желаемый тип экстремума.
	 */
	void setSearchType(SearchType searchType);

	/**
	 * Функция, возвращающая установленный тип работы алгоритма.
	 * @return тип работы алгоритма.
	 */
	bool isGenMode() const { return genMode; };

	/**
	 * Функция установки типа работы алгоритма.
	 * @param genMode желаемый тип работы алгоритма.
	 */
	void setGenMode(bool genMode);

	/**
	 * Функция, возвращающая установленный тип работы алгоритма.
	 * @return тип работы алгоритма.
	 */
	unsigned int getPopulationSize() const { return populationSize; };

	/**
	 * Функция установки размера популяции.
	 * @param populationSize желаемый размер популяции.
	 */
	void setPopulationSize(unsigned int populationSize);

	/**
	 * Функция, возвращающая установленный размер популяции.
	 * @return размер популяции.
	 */
	unsigned int getGenerationsCount() const { return generationsCount; };

	/**
	 * Функция установки количества поколений для отбора.
	 * @param generationsCount жалаемое количество поколений.
	 */
	void setGenerationsCount(unsigned int generationsCount);

	/**
	 * Функция, возвращающая установленное количество детей при размножении (false - 1, true - 2).
	 * @return количество детей при размножении.
	 */
	bool isTwoChild() const { return twoChild; };

	/**
	 * Функция установки количества детей при размножении.
	 * @param twoChild желаемое количество детей (false - 1, true - 2).
	 */
	void setTwoChild(bool twoChild);

	/**
	 * Функция, возвращающая установленную вероятность мутации новой особи.
	 * @return вероятность мутации новой особи.
	 */
	double getMutationRate() const { return mutationRate; };

	/**
	 * Функция установки вероятности мутации новой особи.
	 * @param mutationRate желаемая вероятность мутации новой особи.
	 */
	void setMutationRate(double mutationRate);

	/**
	 * Функция, возвращающая установленную вероятность скрещивания особей.
	 * @return вероятность скрещивания особей.
	 */
	double getCrossoverRate() const { return crossoverRate; };

	/**
	 * Функция установки вероятности скрещивания особей.
	 * @param crossoverRate желаемая вероятность скрещивания особей.
	 */
	void setCrossoverRate(double crossoverRate);

	/**
	 * Функция, возвращающая установленный предел мутации особи.
	 * @return предел мутации особи.
	 */
	unsigned int getRandLimit() const { return randLimit; };

	/**
	 * Функция установки предела мутации особи.
	 * @param randLimit желаемый предел мутации особи.
	 */
	void setRandLimit(unsigned int randLimit);


private:
	/**
	 * Тип поиска экстремумов
	 */
	SearchType searchType = MINIMIZATION;

	/**
	 * Режим работы алгоритма.
	 * @param true пока все особи не будут иметь приблизительно одинаковые координаты.
	 * @param false определённое число поколений.
	 */
	bool genMode = false;

	/**
	 * Размер популяции.
	 */
	unsigned int populationSize = 100;

	/**
	 * Колическтво поколений.
	 */
	unsigned int generationsCount = 2000;

	/**
	 * Количество детей при размножении.
	 * @param true двое.
	 * @param false один.
	 */
	bool twoChild = true;

	/**
	 * Вероятность мутации особи.
	 */
	double mutationRate = 0.05;

	/**
	 * Вероятность скрещивания особей.
	 */
	double crossoverRate = 0.8;

	/**
	 * Пределы мутации особи.
	 */
	unsigned int randLimit = 10;

	/**
	 * Сумма приспособленности всех особей.
	 */
	double totalFitness = 0.0;

	/**
	 * Список особей в популяции.
	 */
	std::vector<Chromosome> population;

	/**
	 * Список особей следующей популяции.
	 */
	std::vector<Chromosome> nextPopulation;

	/**
	 * Список приспособленностей особей.
	 */
	std::vector<double> fitnessList;

	/**
	 * Функция, возвращающая случайное дробное число
	 * в пределах от 0 до 1.
	 * @return случайное число.
	 */
	double random();

	/**
	 * Функция создания первоначальной популяции.
	 */
	void createPopulation();

	/**
	 * Функция оценивания текущей популяции.
	 */
	void rankPopulation();

	/**
	 * Функция, рассчитывающая приспособленность каждой особи.
	 */
	void fitnessChromosomes();

	/**
	 * Функция ортировки особей в массиве по приспособленности.
	 */
	void sortChromosomes();

	/**
	 * Функция создания следующего поколения особей.
	 */
	void createNextGeneration();

	/**
	 * Функция отбора особи для размножения методом рулетки.
	 * @return id особи.
	 */
	unsigned int rouletteSelection();

	/**
	 * Функция скрещивания двух особей.
	 * @param parent1 первая особь.
	 * @param parent2 вторая особь.
	 */
	void crossover(Chromosome parent1, Chromosome parent2);

	/**
	 * Функция мутации особи.
	 * @param g особь, подверженная мутации.
	 */
	void mutation(Chromosome& g);

	/**
	 * Функция проверки окончания работы алгоритма.
	 * @return true алгоритм завершил работу.
	 * @return false алгоритм не нашёл экстремум.
	 */
	bool checkPopulation();
};

#endif //GENETIC_ALGORITHM
