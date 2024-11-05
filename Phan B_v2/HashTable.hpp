#ifndef MYHASHTABLE
#define MYHASHTABLE
#include "./myNode.hpp"
#include <iostream>

template <typename KeyType, typename ValueType>
class HashTable
{
private:
    Node<KeyType, ValueType> **table; // Mang cac danh sach lien ket don
    int capacity;                     // kich thuoc cua bang bam (so table)
    int size;                         // so phan tu hien co (so node)
    float loadFactorThreshold = 0.75;

public:
    virtual int hashFunc(const KeyType &key)
    {
        return 0;
    }
    // khoi tao
    HashTable()
    {
        capacity = 10;
        size = 0;
        loadFactorThreshold = 0.75;
        table = new Node<KeyType, ValueType> *[capacity];
        // Gan ve null cho tat ca
        for (int i = 0; i < capacity; i++)
        {
            table[i] = nullptr;
        }
    };

    HashTable(int cap) : capacity(cap)
    {
        table = new Node<KeyType, ValueType> *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            table[i] = nullptr;
        }
    }

    void reHash()
    {
        int oldCap = capacity;
        capacity = capacity * 2;
        cout << "NEW CAPACITY: " << capacity << endl;
        Node<KeyType, ValueType> **oldTable = table;

        table = new Node<KeyType, ValueType> *[capacity];

        // Gan lai bang
        for (int i = 0; i < capacity; i++)
        {
            table[i] = nullptr;
        }

        for (int i = 0; i < oldCap; i++)
        {
            Node<KeyType, ValueType> *curr = oldTable[i];

            while (curr)
            {
                add(curr->getKey(), curr->getValue());
                Node<KeyType, ValueType> *temp = curr;
                curr = curr->getNext();
                delete temp;
            }
        }
        delete[] oldTable;
    }

    void setCap(int cap)
    {
        this->capacity = cap;
    }

    int getSize()
    {
        return this->size;
    }

    int getCapacity()
    {
        return this->capacity;
    }

    float getLoadFactor()
    {
        float loadFactor = (float)size / (float)capacity;
        return loadFactor;
    }

    bool contains(const KeyType &key)
    {
        int index = hashFunc(key);
        Node<KeyType, ValueType> *curr = table[index];
        while (curr)
        {
            if (curr->getKey() == key)
            {
                return true;
            }
            curr = curr->getNext();
        }
        return false;
    }

    int count()
    {
        int count = 0;
        for (int i = 0; i < capacity; i++)
        {
            Node<KeyType, ValueType> *curr = table[i];
            while (curr)
            {
                count++;
                curr = curr->getNext();
            }
        }
        return count;
    }

    Node<KeyType, ValueType> *add(const KeyType &key, const ValueType &value)
    {

        int idx = hashFunc(key);
        Node<KeyType, ValueType> *curr = table[idx];
        // Tim khoa
        while (curr)
        {
            // Neu khoa ton tai, cap nhat gia tri moi
            if (curr->getKey() == key)
            {
                curr->getValue() = value;
                return curr;
            }
            curr = curr->getNext();
        }

        // Them mot node moi vao dau dach sach lien ket
        Node<KeyType, ValueType> *newNode = new Node<KeyType, ValueType>(key, value);
        newNode->setNext(table[idx]);
        table[idx] = newNode;
        ++size;
        if (getLoadFactor() > loadFactorThreshold)
        {
            reHash();
        }
    }

    void remove(const KeyType &key)
    {
        int idx = hashFunc(key);
        Node<KeyType, ValueType> *curr = table[idx];
        Node<KeyType, ValueType> *prev = nullptr;

        while (curr)
        {
            if (curr->getKey() == key)
            {
                if (prev)
                {
                    prev->setNext(curr->getNext());
                }
                else
                {
                    table[idx] = curr->getNext();
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->getNext();
            size--;
        }
    }

    Node<KeyType, ValueType> *findByKey(const KeyType &key)
    {
        int idx = hashFunc(key);
        Node<KeyType, ValueType> *curr = table[idx];
        while (curr)
        {
            if (curr->getKey() == key)
            {
                return curr;
            }
            curr = curr->getNext();
        }
        return nullptr;
    }

    Node<KeyType, ValueType> *findByValue(const ValueType &value)
    {

        for (int i = 0; i < capacity; i++)
        {
            Node<KeyType, ValueType> *curr = table[i];
            while (curr)
            {
                if (curr->getValue() == value)
                {
                    return curr;
                }
                curr = curr->getNext();
            }
        }
        return nullptr;
    }

    void printTable()
    {
        for (int i = 0; i < this->capacity; i++)
        {
            cout << "BUCKET " << i << ": ";
            Node<KeyType, ValueType> *curr = table[i];
            if (!curr)
            {
                cout << "NULL" << endl;
            }
            else
            {
                while (curr)
                {
                    cout << "(\"" << curr->getKey() << "\", \"" << curr->getValue() << "\") -> ";
                    curr = curr->getNext();
                }
                cout << "NULL" << endl;
            }
        }
    }
};

#endif