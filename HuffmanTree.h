#include "MinHeap.h"
#include <queue>

template<class T>
class Node{
	public:
		int cnt ;				//字符出现的频率
		char c ;				//字符
		Node* leftChild , *rightChild ;

		Node(){
			cnt       = 0 ;
			c         = '\0' ;
			leftChild = rightChild = NULL ;
		}

		bool operator > (Node<T> node){
            return cnt > node.cnt;
        }
		bool operator < (Node<T> node){
			return cnt < node.cnt ;
		}
/*		void operator = (Node<T> node){
		    this->cnt = node.cnt ;
		    this->c = node.c ;
		    this->leftChild = node.leftChild ;
		    this->rightChild = node.rightChild ;
		}*/
};

template<class T>
class HuffmanTree{
	private:
		void DeleteTree(Node<T>* p) {				//递归删除
			if( p ){
				DeleteTree( p->leftChild  ) ;
				DeleteTree( p->rightChild ) ;
				delete p ;
			}
		}
	public:
		Node<T>* root ;				//Huffman 树的树根
		HuffmanTree(T weight[], int n) ;				//构造Huffman树，weight是权值数组，n是数组长度
		~HuffmanTree(){
			DeleteTree(root) ;
		}
		void MergeTree(Node<T>& ht1, Node<T>& ht2, Node<T>& parent) ;				//把ht1和ht2合并成一棵以parent为根的二叉树
		void print(Node<T>* , string& ) ;
};

template <typename T>
HuffmanTree<T>::HuffmanTree(T weight[], int n)
{
    root = new Node<T>() ;					//为root申请空间，以便之后访问Huffman树，因为parent作用域仅在构造函数中
	char tmpc[n] ;
	int i, size=0 ;
	for(i = 0 ; i < n ; i ++){					//统计出不为0的权值组和size
		if(weight[i] != 0){
			tmpc[size]   = i ;
			weight[size] = weight[i] ;
			cout<<tmpc[size]<<' '<<weight[i] <<endl ;
			size ++ ;
		}
	}

	MinHeap<Node<T> > heap(size) ;					//定义最小堆
	Node<T> parent, firstChild, secondChild ;
	Node<T>* nodeList = new Node<T>[size] ;


	for (i = 0; i < size; ++i)
	{
		nodeList[i].cnt       = weight[i] ;
		nodeList[i].c         = tmpc[i];
		nodeList[i].leftChild = nodeList[i].rightChild = NULL ;
		heap.insert( nodeList[i] ) ;
	}
	for (i = 0; i < size-1; ++i)					//通过n-1次合并建立Huffman树
	{
		firstChild  = heap.removeMin() ;
		secondChild = heap.removeMin() ;

		MergeTree(firstChild, secondChild, parent) ;					//合并权值最小的两棵树

		heap.insert( parent ) ;

	}

	*root = parent ;

	delete []nodeList ;
}

template <typename T>
void HuffmanTree<T>::MergeTree(Node<T>& ht1 , Node<T>& ht2 , Node<T>& parent)
{
	parent.leftChild   = new Node<T>() ;
	parent.rightChild  = new Node<T>() ;

	*parent.leftChild  = ht1 ;
	*parent.rightChild = ht2 ;

	parent.cnt         = ht1.cnt+ht2.cnt ;
}

template <typename T>
void HuffmanTree<T>::print(Node<T>* pointer , string &code)
{
    if(this->root->cnt == -1)
        return ;

    if(pointer->leftChild             && pointer->rightChild
       && pointer->leftChild->cnt==-1 && pointer->rightChild->cnt==-1 )
    {
		pointer->cnt = -1 ;
		pointer      = this->root ;
		code.erase() ;
    	print(pointer, code) ;
    }
	if(pointer->leftChild && pointer->leftChild->cnt != -1){
		code += '0' ;
		print(pointer->leftChild, code) ;
	}
	if(pointer->rightChild && pointer->rightChild->cnt != -1){
		code += '1' ;
		print(pointer->rightChild, code) ;
	}
    if (pointer->c )
    {
    	cout<< pointer->c << ' ' << code << endl ;
		pointer->cnt = -1 ;
		pointer      = this->root ;
    	code.erase() ;
    	print(pointer, code) ;
    }
}
