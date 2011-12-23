#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <string.h>
/// Important: destructors will not be called when this class is destroyed
template <typename T>
class MyQueue
{
    public:
        MyQueue();
        MyQueue(unsigned int _capacity);
        void push_front(const T& t);
        void push_back(const T& t);
        void pop_front();
        void pop_back();
        T& front();
        T& back();
        T& operator[](unsigned int i);
        void resize(unsigned int _capacity);
        unsigned int size();
        virtual ~MyQueue();
        int myFront;
        int myBack;
        int mySize;
        unsigned int capacity;
        T* items;
    protected:
    private:
};

template <typename T>
MyQueue<T>::MyQueue()
{
	items = nullptr;
	myFront = 0;
	mySize = 0;
	myBack = 0;
	capacity = 0;
	myBack = capacity-1;
}
template <typename T>
MyQueue<T>::MyQueue(unsigned int _capacity)
{
	items = nullptr;
	myFront = 0;
	mySize = 0;
	myBack = 0;
	resize(_capacity);
	myBack = capacity-1;
}
template <typename T>
MyQueue<T>::~MyQueue()
{
    delete[] (void*)items;
}
#include <cassert>
template <typename T>
void MyQueue<T>::push_front(const T& t)
{
    if (mySize == capacity)
    {
        resize(++capacity*2);
    }
    myFront--;
    if (myFront == -1)
    {
        myFront = capacity-1;
    }
    items[myFront] = t;
    mySize++;

}
template <typename T>
void MyQueue<T>::push_back(const T& t)
{
    if (mySize == capacity)
    {
        resize(++capacity*2);
    }
    myBack++;
    if (myBack == capacity)
    {
        myBack = 0;
    }
    items[myBack] = t;
    mySize++;

}
template <typename T>
void MyQueue<T>::pop_front()
{
    myFront++;
    mySize--;
    if (myFront == capacity)
    {
        myFront = 0;
    }
}
template <typename T>
void MyQueue<T>::pop_back()
{
    myBack--;
    mySize--;
    if (myBack == -1)
    {
        myBack = capacity-1;
    }
}
template <typename T>
T& MyQueue<T>::front()
{
    return items[myFront];
}
template <typename T>
T& MyQueue<T>::back()
{
    return items[myBack];
}
template <typename T>
T& MyQueue<T>::operator[](unsigned int i)
{
    i += myFront;
    if(i >= capacity)
        i -= capacity;
    return items[i];
}
template <typename T>
unsigned int MyQueue<T>::size()
{
    return mySize;
}
template <typename T>
void MyQueue<T>::resize(unsigned int _capacity)
{
    T* newItems = new T[_capacity];
    if (items != nullptr)
    {
        if (myFront > myBack) // Split into two ranges
        {
            // Copy front range first
            memcpy(newItems,items,sizeof(T)*myBack);
            // Then copy back range
            int newMyFront = myFront + _capacity - capacity;
            memcpy(&newItems[newMyFront],&items[myFront],sizeof(T)*(capacity-myFront));
            myFront = newMyFront;
        }
        else
        {
            memcpy(&newItems[myFront],&items[myFront],sizeof(T)*mySize);
        }
    }
    capacity = _capacity;
    delete[] items;
    items = newItems;
}



#endif // MYQUEUE_H
