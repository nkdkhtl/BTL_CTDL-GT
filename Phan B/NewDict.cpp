#include <iostream>
#include <fstream>
#include "./myVector.hpp"
#include "./myNode.hpp"
#include "./myList.hpp"
#include <utility>
#include <string>
#include <math.h>
using namespace std;

const int PRIME_CONST = 31;
class Dictionary
{
private:
	Vector<sList<string>> table; // Vector chua cac linkedlist
	int capacity;				 // so luong o chua linkedlist
	int size;					 // so luong tu trong tu dien
	float loadFactorThreshold;	 // Nguong phai rehash

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
		int oldCap = capacity;
		capacity *= 2;
		Vector<sList<string>> newTable;

		for (int i = 0; i < oldCap; ++i)
		{
			cout << i << " ";
			for (auto node : table[i])
			{
				cout << node->getKey() << endl;
				int newIdx = hashFunc(node->getKey());
				newTable[newIdx].push_back(node);
			}
		}

		table = move(newTable);
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
		loadFactorThreshold = loadFactor;
		size = 0;
		table.reSize(capacity, sList<string>());
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

		if (table[idx].empty())
		{
			table[idx] = sList<string>(); // Initialize if empty
		}
		// Tim xem tu do co trong tu dien hay khong ?
		for (auto node : table[idx])
		{
			if (node->getKey() == key)
			{
				node->setProps(key, value);
				return;
				// cout << "Tu nay da co trong tu dien" << endl;
				// cout << node->getKey() << ": " << node->getValue() << endl;
				// cout << "Ban co muon them tu nay khong ? (neu them se ghi de tu da co trong tu dien)" << endl;
			}
		}

		// Neu khong co, them 1 tu vao cuoi
		Node<string> *newNode = new Node<string>(key, value);
		table[idx].push_back(newNode);
		size++;

		if ((float)(size * 1.0 / capacity) > loadFactorThreshold)
		{
			reHash();
		}
	}

	void removeWord(string &key)
	{
	}

	string searchWordByEnglish(string &key)
	{
	}

	string searchWordByVietnamese(string &value)
	{
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
