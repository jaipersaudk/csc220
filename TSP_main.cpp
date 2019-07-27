#include "TSP.h"
#include <iostream>
#include <limits>
#include <assert.h>

using namespace std;

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
