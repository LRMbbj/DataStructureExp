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
	bool IsConnected(int v1,int v2);
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

	cout<<vertex[v]<<endl; //输出第一个节点
	vistedNodes.push(v); //第一个节点入栈
	visted[v] = true; //标记已访问第一个节点

	while (!vistedNodes.empty())
	{
		now = vistedNodes.top(); //从栈顶开始搜索
		for (int i = 0; i < vNum; i++)
			if (!visted[i] && arc[now][i]) //有可前进的节点，记录并输出
			{
				cout<<vertex[i]<<endl;
				vistedNodes.push(i);
				visted[i] = true;
				break;
			}
		if (now == vistedNodes.top()) //如果没有前进则回退
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
	visted[v] = true; //起点节点入队并标记

	while(!vistedNodes.empty()) //队列为空代表遍历完成
	{
		now = vistedNodes.front(); //队列首元素出队
		vistedNodes.pop();
		cout<<vertex[now]<<endl; //遍历队首元素
		for(int i=0;i<vNum;i++)
			if(!visted[i] && arc[now][i]) //将所有该节点未标记的联通节点都入队
			{
				vistedNodes.push(i);
				visted[i] = true;
			}
	}
}
template<class T>
bool MGraph<T>::IsConnected(int v1,int v2)
{
	return arc[v1][v2];
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
	cout<<"\nConnected(0->1)?";
	cout<<graph->IsConnected(0,1)<<endl;
	delete graph;

}