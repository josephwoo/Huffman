#include <iostream>
#include <cstdlib>

using namespace std;

template<typename T>
class MinHeap
{
    private:
    T* array ;              //存放堆数据的数组
    int currentSize ;       //当前堆中元素的数目

    public:
        MinHeap(int max)
        {
            this->array       = new T[max] ;
            this->currentSize = 0 ;
        }

        void insert(T) ;
        void buildHeap() ;
        void shiftDown(int) ;           //筛选法函数，参数left表示开始处理的数组下标
        T removeMin() ;
};

template <typename T>
void MinHeap<T>::insert(T item)
{
    array[currentSize] = item ;
    currentSize ++ ;

}

template <typename T>
T MinHeap<T>::removeMin()
{
    if(currentSize == 0)
		return T() ;

    else
    {
        buildHeap() ;
        swap( array[0], array[currentSize-1] ) ;
        currentSize -- ;
        return array[currentSize] ;
    }
}

template <typename T>
void MinHeap<T>::buildHeap()
{
    for (int i = currentSize/2-1; i>=0; i--)
        shiftDown(i) ;
}

template <typename T>
void MinHeap<T>::shiftDown(int left)
{
    T temp = array[left] ;                 //保存父节点的值
    int i    = left ;                      //标识父节点
    int j    = i*2+1 ;                     //标识子节点

    while( j<currentSize )
    {
        if( j<currentSize-1 && array[j]>array[j+1] )                //该节点有右孩子且右孩子的值大于左孩子的值时，j指向右子节点
            j ++ ;
        if( temp>array[j] )             //当前temp节点的值小于左右孩子中比较大的那个时
        {
            array[i] = array[j] ;       //交换对应值
            i = j ;
            j = 2*i+1 ;             //向下继续判断
        }
        else
            break ;
    }
    array[i] = temp ;
}


