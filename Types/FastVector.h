#ifndef FASTVECTOR_H_INCLUDED
#define FASTVECTOR_H_INCLUDED
#ifndef NULL
#define NULL 0
#endif
#include <stack>
#include <cstring>
#include <cstdlib>
/// This class supports a delete function that just sets the variable 'active' to false, which needs to be asserted during looping. Its a way of deleting that keeps the contents in their original places.
/// It is likely to be faster too. It stores a list of inactive elements and pushing inserts the new element in one of these, returning the location it was put into
template <typename T>
class FastVector
{
public:
	FastVector();
	FastVector(const FastVector & rhs);
	~FastVector();
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
	int MaxFastVector;
	int EmptyFastVector;
	int Top;
	T* items;
	std::stack<int> inactiveElements;
};

template <typename T>
FastVector<T>::FastVector()
{
	items = NULL;
	Top = -1;
	resize(20);
}
template <typename T>
FastVector<T>::FastVector(const FastVector & rhs)
{
	if (rhs.deleteContents != false)
	{
		//Error("cpy constructor: target should probably have delete contents off", ef_NonFatal);
	}
	//items = rhs.items;
	items = NULL;
	resize(rhs.MaxFastVector);
	memcpy(items,rhs.items,sizeof(T)*MaxFastVector); //FIXME
	Top = rhs.Top;
	EmptyFastVector = rhs.EmptyFastVector;
}
template <typename T>
FastVector<T>::~FastVector()
{
	if (items != NULL)
	{
		delete[] items;
		items = NULL;
	}
}

template <typename T>
void FastVector<T>::resize(int size)
{
    const unsigned int sizeofT = sizeof(T);
    T* newItems = (T*)malloc(sizeofT*size);
	if (items != NULL)
	{
	    memcpy(newItems,items,sizeof(T)*MaxFastVector);
		delete[] items;
	}
	MaxFastVector = size;
	items = newItems;
}

template <typename T>
void FastVector<T>::clear()
{
    Top = EmptyFastVector = -1;
}
template <typename T>
int FastVector<T>::push(T const &d)
{
    if (inactiveElements.empty())
    {
        Top++;
        if (Top == MaxFastVector)
        {
            resize(Top*2);
        }
        items[Top] = d;
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
void FastVector<T>::remove(int i)
{
    inactiveElements.push(i);
    items[i] = NULL;
}

template <typename T>
T const  FastVector<T>::pop()
{
   return items[Top--];
}

template <typename T>
T const  FastVector<T>::top()
{
   return items[Top];
}

template <typename T>
bool FastVector<T>::full()
{
   return Top + 1 == MaxFastVector;
}

template <typename T>
int FastVector<T>::size()
{
	return Top + 1;
}
template <typename T>
int FastVector<T>::maxSize()
{
	return MaxFastVector;
}
template <typename T>
bool FastVector<T>::empty()
{
   return Top == EmptyFastVector;
}

template <typename T>
T& FastVector<T>::at(int j)
{
   return &items[j];
}
#endif // FASTVECTOR_H_INCLUDED
