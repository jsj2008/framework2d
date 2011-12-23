#ifndef LIST_H
#define LIST_H
/// Doubly linked list

template<typename T>
class Iterator;
template<typename T>
struct Node
{
    Node(T _t){t = _t;}
    T t;
    Node* forward,backward;
};
template<typename T>
class List
{
    public:
        List();
        void push_front(T& t);
        void push_back(T& t);
        void moveToFront(Node<T>* i); // Moves a node which (assumedly) is already in the list somewhere
        void remove(Node<T>* i);// Deletes
        Node<T>* operator[](unsigned int i); // Currently undefined
        T& back(){return myBack->t;}
        T& front(){return myFront->t;}
    private:
        friend class Iterator<T>;
        unsigned int mySize;
        Node<T>* myFront;
        Node<T>* myBack;
};
/*template<typename T>
class Iterator
{
    public:
        Iterator(List<T>& list);
    private:
        friend class List<T>;
        Node<T>* node;
};*/
template<typename T>
List<T>::List()
{
    myFront = myBack = nullptr;
    mySize = 0;
}
template<typename T>
void List<T>::push_front(T& t)
{
    Node<T>* newNode = new Node<T>(t);
    newNode->forward = myBack;
    newNode->backward = myFront;
    myFront->forward = newNode;
    myFront = newNode;
    mySize++;
}
template<typename T>
void List<T>::push_back(T& t)
{
    Node<T>* newNode = new Node<T>(t);
    newNode->forward = myBack;
    newNode->backward = myFront;
    myBack->backward = newNode;
    myBack = newNode;
    mySize++;
}
template<typename T>
Node<T>* List<T>::operator[](unsigned int index)
{
    Node<T>* ret = myFront;
    for(unsigned int i = 0; i != index; i++)
    {
        ret = ret->backward;
    }
    return ret;
}
template<typename T>
void List<T>::moveToFront(Node<T>* i)
{
    i->backward->forward = i->forward;
    i->forward->backward = i->backward;
    i->backward = front;
    i->forward = back;
    front = i;
}
template<typename T>
void List<T>::remove(Node<T>* i)
{
    i->backward->forward = i->forward;
    i->forward->backward = i->backward;
    delete i;
}
#endif // LIST_H
