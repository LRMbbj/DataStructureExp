#include<iostream>
using namespace std;

template<class T>
struct Node
{
	T data;
	Node<T> *next;
};

template<class T>
class LinkStack
{
public:
	LinkStack(){top = NULL;}
	~LinkStack();
	void Push(T data);
	T Pop();
	T GetTop();
	bool IsEmpty(){return top == NULL;}
private:
	Node<T> *top;
};

template<class T>
void LinkStack<T>::Push(T data)
{
	Node<T> *next = new Node<T>();
	next->data = data; //添加数据
	next->next = top; //指向原栈顶
	top = next;	//更新栈顶
}
template<class T>
LinkStack<T>::~LinkStack()
{
	while (top != NULL)
	{
		Node<T> *p = top;
		top = top->next;
		delete p;
	}
}
template<class T>
T LinkStack<T>::Pop()
{
	if(top != NULL) // 判断栈非空，否则下溢
	{
		T data = top->data; //暂存数据
		Node<T> *p = top; 
		top = top->next; //修改栈顶指针
		delete p;
		return data;
	}
	else throw "下溢";
}
template<class T>
T LinkStack<T>::GetTop()
{
	return top->data;
}

int main()
{
	LinkStack<int> *linkStack = new LinkStack<int>();
	cout<<linkStack->IsEmpty()<<endl;
	for (int i = 0; i <= 20; i++)
	{
		linkStack->Push(i);
	}
	cout<<linkStack->IsEmpty()<<endl;
	cout<<linkStack->GetTop()<<endl;
	cout<<linkStack->Pop()<<endl;
	cout<<linkStack->GetTop()<<endl;
	delete linkStack;
}