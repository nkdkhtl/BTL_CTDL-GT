#include "./HashTable.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

int PRIME_CONST = 31;

class Dictionary : public HashTable<string, string>
{
public:
    Dictionary(int cap = 10) : HashTable(cap) {}

    string toLowerCase(string &word)
    {
        for (auto &c : word)
        {
            c = tolower(c);
        }
        return word;
    }

    int hashFunc(const string &key)
    {
        unsigned long long hashCode = 0;
        for (int i = 0; i < key.length(); i++)
        {
            hashCode += key[i] * pow(PRIME_CONST, i);
        }
        return hashCode % this->getCapacity();
    }
    // nap file
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
            this->insertWord(english, vietnamese, 0);
        }
        f.close();
    }

    void addWordToFile(string &key, string &value)
    {
        ofstream f("TuDienAnhViet.txt", ios::in | ios::out | ios::app);

        if (!f.is_open())
        {
            cout << "Cap nhat tu dien khong thanh cong!\n";
            return;
        }
        else
        {
            string pair = key + ':' + value;
            f << pair << endl;
            f.close();
        }
    }

    bool isEmpty()
    {
        return this->getSize() == 0;
    }

    void insertWord(string &key, string &value, int role)
    {
        key = toLowerCase(key);
        value = toLowerCase(value);
        if (!contains(key))
        {
            add(key, value);
            if (role)
            {
                addWordToFile(key, value);
                cout << "THEM TU THANH CONG" << endl;
            }
        }
        else
        {
            cout << "TU NAY DA CO TRONG TU DIEN" << endl;
        }

        // 0 de khoi tao , 1 la nguoi dung tao
    }

    string findWordByEnglish(string &key)
    {
        key = toLowerCase(key);
        Node<string, string> *node = findByKey(key);
        return node ? node->getValue() : "Khong tim thay trong tu dien";
    }

    string findWordByVietnamese(string &value)
    {
        value = toLowerCase(value);
        Node<string, string> *node = findByValue(value);
        return node ? node->getKey() : "Khong tim thay trong tu dien";
    }

    void removeWord(string &key)
    {
        key = toLowerCase(key);
        remove(key);
    }
};

class App
{
private:
    Dictionary TuDien;

public:
    void run()
    {
        TuDien.generate();
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
                if (TuDien.isEmpty())
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
                cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl;
                TuDien.insertWord(english, vietnamese, 1);
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                break;
            }

            case 3:
            {
                string english;
                cout << "Nhap tu tieng Anh muon xoa: ";
                cin.ignore(1);
                getline(cin, english);
                TuDien.removeWord(english);
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
                cout << TuDien.findWordByEnglish(english) << endl;
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
                cout << TuDien.findWordByVietnamese(vietnamese) << endl;
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

                break;
            }
            case 6:
            {
                TuDien.printTable();
                break;
            }
            default:
            {
                cout << "Ban da thoat chuong trinh!";
                return;
            }
            }
        } while (choice != 0);
        cout << "Ban da thoat chuong trinh!";
    }
};

main()
{
    App a;
    a.run();
}
