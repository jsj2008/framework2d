#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED
#ifndef NULL
#define NULL 0
#endif
#include <stack>
/// This class supports a delete function that just sets the variable 'active' to false, which needs to be asserted during looping. Its a way of deleting that keeps the contents in their original places.
/// It is likely to be faster too. It stores a list of inactive elements and pushing inserts the new element in one of these, returning the location it was put into
template <typename T>
class MyVector
{
public:
	MyVector(int size = 20);
	MyVector(const MyVector & rhs);
	~MyVector();
	void dontDeleteContents()
	{
		deleteContents = false;
	}
	void resize(int size);
	void clear();
	int push(T const &d);
	void remove(int i);
	T const pop();
	T const top();
	T& at(int i);
	bool empty();
	bool full();
	int size();
	int maxSize();
	inline T & operator [] (unsigned int i) {return items[i];}
private:
	int MaxMyVector;
	int EmptyMyVector;
	int Top;
	T* items;
	bool deleteContents;
	std::stack<int> inactiveElements;
};

template <typename T>
MyVector<T>::MyVector(int size)
{
	items = NULL;
	resize(size);
	deleteContents = true;
}
template <typename T>
MyVector<T>::MyVector(const MyVector & rhs)
{
	if (rhs.deleteContents != false)
	{
		//Error("cpy constructor: target should probably have delete contents off", ef_NonFatal);
	}
	//items = rhs.items;
	items = NULL;
	resize(rhs.MaxMyVector);
	memcpy(items,rhs.items,sizeof(T)*MaxMyVector);
	Top = rhs.Top;
	EmptyMyVector = rhs.EmptyMyVector;
	deleteContents = true;
}
template <typename T>
MyVector<T>::~MyVector()
{
	if (deleteContents && items != NULL)
	{
		delete[] items;
		items = NULL;
	}
}

template <typename T>
void MyVector<T>::resize(int size)
{
	if (items != NULL)
	{
		delete[] items;
	}
	MaxMyVector = size;
	Top = EmptyMyVector = -1;
	items = new Item[MaxMyVector];
}

template <typename T>
void MyVector<T>::clear()
{
    Top = EmptyMyVector = -1;
}
template <typename T>
int MyVector<T>::push(T const &d)
{
    if (inactiveElements.empty())
    {
        items[++Top] = d;
        return Top;
    }
    else
    {
        int element = inactiveElements.top();
        inactiveElements.pop();
        items[element] = d;
        return element;
    }
}
template <typename T>
void MyVector<T>::remove(int i)
{
    inactiveElements.push(i);
    items[i].active = false;
}

template <typename T>
T const  MyVector<T>::pop()
{
   return items[Top--];
}

template <typename T>
T const  MyVector<T>::top()
{
   return items[Top];
}

template <typename T>
bool MyVector<T>::full()
{
   return Top + 1 == MaxMyVector;
}

template <typename T>
int MyVector<T>::size()
{
	return Top + 1;
}
template <typename T>
int MyVector<T>::maxSize()
{
	return MaxMyVector;
}
template <typename T>
bool MyVector<T>::empty()
{
   return Top == EmptyMyVector;
}

template <typename T>
T& MyVector<T>::at(int j)
{
   return &items[j];
}
#endif // MYVECTOR_H_INCLUDED
