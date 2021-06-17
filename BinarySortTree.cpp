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
	BiNode<T> *Search(BiNode<T> *&R, T key);
	void Insert(BiNode<T> *&R, BiNode<T> *s);
	void Delete(BiNode<T> * &R);
	void DeleteBST(BiNode<T> *&R, T key);
private:
	BiNode<T> *Root;
};

template<class T>
BST<T>::BST(T r[],int n)
{

}

template<class T>
BST<T>::~BST()
{

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
	
}
template<class T>
void BST<T>::DeleteBST(BiNode<T> *&R, T key)
{

}

int main()
{
	
}