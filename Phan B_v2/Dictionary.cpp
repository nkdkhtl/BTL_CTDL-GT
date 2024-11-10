#include "./HashTable.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
int hashFunc(string key, int capacity)
{
    unsigned long long hashCode = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hashCode += key[i] * pow(31, i);
    }
    return hashCode % capacity;
}

class Dictionary
{
private:
    HashTable<string, string> TuDien;

public:
    Dictionary(int cap = 10) : TuDien(cap) {}

    string toLowerCase(string &word)
    {
        for (auto &c : word)
        {
            c = tolower(c);
        }
        return word;
    }

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

    void updateFile()
    {
        ofstream f("TuDienAnhViet.txt", ios::trunc); // Open file in truncate mode to clear existing content
        if (!f.is_open())
        {
            cout << "Cap nhat tap tin khong thanh cong!" << endl;
            return;
        }

        for (int i = 0; i < TuDien.getCapacity(); ++i)
        {
            Node<string, string> *curr = TuDien.getBucket(i)->getHead();
            while (curr)
            {
                f << curr->getKey() << ':' << curr->getValue() << endl;
                curr = curr->getNext();
            }
        }

        f.close();
    }

    bool isEmpty()
    {
        return TuDien.getSize() == 0;
    }

    void insertWord(string &key, string &value, int role)
    {
        if (TuDien.getLoadFactor() > TuDien.getLoadFactorThreshold())
        {
            TuDien.reHash(hashFunc);
        }
        key = toLowerCase(key);
        value = toLowerCase(value);
        if (!TuDien.contains(key, hashFunc))
        {
            TuDien.add(key, value, hashFunc);

            if (role)
            {
                updateFile();
                cout << "THEM TU THANH CONG" << endl;
            }
        }
        else
        {
            cout << "TU NAY DA CO TRONG TU DIEN" << endl;
        }
    }

    void modifyWord(string &key, string &value)
    {
        if (TuDien.contains(key, hashFunc))
        {
            TuDien.remove(key, hashFunc);
            TuDien.add(key, value, hashFunc);
            updateFile();
            cout << "DA SUA DOI TU BAN THEM TRONG TU DIEN" << endl;
        }
        else
        {
            cout << "KHONG TIM THAY TU NAY TRONG TU DIEN" << endl;
        }
    }

    string findWordByEnglish(string &key)
    {
        key = toLowerCase(key);
        Node<string, string> *node = TuDien.findByKey(key, hashFunc);
        return node ? node->getValue() : "KHONG TIM THAY TU NAY TRONG TU DIEN";
    }

    string findWordByVietnamese(string &value)
    {
        value = toLowerCase(value);
        Node<string, string> *node = TuDien.findByValue(value);
        return node ? node->getKey() : "KHONG TIM THAY TU NAY TRONG TU DIEN";
    }

    void removeWord(string &key)
    {
        key = toLowerCase(key);
        if (TuDien.contains(key, hashFunc))
        {
            TuDien.remove(key, hashFunc);
            updateFile();
            cout << "XOA TU THANH CONG" << endl;
        }
        else
        {
            cout << "KHONG TIM THAY TU NAY TRONG TU DIEN" << endl;
        }
    }

    void printDictionary()
    {
        TuDien.printTable();
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
        cout << "---------------------------------------------------" << endl;
        cout << "             TU DIEN ANH - VIET                    " << endl;
        cout << "---------------------------------------------------" << endl;
        int choice;
        do
        {
            cout << "1: Kiem tra tu dien rong" << endl;
            cout << "2: Them 1 tu vao tu dien" << endl;
            cout << "3: Sua 1 tu trong tu dien" << endl;
            cout << "4: Xoa 1 tu trong tu dien" << endl;
            cout << "5: Tim tu theo Tieng Anh" << endl;
            cout << "6: Tim tu theo Tieng Viet" << endl;
            cout << "7: In toan bo tu dien!" << endl;
            cout << "0: Thoat" << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "Chon thao tac: ";

            cin >> choice;

            switch (choice)
            {
            case 1:
                if (TuDien.isEmpty())
                {
                    cout << "---------------------------------------------------" << endl;
                    cout << "Tu dien rong!" << endl;
                    cout << "---------------------------------------------------" << endl;
                }
                else
                {
                    cout << "---------------------------------------------------" << endl;
                    cout << "Tu dien da duoc nap!" << endl;
                    cout << "---------------------------------------------------" << endl;
                }
                break;

            case 2:
            {
                string english, vietnamese;
                cout << "Nhap tu tieng Anh muon them: ";
                cin.ignore(1);
                getline(cin, english);
                cout << "Nhap nghia tieng Viet: ";
                getline(cin, vietnamese);
                cout << "---------------------------------------------------" << endl;
                TuDien.insertWord(english, vietnamese, 1);
                cout << "---------------------------------------------------" << endl;
            }
            break;

            case 3:
            {
                string english;
                cout << "Nhap tu tieng Anh muon sua: ";
                cin.ignore(1);
                getline(cin, english);
                string vietnamese;
                cout << "Nhap nghia tieng Viet cua tu muon sua: ";
                getline(cin, vietnamese);
                cout << "---------------------------------------------------" << endl;
                TuDien.modifyWord(english, vietnamese);
                cout << "---------------------------------------------------" << endl;
            }
            break;

            case 4:
            {
                string english;
                cout << "Nhap tu tieng Anh muon xoa: ";
                cin.ignore(1);
                getline(cin, english);
                cout << "---------------------------------------------------" << endl;
                TuDien.removeWord(english);
                cout << "---------------------------------------------------" << endl;
            }
            break;

            case 5:
            {
                string english;
                cout << "Nhap tu tieng Anh muon tim: ";
                cin.ignore(1);
                getline(cin, english);
                cout << "---------------------------------------------------" << endl;
                cout << TuDien.findWordByEnglish(english) << endl;
                cout << "---------------------------------------------------" << endl;
            }
            break;

            case 6:
            {
                string vietnamese;
                cout << "Nhap tu tieng Viet muon tim: ";
                cin.ignore(1);
                getline(cin, vietnamese);
                cout << "---------------------------------------------------" << endl;
                cout << TuDien.findWordByVietnamese(vietnamese) << endl;
                cout << "---------------------------------------------------" << endl;
            }
            break;

            case 7:
                TuDien.printDictionary();
                break;

            case 0:
                cout << "Ban da thoat chuong trinh!" << endl;
                break;

            default:
                cout << "Lua chon khong hop le! Vui long chon lai." << endl;
            }
        } while (choice != 0);
    }
};

int main()
{
    App a;
    a.run();
    return 0;
}
