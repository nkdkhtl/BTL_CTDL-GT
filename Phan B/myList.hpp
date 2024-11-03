#ifndef MYSLIST
#define MYSLIST
using namespace std;
template <typename T>
class sList
{
private:
    Node<T> *head, *tail;
    int length;

public:
    sList() : head(nullptr), tail(nullptr), length(0) {}
    ~sList()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    Node<T> *getHead() const
    {
        return head;
    }

    void setHead(Node<T> *newHead)
    {
        head = newHead;
    }

    class iterator
    {
    private:
        Node<T> *curr;

    public:
        iterator(Node<T> *n) : curr(n) {}
        bool operator==(const iterator &other) const
        {
            return this->curr == other.curr;
        }

        bool operator!=(const iterator &other) const
        {
            return this->curr != other.curr;
        }

        iterator &operator++() // Prefix increment
        {
            curr = curr->getNext();
            return *this;
        }

        iterator operator++(int) // Postfix increment
        {
            iterator tmp = *this;
            curr = curr->getNext();
            return tmp;
        }

        Node<T> *operator*() const // Return a pointer to Node
        {
            return curr;
        }
    };

    iterator begin()
    {
        return iterator(head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    int size() const
    {
        return length;
    }

    bool empty() const
    {
        return length == 0;
    }

    void push_back(Node<T> *newNode)
    {

        if (empty())
        {
            head = tail = newNode;
        }
        else
        {
            tail->setNext(newNode);
            tail = newNode;
        }
        ++length;
    }

    void pop_front()
    {
        if (empty())
        {
            return;
        }
        Node<T> *tmp = head;
        head = head->getNext();
        delete tmp;
        --length;
        if (length == 0)
        {
            tail = nullptr;
        }
    }

    void pop_back()
    {
        if (empty())
        {
            return;
        }
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node<T> *tmp = head;
            while (tmp->getNext() != tail)
            {
                tmp = tmp->getNext();
            }
            delete tail;
            tail = tmp;
            tail->setNext(nullptr);
        }
        --length;
    }

    void erase(iterator it)
    {
        if (empty() || it == end())
            return;

        Node<T> *nodeToDelete = *it;
        if (nodeToDelete == head)
        {
            pop_front();
            return;
        }

        Node<T> *current = head;
        while (current->getNext() != nodeToDelete)
        {
            current = current->getNext();
        }

        current->setNext(nodeToDelete->getNext());
        if (nodeToDelete == tail)
        {
            tail = current;
        }

        delete nodeToDelete;
        --length;
    }
};

#endif
