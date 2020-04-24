#pragma once 
#include<iostream>
#include "Graph.h"
#include<vector>
#include<list>
#include<stack>

using namespace std;

Graph AlgPrima(Graph A)
{
	cout << "Prim Algorithm MST: " << endl;

	int size = A.NumV();
	Graph MST = A;
	MST.NULLGraph();

	if (size < 3)
	{
		//A.print2();
		return A;
		cout << endl;
	}

	int edge = 0;            
	vector<int> selected(size, false);

	selected[0] = true;

	node *pair;
	pair = new node;
	vector<int> st(2,0);

	while (edge < size - 1)
	{
		pair -> v1 = 0;
		pair -> v2 = 0;
		pair -> w = 1e+10;
		pair -> str = st;
		for (int i = 0; i < size; i ++)
		{
			if (selected[i])
			{
				for (int j = 0; j < A[i].size(); j ++)
				{
					if (A[i][j] -> v1 != i)
						swap(A[i][j] -> v1, A[i][j] -> v2);
					if (!selected[A[i][j] -> v2])
					{
						if ((A[i][j] -> w < pair -> w) && (!MST.Edges(A[i][j] -> v1, A[i][j] -> v2)))
						 {
							 pair -> v1 = A[i][j] -> v1;
							 pair -> v2 = A[i][j] -> v2;
							 pair -> w = A[i][j] -> w;
						 }
					}
				}
			}
		}

		MST.addEdges2(pair -> v1, pair -> v2, pair -> w, pair -> str);
		selected[pair -> v2] = true;
		edge++;
	}
	//MST.print2();
	return MST;
}

Graph Alg1(Graph A)
{
	cout << "Alg1  MST:  " << endl;

	if (A.NumV() < 3)
	{
		cout << endl;
		//A.print();
		return A;
	} 

	Graph C = A;
	int edges = A.NumE();
	Graph MST = A;
	MST.NULLGraph();
	int flag = 0;

	while (edges != 0)
	{
		//Временный граф на том же множестве вершин 
		Graph B = C;
		B.NULLGraph();
		for (int i = 0; i < B.NumV(); i ++)
		{
			node *min;
			min = new node();
			min = C.MinEdges(i);
			B.addEdges2(min -> v1, min -> v2, min -> w, min -> str);
		}

		if (edges == A.NumE())
			MST = B;

		//Собираем МСТ 
		if (flag == 1)
		{
			if (B.NumE() == 0)
				return MST;

			stack<node*> st;
			for (int i = 0; i < B.NumV(); i ++)
			{
				for (int j = 0; j < B[i].size(); j ++)
				{
					st.push(B[i][j]);
				}
			}
			
			while (!st.empty())
			{
				node* p = st.top();
				st.pop();
				MST.addEdges2(p -> str[0], p -> str[1], p -> w, p -> str);
			}
			
		}
		//

		//Поиск компонент связности
		int cur = 0;
		vector <int> was(B.NumV(), -1);
		stack <int> q;
		for (int i = 0; i < B.NumV(); i++)
		{
			if (was[i] != -1)
				continue;
			q.push(i);
			while (!q.empty())
			{
				int v = q.top();
				q.pop();
				if (was[v] != -1)
					continue;
				was[v] = cur;
				
				for (int it = 0; it < B[v].size(); it++)
				{
					if (((B[v][it]) -> w != 0) && (was[(B[v][it]) -> v2] == -1))
					{
						q.push((B[v][it]) -> v2);
					}
				}
			}
			cur++;
		}
		
		/*
		cout << endl;
		for (int i = 0; i < was.size(); i++)
		{
			cout << "---" << was[i]; 
		}
		cout << endl;
		*/

		//Перенумеровка 
		B.NULLGraph();
		for (int i = 0; i < B.NumV(); i ++)
		{
			vector<node*> l;
			l = C.ListVertices(i);
			B.AddVertices1(was[i], was, l);
		}
		C.NULLGraph();
		C = B; 

		//Очистка
		C.clearing();

		edges = C.NumE();
		flag = 1;
		/*
		cout << "C: " << endl;
		C.print();
		cout << endl;
		cout << "nE   " << C.NumE() << endl;
		cout << "nV   " << C.NumV() << endl;
		*/
		
	}

	//MST.print2();
	return MST;
}