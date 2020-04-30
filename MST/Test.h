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
	Graph P = Prim(a);
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
		Prim(a);
		
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
		
		Graph Pr = Prim(a);
		int P = Pr.SumWeight();
		cout << P << endl;
		Graph A1 = Alg1(a);
		int A = A1.SumWeight();
		cout << A << endl;

		if (P == A)
			cout << "+++++++++++++++" << endl;
		else
			cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
	}
}

//Время работы Алгоритмов Прима и 1
void test4()
{
	cout <<"Test4: " << endl;
	int n;
	cout << "Enter n: " ;
	cin >> n;
	cout << endl;

	Graph a(n);
	
	int t1 = clock();
	Graph b = Prim(a);
	int t2 = clock();
	cout << endl;
	cout << "Time AlgPrima:    " <<( t2 - t1)<< endl;
	
	int t3 = clock();
	Graph c = Alg1(a);
	int t4 = clock();
	cout << "Time Alg1:    " <<(t4 - t3)<< endl;
}

//Создается ли планарный граф размера от 3 до n 
void test5()
{
	cout <<"Test5: " << endl;
	int n;
	cout << "Enter n:  " << endl;
	cin >> n;
	for (int i = 3; i < n; i ++)
	{
		cout << i << endl;
		Graph a(i);
		if (a.NumE() <= 3*a.NumV() - 6)
			cout << "+" << endl;
		else 
			cout << "----------------------------------------" << endl;
	}
}

//Создает рандомный граф размера n и выполняет для него алгориты Прима и Алгоритм 2
void test6()
{
	cout << "Test6: " << endl;
	int n;
	cout << "Enter n: " ;
	cin >> n;
	cout << endl;
	Graph a(n);
	Graph P = Prim(a);
	P.print2();
	cout << endl;
	Graph A2 = Alg2(a);
	A2.print2();
}

//Сравнит дают ли алгоритмы Прима и Алгоритм 2 одинаковые результаты для графа с 3-n вершинами 
void test7()
{
	
	cout << "Test7: " << endl;
	int n;
	cout << "Enter n:  ";
	cin >> n;

	for (int i = 3; i < n; i ++)
	{
		cout << "  " << i << endl;
		Graph a(i);
		Graph Pr = Prim(a);
		int P = Pr.SumWeight();
		cout << P << endl;
		Graph A2 = Alg2(a);
		int A = A2.SumWeight();
		cout << A << endl;

		if (P == A)
			cout << "+++++++++++++++" << endl;
		else
			cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
	}
}

/*-------------------------------------------------------------------------------------------------------------------*/
//Время работы Алгоритмов Прима, Крускала и 1, 2, Борувки 
void test8()
{
	cout <<"Test8: " << endl;
	int n;
	cout << "Enter n: " ;
	cin >> n;
	cout << endl;

	Graph a(n);

	int t3 = clock();
	Graph c = Alg1(a);
	int t4 = clock();
	cout << "Time Alg1:    " <<(t4 - t3)<< endl;
	cout << endl;

	int t5 = clock();
	Graph d = Alg2(a);
	int t6 = clock();
	cout << "Time Alg2:    " <<(t6 - t5)<< endl;
	cout << endl;

	int t7 = clock();
	Graph e = Kruskal(a);
	int t8 = clock();
	cout << "Time Kruskal:    " <<( t8 - t7)<< endl;
	cout << endl;

	int t9 = clock();
	Graph f = Boruvka(a);
	int t10 = clock();
	cout << "Time Boruvka:    " <<(t10 - t9)<< endl;
	cout << endl;

	int t1 = clock();
	Graph b = Prim(a);
	int t2 = clock();
	cout << "Time Prim:    " <<( t2 - t1)<< endl;
	cout << endl;
}
/*-------------------------------------------------------------------------------------------------------------------*/

//Сравнит дают ли Алгоритм 1 и Алгоритм 2 одинаковые результаты для графа с 3-n вершинами 
void test9()
{
	cout << "Test9: " << endl;
	int n;
	cout << "Enter n:  ";
	cin >> n;

	for (int i = 3; i < n; i ++)
	{
		cout << "  " << i << endl;
		Graph a(i);

		Graph A1 = Alg1(a);
		int A11 = A1.SumWeight();
		cout << A11 << endl;
		Graph A2 = Alg2(a);
		int A22 = A2.SumWeight();
		cout << A22 << endl;

		if (A11 == A22)
			cout << "+++++++++++++++" << endl;
		else
			cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
	}
}

//Создание графа с n вершинами и выполнение для него всех алгоритмов 
void test10()
{
	cout << "Test10: " << endl;
	int n;
	cout << "Enter n:  ";
	cin >> n;

	Graph a(n);
	Graph b = Prim(a);
	int bw = b.SumWeight();
	cout << bw << endl;
	Graph c = Kruskal(a);
	int kw = c.SumWeight();
	cout << kw << endl;
	Graph g = Boruvka(a);
	int gw = g.SumWeight();
	cout << gw << endl;
	Graph d = Boruvka(a);
	int dw = d.SumWeight();
	cout << dw << endl;
	Graph e = Alg1(a);
	int a1w = e.SumWeight();
	cout << a1w << endl;
	Graph f = Alg2(a);
	int a2w = f.SumWeight();
	cout << a2w << endl;

}

//Сравнит дают ли Алгоритм 1 и Алгоритм Борувки одинаковые результаты для графа с 3-n вершинами 
void test11()
{
	cout << "Test11: " << endl;
	int n;
	cout << "Enter n:  ";
	cin >> n;

	for (int i = 3; i < n; i ++)
	{
		cout << "  " << i << endl;
		Graph a(i);

		Graph A1 = Alg1(a);
		int A11 = A1.SumWeight();
		cout << A11 << endl;
		Graph B = Boruvka(a);
		int B2 = B.SumWeight();
		cout << B2 << endl;

		if (A11 == B2)
			cout << "+++++++++++++++" << endl;
		else
			cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
	}
}

//Сравнит дают ли Алгоритм Крускаля и Алгоритм 2 одинаковые результаты для графа с 3-n вершинами 
void test12()
{
	cout << "Test12: " << endl;
	int n;
	cout << "Enter n:  ";
	cin >> n;

	for (int i = 3; i < n; i ++)
	{
		cout << "  " << i << endl;
		Graph a(i);

		Graph A1 = Kruskal(a);
		int A11 = A1.SumWeight();
		cout << A11 << endl;
		Graph A2 = Alg2(a);
		int A22 = A2.SumWeight();
		cout << A22 << endl;

		if (A11 == A22)
			cout << "+++++++++++++++" << endl;
		else
			cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
	}
}