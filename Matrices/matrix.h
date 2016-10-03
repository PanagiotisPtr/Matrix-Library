#pragma once
#include <vector>
#include <string>

using namespace std;

class matrix
{
public:
	//Constructor
	matrix(vector< vector<double> > a);
	matrix(vector<double> a);
	matrix(char I, int a); // Identity Matrix
	
	//Basic Math
	void add(matrix a);
	void sab(matrix a);
	void mult(matrix a);

	//Advanced Operations
	double det();
	matrix minors();
	matrix cof();
	matrix inv();

	//transformation
	void T();

	//Utility
	void print();
	void printType();
	void printRows();
	void printCols();
	int getCols();
	int getRows();
	string getType();
	vector< vector<double> > getVec();
private:
	double det2x2(matrix a);
	double det3x3(matrix a);
	double detNxN(matrix a);
	int cols;
	int rows;
	vector< vector<double> > shave(vector< vector<double> > a, int i);
	vector< vector<double> > shave(vector< vector<double> > a, int i, int j);
	string type;
	vector< vector<double> > elements;
};

