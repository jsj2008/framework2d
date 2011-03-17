#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

struct Node
{
    Node(unsigned int _node = -1, unsigned int _set = -1){node = _node; set = _set;}
    unsigned int node;
    unsigned int set;
    bool operator == (const Node& rhs){return node == rhs.node && set == rhs.set;}
    bool operator != (const Node& rhs){return !(*this == rhs);}
};


#endif // NODE_H_INCLUDED
