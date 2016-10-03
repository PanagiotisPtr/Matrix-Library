#include "matrix.h"
#include <vector>
#include <iostream>
#include <assert.h>
#include <string>
#include <algorithm>

using namespace std;

//Constructor
matrix::matrix(vector< vector<double> > a){
	elements = a;
	type = "matrix";
	cols = a[0].size();
	rows = a.size();
}

matrix::matrix(vector<double> a){
	for (auto e : a) {
		elements.push_back(vector<double>{e});
	}
	type = "vector";
	cols = 1;
	rows = a.size();
}

matrix::matrix(char I, int a){
	if (I == 'I') {
		for (int i = 0; i < a; i++) {
			elements.push_back(vector<double> {});
			for (int j = 0; j < a; j++) {
				int num = j != i ? 0 : 1;
				elements[i].push_back(num);
			}
		}
		cols = a;
		rows = a;
	}
}

//Basic Math

// Addition
void matrix::add(matrix a) {
	assert(a.getCols() == cols && a.getRows() == rows);
	//For Matrices
	if (rows > 1 && cols > 1) {
		for (int i = 0; i < a.getCols(); i++) {
			for (int j = 0; j < a.getRows(); j++) {
				elements[i][j] += a.getVec()[i][j];
			}
		}
	}
	//For Vectors
	else {
		for (int i = 0; i < cols; i++) {
			elements[i][0] += a.getVec()[i][0];
		}
	}
}

// Sabtraction
void matrix::sab(matrix a) {
	assert(a.getCols() == cols && a.getRows() == rows);
	//For Matrices
	if (rows > 1 && cols > 1) {
		for (int i = 0; i < a.getCols(); i++) {
			for (int j = 0; j < a.getRows(); j++) {
				elements[i][j] -= a.getVec()[i][j];
			}
		}
	}
	//For Vectors
	else {
		for (int i = 0; i < cols; i++) {
			elements[i][0] -= a.getVec()[i][0];
		}
	}
}

//Multiply
void matrix::mult(matrix a) {
	vector< vector<double> > temp;
	if (cols == a.getRows()) {
		for (int i = 0; i < rows; i++) {
			temp.push_back(vector<double>{});
			for (int k = 0; k < a.getCols(); k++) {
				double sum = 0;
				for (int j = 0; j < cols; j++) {
					sum += elements[i][j] * a.getVec()[j][k];
				}
				temp.back().push_back(sum);
			}
		}
		elements = temp;
		cols = a.getCols();
	}
	//We may also have a scalar as an argument ;)
	else if (a.getCols() == 1 && a.getRows() == 1) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				elements[i][j] *= a.getVec()[0][0];
			}
		}
	}
	else {
		cout << "ERROR: " << "Matrices can only be multiplied if the number of columns in the first matrix is the same as the number of rows in the second matrix. Looks like you did some math wrong. Sorry :(" << endl;
	}
}

//Advanced Operations

//Determinant

//For 2x2
double matrix::det2x2(matrix a) {
	return a.getVec()[0][0] * a.getVec()[1][1] - a.getVec()[0][1] * a.getVec()[1][0];
}

//For 3x3 //not used
double matrix::det3x3(matrix a) { 
	// there's pretty much no reason for this function to exist. But it is a good thing that it is in here just in case I need it later.
	double sum = 0;
	for (int i = 0; i < cols; i++) {
		int k = 0;
		double temp = 1;
		for (int j = 0; j < rows; j++) {
			int index = j + i;
			if (index >= cols) { index = index%rows; }
			temp *= a.getVec()[k][index];
			k++;
		}
		sum += temp;
	}
	for (int i = 0; i < cols; i++) {
		int k = 0;
		double temp = 1;
		for (int j = cols - 1; j >= 0; j--) {
			int index = j + i;
			if (index >= cols) { index = index%rows; }
			temp *= a.getVec()[k][index];
			k++;
		}
		sum -= temp;
	}
	return sum;
}

// For an NxN matrix

double matrix::detNxN(matrix a) {
	double sum = 0;
	for (int i = 0; i < a.getCols(); i++) {
		if ((i + 1) % 2 == 0) {
			sum += a.getVec()[0][i] * matrix(shave(a.getVec(), i)).det()*(-1);
		}
		else {
			sum += a.getVec()[0][i] * matrix(shave(a.getVec(), i)).det()*(1);
		}
	}
	return sum;
}

//Calculate Determinant
double matrix::det() {
	assert(rows==cols && rows!=1); // You can't get the determinant of a vector ;)
	if (rows == 2 && cols == 2) {
		return det2x2(matrix(elements));
	}
	else {
		return detNxN(matrix(elements));
	}
}

//Matrix of Minors
matrix matrix::minors() {
	vector< vector<double> > minors;

	double sum = 0;
	for (int i = 0; i < rows; i++) {
		minors.push_back(vector<double> {});
		for (int j = 0; j < cols; j++) {
			minors.back().push_back(matrix(shave(elements, i, j)).det());
		}
	}
	
	matrix minrs(minors);
	minrs.T();
	return minrs;
}

//Cofactor Matrix 
matrix matrix::cof() {
	vector< vector<double> > cofactors;

	double sum = 0;
	for (int i = 0; i < rows; i++) {
		cofactors.push_back(vector<double> {});
		for (int j = 0; j < cols; j++) {
			int g = ((i + 1 + j) % 2 == 0) ? -1 : 1;
			cofactors.back().push_back(matrix(shave(elements, i, j)).det() * g);
		}
	}

	matrix cof(cofactors);
	cof.T();
	return cof;
}

// Inverse
matrix matrix::inv() {
	if (rows >= 3) {
		matrix mat(elements);
		double det = mat.det();
		matrix inv = mat.cof();
		inv.T();
		inv.mult(matrix({ 1 / det }));
		return inv;
	}
	else {
		matrix inv({ { elements[1][1],elements[0][1] * -1 },{ elements[1][0] * -1, elements[0][0] } });
		inv.mult({ {1 / matrix(elements).det()} });
		return inv;
	}
}

//Transformations

//Transpose
void matrix::T() {
	vector< vector<double> > temp;
	if (rows > 1) {
		//For Vectors
		if (cols == 1) {
			temp.push_back(vector<double>{});
			for (int i = 0; i < rows; i++) {
				temp.back().push_back(elements[i][0]);
			}
			elements = temp;
			cols = rows;
			rows = temp.size();
		}
		//For Matrices
		else {
			for (int i = 0; i < cols; i++) {
				temp.push_back(vector<double> {});
				for (int j = 0; j < rows; j++) {
					temp.back().push_back(elements[j][i]);
				}
			}
			elements = temp;
			int tempCols = cols;
			cols = rows;
			rows = tempCols;
		}
	}
	//For Transposed Vectors(i.e vectors that have only one column)
	else {
		temp.push_back(vector<double> {});
		for (int i = 0; i < cols; i++) {
			temp.back().push_back(elements[i][0]);
		}
		elements = temp;
		cols = 1;
		rows = temp.back().size();
	}
}

//Utility

void matrix::print()
{
	for (int i = 0; i < elements.size(); i++) {
		for (int j = 0; j < elements[i].size(); j++) {
			cout << elements[i][j] << "\t";
		}
		cout << endl;
	}
}

void matrix::printType()
{
	cout << "Type: " << type << endl;
}

void matrix::printRows()
{
	cout << "Rows: " << rows << endl;
}

void matrix::printCols()
{
	cout << "Columns: " << cols << endl;
}

int matrix::getCols(){
	return cols;
}

int matrix::getRows() {
	return rows;
}

string matrix::getType() {
	return type;
}

vector< vector<double> > matrix::getVec() {
	return elements;
}

//Shave Vector
vector< vector<double> > matrix::shave(vector< vector<double> > a, int i) {
	a.erase(a.begin() + 0);
	for (int j = 0; j < a.size(); j++) {
		a[j].erase(begin(a[j]) + i);
	}

	return a;
}

vector< vector<double> > matrix::shave(vector< vector<double> > a, int i, int j) {
	a.erase(a.begin() + j);
	for (int j = 0; j < a.size(); j++) {
		a[j].erase(begin(a[j]) + i);
	}

	return a;
}