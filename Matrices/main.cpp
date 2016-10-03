#include <vector>
#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
	vector < vector<double> > a{ { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
	vector < vector<double> > b{ { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
	vector < vector<double> > c{ { 1,2 },{ 3,4 },{ 5,6 } };
	vector < vector<double> > d{ { 1,2,3 },{ 4,5,6 } };
	vector < vector<double> > sa{ { 1,2 },{ 3,4 } };
	vector < vector<double> > sb{ { 2,0 },{ 1,2 } };
	vector < vector<double> > da{ { 1,5,7 },{ 4,3,9 },{ 2,6,8 } };
	vector < vector<double> > db{ { 1,6,1,3 },{ 8,-9,-9,7 },{ 2,1,7,5 },{ 6,7,-3,5 } };
	vector < vector<double> > dc{ { 1,5,2,2,1 },{ 5,5,2,2,3 },{ 9,13,7,11,3 },{ 5,1,-3,5,4 },{ 9,8,7,6,5 } };
	vector < vector<double> > st{ {3,0,2},{ 2,0,-2 },{ 0,1,1 } };
	vector < vector<double> > ss{ { 8,3 },{ 1,2 } };
	vector < vector<double> > result{ {46},{9} };
	vector < vector<double> > test{ { 5,3,9 },{ 2,8,7 },{ 4,9,3 } };
	vector <double> va{ 1,2,3 };
	vector <double> vb{ 1,2,3 };
	matrix mat(ss);

	double det = mat.det();
	
	mat = mat.inv();
	mat.mult(matrix(result));

	mat.print();

	system("PAUSE");
	return 0;
}