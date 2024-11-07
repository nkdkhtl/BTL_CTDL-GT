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

    Node<KeyType, ValueType> *getHead()
    {
        return this->head;
    }

    // them node vao dau ds
    void addFirst(KeyType key, ValueType value)
    {
        Node<KeyType, ValueType> *newNode = new Node<KeyType, ValueType>(key, value);
        newNode->setNext(head); // Node mới trỏ tới head hiện tại
        head = newNode;         // Cập nhật head là Node mới

        // Nếu danh sách trước đó trống, tail cũng cần trỏ đến Node mới
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
        { // Nếu danh sách trống
            head = tail = newNode;
        }
        else
        {
            tail->setNext(newNode); // tail hiện tại trỏ tới Node mới
            tail = newNode;         // Cập nhật tail là Node mới
        }
    }

    // xoa 1 Node voi key cho trc
    void remove(KeyType key)
    {
        if (!head)
            return; // Nếu danh sách trống

        // Nếu Node cần xoá là head
        if (head->getKey() == key)
        {
            Node<KeyType, ValueType> *temp = head;
            head = head->getNext();
            delete temp;
            if (!head) // Nếu danh sách trở nên trống sau khi xoá
                tail = nullptr;
            return;
        }

        // Duyệt danh sách để tìm và xoá Node
        Node<KeyType, ValueType> *temp = head;
        while (temp->getNext() && temp->getNext()->getKey() != key)
        {
            temp = temp->getNext();
        }
        if (temp->getNext())
        {
            Node<KeyType, ValueType> *toDelete = temp->getNext();
            temp->setNext(toDelete->getNext());

            // Nếu Node xoá là Node cuối, cập nhật lại tail
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
        return nullptr; // Trả về nullptr nếu không tìm thấy
    }

    // in cac Node trong lst
    void printList() const
    {
        Node<KeyType, ValueType> *temp = head;
        while (temp)
        {
            std::cout << "(\"" << temp->getKey() << "\", \"" << temp->getValue() << "\") -> ";
            temp = temp->getNext();
        }
        std::cout << "NULL" << std::endl;
    }

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
};

#endif
