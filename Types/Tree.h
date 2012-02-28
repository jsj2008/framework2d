#ifndef _LISTNODE_H
#define _LISTNODE_H

template <typename Object> /// <Type stored in the List>
class ListNode;

template <typename Object> /// <Type stored in the List>
class List
{
public:
  List(){children = nullptr;}
  ~List();
  void attachChild(ListNode<Object>* _child);
  void detachChild(ListNode<Object>* _child);
  ListNode<Object>* getChildren(){return children;}
protected:
  ListNode<Object>* children;
};

template <typename Node> /// <Type of the List>
class ListNode
{
 public:
  ListNode(){next = prev = nullptr; parent = nullptr;}
  ~ListNode();
  ListNode<Node>* getNext(){return next;}
  ListNode<Node>* getPrev(){return prev;}
  List<Node>* getParent(){return parent;}
  Node& operator()(){return static_cast<Node&>(*this);}
protected:
  friend class List<Node>;
  ListNode<Node>* next,* prev;
  List<Node>* parent;
};

template <typename Node> /// <Type of the Tree>
class TreeNode: public ListNode<TreeNode<Node>>, public List<TreeNode<Node>>
{
public:
  TreeNode(){}
  ~TreeNode(){}
  Node* getParent(){return static_cast<Node*>(static_cast<ListNode<TreeNode<Node>>*>(this)->getParent());}
  Node* getPrev(){return static_cast<Node*>(static_cast<ListNode<TreeNode<Node>>*>(this)->getPrev());}
  Node* getNext(){return static_cast<Node*>(static_cast<ListNode<TreeNode<Node>>*>(this)->getNext());}
  Node* getChildren(){return static_cast<Node*>(static_cast<List<TreeNode<Node>>*>(this)->getChildren());}
  Node& operator()(){return static_cast<Node&>(*this);}
  //  void attachChild(Node* _child);
  //  void detachChild(Node* _child);
protected:
};


#include <cassert>
template <typename Object>
List<Object>::~List()
{
  ListNode<Object>* child = children;
  while (child != nullptr)
    {
      ListNode<Object>* prev = child;
      child = child->next;
      delete prev;
    }
}
template <typename Node>
ListNode<Node>::~ListNode()
{
  parent->detachChild(this);
}
template <typename Object>
void List<Object>::attachChild(ListNode<Object>* _child)
{
  assert(_child->getParent() != this);
  if (_child->getParent())
      _child->getParent()->detachChild(_child);
    _child->parent = static_cast<Object*>(this);
    _child->prev = nullptr;
    _child->next = children;
    if (children != nullptr)
    {
        children->prev = _child;
    }
    children = _child;
}
template <typename Object>
void List<Object>::detachChild(ListNode<Object>* _child)
{
  /*    if (dynamic_cast<Entity*>(this) && dynamic_cast<BodyPart*>(_child))
    {
        assert(false);
	}*/
  assert(_child->getParent() == this);
    if (_child->prev)
        _child->prev->next = _child->next;
    else
        children = _child->next;
    if (_child->next)
        _child->next->prev = _child->prev;
}
/*template <typename Node>
void TreeNode<Node>::attachChild(Node* _child)
{
  this->List<Node>::attachChild(_child);
}
template <typename Node>
void TreeNode<Node>::detachChild(Node* _child)
{
  this->List<Node>::detachChild(_child);
  }*/

#endif /* _LISTNODE_H */

