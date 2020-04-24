#pragma once
#include<iostream>
#include<vector>
#include<time.h>
#include<list>

using namespace std;

struct node
{
	int v1, v2, w;
	vector<int> str;
};


class Graph
{
	vector<vector<node*>> graph;
	int nV, nE;
public:

	//Проверка на планарность
	bool planar()
	{
		if (nE < 3*nV - 6)
			return true;
		else return false;
	}
	//Является ли ребром?
	bool Edges(int V1, int V2)
	{ 
		for (int it = 0; it < graph[V1].size(); it++) 
			{ 
				if (graph[V1][it] -> v2 == V2)
					return true;
			}
		return false;
	}
	//Степень
	int deg(int V)
	{
		return graph[V].size();
	}
	//Добавить Ребро
	void addEdges(int V1, int V2, int W)
	{

		if ((deg(V1) == nV - 1) || (deg(V1) == nV - 1) || (Edges(V1,V2)))
		{
			return;
		}

		node* p = new node;
		p->v1 = V1;
		p->str.push_back(p -> v1 );
		p->w = W;
		p->v2 = V2;
		p->str.push_back(p -> v2 );
		graph[V1].push_back(p);

		node* p2 = new node;
		p2->v1 = V2;
		p2->str.push_back(p2 -> v1 );
		p2->v2 = V1;
		p2->str.push_back(p2 -> v2 );
		p2->w = W;
		graph[V2].push_back(p2);
		nE ++;
	}
	//Добавить Ребро которое существует
	void addEdges2(int V1, int V2, int W, vector<int> s)
	{

		if ((deg(V1) == nV - 1) || (deg(V1) == nV - 1) || (Edges(V1,V2)))
		{
			return;
		}

		node* p = new node;
		p->v1 = V1;
		p->str.push_back(s[0]);
		p->w = W;
		p->v2 = V2;
		p->str.push_back(s[1]);
		graph[V1].push_back(p);

		node* p2 = new node;
		p2->v1 = V2;
		p2->str.push_back(s[1]);
		p2->v2 = V1;
		p2->str.push_back(s[0]);
		p2->w = W;
		graph[V2].push_back(p2);
		nE ++;
	}
	//Добавить вершину
	void addVertices(int V1, int W)
	{
		int V2 = nV;
		nV ++;
		nE++;

		node *nov = new node;
		nov-> v1 = V1;
		nov->str.push_back(nov -> v1 );
		nov -> v2 = V2;
		nov->str.push_back(nov -> v2 );
		nov -> w = W;
		node *nov2 = new node;
		nov2-> v1 = V2;
		nov2->str.push_back(nov2 -> v1 );
		nov2 -> v2 = V1;
		nov2->str.push_back(nov2 -> v2 );
		nov2 -> w = nov -> w;

		graph.resize(nV);
		addEdges(V1,V2,W);
	}
	//Критерии непланарных графов
	bool notplanar(vector<int> DV)
	{
		//K5
		if (nV >= 5)
		{
			int d = 0;
			for (int i = 0; i < DV.size(); i ++) 
			{
				if (DV[i] == 4)
					d++;
			}
			if (d == 5)
				return true;
		}
		//K3,3
		if (nV >= 6)
		{
			int d = 0;
			for (int i = 0; i < DV.size(); i ++) 
			{
				if (DV[i] == 3)
					d++;
			}
			if (d == 6)
				return true;
		}

		int d4 = 0;
		int d5 = 0;
		for (int i = 0; i < DV.size(); i ++) 
			{
				if (DV[i] > 3)
					d4++;
				if (DV[i] > 2)
					d5++;
			}

		if ((d4 > 4) || (d5 > 5))
			return true;

		return false;
	}
	//Конструктор графа
	Graph(int V)
	{
		//srand(time(NULL));
		nV = V;
		if ((nV == 1) || (nV == 0))
		{
			nE = 0;
			return;
		}
		nE = V;
		if (nV == 2)
		{
			nE = 1;
		}
		graph.resize(nV);

		// Создание пути через все вершины
		int wk = 0;
		int wk0 = 0;
		for (int i = 0; i < nV; i ++)
		{
			node *p = new node;
			p->v1 = i;
			p->str.push_back(i );
			
			node *n = new node;
			n -> v1 = i;
			n->str.push_back(i );
			if (i == 0)
			{
				p->v2 = i + 1;
				p->str.push_back(p->v2 );
				p->w = rand()%1000;
				wk = p-> w;
				n->v2 = nV - 1;
				n->str.push_back(n -> v2 );
				n -> w = rand()%1000;
				wk0 = n->w;
			}
			if (i == nV - 1)
			{ 
				p -> v2 = 0;
				p->str.push_back(p->v2 );
				n -> v2 = i - 1;
				n->str.push_back(n -> v2 );
				n -> w = wk;
				p -> w = wk0;
			}
			if ((i != 0) && (i != nV - 1))
			{
				p -> v2 = i - 1;
				p->str.push_back(p->v2 );
				n -> v2 = i + 1;
				n->str.push_back(n -> v2 );
				p -> w = wk;
				n -> w = rand()%1000;
				wk = n -> w;
			}
			vector<node*> l;
			l.push_back(p);
			l.push_back(n);
			graph[i] = l;
		}
		//

		// Добавление дополнительных ребер
		int i;
		int j;
		int w;

		vector<int> DegsV(nV, 2); //Вектор степеней вершин

		while((planar()) && (!notplanar(DegsV)))
		{
			i = rand()%nV;
			j = rand()%nV;
			w = rand()%1000;
			while((i == j) || (Edges(i,j)))
			{
				i = rand()%nV;
				j = rand()%nV;
			}
			addEdges(i, j, w);
			nE ++;
			DegsV[i] = deg(i);
			DegsV[j] = deg(j);
		}
	}
	//Зануление графа
	void NULLGraph()
	{
		graph.clear();
		nE = 0;
		graph.resize(nV);
	}

	vector<node*>& operator[] (const int index)
	{
		return graph[index];
	}

	//Количество вершин
	int NumV()
	{
		return nV;
	}
	//Количество ребер
	int NumE()
	{
		return nE;
	}
	//Возвращает ребро минимального веса 
	node* MinEdges(int V1)
	{
		node *V2;
		V2 = new node;
		V2 -> v1 = graph[V1].front() -> v1;
		V2 -> v2 = graph[V1].front() -> v2;
		V2 -> w = graph[V1].front() -> w;
		for(int i = 0; i < 2; i ++)
		{
			V2 -> str.push_back(graph[V1].front() ->str[i]);
		}

		for (int j = 0; j < graph[V1].size(); j ++)
		{
			if (graph[V1][j] -> w < V2 -> w)
			{
				V2 -> v1 = graph[V1][j] -> v1;
				V2 -> v2 = graph[V1][j] -> v2;
				V2 -> w = graph[V1][j] -> w;
				for(int i = 0; i < 2; i ++)
				{
					V2 -> str[i] = graph[V1][j] ->str[i];
				}
			}
		}

		return V2;
	}

	//Удаляет все вершины начиная с V
	void DelVertices1(int V)
	{
		graph.resize(V);
		nV = graph.size();
	}

	//Добавляет список вершин в другую вершину
	void AddVertices1(int V,vector<int> new_name, vector<node*> l)
	{
		nE += l.size();
		for(int it = 0; it < l.size(); it ++)
		{
			l[it] -> v1 = new_name[l[it] -> v1];
			
			l[it] -> v2 = new_name[l[it] -> v2];

			if (l[it] -> v1 == l[it] -> v2)
				nE--;
			if (l[it] -> v1 != l[it] -> v2)
				graph[V].push_back(l[it]);
		}
	}

	//Получить список смежных вершин
	vector<node*> ListVertices(int V)
	{
		return graph[V];
	}

	//Равны ли две вершины
	bool equally(node*r, node *l)
	{
		bool T = false;
		if ((r -> v1 == l -> v1) && (r -> v2 == l -> v2) && (r -> w == l -> w))
			T = true;
		return T;
	}
	//Сравнение двух вершин
	bool  less(node*min ,node* rl) 
	{
		if (min == rl) 
			return false;
		bool T = false;
		if ((min -> v1 == rl -> v1) && (min-> v2 == rl -> v2) && (min -> w < rl -> w))
			T = true;
		if ((min -> v1 == rl -> v1) && (min -> v2 < rl -> v2))
			T = true;
		if (min -> v1 < rl -> v1)
			T = true;
		return T;
	}
	

	//Сортировка слиянием 
	void Merge(int Vertices, int first, int last)
	{
		int middle, start, final;
		vector<node*> mas;
		mas.resize(last + 1);
		middle = (first + last)/2; //вычисление среднего элемента
		start = first; //начало левой части
		final = middle + 1; //начало правой части
		for(int j = first; j <= last; j++) //выполнять от начала до конца
		if ((start <= middle) && ((final > last) || (less(graph[Vertices][start],graph[Vertices][final]))))
		{
			mas[j] = graph[Vertices][start];
			start++;
		}
		else
		{
			mas[j] = graph[Vertices][final];
			final++;
		}
		//возвращение результата в список
		for (int j = first; j < mas.size(); j++) 
		{
			graph[Vertices][j] = mas[j];
		}
			
		mas.clear();
	}
	//рекурсивная процедура сортировки
	void MergeSort(int Vertices, int first, int last)
	{
		if (first < last)
			{
				MergeSort(Vertices, first, (first + last)/2); //сортировка левой части
				MergeSort(Vertices, (first + last)/2 + 1, last); //сортировка правой части
				Merge(Vertices, first, last); //слияние двух частей
			}
	}

	//Очистка
	void clearing()
	{
		int c = 0;
		for (int i = 0; i < graph.size(); i ++)
		{
			for (int j = 0; j < graph[i].size();j ++)
			{
				if (graph[i][j] -> v1 > graph[i][j] -> v2)
					swap(graph[i][j] -> v1,graph[i][j] -> v2);
			}

			//Сортировка
			MergeSort(i, 0, graph[i].size() - 1);

			//Удаление параллельных ребер и нулевых вершин 
			auto iter = graph[i].cbegin();
			for (int j = 1; j <graph[i].size(); j ++)
			{
				if ((graph[i][j-1] -> v1 == graph[i][j] -> v1) && (graph[i][j-1] -> v2 == graph[i][j] -> v2))
				{
					graph[i].erase(iter + j);
					iter = graph[i].cbegin();
					j --;
					nE --;
				}
			}

			if (deg(i) == 0)
			{
				for (int j = i; j < graph.size() - 1; j ++)
				{
					graph[j] = graph[j + 1];
				}
			}
		}

		nE = nE/2;
		nV = 0;
		for (int i = 0; i < graph.size(); i ++)
		{
			if (deg(i) != 0)
				nV ++;
		}
		graph.resize(nV);
	}

	//Печать 
	void print()
	{
		if(graph.size() == 0)
		{
			return ;
		}

		for (int i = 0; i < graph.size(); i ++)
		{
			vector<node*> l;
			l = graph[i];
			l = graph[i];
			if (l.size() == 0) 
			{
				continue;
			}
			cout << "Vertices  " << i << ":  " << endl; 
 
			for (int it = 0; it < l.size(); it++) 
			{ 
				/*
				for(int k = 0; k < l[it]->str.size(); k ++)
				{
					cout << l[it] -> str[k] << "";
				}
				cout << "       ";
				*/

				cout <<(l[it])->v1 << "--" << (l[it])->v2 << ":   " << (l[it])->w << endl;
			}
		}
	}
	//Красивая печать 
	void print2()
	{
		int SumWeight = 0;
		if (graph.size() == 0)
			return;

		vector<node*> List;

		for (int i = 0; i < graph.size(); i ++)
		{
			for (int j =  0; j < graph[i].size(); j ++)
			{
				List.push_back(graph[i][j]);
			}
		}

		graph.clear();
		graph.resize(1);
		graph[0] = List;
		clearing();

		for (int i = 0; i < graph.size(); i ++)
		{
			for (int j = 0; j < graph[i].size(); j ++)
			{
				cout << j << "   "<< "( " << graph[i][j] -> v1 << " , " << graph[i][j] -> v2 << " ) " << "weight: " << graph[i][j] -> w << endl; 
				SumWeight += graph[i][j] -> w;
			}
		}

		cout << "Total weight:  " << SumWeight << endl;
	}

	//Перевод в матрицу 
	void InMatrix()
	{
		vector<vector<int>> Matrix;
		Matrix.resize(graph.size());
		for (int i = 0; i <graph.size(); i ++)
		{
			Matrix[i].resize(graph.size());
		}
		for(int i = 0; i < Matrix.size(); i ++)
			for (int j = 0; j < Matrix[i].size(); j ++)
				Matrix[i][j] = 0;

		vector<node*> L;

		for (int i = 0; i < graph.size(); i ++)
		{
			for (int j = 0; j < graph[i].size(); j ++)
			{
				L.push_back(graph[i][j]);
			}
		}

		graph.clear();
		graph.resize(1);
		graph[0] = L;
		clearing();

		for (int i = 0; i < graph[0].size(); i ++)
		{
			int v1 = graph[0][i] -> v1;
			int v2 = graph[0][i] -> v2;
			int w = graph[0][i] -> w;
			Matrix[v1][v2] = w;
			Matrix[v2][v1] = w;
		}

		for(int i = 0; i < Matrix.size(); i ++)
		{
			for(int j = 0; j < Matrix[i].size(); j ++)
				cout << Matrix[i][j] << "  ";
			cout << endl;
		}

	}

	//В один вектор, возвращает суммарный вес 
	int inVector()
	{
		int SumWeight = 0;
		if (graph.size() == 0)
			exit(0);

		vector<node*> List;

		for (int i = 0; i < graph.size(); i ++)
		{
			for (int j =  0; j < graph[i].size(); j ++)
			{
				List.push_back(graph[i][j]);
			}
		}

		graph.clear();
		graph.resize(1);
		graph[0] = List;
		clearing();

		for (int i = 0; i < graph.size(); i ++)
		{
			for (int j = 0; j < graph[i].size(); j ++)
			{
				//cout << j << "   "<< "( " << graph[i][j] -> v1 << " , " << graph[i][j] -> v2 << " ) " << "weight: " << graph[i][j] -> w << endl; 
				SumWeight += graph[i][j] -> w;
			}
		}

		cout << "Total weight:  " << SumWeight << endl;
		//return graph[0];
		return SumWeight;
	}
};