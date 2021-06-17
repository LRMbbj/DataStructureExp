#include<iostream>
using namespace std;

template<class T> class BiNode
{
public:
	T data;
	BiNode<T> *lch,*rch;
	BiNode():lch(NULL),rch(NULL){};
};

template<class T> class BST
{
public:
	BST(T r[],int n); //构造函数
	~BST(); //析构函数
	BiNode<T> *Search(T key); //公有搜索函数
	void Insert(T key); //公有插入函数
	bool DeleteBST(T key); //公有删除函数
	void PrintBST(BiNode<T> *&R); //打印函数
	void PrintBST(){PrintBST(Root);} //打印函数
private:
	BiNode<T> *Search(BiNode<T> *&R, T key); //私有搜索函数
	void Insert(BiNode<T> *&R, BiNode<T> *s); //私有插入
	void Delete(BiNode<T> * &R); //私有删除节点
	bool DeleteBST(BiNode<T> *&R, T key); //私有删除
	void ReleaseNode(BiNode<T> *&R); //私有删除节点元素
	BiNode<T> *Root;
};

template<class T>
BST<T>::BST(T r[],int n)
{
	Root = NULL;
	for (int i = 0; i < n; i++)
	{
		BiNode<T> *node = new BiNode<T>();
		node->data = r[i];
		node->lch = NULL;
		node->rch = NULL;
		Insert(Root,node);
	}
	
}
template<class T>
BST<T>::~BST()
{
	ReleaseNode(Root);
}
template<class T>
BiNode<T>* BST<T>::Search(BiNode<T> *&R, T key)
{
	if(R == NULL) return NULL;
	if(key == R->data) return R;
	if(key < R->data)
		return Search(R->lch,key);
	else
		return Search(R->rch,key);
}
template<class T>
void BST<T>::Insert(BiNode<T> *&R, BiNode<T> *s)
{
	if(R == NULL)
		R = s;
	else if(s->data < R->data)
		Insert(R->lch,s);
	else
		Insert(R->rch,s);
}
template<class T>
void BST<T>::Delete(BiNode<T> * &R)
{
	BiNode<T> *q = R;
	if (R->lch == NULL && R->rch == NULL) //叶子节点直接删除
	{
		R = NULL;
		delete q;
	}
	else if(R->rch == NULL) //只有左子节点，将父节点连接到左子节点
	{
		R = R->lch;
		delete q;
	}
	else if(R->lch == NULL) //只有右子节点，将父节点连接到右子节点
	{
		R = R->rch;
		delete q;
	}
	else //左右子节点都有，先复制左子节点，删除左子节点
	{
		BiNode<T> *s = R->lch;
		while (s->rch!=NULL)
		{
			q = s;
			s = s->rch;
		}
		R->data = s->data;
		if( q!= R)
			q->rch = s->lch;
		else
			R->lch = s->lch;
		delete s;
	}
}
template<class T>
bool BST<T>::DeleteBST(BiNode<T> *&R, T key)
{
	if(R == NULL)
		return false;
	
	if(R->data == key)
	{
		Delete(R);
		return true;
	}
	else if(key < R->data)
		return DeleteBST(R->lch, key);
	else
		return DeleteBST(R->rch, key);
}
template<class T>
void BST<T>::ReleaseNode(BiNode<T> *&R)
{
	if(R == NULL)
		return;
	ReleaseNode(R->lch);
	ReleaseNode(R->rch);
	// cout<<"Releasing Node:"<<R->data<<endl;
	delete R;

}

template<class T>
BiNode<T> * BST<T>::Search(T key)
{
	return Search(Root, key);
}
template<class T>
void BST<T>::Insert(T key)
{
	Insert(Root, key);
}
template<class T>
bool BST<T>::DeleteBST(T key)
{
	return DeleteBST(Root, key);
}
template<class T>
void BST<T>::PrintBST(BiNode<T> *&R)
{
	if(R == NULL)
		return;
	PrintBST(R->lch);
	cout<<R->data<<endl;
	PrintBST(R->rch);
}


int main()
{
	int a[] = {2,5,4,8,6,1,7};
	BST<int> *bst = new BST<int>(a,7);
	bst->DeleteBST(5);
	bst->PrintBST();
	delete bst;
}