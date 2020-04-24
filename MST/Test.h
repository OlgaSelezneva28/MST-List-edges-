#pragma once
#include<iostream>
#include "Graph.h"
#include"Algorithms.h"
#include<time.h>
using namespace std;

//Создает рандомный граф размера n и выполняет для него алгориты Прима и Алгоритм 1
void test1()
{
	cout << "Test 1: " << endl;
	int n;
	cout << "Enter n: " ;
	cin >> n;
	cout << endl;
	Graph a(n);
	//Graph b = a;
	//Graph c = a;
	//cout << "Graph: " << endl;
	//b.print2();
	//c.InMatrix();
	//cout << endl;
	Graph P = AlgPrima(a);
	P.print2();
	cout << endl;
	Graph A1 = Alg1(a);
	A1.print2();
}

//Создает Графы от 3 до ... и выполняет алгоритмы Прима и Алгоритм 1 
void test2()
{
	cout << "Test 2" << endl;
	int n;
	cin >> n;
	cout << "Enter n:  " << endl;
	for (int i = 3; i < n; i ++)
	{
		Graph a(n);
		cout << i << endl;
		cout << endl;
		AlgPrima(a);
		
		Alg1(a);
	}
}

//Сравнит дают ли алгоритмы Прима и Алгоритм 1 одинаковые результаты для графа с 3-n вершинами 
void test3()
{
	cout << "Test3: " << endl;
	int n;
	cout << "Enter n:  ";
	cin >> n;

	for (int i = 3; i < n; i ++)
	{
		cout << "  " << i << endl;
		Graph a(i);
		Graph Prim = AlgPrima(a);
		Graph A1 = Alg1(a);

		int P = Prim.inVector();
		int A = A1.inVector();

		if (P == A)
			cout << "+++++++++++++++" << endl;
		else
			cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
	}
}

//Время работы Алгоритмов 1 и Прима 
void test4()
{
	cout <<"Test4: " << endl;
	int n;
	cout << "Enter n: " ;
	cin >> n;
	cout << endl;

	Graph a(n);

	int t1 = clock();
	Graph b = AlgPrima(a);
	int t2 = clock();
	cout << endl;
	cout << "Time AlgPrima:    " <<( t2 - t1)<< endl;

	int t3 = clock();
	Graph c = Alg1(a);
	int t4 = clock();
	cout << "Time Alg1:    " <<( t4 - t3)<< endl;
}