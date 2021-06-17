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
	BST(T r[],int n);
	~BST();
	BiNode<T> *Search(T key);
	void Insert(T key);
	bool DeleteBST(T key);
private:
	BiNode<T> *Search(BiNode<T> *&R, T key);
	void Insert(BiNode<T> *&R, BiNode<T> *s);
	void Delete(BiNode<T> * &R);
	bool DeleteBST(BiNode<T> *&R, T key);
	void ReleaseNode(BiNode<T> *&R);
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
	if (R->lch == NULL && R->rch == NULL)
	{
		R = NULL;
		delete q;
	}
	else if(R->rch == NULL)
	{
		R = R->lch;
		delete q;
	}
	else if(R->lch == NULL)
	{
		R = R->rch;
		delete q;
	}
	else
	{
		R->data = R->rch->data;
		Delete(R->rch);
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

int main()
{
	int a[] = {2,5,4,8,6,1,7};
	BST<int> *bst = new BST<int>(a,7);
	bst->DeleteBST(5);
	delete bst;
}