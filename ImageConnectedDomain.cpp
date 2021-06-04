#include<fstream>
#include<iostream>
#include<queue>

#define SIZE 7
#define ID_NUM 4

using namespace std;

// const short dir[8][2] = {{-1,-1},{0,-1},{1,-1},{-1,0}
// ,{1,0},{-1,1},{0,1},{1,1}};
const short dir[4][2] = {{0,-1},{-1,0}
,{1,0},{0,1}};

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
	for (int i = 0; i < num; i++)
	{
		Position pos = list[i];
		if(groupGraph[pos.x][pos.y]) continue;//剔除已分组的黑块
		group.push(pos);// 将黑块入队
		printf_s("未搜索黑块入队 %d,%d\n", pos.x, pos.y);
		groupGraph[pos.x][pos.y] = groupNum;
		while ( !group.empty() )// 判断是否还有黑块
		{
			Position nowPos = group.front();
			group.pop();
			printf_s("搜索邻居 %d,%d\n", nowPos.x, nowPos.y);
			for (int id = 0; id < ID_NUM; id++)// 寻找相邻黑块
			{
				Position neighboor = Neighboor(nowPos, id, N);

				if( neighboor.y == -1 || groupGraph[neighboor.x][neighboor.y] ) // 跳过无效位置和已搜索过的位置
					continue;

				if(orgGraph[neighboor.x][neighboor.y]) 
				{
					printf_s(">>黑块入队 %d,%d\n", neighboor.x, neighboor.y);
					group.push(neighboor); // 将相邻黑块入队
					groupGraph[neighboor.x][neighboor.y] = groupNum; // 标记入队黑块
				}
			}

			// 无相邻黑块后出队
		}// 已搜索完
		// 组+1
		groupNum++;
	}
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.in",ios::in);
	fout.open("output.out",ios::out);

	int n;
	fin >> n;
	bool **graph;
	int **res;
	char input[100];
	graph = new bool *[n];
	res = new int *[n];
	for (int i = 0;i<n;i++)
	{
		graph[i] = new bool[n]();
		res[i] = new int[n]();
		fin >> input;
		for (int j = 0; j<n; j++)
			graph[i][j] = input[j] - '0';
	}

	Position *blackList = new Position[n*n]();
	int blackNum = FindBlack(graph, blackList, n);
	MarkingGroup(n, graph, blackList, blackNum, res);

	for (int i = 0;i<n;i++)
	{
		for (int j = 0; j<n; j++)
			fout<<res[i][j];
		fout<<endl;
		delete [] graph[i];
		delete [] res[i];
	}

	delete [] res;
	delete [] graph;
	delete [] blackList;

	fin.close();
	fout.close();

	return 0;

}