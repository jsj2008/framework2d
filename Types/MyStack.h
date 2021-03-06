#ifndef MYSTACK_H // Why not
#define MYSTACK_H

template <typename T>
class MyStack
{
public:
	MyStack();
	MyStack(const MyStack & rhs);
	~MyStack();
	void dontDeleteContents()
	{
		deleteContents = false;
	}
	void resize(int size);
	void clear();
	void push(T const &d);
	inline void push_back(T const &d){push(d);}
	T const pop();
	T const top();
	T& at(int j);
	bool empty();
	bool full();
	int size();
	int maxSize();
	inline T & operator [] (unsigned int j) {return items[j];}
private:
	int MaxMyStack;
	int  EmptyMyStack;
	int Top;
	T* items;
	bool deleteContents;
};

template <typename T>
MyStack<T>::MyStack()
{
	items = nullptr;
	resize(1);
	deleteContents = true;
}
template <typename T>
MyStack<T>::MyStack(const MyStack & rhs)
{
	if (rhs.deleteContents != false)
	{
		//Error("cpy constructor: target should probably have delete contents off", ef_NonFatal);
	}
	//items = rhs.items;
	items = nullptr;
	resize(rhs.MaxMyStack);
	memcpy(items,rhs.items,sizeof(T)*MaxMyStack);
	Top = rhs.Top;
	EmptyMyStack = rhs.EmptyMyStack;
	deleteContents = true;
}
template <typename T>
MyStack<T>::~MyStack()
{
	if (deleteContents && items != nullptr)
	{
		delete[] items;
		items = nullptr;
	}
}

template <typename T>
void MyStack<T>::resize(int _size)
{
	if (items != nullptr)
	{
		delete[] items;
	}
	MaxMyStack = _size;
	Top = EmptyMyStack = -1;
	items = new T[MaxMyStack];
}

template <typename T>
void MyStack<T>::clear()
{
    Top = EmptyMyStack = -1;
}
template <typename T>
void MyStack<T>::push(T const &d)
{
    if (Top == MaxMyStack)
    {
        resize(MaxMyStack*2);
    }
   items[++Top] = d;
}

template <typename T>
T const  MyStack<T>::pop()
{
   return items[Top--];
}

template <typename T>
T const  MyStack<T>::top()
{
   return items[Top];
}

template <typename T>
bool MyStack<T>::full()
{
   return Top + 1 == MaxMyStack;
}

template <typename T>
int MyStack<T>::size()
{
	return Top + 1;
}
template <typename T>
int MyStack<T>::maxSize()
{
	return MaxMyStack;
}
template <typename T>
bool MyStack<T>::empty()
{
   return Top == EmptyMyStack;
}

template <typename T>
T& MyStack<T>::at(int j)
{
   return &items[j];
}
#endif // MYSTACK_H
