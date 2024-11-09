#ifndef SINGLYLINKEDLIST
#define SINGLYLINKEDLIST

#include <iostream>
#include "myNode.hpp"

template <typename KeyType, typename ValueType>
class SinglyLinkedList
{
private:
    Node<KeyType, ValueType> *head; // Con tro toi Node dau ds
    Node<KeyType, ValueType> *tail; // con tro toi Node cuoi ds

public:
    // Constructor
    SinglyLinkedList() : head(nullptr), tail(nullptr) {}
    // Destructor
    ~SinglyLinkedList()
    {
        Node<KeyType, ValueType> *temp;
        while (head)
        {
            temp = head;
            head = head->getNext();
            delete temp;
        }
        tail = nullptr;
    }

    class Iterator
    {
    private:
        Node<KeyType, ValueType> *curr;

    public:
        Iterator(Node<KeyType, ValueType> *node = nullptr) : curr(node) {}

        bool hasNext()
        {
            return curr != nullptr;
        }

        void next()
        {
            if (curr)
            {
                curr = curr->getNext();
            };
        }

        KeyType getKey() const
        {
            return curr->getKey();
        }

        ValueType getValue() const
        {
            return curr->getValue();
        }

        Iterator begin() const
        {
            return Iterator(head);
        }
    };

    Node<KeyType, ValueType> *getHead()
    {
        return this->head;
    }

    // them node vao dau ds
    void addFirst(KeyType key, ValueType value)
    {
        Node<KeyType, ValueType> *newNode = new Node<KeyType, ValueType>(key, value);
        newNode->setNext(head); // Node moi tro toi head hien tai
        head = newNode;         // Cap nhat head la Node moi

        // Neu danh sach truoc đo trong, tail cũng can tro đen Node moi
        if (tail == nullptr)
        {
            tail = newNode;
        }
    }

    // them Node vao cuoi ds
    void addLast(KeyType key, ValueType value)
    {
        Node<KeyType, ValueType> *newNode = new Node<KeyType, ValueType>(key, value);
        if (!tail)
        { // DS trong
            head = tail = newNode;
        }
        else
        {
            tail->setNext(newNode); // tail tro toi node moi
            tail = newNode;         // cap nhat tail la node moi
        }
    }

    // xoa 1 Node voi key cho trc
    void remove(KeyType key)
    {
        if (!head)
            return; // DS trong

        // Neu node can xoa la head
        if (head->getKey() == key)
        {
            Node<KeyType, ValueType> *temp = head;
            head = head->getNext();
            delete temp;
            if (!head) // Neu DS trong sau khi xoa
                tail = nullptr;
            return;
        }

        // Duyet DS va tim Node
        Node<KeyType, ValueType> *temp = head;
        while (temp->getNext() && temp->getNext()->getKey() != key)
        {
            temp = temp->getNext();
        }
        if (temp->getNext())
        {
            Node<KeyType, ValueType> *toDelete = temp->getNext();
            temp->setNext(toDelete->getNext());

            // Nếu Node xoa là Node cuoi, cap nhat lai tail
            if (toDelete == tail)
                tail = temp;

            delete toDelete;
        }
    }

    // tim Node
    Node<KeyType, ValueType> *find(KeyType key)
    {
        Node<KeyType, ValueType> *temp = head;
        while (temp)
        {
            if (temp->getKey() == key)
                return temp;
            temp = temp->getNext();
        }
        return nullptr; // tra ve nullptr neu khong tim thay
    }

    // in cac Node trong lst
    void printList() const
    {
        Node<KeyType, ValueType> *temp = head;
        while (temp)
        {
            cout << "(" << temp->getKey() << ", " << temp->getValue() << ") -> ";
            temp = temp->getNext();
        }
        cout << "NULL" << endl;
    }
};

#endif
