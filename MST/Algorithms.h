#pragma once 
#include<iostream>
#include "Graph.h"
#include<vector>
#include<list>
#include<stack>
#include<queue>


using namespace std;


Graph Prim(Graph A)
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
				for (int j = 0; j < A.NumE(); j ++)
				{
					if (A[j] -> v1 != i)
						swap(A[j] -> v1, A[j] -> v2);
					if (A[j] -> v1 != i)
						continue;
					if (!selected[A[j] -> v2])
					{
						if ((A[j] -> w < pair -> w) && (!MST.Edges(A[j] -> v1, A[j] -> v2)))
						 {
							 pair -> v1 = A[j] -> v1;
							 pair -> v2 = A[j] -> v2;
							 pair -> w = A[j] -> w;
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
	

	return 0;
}

Graph Kruskal(Graph A)
{
	cout << "Kruskal Algorithm MST: " << endl;

	int size = A.NumV();
	Graph MST = A;
	MST.NULLGraph();

	if (size < 3)
	{
		//A.print2();
		return A;
		cout << endl;
	}
	Graph C = A;
	int edges = 0; 
	vector<vector<int>> comp;
	comp.resize(A.NumV());
	for(int i = 0; i < A.NumV(); i ++)
		comp[i].push_back(i);
	for (int i = 0; i < A.NumE(); i ++)
	{
		C[i] -> v1 = 1;
		C[i] -> v2 = 2;
	}
	C.MergeSort(0, A.NumE() - 1);
	queue<node*> q;
	for (int i = 0; i < A.NumE(); i ++)
	{
		C[i] -> v1 = C[i] -> str[0];
		C[i] -> v2 = C[i] -> str[1];
		q.push(C[i]);
	}
	while(edges != size - 1)
	{
		while  ((comp.size() > 1) && (!q.empty()))
		{
			node* e = q.front();
			q. pop();

			int e1 = -1, e2 = -1;
			for (int i = 0; i < comp.size(); i ++)
			{
				if ((e1 != -1) && (e2 != -1))
					break;
				for (int j = 0; j < comp[i].size(); j++)
				{
					if ((e1 != -1) && (e2 != -1))
						break;
					if (comp[i][j] == e -> v1)
						e1 = i;
					if (comp[i][j] == e -> v2)
						e2 = i;
				}
			}
			if (e1 != e2)
			{
				auto iter = comp.begin();
				comp[e1].insert(comp[e1].begin(), comp[e2].begin(), comp[e2].end());
				comp.erase(iter + e2);
				MST.addEdges2(e -> v1, e -> v2, e -> w, e -> str);
				edges++;
			}

		}
		
	}

	return MST;
}

struct  subset
{
	int parent; 
	int rank;
};

int find(vector<subset*> sets, int i)
{
    if (sets[i] -> parent != i)
      sets[i] -> parent = find(sets, sets[i] -> parent);

    return sets[i] -> parent;
}

void Union(vector<subset*> sets, int x, int y)
{
    int xroot = find(sets, x);
    int yroot = find(sets, y);

    // Прикрепить дерево меньшего ранга под корень высокого
    // (объединение по рангу)

    if (sets[xroot] -> rank < sets[yroot] -> rank)
        sets[xroot] -> parent = yroot;
    else 
		if (sets[xroot] -> rank > sets[yroot] -> rank)
			sets[yroot] -> parent = xroot;
		else // Если ранги одинаковы, то создаем их как root
    {
        sets[yroot] -> parent = xroot;
        sets[xroot] -> rank++;
    }
}

Graph Boruvka(Graph A)
{
	cout << "Boruvka Algorithm MST: " << endl;

	Graph MST = A;
	MST.NULLGraph();

	if (A.NumV() < 3)
	{
		//A.print2();
		return A;
		cout << endl;
	}
	
	vector<subset*> set;
	vector<int> cheapest; // Массив для хранения индекса самого дешевого края
	for (int v = 0; v < A.NumV(); v ++)
    {
		subset* s = new subset;
		s -> parent = v;
		s -> rank = 0;
		set.push_back(s); 
		cheapest.push_back(-1); 
    }

	int numTrees = A.NumV();

	while (numTrees > 1)
    {
        for (int v = 0; v < A.NumV(); v++)
        {
			cheapest[v] = -1;
        }

        for (int i = 0; i < A.NumE(); i++)
        {
            int set1 = find(set, A[i] -> v1);

            int set2 = find(set, A[i] -> v2);

            if (set1 == set2)
                continue;
            else
            {
               if ((cheapest[set1] == -1) || (A[cheapest[set1]] -> w > A[i] -> w))
                 cheapest[set1] = i;
               if ((cheapest[set2] == -1) || (A[cheapest[set2]] -> w > A[i] -> w))
                 cheapest[set2] = i;
            }
        }

        // в MST
		for (int i = 0; i < A.NumV(); i++)
        {
            // Проверяем, существует ли самый дешевый для текущего набора
            if (cheapest[i] != -1)
            {
                int set1 = find(set, A[cheapest[i]] -> v1);
                int set2 = find(set, A[cheapest[i]] -> v2);
                if (set1 == set2)
                    continue;
				MST.addEdges2(A[cheapest[i]] -> v1, A[cheapest[i]] -> v2, A[cheapest[i]] -> w, A[cheapest[i]] -> str);

                // Делаем объединение set1 и set2 и уменьшаем число
                // деревьев
                Union(set, set1, set2);
                numTrees--;
            }
        }
    }

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
		C.MergeSort(0, C.NumE() - 1);
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

			for (int i = 0; i < B.NumE(); i ++)
			{
				MST.addEdges2(B[i] -> str[0], B[i] -> str[1], B[i] -> w, B[i] -> str);
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

				for (int it = 0; it < B.NumE(); it++)
				{
					if ((B[it] -> v1 == v) || (B[it] -> v2 == v))
					{
						if ((was[(B[it]) -> v2] == -1) && (B[it] -> v1 == v))
							q.push(B[it] -> v2);
						else
							q.push(B[it] -> v1);
					}
				}
			}
			cur++;
		}
		/*
		cout << "was[i]   ";
		for(int i = 0; i < was.size(); i ++)
		{
			cout << was[i] << "--" ;
		}
		*/
		
		//Перенумеровка 
		C.newname(was);
		C.Vertices(cur);
		//Очистка
		C.clearing();

		edges = C.NumE();
		flag = 1;
	}
	
	//MST.print2();
	return MST;
}

Graph Alg2(Graph A)
{
	cout << "Alg2  MST:  " << endl;
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
	
	while (edges != 0)
	{
		int t = 2;
		vector<int> D = C.NumD();
		queue<int> q;
		for (int i = 0; i < D.size(); i ++)
		{
			if (D[i] <= 4*t)
				q.push(i);
		}

		while (!q.empty())
		{
			if (C.NumE() == 0)
				break;

			int v = q.front();
			q.pop();
			//Выбираем самое легкое ребро
			node *min;
			min = new node;
			min = C.MinEdges(v);
			if (MST.NumE() < MST.NumV() - 1)
				MST.addEdges2(min -> str[0], min -> str[1], min -> w, min -> str);

			int end = v;
			if (min -> v1 != v)
				end = min -> v1;
			else 
				end = min -> v2;
			C.DelEdges1(v, end);
		}

		C.clearing();
		edges = C.NumE();
	}

	return MST;
}