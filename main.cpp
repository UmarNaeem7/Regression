// regression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

class DataSet
{
private:
	int n = 38;
	string fileName = "data.txt";
	int* year;
	float* x;
	float* y;
public:
	DataSet()
	{
		year = new int[n];
		x = new float[n];
		y = new float[n];
	}

	float* getX()
	{
		return x;
	}

	float* getY()
	{
		return y;
	}

	int* getYear()
	{
		return year;
	}

	int getN()
	{
		return n;
	}

	void readFile()
	{
		ifstream ifile;
		ifile.open(fileName);
		if (!ifile)
		{
			cout << "Error opening file.......";
			return;
		}
		string s;
		getline(ifile, s);
		int i = 0;
		while (ifile)
		{
			ifile >> year[i];
			ifile >> x[i];
			ifile >> y[i];
			i++;
		}
	}

	void print()
	{
		if (!year || !x || !y)
		{
			cout << "DataSet is empty.";
			return;
		}
		for (int i = 0; i < n; i++)
			cout << year[i] << "\t" << x[i] << "\t" << y[i] << endl;
	}

	~DataSet()
	{
		if (year)
			delete[]year;
		if (x)
			delete[]x;
		if (y)
			delete[]y;
	}
};

class Regression
{
private:
	float b = 0; //slope
	float a = 0; //intercept
	string equation;
	int n = 38;
	float* xy;
	float* squarex;
	float* regressedY;
	float* error;
	float sum_xy = 0;
	float sum_x = 0;
	float sum_y = 0;
	float sum_squarex = 0;
	float sum_error = 0;
	float sum_reg = 0;
public:
	Regression(float* x,float* y)
	{
		xy = new float[n];
		squarex = new float[n];
		for (int i = 0; i < n; i++)
		{
			xy[i] = x[i] * y[i];
			squarex[i] = x[i] * x[i];
		}

		for (int i = 0; i < n; i++)
		{
			sum_xy += xy[i];
			sum_x += x[i];
			sum_y += y[i];
			sum_squarex += squarex[i];
		}
	}
	float getSumX()
	{
		return sum_x;
	}
	float getSumY()
	{
		return sum_y;
	}
	float getSumXY()
	{
		return sum_xy;
	}
	float getSumSquareX()
	{
		return sum_squarex;
	}
	float getA()
	{
		return a;
	}
	float getB()
	{
		return b;
	}
	float* getSquareX()
	{
		return squarex;
	}
	float* getXY()
	{
		return xy;
	}
	float* getRegressedY()
	{
		return regressedY;
	}
	float* getError()
	{
		return error;
	}
	float getSumReg()
	{
		return sum_reg;
	}
	float getSumError()
	{
		return sum_error;
	}
	void getEq()
	{
		cout << "Regression Equation:	";
		cout << "y = " << a << " + " << b << "x" << endl;
	}
	void computeA(float* x, float* y)
	{
		a = (sum_y - b * sum_x) / n;
	}
	void computeB(float* x, float* y)
	{

		b = (n*sum_xy - sum_x * sum_y) / (n*sum_squarex - sum_x * sum_x);
	}
	float computeError(float* x,float* y)
	{
		regressedY = new float[n];
		error = new float[n];

		for (int i = 0; i < n; i++)
		{
			regressedY[i] = a + b * x[i];
			sum_reg += regressedY[i];
			error[i] = abs(regressedY[i] - y[i]);
		}

		float mean_error = 0;
		for (int i = 0; i < n; i++)
		{
			sum_error += error[i];
		}
		return (mean_error = sum_error / n);

	}
	void exhaustiveSearch(float* x,float* y)
	{
		cout << endl << "Exhaustive Search:" << endl;
		float Y[100000], E[100000];
		int count = 0;
		for (signed int b = -10; b <= 10; b+=3)
		{
			for (signed int a = -10; a <= 10; a+=3)
			{
				for (int x = 1; x <= 38; x++)
				{
					Y[count] = a + b * x;
					E[count] = abs(y[x-1] - Y[count]);

					cout << "Y'(" << count << ") =" << Y[count] << endl;
					cout << "Error'(" << count << ") =" << E[count] << endl;
					count++;
				}
			}
		}

		int c = 1;
		float sum = 0;
		for (int i = 0; i < count; i += 38)
		{
			for (int j = i; j < i + 38; j++)
			{
				sum += E[j];
			}
			float avg = sum / 38;
			cout << "Set " << c << " error = " << setprecision(4) << avg << endl;
			c++;
			sum = 0;
		}


	}
	~Regression()
	{
		if (xy)
			delete[]xy;
		if (squarex)
			delete[]squarex;
		if (regressedY)
			delete[]regressedY;
		if (error)
			delete[]error;
	}
};

void printTable(int* year, float* x, float* y, float* square_x, float* xy, float* reg, float* error, float sumX, float sumY, float sumSqX, float sumXY, float sumReg, float sumError, int n)
{
	cout << "\t" << "Year" << "\t" << "X" << "\t" << "Y" << "\t" << "X^2" << "\t" << "XY" << "\t" << "Y'" << "\t" << "Error" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "\t" << year[i] << "\t" << x[i] << "\t" << y[i] << "\t";
		cout << setprecision(4) << square_x[i] << "\t" << xy[i] << "\t" << reg[i] << "\t" << error[i] << endl;
	}
	cout << "Total" << "\t\t" << sumX << "\t" << sumY << "\t" << sumSqX << "\t" << sumXY << "\t" << sumReg << "\t" << sumError << endl;
}


int main()
{
	cout << endl << "\t\t\t\t" << "Table" << endl;
	DataSet* d = new DataSet();
	d->readFile();

	Regression* r = new Regression(d->getX(), d->getY());
	r->computeB(d->getX(), d->getY());
	r->computeA(d->getX(), d->getY());
	float er = r->computeError(d->getX(), d->getY());
	cout << endl;
	printTable(d->getYear(), d->getX(), d->getY(), r->getSquareX(), r->getXY(), r->getRegressedY(), r->getError(), r->getSumX(), r->getSumY(), r->getSumSquareX(), r->getSumXY(), r->getSumReg(), r->getSumError(), d->getN());
    r->getEq();
	cout << endl;
	cout << "a = " << r->getA() << endl;
	cout << "b = " << r->getB() << endl;

	cout << "Average Error = " << er;

	r->exhaustiveSearch(d->getX(), d->getY());

}


