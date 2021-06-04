#include<iostream>
#include<queue>

#define SIZE 7

using namespace std;

const short dir[8][2] = {{-1,-1},{0,-1},{1,-1},{-1,0}
,{1,0},{-1,1},{0,1},{1,1}};

struct Position
{
	int x, y;
};
Position Neighboor(Position index, int id, int N) // 返回相邻坐标
{
	int xx, yy;
	xx = index.x + dir[id][0];
	yy = index.y + dir[id][1];
	Position res;
	res.x = -1;
	res.y = -1;
	if(xx >= 0 && xx < N && yy >= 0 && yy < N)
	{
		res.x = xx;
		res.y = yy;
	}
	return res;
}
int FindBlack(bool **graph, Position *list, int n) //搜索所有黑块
{
	int k=0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(graph[i][j])
			{
				Position *pos = new Position();
				pos->x = i;
				pos->y = j;
				list[k++] = *pos;
				delete pos;
			}
		}
		
	}
	return k;
	
}
void MarkingGroup(int N, bool **orgGraph, Position *list, int num, int **groupGraph) //分组
{
	queue<Position> group;
	int groupNum = 1;
	for (int i = 0; i < N; i++)
	{
		Position pos = list[i];
		if(!groupGraph[pos.x][pos.y]) continue;//剔除已分组的黑块
		group.push(pos);// 将黑块入队
		while ( !group.empty() )// 判断是否还有黑块
		{
			Position nowPos = group.front();
			group.pop();
			// 标记出队黑块
			groupGraph[nowPos.x][nowPos.y] = groupNum;
			// 寻找相邻黑块
			for (int id = 0; id < 8; id++)
			{
				Position neighboor = Neighboor(nowPos, id, N);
				if(neighboor.y == -1) continue;
				if(orgGraph[neighboor.x][neighboor.y]) group.push(neighboor);
			}
			// 将相邻黑块入队
			// 无相邻黑块后出队
		}// 已搜索完
		// 组+1
		groupNum++;
	}
}

int main()
{
	int n;
	cin >> n;
	bool **graph;
	int **res;
	graph = new bool *[n];
	res = new int *[n];
	for (int i = 0;i<n;i++)
	{
		char* input;
		graph[i] = new bool[n];
		res[i] = new int[n];
		cin >> input;
		for (int j = 0; j<n; j++)
			graph[i][j] = input[j] - '0';
	}
	Position *blackList = new Position[n*n];
	int blackNum = FindBlack(graph, blackList, n);
	MarkingGroup(n, graph, blackList, blackNum, res);
	cout<<endl;
	for (int i = 0;i<n;i++)
	{
		for (int j = 0; j<n; j++)
			cout<<res[i][j];
		cout<<endl;
	}
	return 0;
}