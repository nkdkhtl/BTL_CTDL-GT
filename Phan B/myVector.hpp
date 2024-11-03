#ifndef MYVECTOR
#define MYVECTOR

using namespace std;

const int DEFAULT_VECTOR_SIZE = 5;

template <typename T>
class Vector
{
private:
    T *elements;  // coi la 1 mang
    int size;     // so luong elem dang co
    int capacity; // so luong elem toi da

public:
    Vector() // Vector<float> v;
    {
        size = 0;
        capacity = DEFAULT_VECTOR_SIZE;
        elements = new T[DEFAULT_VECTOR_SIZE];
    }
    Vector(int n) // Vector<float> v;
    {
        size = n;
        capacity = n * 2;
        elements = new T[capacity];
    }
    Vector(int n, const T &value) // Vector<float> v(10,n)
    {
        size = n;
        capacity = n * 2;
        elements = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            elements[i] = value;
        }
    }
    Vector(const Vector &other)
    {
        size = other.size;
        capacity = other.capacity;
        elements = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            elements[i] = other.elements[i];
        }
    } // Vector<float> v(w)

    ~Vector()
    {
        delete[] elements;
    }

    typedef T *iterator;
    iterator begin()
    {
        return elements;
    }
    iterator end()
    {
        return elements + size;
    }
    int getSize() const
    {
        return size;
    }

    int getCapacity() const
    {
        return capacity;
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    T &operator[](int index) // v[i] = x
    {
        return elements[index];
    }
    const T &operator[](int index) const // x = v[i]
    {
        return elements[index];
    };
    Vector &operator=(const Vector &other) // v = w
    {
        if (this != &other) // Check for self-assignment
        {
            delete[] elements;
            size = other.size;
            capacity = other.capacity;
            elements = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    void push_back(const T &elem) // v.push_back('A')
    {
        if (size == capacity)
        {
            T *newArr = new T[capacity * 2];

            for (int i = 0; i < size; i++)
            {
                newArr[i] = elements[i];
            }
            delete[] elements;
            elements = newArr;
            capacity = capacity * 2;
        }
        elements[size] = elem;
        size++;
    }
    void pop_back() // v.pop_back()
    {
        if (size > 0)
        {
            size--;
        }
    }
    // void insert(int index, T value);  v.insert(0,'A')
    void erase(int index) // v.erase(0)
    {
        for (int i = index; i < size - 1; i++)
        {
            elements[i] = elements[i + 1];
        }
        size--;
    }
    void clear() // v.clear()
    {
        size = 0;
    }

    void reSize(int newSize, const T &fillElem = T()) // v.resize()
    {
        T *newArr = new T[newSize];
        for (int i = 0; i < (newSize < size ? newSize : size); i++)
        {
            newArr[i] = elements[i];
        }
        for (int i = size; i < newSize; i++)
        {
            newArr[i] = fillElem;
        }
        delete[] elements;
        elements = newArr;
        size = newSize;
        capacity = newSize; // Optionally update capacity to newSize
    }
};

#endif
