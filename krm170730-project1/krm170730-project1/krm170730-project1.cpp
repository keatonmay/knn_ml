#include "pch.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <array>

using namespace std;

// Calculate euclidean distance based on the 4 features of each variable
double EuclidDist(double a, double b, double c, double d, double e, double f, double g, double h)
{
	double dist = 0;

	dist = (pow(a - e, 2) + pow(b - f, 2) + pow(c - g, 2) + pow(d - h, 2));

	dist = sqrt(dist);
	


	return dist;
}

// sort the a vector pair based on the left parameter (euclidean distance, in this case)
void sortdist(vector<pair<double, int>>& dist)
{
	sort(dist.begin(), dist.end(), [](auto &left, auto &right) {
		return left.first < right.first;
	});

}

// main knn function
void knn(vector<double>& s_l, vector<double>& s_w, vector<double>& p_l, vector<double>& p_w, vector<int>& species)
{
	// split data into train and test set based on our R split
	int train[] = { 1, 3, 4, 5, 6, 7, 9, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41, 42, 45, 46, 47, 48, 49, 52, 53, 54, 55, 56, 57,
	58, 59, 60, 61, 63, 64, 65, 66, 67, 68, 69, 70, 72, 73, 74, 75, 76, 77, 79, 80, 81, 84, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 97, 99, 100, 101, 102, 103, 104, 106, 108, 109, 110, 111, 112,
	113, 114, 116, 118, 119, 120, 121, 124, 125, 126, 127, 130, 131, 132, 133, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148 };

	int test[] = { 0, 2, 8, 10, 11, 15, 26, 40, 43, 44, 50, 51, 62, 71, 78, 82, 83, 85, 96, 98, 105, 107, 115, 117, 122, 123, 128, 129, 134, 149 };

	int correct = 0;

	vector<pair<double, int>> distance;
	vector<double> min;
	vector<int> pred;
	
	// 1st iteration of loop calculates distance to each train point from the first test point and stores the results in distance with a reference to the index of the data.
	// After it is sorted, we access the class of the 3 that are at the beginning of the vector and increment the values of temp, then push the class to the pred vector to indicate
	// our prediction. Repeat for each instance of test data
	for (int i = 0; i < size(test); i++)
	{
		// temp will tell us which class has the most neighbors
		int temp[3] = { 0, 0, 0 };

		// calculate distance for each point in train and store it in distance
		for (int j = 0; j < size(train); j++)
		{
			 distance.emplace_back(EuclidDist(s_l[test[i]], s_w[test[i]], p_l[test[i]], p_w[test[i]], s_l[train[j]], s_w[train[j]], p_l[train[j]], p_w[train[j]]), train[j]);
		}

		sortdist(distance);

		for (int i = 0; i < 3; i++)
		{
			if (species[distance[i].second] == 0)
				temp[0] += 1;
			else if (species[distance[i].second] == 1)
				temp[1] += 1;
			else
				temp[2] += 1;
		}

		if (temp[0] >= 2)
		{
			pred.push_back(0);
		}
		else if (temp[1] >= 2)
		{
			pred.push_back(1);
		}
		else
		{
			pred.push_back(2);
		}

		distance.clear();

		cout << pred[i] << " ";
	}

	// calculate accuracy of predictions
	for (int i = 0; i < pred.size(); i++)
	{
		if (pred[i] == species[test[i]])
		{
			correct++;
		}
	}

	printf("\nClassified %d out of %d correctly\n", correct, pred.size());
	printf("Accuracy: %2f\n", ((double)correct/pred.size()));
	
	
}

// reads file and stores each column in a vector
void readFile(vector<double>& s_l, vector<double>& s_w, vector<double>& p_l, vector<double>& p_w, vector<int>& species)
{
	ifstream file("iris.csv");
	string value;

	getline(file, value, ',');
	getline(file, value, '\n');

	for(int i = 0; i < 150; i++)
	{
		getline(file, value, ',');
		s_l.push_back(stod(value));
		getline(file, value, ',');
		s_w.push_back(stod(value));
		getline(file, value, ',');
		p_l.push_back(stod(value));
		getline(file, value, ',');
		p_w.push_back(stod(value));
		getline(file, value, '\n');
		species.push_back(stoi(value));
	}

}

int main()
{
	clock_t t1;

	

	vector<double> s_l;
	vector<double> s_w;
	vector<double> p_l;
	vector<double> p_w;
	vector<int> species;

	printf("Running kNN on test data. \n");
	printf("0 = Setosa, 1 = Versicolor, 2 = Virginica\n");

	readFile(s_l, s_w, p_l, p_w, species);

	t1 = clock();
	knn(s_l, s_w, p_l, p_w, species);

	printf("Execution time: %d ms\n", (clock() - t1 / CLOCKS_PER_SEC));

	return 0;
}
