// #include "TSP.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <limits>

using namespace std;

TSP::TSP(const double crossoverProbability, const double mutationProbability) : crossoverProbability(crossoverProbability),
	mutationProbability(mutationProbability), solutions(new int[chromosones][cities]), newPopulation(new int[chromosones][cities])
{
	/* Seed the random number generator */
	srand((unsigned int)time(NULL));
	/* Use the same number to generate a specific sequence */
	//srand(0);
	/* Set random coordinates */
	for(size_t coordinateIndex = 0; coordinateIndex < cities; ++coordinateIndex)
	{
		/* 0 <= x <= xMax */
		citiesX[coordinateIndex] = randomInclusive(xMax);
		/* 0 <= y <= yMax */
		citiesY[coordinateIndex] = randomInclusive(yMax);
	}

	/* Generate random population */
	randomPopulation();
}

void TSP::randomPopulation()
{
	/* Iterate throught each chromosone... */
	for(size_t chromosoneIndex = 0; chromosoneIndex < chromosones; ++chromosoneIndex)
	{
		/* ... and give it a random path */
		setRandomPath(solutions[chromosoneIndex]);
	}
}

double TSP::getBestFitness() const
{
	return evaluateFitness(bestChromosone);
}

double TSP::getAverageDistance() const
{
	double distance = 0;
	for(size_t chromosoneIndex = 0; chromosoneIndex < chromosones; ++chromosoneIndex)
	{
		distance += totalDistance(solutions[chromosoneIndex]);
	}
	return distance/chromosones;
}

string TSP::getBestPathString() const
{
	stringstream path;
	for(size_t gene = 0; gene < cities; ++gene)
	{
		if(gene != 0)
		{
			path << ",";
		}
		path << bestChromosone[gene];
	}
	return path.str();
}

double TSP::getLowestTotalDistance() const
{
	return totalDistance(bestChromosone);
}

void TSP::nextPopulation()
{
	double fitness[chromosones];
	/* Fill an array with a fitness score for each chromosone,
	 * the index of a score corresponds with the chromosone's index in solutions[index]
	 */
	for(size_t chromosoneIndex = 0; chromosoneIndex < chromosones; ++chromosoneIndex)
	{
		fitness[chromosoneIndex] = evaluateFitness(solutions[chromosoneIndex]);
	}

	/* Use elitism, find and copy over the two best chromosones to the new population */
	int eliteIndex1 = 0, eliteIndex2 = 0;
	/* find the best solution */
	eliteIndex1 = max_element(fitness, fitness + chromosones) - fitness;
	this->bestChromosone = solutions[eliteIndex1];

	double highestFitness = 0;
	/* Find the second best solution */
	for(size_t chromosoneIndex = 0; chromosoneIndex < chromosones; ++chromosoneIndex)
	{
		if(chromosoneIndex != eliteIndex1 && fitness[chromosoneIndex] > highestFitness)
		{
			highestFitness = fitness[chromosoneIndex];
			eliteIndex2 = chromosoneIndex;
		}
	}

	/* Keep track of how many chromosones exists in the new population */
	size_t offspringCount = 0;
	/* Copy over the two best solutions to the new population */
	copyToNewPopulation(solutions[eliteIndex1], offspringCount);
	++offspringCount;
	copyToNewPopulation(solutions[eliteIndex2], offspringCount);
	++offspringCount;

	/* Create the rest of the new population, break this loop when the new population is complete */
	while(true)
	{
		int * parentA;
		int * parentB;
		parentA = rouletteSelection(fitness);
		parentB = rouletteSelection(fitness);
		while (parentB == parentA)
		{
			parentB = rouletteSelection(fitness);
		}
		int offspringA[cities];
		int offspringB[cities];
		crossover(parentA, parentB, offspringA, offspringB);
		mutate(offspringA);
		mutate(offspringB);

		/* Add to new population if an equal chromosone doesn't exist already */
		if(!hasDuplicate(offspringA, offspringCount))
		{
			copyToNewPopulation(offspringA, offspringCount);
			++offspringCount;
		}
		/* We need to check if the new population is filled */
		if(offspringCount == chromosones)
		{
			break;
		}
		if(!hasDuplicate(offspringB, offspringCount))
		{
			copyToNewPopulation(offspringB, offspringCount);
			++offspringCount;
		}
		/* Check again so that we don't accidentaly write all over the heap and have to spend an evening wondering why the heap is corrupt... :) */
		if(offspringCount == chromosones)
		{
			break;
		}
	}

	/*
	 * We now have a new population,
	 * now it needs to replace the current population
	 * so that we don't go through the same population every time we run this function
	 */
	for(size_t chromosoneIndex = 0; chromosoneIndex < chromosones; ++chromosoneIndex)
	{
		memcpy(solutions[chromosoneIndex], newPopulation[chromosoneIndex], sizeof(int) * cities);
	}
}

bool TSP::hasDuplicate(const int * const chromosone, size_t populationCount)
{
	/* Iterate throught each chromosone in newPopulation and compare them gene by gene */
	for(size_t chromosoneIndex = 0; chromosoneIndex < populationCount; ++chromosoneIndex)
	{
		int genesCompared = 0;
		for(size_t gene = 0; gene < cities; ++gene)
		{
			if(chromosone[gene] != newPopulation[chromosoneIndex][gene])
			{
				/* These chromosones are not equal! */
				break;
			}
			++genesCompared;
		}

		if(genesCompared == cities)
		{
			return true;
		}
	}

	return false;
}

void TSP::mutate(int * const chromosone)
{
	/* 0.0 <= random <= 1 */
	{
		double random = randomInclusive(1);
		/* Nope, didn't happen */
		if(random > mutationProbability)
		{
			return;
		}
	}

	int tmp;
	int random1 = (int)randomExclusive(cities);
	int random2 = (int)randomExclusive(cities);
	while(random1 == random2)
	{
		random2 = (int)randomExclusive(cities);
	}

	tmp = chromosone[random1];
	chromosone[random1] = chromosone[random2];
	chromosone[random2] = tmp;

}

void TSP::crossover(int const * const parentA, const int * const parentB, int * offspringA, int * offspringB)
{
	{
		/* There is a chance we don't perform a crossover,
		 * in that case the offspring is a copy of the parents
		 */
		/* 0.0 <= random <= 1 */
		double random = randomInclusive(1);
		/* The offspring is a copy of their parents */
		if(random > crossoverProbability)
		{
			memcpy(offspringA, parentA, sizeof(int) * cities);
			memcpy(offspringB, parentB, sizeof(int) * cities);
			return;
		}
	}
	/* Perform multi-point crossover to generate offspring */

	/* 0 <= cuttOffIndex <= cities */
	int cuttOffIndex1 = (int)randomInclusive(cities);
	int cuttOffIndex2 = (int)randomInclusive(cities);
	while(cuttOffIndex2 == cuttOffIndex1)
	{
		cuttOffIndex2 = (int)randomExclusive(cities);
	}

	unsigned int start;
	unsigned int end;
	if(cuttOffIndex1 < cuttOffIndex2)
	{
		start = cuttOffIndex1;
		end = cuttOffIndex2;
	}
	else
	{
		start = cuttOffIndex2;
		end = cuttOffIndex1;
	}
	/* Offspring A is initially copy of parent A */
	memcpy(offspringA, parentA, sizeof(int) * cities);
	/* Offspring B is initially copy of parent B */
	memcpy(offspringB, parentB, sizeof(int) * cities);

	/* Put a sequence of parent B in offspring A */
	memcpy(offspringA + start, parentB + start, sizeof(int) * (end - start));
	/* Put a sequence of parent A in offspring B */
	memcpy(offspringB + start, parentA + start, sizeof(int) * (end - start));

	/* Mark collisions in offspring with -1*/
	for(size_t cityIndex = 0; cityIndex  < cities; ++cityIndex)
	{
		/* Index is part of the parent sequence */
		if((cityIndex  >= start && cityIndex  < end)) {
			/* Do nothing, we want to keep this sequence intact */
		}
		else
		{
			/* Check if the item at cityIndex also occurs somewhere in the copied substring */
			for(size_t substringIndex = start; substringIndex < end; ++substringIndex)
			{
				/* A duplicate, mark it */
				if(offspringA[cityIndex] == offspringA[substringIndex])
				{
					offspringA[cityIndex] = -1;
				}
				if(offspringB[cityIndex] == offspringB[substringIndex])
				{
					offspringB[cityIndex] = -1;
				}
			}
		}

	}

	/*
	* Go through the offspring,
	* if an element is marked we fill the hole with an element from the other offspring
	*/
	for(size_t offspringIndex = 0; offspringIndex < cities; ++offspringIndex)
	{
		/* There is a hole here */
		if(offspringA[offspringIndex] == -1)
		{
			repairOffspring(offspringA, offspringIndex, offspringB);
		}
		if(offspringB[offspringIndex] == -1)
		{
			repairOffspring(offspringB, offspringIndex, offspringA);
		}
	}
}

void TSP::repairOffspring(int * const offspringToRepair, int missingIndex, const int * const other)
{
	/* Iterate through the other offspring until we find an element which doesn't exist in the offspring we are repairing */
	for(size_t patchIndex = 0; patchIndex < cities; ++patchIndex)
	{
		/* Look for other[patchIndex] in offspringToRepair */
		int *missing = find(offspringToRepair, offspringToRepair + cities, other[patchIndex]);

		/* The element at other[patchIndex] is missing from offspringToRepair */
		if(missing == (offspringToRepair + cities))
		{
			//cout << "1:" << offspringToRepair[missingIndex] << endl;
			offspringToRepair[missingIndex] = other[patchIndex];
			//cout << "2:" << offspringToRepair[missingIndex] << endl;
			break;
		}
	}
}

void TSP::copyToNewPopulation(int const * const chromosone, size_t index)
{
	assert(index < chromosones && "Index out of bounds");
	for(size_t i = 0; i < cities; ++i)
	{
		newPopulation[index][i] = chromosone[i];
	}

}

int * TSP::rouletteSelection(double const * const fitness) const
{
	double sum = 0;
	/* Calculate sum of all chromosome fitnesses in population */
	for(size_t i = 0; i < chromosones; ++i)
	{
		sum += fitness[i];
	}

	/* 0.0 <= random <= sum */
	double random = randomInclusive(sum);

	sum = 0;
	/* Go through the population and sum fitnesses from 0 to sum s. When the sum s is greater or equal to r; stop and return the chromosome where you are */
	for(size_t i = 0; i < chromosones; ++i)
	{
		sum += fitness[i];
		if(sum >= random)
		{
			return solutions[i];
		}
	}
	assert(false && "A chromosone should have been picked by now");
	return(NULL);
}

void TSP::setRandomPath(int * chromosone)
{
	for(size_t i = 0; i < cities; ++i)
	{
		chromosone[i] = i;
	}

	/*
	 * Shuffle the chromosone using the Fisher�Yates shuffle.
	 */
	for(size_t i = cities-1; i > 0; --i)
	{
		/* 0 <= random <= i */
		int random = (int)randomInclusive(i);
		int temp = chromosone[i];
		chromosone[i] = chromosone[random];
		chromosone[random] = temp;
	}
}

double TSP::evaluateFitness(int const * const chromosone) const
{
	return 1/totalDistance(chromosone);
}

double TSP::totalDistance(int const * const chromosone) const
{
	double distance = 0;
	/* Calculate the total distance between all cities */
	for(size_t i = 0; i < cities-1; ++i)
	{
		double dx = citiesX[chromosone[i]] - citiesX[chromosone[i+1]];
		double dy = citiesY[chromosone[i]] - citiesY[chromosone[i+1]];

		/* The distance between two points is the square root of (dx^2+dy^2) */
		distance += sqrt((pow(dx, 2.0) + pow(dy, 2.0)));
	}
	/* We complete the tour by adding the distance between the last and the first city */
	double dx = citiesX[chromosone[cities-1]] - citiesX[chromosone[0]];
	double dy = citiesY[chromosone[cities-1]] - citiesY[chromosone[0]];
	distance += sqrt((pow(dx, 2.0) + pow(dy, 2.0)));

	return distance;
}

double TSP::randomInclusive(double max)
{
	/* Generate random number r, 0.0 <= r <= max */
	//return ((double)rand() / (double)RAND_MAX * max);
	return ((double)rand() * max) / (double)RAND_MAX;
}

double TSP::randomExclusive(double max)
{
	/* Generate random number r, 0.0 <= r < max */
	//return ((double)rand() / ((double)RAND_MAX + 1) * max);
	return ((double)rand() * max) / ((double)RAND_MAX + 1);
}


int main(int argc, const char *argv[])
{
	/* 90% mutation probability, 2% mutation probability */
	TSP *tsp = new TSP(0.9, 0.02);
	size_t generations = 0, generationsWithoutImprovement = 0;
	double bestFitness = -1;
	double initialAverage = tsp->getAverageDistance();
	/* We'll stop when we've gone 10k generations without improvement */
	while(generationsWithoutImprovement < 10000)
	{
		tsp->nextPopulation();
		++generations;
		double newFitness = tsp->getBestFitness();
		/* The new fitness is higher, the chromosone is better */
		if(newFitness > bestFitness)
		{
			bestFitness = newFitness;
			generationsWithoutImprovement = 0;
			cout << "Best goal function: " << tsp->getBestFitness() << endl;
		}
		else
		{
			++generationsWithoutImprovement;
		}
	}
	cout << "DONE!" << endl;
	cout << "Number of generations: " << generations << endl;
	cout << "Best chromosone info: " << endl;
	cout << "\t-Path: " << tsp->getBestPathString() << endl;
	cout << "\t-Goal function: " << tsp->getBestFitness() << endl;
	cout << "\t-Distance: " << tsp->getLowestTotalDistance() << endl;
	cout << "Average distance: " << tsp->getAverageDistance() << endl;
	cout << "Initial average: " << initialAverage << endl;
	delete tsp;
	return 0;
}
