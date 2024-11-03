#ifndef MYNODE
#define MYNODE

using namespace std;
template <typename T>
class Node
{
private:
    T key;   // English
    T value; // Vietnamese
    Node *next;

public:
    Node() : next(nullptr) {}
    Node(T key, T value, Node *nextNode = nullptr)
    {
        this->key = key;
        this->value = value;
        this->next = nextNode;
    }

    void setProps(T key, T value)
    {
        this->key = key;
        this->value = value;
    }

    void setNext(Node *nextNode)
    {
        this->next = nextNode;
    }

    T getKey() const
    {
        return this->key;
    }

    T getValue() const
    {
        return this->value;
    }

    Node<T> *getNext() const
    {
        return this->next;
    }
};

#endif