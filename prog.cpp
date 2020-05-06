#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
void SelectionSort(vector<double> &array, vector<double> &array2, int size)
{
	for (int startIndex = 0; startIndex < size; ++startIndex)
	{
		int smallestIndex = startIndex;

		for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
		{

			if (array[smallestIndex] > array[currentIndex])

				smallestIndex = currentIndex;
		}

		swap(array[startIndex], array[smallestIndex]);
		swap(array2[startIndex], array2[smallestIndex]);
	}
}
double func(double x1, double x2, double x3)
{
	return x1 * x1 + 8 * x1 + 5 * x2*x2 + 7 * x3*x3 + 119.0*x3 + 531.75;
}

double f(double t, double x1, double x2, double x3, double grad1, double grad2, double grad3)
{
	return (x1 - t * grad1) * (x1 - t * grad1) + 8 * (x1 - t * grad1) + 5 * (x2 - t * grad2)*(x2 - t * grad2) + 7 * (x3 - t * grad3)*(x3 - t * grad3) + 119.0*(x3 - t * grad3) + 531.75;
}

double Method_kvadr_interpol(double a, double b, double h, double epsilon, double x1, double x2, double x3, double grad1, double grad2, double grad3)
{
	double t1 = (a + b) / 2;
	double t2;
	double t3;
	double num, denum;
	double t_star;
	double t_min;
	bool check = false;
	do
	{
		if (check)
		{
			if ((t_star > t1 && t_star < t3) || (t_star > t3 && t_star < t1))
			{
				if (f(t_min, x1, x2, x3, grad1, grad2, grad3) < f(t_star, x1, x2, x3, grad1, grad2, grad3))
				{
					t1 = t_min;
				}
				else
				{
					t1 = t_star;
				}
			}
			else
			{
				t1 = t_star;
			}
		}

		t2 = t1 + h;
		if (f(t1, x1, x2, x3, grad1, grad2, grad3) > f(t2, x1, x2, x3, grad1, grad2, grad3))
		{
			t3 = t1 + 2 * h;
		}
		else
		{
			t3 = t1 - h;
		}

		if (f(t1, x1, x2, x3, grad1, grad2, grad3) < f(t2, x1, x2, x3, grad1, grad2, grad3))
		{
			if (f(t1, x1, x2, x3, grad1, grad2, grad3) < f(t3, x1, x2, x3, grad1, grad2, grad3))
			{
				t_min = t1;
			}
			else
			{
				t_min = t3;
			}
		}
		else
		{
			if (f(t2, x1, x2, x3, grad1, grad2, grad3) < f(t3, x1, x2, x3, grad1, grad2, grad3))
			{
				t_min = t2;
			}
			else
			{
				t_min = t3;
			}
		}

		num = (t2*t2 - t3 * t3) * f(t1, x1, x2, x3, grad1, grad2, grad3) + (t3*t3 - t1 * t1) * f(t2, x1, x2, x3, grad1, grad2, grad3) + (t1*t1 - t2 * t2) * f(t3, x1, x2, x3, grad1, grad2, grad3);
		denum = (t2 - t3) * f(t1, x1, x2, x3, grad1, grad2, grad3) + (t3 - t1) * f(t2, x1, x2, x3, grad1, grad2, grad3) + (t1 - t2) * f(t3, x1, x2, x3, grad1, grad2, grad3);

		if (denum == 0)
		{
			t1 = t_min;
			num = (t2*t2 - t3 * t3) * f(t1, x1, x2, x3, grad1, grad2, grad3) + (t3*t3 - t1 * t1) * f(t2, x1, x2, x3, grad1, grad2, grad3) + (t1*t1 - t2 * t2) * f(t3, x1, x2, x3, grad1, grad2, grad3);
			denum = (t2 - t3) * f(t1, x1, x2, x3, grad1, grad2, grad3) + (t3 - t1) * f(t2, x1, x2, x3, grad1, grad2, grad3) + (t1 - t2) * f(t3, x1, x2, x3, grad1, grad2, grad3);
		}

		t_star = 0.5 * (num / denum);
		check = true;
	} while ((abs(f(t_min, x1, x2, x3, grad1, grad2, grad3) - f(t_star, x1, x2, x3, grad1, grad2, grad3)) > epsilon) || (abs(t_min - t_star) > epsilon));

	return t_star;
}

void Skolz_okno(double &a, double &b, double x0, double h, double x1, double x2, double x3, double grad1, double grad2, double grad3)
{
	if ((f(x0, x1, x2, x3, grad1, grad2, grad3) < f((x0 - h), x1, x2, x3, grad1, grad2, grad3)) && (f(x0, x1, x2, x3, grad1, grad2, grad3) < f((x0 + h), x1, x2, x3, grad1, grad2, grad3)))
	{
		a = x0 - h;
		b = x0 + h;
	}
	else if (f(x0 - h, x1, x2, x3, grad1, grad2, grad3) > f((x0 + h), x1, x2, x3, grad1, grad2, grad3))
	{
		x0 = x0 + h;
		Skolz_okno(a, b, x0, h, x1, x2, x3, grad1, grad2, grad3);
	}
	else
	{
		x0 = x0 - h;
		Skolz_okno(a, b, x0, h, x1, x2, x3, grad1, grad2, grad3);
	}
}

void Method_naiskor_spuska(double epsilon, double x01, double x02, double x03, double &x1_finish, double &x2_finish, double &x3_finish)
{
	ofstream foutT1("fileT1.txt");
	ofstream foutT2("fileT2.txt");
	ofstream foutT3("fileT3.txt");
	double x1 = x01;
	double x2 = x02;
	double x3 = x03;
	double x1_new, x2_new, x3_new;
	double t;
	double grad1, grad2, grad3;
	double a;
	double b;
	double h = 0.01;
	double x0 = 0.5;
	int index = 0;

	do {
		if (index != 0)
		{
			x1 = x1_new;
			x2 = x2_new;
			x3 = x3_new;
		}
		grad1 = 2 * x1 + 8;
		grad2 = 10 * x2;
		grad3 = 14 * x3 + 119.0;
		Skolz_okno(a, b, x0, h, x1, x2, x3, grad1, grad2, grad3);
		t = Method_kvadr_interpol(a, b, h, epsilon, x1, x2, x3, grad1, grad2, grad3);
		x1_new = x1 - t * grad1;
		x2_new = x2 - t * grad2;
		x3_new = x3 - t * grad3;
		index++;

		
		foutT1 << x1 << "    " << x2 << endl;
		foutT2 << x3 << "    " << x2 << endl;
		foutT3 << x3 << "    " << x1 << endl;

	} while ((abs(func(x1_new, x2_new, x3_new) - func(x1, x2, x3)) > epsilon) || (abs(x1_new - x1) > epsilon) || (abs(x2_new - x2) > epsilon) || (abs(x3_new - x3) > epsilon));
	foutT1 << x1_new << "    " << x2_new << endl;
	foutT2 << x3_new << "    " << x2_new << endl;
	foutT3 << x3_new << "    " << x1_new << endl;

	cout << "Number of iterations: " << index << endl;

	x1_finish = x1_new;
	x2_finish = x2_new;
	x3_finish = x3_new;

	foutT1.close();
	foutT2.close();
	foutT3.close();
}

int main()
{
	ofstream fout1("file1.txt");
	ofstream fout2("file2.txt");
	ofstream fout3("file3.txt");
	ofstream fout4("file4.txt");
	ofstream fout5("file5.txt");
	
	double x1, x2, x3;
	double first, second, third;
	double epsilon;
	cout << "Enter first coordinats f(x1, x2, x3)" << endl;
	cout << "x1 = ";
	cin >> first;
	cout << "x2 = ";
	cin >> second;
	cout << "x3 = ";
	cin >> third;
	cout << "Enter error(e.g. 0.01): ";
	cin >> epsilon;
	Method_naiskor_spuska(epsilon, first, second, third, x1, x2, x3);
	cout << "x1 = " << x1 << "    x2 = " << x2 << "    x3 = " << x3 << endl;
	cout << "f(x1,x2,x3) = " << func(x1, x2, x3) << endl;

	/////////////////////             ГРАФИКИ              /////////////////////  

	double x11, x22, x33;
	int foo;

	vector<double> vec11;
	vector<double> vec21;

	vector<double> vec12;
	vector<double> vec22;

	vector<double> vec13;
	vector<double> vec23;

	vector<double> vec14;
	vector<double> vec24;

	vector<double> vec15;
	vector<double> vec25;
	

	foo = 20;
	x33 = x3;


	while (foo <= 420)
	{
		x11 = -4;
		while (x11 <= pow(-10 + foo, 0.5) - 4 && x11 >= -pow(-10 + foo, 0.5) - 4)
		{
			x22 = pow((-pow(x11 + 4, 2) - 10 + foo) / 5, 0.5);
			switch (foo)
			{
			case 20:
				vec11.push_back(x11);
				vec21.push_back(x22);
				break;
			case 120:
				vec12.push_back(x11);
				vec22.push_back(x22);
				break;
			case 220:
				vec13.push_back(x11);
				vec23.push_back(x22);
				break;
			case 320:
				vec14.push_back(x11);
				vec24.push_back(x22);
				break;
			case 420:
				vec15.push_back(x11);
				vec25.push_back(x22);
				break;
			}
			x11 = x11 + 0.1;
		}
		x11 = -4 - 0.1;
		while (x11 <= pow(-10 + foo, 0.5) - 4 && x11 >= -pow(-10 + foo, 0.5) - 4)
		{
			x22 = pow((-pow(x11 + 4, 2) - 10 + foo) / 5, 0.5);
			switch (foo)
			{
			case 20:
				vec11.push_back(x11);
				vec21.push_back(x22);
				break;
			case 120:
				vec12.push_back(x11);
				vec22.push_back(x22);
				break;
			case 220:
				vec13.push_back(x11);
				vec23.push_back(x22);
				break;
			case 320:
				vec14.push_back(x11);
				vec24.push_back(x22);
				break;
			case 420:
				vec15.push_back(x11);
				vec25.push_back(x22);
				break;
			}
			x11 = x11 - 0.1;
		}
		foo += 100;
	}


	SelectionSort(vec11, vec21, vec11.size());
	for (int i = 0; i < vec11.size(); i++)
	{
		fout1 << vec11[i] << "    " << vec21[i] << endl;
	}
	SelectionSort(vec12, vec22, vec12.size());
	for (int i = 0; i < vec12.size(); i++)
	{
		fout2 << vec12[i] << "    " << vec22[i] << endl;
	}
	SelectionSort(vec13, vec23, vec13.size());
	for (int i = 0; i < vec13.size(); i++)
	{
		fout3 << vec13[i] << "    " << vec23[i] << endl;
	}
	SelectionSort(vec14, vec24, vec14.size());
	for (int i = 0; i < vec14.size(); i++)
	{
		fout4 << vec14[i] << "    " << vec24[i] << endl;
	}
	SelectionSort(vec15, vec25, vec15.size());
	for (int i = 0; i < vec15.size(); i++)
	{
		fout5 << vec15[i] << "    " << vec25[i] << endl;
	}

	
	for (int i = vec11.size() - 1; i >= 0; i--)
	{
		fout1 << vec11[i] << "    " << -vec21[i] << endl;
	}
	for (int i = vec12.size() - 1; i >= 0; i--)
	{
		fout2 << vec12[i] << "    " << -vec22[i] << endl;
	}
	for (int i = vec13.size() - 1; i >= 0; i--)
	{
		fout3 << vec13[i] << "    " << -vec23[i] << endl;
	}
	for (int i = vec14.size() - 1; i >= 0; i--)
	{
		fout4 << vec14[i] << "    " << -vec24[i] << endl;
	}
	for (int i = vec15.size() - 1; i >= 0; i--)
	{
		fout5 << vec15[i] << "    " << -vec25[i] << endl;
	}

	fout1 << vec11[0] << "    " << vec21[0] << endl;
	fout2 << vec12[0] << "    " << vec22[0] << endl;
	fout3 << vec13[0] << "    " << vec23[0] << endl;
	fout4 << vec14[0] << "    " << vec24[0] << endl;
	fout5 << vec15[0] << "    " << vec25[0] << endl;
	
	fout1.close();
	fout2.close();
	fout3.close();
	fout4.close();
	fout5.close();

	vec11.clear();
	vec21.clear();
	vec12.clear();
	vec22.clear();
	vec13.clear();
	vec23.clear();
	vec14.clear();
	vec24.clear();
	vec15.clear();
	vec25.clear();

	////////////////////////////////////////////////////////////

	fout1.open("file11.txt");
	fout2.open("file22.txt");
	fout3.open("file33.txt");
	fout4.open("file44.txt");
	fout5.open("file55.txt");

	foo = 20;
	x11 = x1;

	while (foo <= 420)
	{
		x33 = -22.4888861 / pow(7, 0.5);
		while (  x33 <= (pow(-10 + foo, 0.5) - 22.4888861) / pow(7, 0.5) && x33 >= (-pow(-10 + foo, 0.5) - 22.4888861) / pow(7, 0.5)  )
		{
			x22 = pow((-pow(pow(7, 0.5)*x33 + 22.4888861, 2) - 10 + foo) / 5, 0.5);
			switch (foo)
			{
			case 20:
				vec11.push_back(x33);
				vec21.push_back(x22);
				break;
			case 120:
				vec12.push_back(x33);
				vec22.push_back(x22);
				break;
			case 220:
				vec13.push_back(x33);
				vec23.push_back(x22);
				break;
			case 320:
				vec14.push_back(x33);
				vec24.push_back(x22);
				break;
			case 420:
				vec15.push_back(x33);
				vec25.push_back(x22);
				break;
			}
			x33 = x33 + 0.1;
		}
		x33 = -22.4888861 / pow(7, 0.5) - 0.1;
		while (  x33 <= (pow(-10 + foo, 0.5) - 22.4888861) / pow(7, 0.5) && x33 >= (-pow(-10 + foo, 0.5) - 22.4888861) / pow(7, 0.5)  )
		{
			x22 = pow((-pow(pow(7, 0.5)*x33 + 22.4888861, 2) - 10 + foo) / 5, 0.5);
			switch (foo)
			{
			case 20:
				vec11.push_back(x33);
				vec21.push_back(x22);
				break;
			case 120:
				vec12.push_back(x33);
				vec22.push_back(x22);
				break;
			case 220:
				vec13.push_back(x33);
				vec23.push_back(x22);
				break;
			case 320:
				vec14.push_back(x33);
				vec24.push_back(x22);
				break;
			case 420:
				vec15.push_back(x33);
				vec25.push_back(x22);
				break;
			}
			x33 = x33 - 0.1;
		}
		foo += 100;
	}


	SelectionSort(vec11, vec21, vec11.size());
	for (int i = 0; i < vec11.size(); i++)
	{
		fout1 << vec11[i] << "    " << vec21[i] << endl;
	}
	SelectionSort(vec12, vec22, vec12.size());
	for (int i = 0; i < vec12.size(); i++)
	{
		fout2 << vec12[i] << "    " << vec22[i] << endl;
	}
	SelectionSort(vec13, vec23, vec13.size());
	for (int i = 0; i < vec13.size(); i++)
	{
		fout3 << vec13[i] << "    " << vec23[i] << endl;
	}
	SelectionSort(vec14, vec24, vec14.size());
	for (int i = 0; i < vec14.size(); i++)
	{
		fout4 << vec14[i] << "    " << vec24[i] << endl;
	}
	SelectionSort(vec15, vec25, vec15.size());
	for (int i = 0; i < vec15.size(); i++)
	{
		fout5 << vec15[i] << "    " << vec25[i] << endl;
	}


	for (int i = vec11.size() - 1; i >= 0; i--)
	{
		fout1 << vec11[i] << "    " << -vec21[i] << endl;
	}
	for (int i = vec12.size() - 1; i >= 0; i--)
	{
		fout2 << vec12[i] << "    " << -vec22[i] << endl;
	}
	for (int i = vec13.size() - 1; i >= 0; i--)
	{
		fout3 << vec13[i] << "    " << -vec23[i] << endl;
	}
	for (int i = vec14.size() - 1; i >= 0; i--)
	{
		fout4 << vec14[i] << "    " << -vec24[i] << endl;
	}
	for (int i = vec15.size() - 1; i >= 0; i--)
	{
		fout5 << vec15[i] << "    " << -vec25[i] << endl;
	}

	fout1 << vec11[0] << "    " << vec21[0] << endl;
	fout2 << vec12[0] << "    " << vec22[0] << endl;
	fout3 << vec13[0] << "    " << vec23[0] << endl;
	fout4 << vec14[0] << "    " << vec24[0] << endl;
	fout5 << vec15[0] << "    " << vec25[0] << endl;

	fout1.close();
	fout2.close();
	fout3.close();
	fout4.close();
	fout5.close();

	vec11.clear();
	vec21.clear();
	vec12.clear();
	vec22.clear();
	vec13.clear();
	vec23.clear();
	vec14.clear();
	vec24.clear();
	vec15.clear();
	vec25.clear();

	///////////////////////////////////////////////////////////////
	

	fout1.open("file111.txt");
	fout2.open("file222.txt");
	fout3.open("file333.txt");
	fout4.open("file444.txt");
	fout5.open("file555.txt");

	foo = 20;
	x22 = x2;

	while (foo <= 420)
	{
		x33 = -22.4888861 / pow(7, 0.5);
		while (x33 <= (pow(-10 + foo, 0.5) - 22.4888861) / pow(7, 0.5) && x33 >= (-pow(-10 + foo, 0.5) - 22.4888861) / pow(7, 0.5))
		{
			x11 = pow((-pow(pow(7, 0.5)*x33 + 22.4888861, 2) - 10 + foo), 0.5);
			switch (foo)
			{
			case 20:
				vec11.push_back(x33);
				vec21.push_back(-4 + x11);
				break;
			case 120:
				vec12.push_back(x33);
				vec22.push_back(-4 + x11);
				break;
			case 220:
				vec13.push_back(x33);
				vec23.push_back(-4 + x11);
				break;
			case 320:
				vec14.push_back(x33);
				vec24.push_back(-4 + x11);
				break;
			case 420:
				vec15.push_back(x33);
				vec25.push_back(-4 + x11);
				break;
			}
			x33 = x33 + 0.1;
		}
		x33 = -22.4888861 / pow(7, 0.5) - 0.1;
		while (x33 <= (pow(-10 + foo, 0.5) - 22.4888861) / pow(7, 0.5) && x33 >= (-pow(-10 + foo, 0.5) - 22.4888861) / pow(7, 0.5))
		{
			x11 = pow((-pow(pow(7, 0.5)*x33 + 22.4888861, 2) - 10 + foo) , 0.5);
			switch (foo)
			{
			case 20:
				vec11.push_back(x33);
				vec21.push_back(-4 + x11);
				break;
			case 120:
				vec12.push_back(x33);
				vec22.push_back(-4 + x11);
				break;
			case 220:
				vec13.push_back(x33);
				vec23.push_back(-4 + x11);
				break;
			case 320:
				vec14.push_back(x33);
				vec24.push_back(-4 + x11);
				break;
			case 420:
				vec15.push_back(x33);
				vec25.push_back(-4 + x11);
				break;
			}
			x33 = x33 - 0.1;
		}
		foo += 100;
	}


	SelectionSort(vec11, vec21, vec11.size());
	for (int i = 0; i < vec11.size(); i++)
	{
		fout1 << vec11[i] << "    " << vec21[i] << endl;
	}
	SelectionSort(vec12, vec22, vec12.size());
	for (int i = 0; i < vec12.size(); i++)
	{
		fout2 << vec12[i] << "    " << vec22[i] << endl;
	}
	SelectionSort(vec13, vec23, vec13.size());
	for (int i = 0; i < vec13.size(); i++)
	{
		fout3 << vec13[i] << "    " << vec23[i] << endl;
	}
	SelectionSort(vec14, vec24, vec14.size());
	for (int i = 0; i < vec14.size(); i++)
	{
		fout4 << vec14[i] << "    " << vec24[i] << endl;
	}
	SelectionSort(vec15, vec25, vec15.size());
	for (int i = 0; i < vec15.size(); i++)
	{
		fout5 << vec15[i] << "    " << vec25[i] << endl;
	}


	for (int i = vec11.size() - 1; i >= 0; i--)
	{
		fout1 << vec11[i] << "    " << -8 - vec21[i] << endl;
	}
	for (int i = vec12.size() - 1; i >= 0; i--)
	{
		fout2 << vec12[i] << "    " << -8 - vec22[i] << endl;
	}
	for (int i = vec13.size() - 1; i >= 0; i--)
	{
		fout3 << vec13[i] << "    " << -8 - vec23[i] << endl;
	}
	for (int i = vec14.size() - 1; i >= 0; i--)
	{
		fout4 << vec14[i] << "    " << -8 - vec24[i] << endl;
	}
	for (int i = vec15.size() - 1; i >= 0; i--)
	{
		fout5 << vec15[i] << "    " << -8 - vec25[i] << endl;
	}

	fout1 << vec11[0] << "    " << vec21[0] << endl;
	fout2 << vec12[0] << "    " << vec22[0] << endl;
	fout3 << vec13[0] << "    " << vec23[0] << endl;
	fout4 << vec14[0] << "    " << vec24[0] << endl;
	fout5 << vec15[0] << "    " << vec25[0] << endl;

	fout1.close();
	fout2.close();
	fout3.close();
	fout4.close();
	fout5.close();

	vec11.clear();
	vec21.clear();
	vec12.clear();
	vec22.clear();
	vec13.clear();
	vec23.clear();
	vec14.clear();
	vec24.clear();
	vec15.clear();
	vec25.clear();






	///////////////////////////////////////////////////////////////



	system("pause");
	return 0;
}