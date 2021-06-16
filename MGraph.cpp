#include<iostream>
#include<stack>
#include<queue>
using namespace std;

const int MAXSIZE = 20;

template<class T> class MGraph
{
public:
	MGraph(int ver, T v[], int arc, int a[][2]);
	void DFS(int v);
	void BFS(int v);
private:
	T vertex[MAXSIZE] = {0};
	bool arc[MAXSIZE][MAXSIZE] = {0};
	int vNum,arcNum;
};
template<class T>
MGraph<T>::MGraph(int verN, T v[], int arcN, int a[][2])
{
	vNum = verN;
	arcNum = arcN;
	for (int i = 0; i < verN; i++)
	{
		vertex[i] = v[i];
	}
	for (int i = 0; i < arcN; i++)
	{
		arc[a[i][0]][a[i][1]] = true;
		arc[a[i][1]][a[i][0]] = true;
	}
}
template<class T>
void MGraph<T>::DFS(int v)
{
	bool visted[MAXSIZE] = {0};
	stack<int> vistedNodes;
	int now;

	cout<<vertex[v]<<endl;
	vistedNodes.push(v);
	visted[v] = true;

	while (!vistedNodes.empty())
	{
		now = vistedNodes.top();
		for (int i = 0; i < vNum; i++)
			if (!visted[i] && arc[now][i])
			{
				cout<<vertex[i]<<endl;
				vistedNodes.push(i);
				visted[i] = true;
				break;
			}
		if (now == vistedNodes.top())
		{
			vistedNodes.pop();
		}
	}
}
template<class T>
void MGraph<T>::BFS(int v)
{
	bool visted[MAXSIZE] = {0};
	queue<int> vistedNodes;
	int now;

	vistedNodes.push(v);
	visted[v] = true;

	while(!vistedNodes.empty())
	{
		now = vistedNodes.front();
		vistedNodes.pop();
		cout<<vertex[now]<<endl;
		for(int i=0;i<vNum;i++)
			if(!visted[i] && arc[now][i])
			{
				vistedNodes.push(i);
				visted[i] = true;
			}
	}
}

int main()
{
	int v[6] = {1,2,3,4,5,6};
	int a[6][2] = {{0,5},{0,1},{0,2},{1,2},{2,3},{1,4}};
	MGraph<int> *graph = new MGraph<int>(6,v,6,a);

	cout<<"\nDFS:\n";
	graph->DFS(0);
	cout<<"\nBFS:\n";
	graph->BFS(0);

	delete graph;

}