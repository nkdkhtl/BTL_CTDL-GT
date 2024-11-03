#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <cmath>

using namespace std;
const int PRIME_CONST = 31;

class Node
{
private:
	string key; // key-value <=> Tieng Anh - Tieng Viet
	string value;
	Node *next;

public:
	Node() : next(nullptr) {}
	Node(string key, string value, Node *nextNode = nullptr)
	{
		this->key = key;
		this->value = value;
		this->next = nextNode;
	}

	void setProps(string key, string value)
	{
		this->key = key;
		this->value = value;
	}

	void setNext(Node *nextNode)
	{
		this->next = nextNode;
	}

	string getKey()
	{
		return this->key;
	}

	string getValue()
	{
		return this->value;
	}

	Node *getNext()
	{
		return this->next;
	}
};
// Tu dien dua tren bang bam
class Dictionary
{
private:
	vector<list<Node *>> table; // vector chua cac linkedlist
	int capacity;				// so luong o chua linkedlist
	int size;					// so luong tu trong tu dien
	float loadFactorThreshold;	// Nguong phai rehash

	int hashFunc(const string &key)
	{
		unsigned long long hashCode = 0;
		for (int i = 0; i < key.length(); i++)
		{
			hashCode += key[i] * pow(PRIME_CONST, i);
		}
		return hashCode % capacity;
	}

	void reHash()
	{
		int oldCapacity = capacity;
		capacity *= 2;
		vector<list<Node *>> newTable(capacity);
		for (int i = 0; i < oldCapacity; ++i)
		{
			for (auto node : table[i])
			{
				int newIdx = hashFunc(node->getKey()) % capacity;

				newTable[newIdx].push_back(node);
			}
		}

		table = (newTable);
	}

	string toLowerCase(string &word)
	{
		for (auto &c : word)
		{
			c = tolower(c);
		}
		return word;
	}

public:
	// Ham tao
	Dictionary(int cap = 10, float loadFactor = 0.75)
	{
		capacity = cap;
		size = 0;
		loadFactorThreshold = loadFactor;
		table.resize(capacity, list<Node *>()); // khoi tao bang bam voi capacity
	}
	// ham huy
	~Dictionary()
	{
		for (int i = 0; i < capacity; ++i)
		{
			for (auto node : table[i])
			{
				delete node;
			}
		}
	}
	// Nap tu dien
	void generate()
	{

		ifstream f("TuDienAnhViet.txt");

		if (!f.is_open())
		{
			cout << "Nap tu dien khong thanh cong!\n";
			return;
		}

		string s;
		while (getline(f, s))
		{
			string english = s.substr(0, s.find(':'));
			string vietnamese = s.substr(s.find(':') + 1, s.length());
			this->insertWord(english, vietnamese);
		}
		f.close();
	}

	bool isEmpty()
	{
		return size == 0;
	}

	void insertWord(string &key, string &value)
	{
		key = toLowerCase(key);
		value = toLowerCase(value);

		int idx = hashFunc(key);
		// Kiem tra co tu do chua, neu co thi cap nhat

		for (auto node : table[idx])
		{
			if (node->getKey() == key)
			{
				node->setProps(key, value);
				return;
			}
		}

		// Neu khong co, them 1 tu vao cuoi
		Node *newNode = new Node(key, value);
		table[idx].push_back(newNode);
		size++;

		// Kiem tra xem co phai rehash lai
		if ((float)size / capacity > loadFactorThreshold)
		{
			reHash();
		}
	}

	void removeWord(string &key)
	{
		key = toLowerCase(key);
		int idx = hashFunc(key);
		auto &chain = table[idx];

		for (auto it = chain.begin(); it != chain.end(); ++it)
		{
			if ((*it)->getKey() == key)
			{
				delete *it;		 // giai phong bo nho
				chain.erase(it); // xoa khoi danh sach
				size--;
				return;
			}
		}

		cout << "Khong co" << key << " trong tu dien!" << endl;
	}

	string searchWordByEnglish(string &key)
	{
		key = toLowerCase(key);
		int idx = hash<string>{}(key) % capacity;
		for (auto node : table[idx])
		{
			if (node->getKey() == key)
			{
				return node->getValue();
			}
		}
		return "Khong tim thay trong tu dien\n";
	}

	string searchWordByVietnamese(string &value)
	{
		value = toLowerCase(value);
		for (int i = 0; i < capacity; ++i)
		{
			for (auto node : table[i])
			{
				if (node->getValue() == value)
				{
					return node->getKey();
				}
			}
		}
		return "Khong tim thay trong tu dien\n";
	}

	void printTable()
	{
		for (int i = 0; i < capacity; ++i)
		{
			// In theo bang bam
			cout << "BUCKET " << i << ": ";
			for (auto node : table[i])
			{
				cout << "(\"" << node->getKey() << "\", \"" << node->getValue() << "\") -> ";
			}
			cout << "NULL" << endl;

			// Liet ke

			// for (auto node : table[i])
			// {
			// 	cout << node->getKey() << ": " << node->getValue() << endl;
			// }
		}
	}

	void run()
	{
		cout << "TU DIEN ANH-VIET" << endl;
		int choice;
		do
		{
			cout << "//////////////////////////" << endl;
			cout << "1: Kiem tra tu dien rong" << endl;
			cout << "2: Them 1 tu vao tu dien" << endl;
			cout << "3: Xoa 1 tu trong tu dien" << endl;
			cout << "4: Tim tu theo Tieng Anh" << endl;
			cout << "5: Tim tu theo Tieng Viet" << endl;
			cout << "6: In toan bo tu dien!" << endl;
			cout << "0: Thoat" << endl;
			cout << "//////////////////////////" << endl;
			cout << "Nhap lua chon: ";

			cin >> choice;

			switch (choice)
			{
			case 1:
			{
				if (isEmpty())
				{
					cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
					cout << "Tu dien rong!" << endl;
					cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
				}
				else
				{
					cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
					cout << "Tu dien da duoc nap!" << endl;
					cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
				}
				break;
			}

			case 2:
			{
				string english;
				string vietnamese;
				cout << "Nhap tu tieng Anh muon them: ";
				cin.ignore(1);
				getline(cin, english);
				cout << "Nhap nghia tieng Viet: ";
				getline(cin, vietnamese);
				insertWord(english, vietnamese);
				cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
				cout << "Them tu thanh cong!" << endl;
				cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
				break;
			}

			case 3:
			{
				string english;
				cout << "Nhap tu tieng Anh muon xoa: ";
				cin.ignore(1);
				getline(cin, english);
				removeWord(english);
				cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
				cout << "Xoa tu thanh cong!" << endl;
				cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
				break;
			}

			case 4:
			{
				string english;
				cout << "Nhap tu tieng Anh muon tim: ";
				cin.ignore(1);
				getline(cin, english);
				cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
				cout << searchWordByEnglish(english) << endl;
				cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

				break;
			}

			case 5:
			{
				string vietnamese;
				cout << "Nhap tu tieng Viet muon tim: ";
				cin.ignore(1);
				getline(cin, vietnamese);
				cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
				cout << searchWordByVietnamese(vietnamese) << endl;
				cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

				break;
			}
			case 6:
			{
				printTable();
				break;
			}
			default:
			{
				break;
			}
			}
		} while (choice != 0);
		cout << "Ban da thoat chuong trinh!";
	}
};

int main()
{
	Dictionary TuDien;
	TuDien.generate();
	TuDien.run();
	return 0;
}
