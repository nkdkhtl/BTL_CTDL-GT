#ifndef MYNODE
#define MYNODE
using namespace std;

template <typename KeyType, typename ValueType>
class Node
{
private:
    KeyType key;     // Tieng Anh
    ValueType value; // Tieng Viet
    Node *next;      // Con tro next

public:
    // khởi tạo với giá trị mặc định
    Node(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}

    void setNext(Node *nextNode)
    {
        this->next = nextNode;
    }

    KeyType getKey()
    {
        return this->key;
    }

    ValueType getValue()
    {
        return this->value;
    }
    Node *getNext()
    {
        return this->next;
    }
};
#endif