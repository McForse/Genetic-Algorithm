#ifndef GENETIC_ALGORITHM_CHROMOSOME_H
#define GENETIC_ALGORITHM_CHROMOSOME_H

/**
 * Структура особи (хромосомы).
 */
class Chromosome {
public:
	/**
	 * Координата X.
	 */
	double x = 0.0;

	/**
	 * Координата Y.
	 */
	double y = 0.0;

	/**
	 * Приспособленность к выживанию.
	 */
	double fitness = 0.0;
};

#endif //GENETIC_ALGORITHM_CHROMOSOME_H
