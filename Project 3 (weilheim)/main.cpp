/*{ofstream outputT("./output/temp.txt");
outputT << "rows: " << temp.rows << ", cols: " << temp.cols << ", type: " << temp.type() << std::endl;
outputT << temp << std::endl;
}*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <random>

#include"genetic.h"

using namespace std;
using std::vector;


int main(int argc, char * argv[]) {

	int cityNb = 42;
	int route = 300;
	int ep = 5;
	int iteration = 200;

	string dataPath = "./data/dantzig42_d.txt";

	vector<vector<int>> distance = inTxt(dataPath, cityNb);

	vector<vector<int>> population = initPath(route, cityNb);

	vector<vector<int>>::const_iterator pRow;
	vector<int>::const_iterator pCol;

	ofstream outputP("./output/population.txt");
	for (pRow = population.cbegin(); pRow != population.cend(); pRow++) {
		for (pCol = (*pRow).cbegin(); pCol != (*pRow).cend(); pCol++) {
			outputP << *pCol << " ";
		}
		outputP << endl;
	}

	vector<int> routeLength;
	for (int i = 0; i < route; i++) {
		routeLength.push_back(fitness(population[i], distance));
	}

	vector<double> range = choseRange(routeLength, ep);
	outputP << endl;
	outputP << "range:" << endl;
	vector<double>::const_iterator rIter = range.cbegin();
	for (; rIter != range.cend(); rIter++) {
		outputP << *rIter << " ";
	}

	vector<vector<int>> mini(iteration, vector<int>(cityNb));

	for (int j = 0; j < iteration; j++) {

		population = mutate(population, range, routeLength);
		population = change(population, 0.06, cityNb);

		vector<int> routeLength;
		for (int i = 0; i < population.size(); i++) {
			routeLength.push_back(fitness(population[i], distance));
		}

		mini[j] = saveMin(population, routeLength);

		vector<double> range = choseRange(routeLength, ep);

		vector<vector<int>>::const_iterator spRow;
		vector<int>::const_iterator spCol;
		ofstream outputGen("./output/generation.txt");
		for (spRow = population.cbegin(); spRow != population.cend(); spRow++) {
			for (spCol = (*spRow).cbegin(); spCol != (*spRow).cend(); spCol++) {
				outputGen << *spCol << " ";
			}
			outputGen << endl;
		}
	}

	vector<int> finalLength;
	for (int i = 0; i < iteration; i++) {
		finalLength.push_back(fitness(mini[i], distance));
	}

	vector<int>::const_iterator fitIter = finalLength.cbegin();
	int minFit = *fitIter;
	int index = 0;
	for (; fitIter != finalLength.cend(); fitIter++) {
		if (*fitIter < minFit) {
			minFit = *fitIter;
			index = fitIter - finalLength.cbegin();
		}
	}
	cout << "Minimum length: " << minFit << endl;

	return 0;
}


//vector<int> child = inheritance(population[0], population[1], generator);
//
//vector<int>::const_iterator fIter = population[0].cbegin();
//vector<int>::const_iterator mIter = population[1].cbegin();
//vector<int>::const_iterator cIter = child.cbegin();

//ofstream outputC("./output/child.txt");
//outputC << "father:" << endl;
//for (; fIter != population[0].cend(); fIter++) {
//	outputC << *fIter << " " ;
//}

//outputC << endl << "mother:" << endl;
//for (; mIter != population[1].cend(); mIter++) {
//	outputC << *mIter << " " ;
//}

//outputC << endl << "child:" << endl;
//for (; cIter != child.cend(); cIter++) {
//	outputC << *cIter << " ";
//}
