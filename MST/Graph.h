#pragma once
#include<iostream>
#include<vector>
#include<time.h>
#include<list>
#include<stack>
#include<queue>

using namespace std;

struct node
{
	int v1, v2, w;
	vector<int> str; 
};


class Graph
{
	vector<node*> graph;
	int nV, nE;
	vector<int> Degs;
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
		for (int it = 0; it < graph.size(); it++) 
			{ 
				if (((graph[it] -> v1 == V1) && (graph[it] -> v2 == V2)) || (graph[it] -> v2 == V1) && (graph[it] -> v1 == V2))
					return true;
			}
		return false;
	}
	//Степень
	int deg(int V)
	{
		return Degs[V];
	}
	//Добавить Ребро
	void addEdges(int V1, int V2, int W, vector<int> deg)
	{

		if ((deg[V1] == nV - 1) || (deg[V2] == nV - 1) || (Edges(V1,V2)))
		{
			return;
		}

		node* p = new node;
		p->v1 = V1;
		p->str.push_back(p -> v1 );
		p->w = W;
		p->v2 = V2;
		p->str.push_back(p -> v2 );
		graph.push_back(p);

		nE ++;
	}
	//Добавить Ребро которое существует
	void addEdges2(int V1, int V2, int W, vector<int> s)
	{
		if ((Edges(V1,V2)))
		{
			return;
		}

		node* p = new node;
		p->v1 = V1;
		p->str.push_back(s[0]);
		p->w = W;
		p->v2 = V2;
		p->str.push_back(s[1]);
		graph.push_back(p);

		nE ++;
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
		srand(time(NULL));
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

		// Создание пути через все вершины
		for (int i = 0; i < nV; i ++)
		{
			node *p = new node;
			p->v1 = i;
			p->str.push_back(i );
			
			if (i == 0) //(0,1)
			{
				p->v2 = i + 1;
				p->str.push_back(p->v2 );
				p->w = rand()%1000 + 1;
			}
			if (i == nV - 1) //(nV-1,0)
			{ 
				p -> v2 = 0;
				p->str.push_back(p->v2 );
				p -> w = rand()%1000 + 1;
			}
			if ((i != 0) && (i != nV - 1)) //Остальные ребра 
			{
				p -> v2 = i + 1;
				p->str.push_back(p->v2 );
				p -> w = rand()%1000 + 1;
			}
			
			graph.push_back(p);
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
			w = rand()%1000 + 1;
			while((i == j) || (Edges(i,j)))
			{
				i = rand()%nV;
				j = rand()%nV;
			}
			int k = graph.size();
			addEdges(i, j, w, DegsV);
			//nE ++;
			if (graph.size() != k)
			{
				DegsV[i] ++;
				DegsV[j] ++;
 			}
		}

		Degs = DegsV;
	}
	Graph(){}
	Graph(const Graph & klass) 
	{
		nV = klass.nV;
		nE = klass.nE;
		graph.clear();
		Degs.clear();
		for (int i = 0; i < klass.nE; i ++)
		{
			node* k = new node;
			k -> v1 = klass.graph[i] -> v1;
			k -> v2 = klass.graph[i] -> v2;
			k -> w = klass.graph[i] -> w;
			k -> str.push_back( klass.graph[i] -> str[0]);
			k -> str.push_back( klass.graph[i] -> str[1]);

			graph.push_back(k);
		}
		for (int i = 0; i < klass.nV; i ++)
		{
			Degs.push_back(klass.Degs[i]);
		}

	}
	Graph & operator=(const Graph & klass) 
	{
		if (this != &klass) 
		{
			graph.clear();
			Degs.clear();
			nV = klass.nV;
			nE = klass.nE;
			for (int i = 0; i < klass.nE; i ++)
				graph.push_back(klass.graph[i]);
			for (int i = 0; i < klass.nV; i ++)
				Degs.push_back(klass.Degs[i]);
		}
		
		return *this;
	}

	//Зануление графа
	void NULLGraph()
	{
		graph.clear();
		nE = 0;
	}
	node* & operator[] (const int index)
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
	//Степени вершин
	vector<int> NumD()
	{
		return Degs;
	}
	//Считает сколько ребер в графе
	int NEdges()
	{
		return graph.size();
	}
	//Возвращает ребро минимального веса 
	node* MinEdges(int V1)
	{
		if (graph.size() == 0)
			exit(0);

		node *V2;
		V2 = new node;
		V2 -> v1 = 0;
		V2 -> v2 = 0;
		V2 -> w = 1e+10;
		for(int i = 0; i < 2; i ++)
		{
			V2 -> str.push_back(0);
		}

		for (int j = 0; j < graph.size(); j ++)
		{
			if ((( (graph[j] -> v1 == V1)) || (graph[j] -> v2 == V1)) && (graph[j] -> w < V2 -> w))
			{
				V2 -> v1 = graph[j] -> v1;
				V2 -> v2 = graph[j] -> v2;
				V2 -> w = graph[j] -> w;
				for(int i = 0; i < 2; i ++)
				{
					V2 -> str[i] = graph[j] ->str[i];
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
	//Удаляет все вершины из v и добавляет их обратно с др концом 
	void DelEdges1(int V, int end)
	{
		stack<node*> st;
		auto iter = graph.begin();
		for (int i = 0; i < graph.size(); i ++)
		{
			if ((graph[i] -> v1 == V) || (graph[i] -> v2 == V))
			{
				st.push(graph[i]);
				graph.erase(iter + i);
				iter = graph.begin();
				i --;
			}
			if (!st.empty())
			{
				node * e = st.top();
				st.pop();
				if (e -> v1 == V)
					e -> v1 = end;
				if (e -> v2 == V)
					e -> v2 = end;
				if (e -> v1 != e -> v2)
					graph.push_back(e);
				else
					nE --;
			}
		}
		nV --;
		Degs[end] += Degs[V] - 2;//Общее ребро ушло 
		Degs[V] = 1e+10;
	}
	//Переименовывает вершины
	void newname(vector<int> new_name)
	{
		auto iter = graph.begin();
		for(int it = 0; it < graph.size(); it ++)
		{
			graph[it] -> v1 = new_name[graph[it] -> v1];
			graph[it] -> v2 = new_name[graph[it] -> v2];

			if (graph[it] -> v1 == graph[it] -> v2)
			{
				graph.erase(iter + it);
				iter = graph.begin();
				nE --;
				it--;
			}
				
		}
		graph.resize(nE);
	}


	//Переустанавливает количество вершин
	void Vertices(int cur)
	{
		nV = cur;
	}
	//Переустанавливает количество ребер
	void NewEdges(int E)
	{
		nE = E;
	}
	//Поменять степень вершины
	void newDeg(int V)
	{
		Degs[V] ++;
	}


	//Получить список смежных вершин
	vector<node*> ListVertices(int V)
	{
		vector<node*> List;
		for (int i = 0; i < graph.size(); i ++)
		{
			if ((graph[i] -> v1 == V) || (graph[i] -> v2 == V))
				List.push_back(graph[i]);
		}
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
	void Merge(int first, int last)
	{
		int middle, start, final;
		vector<node*> mas;
		mas.resize(last + 1);
		middle = (first + last)/2; //вычисление среднего элемента
		start = first; //начало левой части
		final = middle + 1; //начало правой части
		for(int j = first; j <= last; j++) //выполнять от начала до конца
		if ((start <= middle) && ((final > last) || (less(graph[start],graph[final]))))
		{
			mas[j] = graph[start];
			start++;
		}
		else
		{
			mas[j] = graph[final];
			final++;
		}
		//возвращение результата в список
		for (int j = first; j < mas.size(); j++) 
		{
			graph[j] = mas[j];
		}
			
		mas.clear();
	}
	//рекурсивная процедура сортировки
	void MergeSort(int first, int last)
	{
		if (first < last)
			{
				MergeSort( first, (first + last)/2); //сортировка левой части
				MergeSort( (first + last)/2 + 1, last); //сортировка правой части
				Merge( first, last); //слияние двух частей
			}
	}

	//Очистка
	void clearing()
	{
		for (int i = 0; i < graph.size(); i ++)
		{
			if (graph[i] -> v1 > graph[i] -> v2)
				swap(graph[i] -> v1,graph[i] -> v2);
		}
		//Сортировка
		MergeSort(0, graph.size() - 1);
		
		//Удаление параллельных ребер и нулевых вершин 
		auto iter = graph.cbegin();
		for (int i = 1; i < graph.size(); i ++)
		{
			if ((((graph[i - 1]) -> v1 == (graph[i] -> v1)) && (graph[i - 1] -> v2) == (graph[i] -> v2)))
			{
				graph.erase(iter + i);
				nE --;
				iter = graph.begin();
				i --;
			}
		}
		graph.resize(nE);
	}

	//Печать 
	void print()
	{
		int SumWeight = 0;
		if(graph.size() == 0)
		{
			return ;
		}

		for (int i = 0; i < graph.size(); i ++)
		{
			cout <<(graph[i])->v1 << "--" << (graph[i])->v2 << ":   " << (graph[i])->w << endl;
			SumWeight += graph[i] -> w;
		}
		cout << "Total weight:  " << SumWeight << endl;
	}
	//Красивая печать 
	void print2()
	{
		int SumWeight = 0;
		if (graph.size() == 0)
			return;

		clearing();

		for (int i = 0; i < graph.size(); i ++)
		{
			cout << i << "   "<< "( " << graph[i] -> v1 << " , " << graph[i] -> v2 << " ) " << "weight: " << graph[i] -> w << endl; 
			SumWeight += graph[i] -> w;
			
		}

		cout << "Total weight:  " << SumWeight << endl;
	}
	//Сумма ребер 
	int SumWeight()
	{
		int sum = 0;
		for (int i = 0; i < graph.size(); i ++)
			sum += graph[i] -> w;

		return sum;
	}

	//Перевод в матрицу 
	void InMatrix()
	{
		vector<vector<int>> Matrix;
		Matrix.resize(nV);
		for (int i = 0; i <nV; i ++)
		{
			Matrix[i].resize(nV);
		}
		for(int i = 0; i < Matrix.size(); i ++)
			for (int j = 0; j < Matrix[i].size(); j ++)
				Matrix[i][j] = 0;


		for (int i = 0; i < graph.size(); i ++)
		{
			int v1 = graph[i] -> v1;
			int v2 = graph[i] -> v2;
			int w = graph[i] -> w;
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


};