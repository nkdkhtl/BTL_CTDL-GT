#ifndef MYHASHTABLE
#define MYHASHTABLE
#include "./myList.hpp"
#include "./myNode.hpp"
#include <iostream>

template <typename KeyType, typename ValueType>
class HashTable
{
private:
    SinglyLinkedList<KeyType, ValueType> *table; // Mang cac danh sach lien ket don
    int capacity;                                // kich thuoc cua bang bam (so table)
    int size;                                    // so phan tu hien co (so node)
    float loadFactorThreshold = 0.75;

public:
    // khoi tao
    HashTable()
    {
        capacity = 10;
        size = 0;
        loadFactorThreshold = 0.75;
        table = new SinglyLinkedList<KeyType, ValueType>[capacity];
    };
    HashTable(int cap = 10) : capacity(cap), size(0), loadFactorThreshold(0.75)
    {
        table = new SinglyLinkedList<KeyType, ValueType>[capacity];
    }
    ~HashTable()
    {
        delete[] table;
    }

    void reHash(int (*hashFunc)(KeyType, int))
    {
        int oldCap = capacity;
        capacity = capacity * 2;
        // Tao bang moi voi x2 capacity
        SinglyLinkedList<KeyType, ValueType> *newTable = new SinglyLinkedList<KeyType, ValueType>[capacity];

        for (int i = 0; i < oldCap; i++)
        {
            Node<KeyType, ValueType> *curr = table[i].getHead();

            while (curr)
            {
                int newIdx = hashFunc(curr->getKey(), capacity);
                newTable[newIdx].addLast(curr->getKey(), curr->getValue());
                curr = curr->getNext();
            }
        }
        delete[] table;
        table = newTable;
    }

    void setCap(int cap)
    {
        this->capacity = cap;
    }

    int getSize() const
    {
        return this->size;
    }

    int getCapacity() const
    {
        return this->capacity;
    }

    float getLoadFactor()
    {
        float loadFactor = (float)size / (float)capacity;
        return loadFactor;
    }

    float getLoadFactorThreshold()
    {
        return this->loadFactorThreshold;
    }

    SinglyLinkedList<KeyType, ValueType> *getBucket(int index) const
    {
        return &table[index];
    }

    bool contains(const KeyType key, int (*hashFunc)(KeyType, int))
    {
        int idx = hashFunc(key, capacity);
        Node<KeyType, ValueType> *foundNode = table[idx].find(key);
        return foundNode != nullptr;
    }

    int count()
    {
        return size;
    }

    Node<KeyType, ValueType> *add(const KeyType key, const ValueType &value, int (*hashFunc)(KeyType, int))
    {

        int idx = hashFunc(key, capacity);
        Node<KeyType, ValueType> *foundNode = table[idx].find(key);
        // Neu tim thay
        if (foundNode)
        {
            foundNode->getValue() = value;
        }

        // Them mot node moi vao dau dach sach lien ket
        table[idx].addLast(key, value);
        ++size;
        return table[idx].find(key);
    }

    void remove(const KeyType key, int (*hashFunc)(KeyType, int))
    {
        int idx = hashFunc(key, capacity);
        table[idx].remove(key);
        --size;
    }

    Node<KeyType, ValueType> *findByKey(const KeyType key, int (*hashFunc)(KeyType, int))
    {
        int idx = hashFunc(key, capacity);
        return table[idx].find(key);
    }

    Node<KeyType, ValueType> *findByValue(const ValueType &value)
    {
        for (int i = 0; i < capacity; ++i)
        {
            Node<KeyType, ValueType> *curr = table[i].getHead();
            while (curr)
            {
                if (curr->getValue() == value)
                    return curr;
                curr = curr->getNext();
            }
        }
        return nullptr;
    }

    void printTable()
    {
        for (int i = 0; i < capacity; i++)
        {
            std::cout << "Bucket " << i << ": ";
            table[i].printList();
        }
    }
};

#endif