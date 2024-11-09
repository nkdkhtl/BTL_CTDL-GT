// Khuc Phuong Nam - 231230845
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <iomanip>
using namespace std;

class Transaction
{
private:
    string id;
    string description;
    unsigned long long amount;
    string type;
    string date;

public:
    Transaction() : id(""), description(""), amount(0.0), type(""), date("") {}
    Transaction(string id, string desc, float amount, string type, string date)
    {
        this->id = id;
        this->description = desc;
        this->amount = amount;
        this->type = type;
        this->date = date;
    }

    friend istream &operator>>(istream &inp, Transaction &a)
    {
        cout << "Nhap ma GD: ";
        inp >> a.id;
        cout << "Nhap mo ta: ";
        inp.ignore();
        getline(inp, a.description);
        cout << "Nhap so tien: ";
        inp >> a.amount;
        cout << "Nhap loai GD (ThuNhap hoac ChiPhi): ";
        inp >> a.type;
        cout << "Nhap ngay GD (dd/mm/yyyy): ";
        inp >> a.date;
        return inp;
    }

    friend ostream &operator<<(ostream &out, const Transaction &a)
    {
        out << a.id
            << "\t"
            << a.description
            << "\t\t\t"
            << a.amount
            << "\t"
            << a.type
            << "\t"
            << a.date << endl;
        return out;
    }

    bool operator<(const Transaction &b) const
    {
        return this->amount < b.amount;
    }

    unsigned long long getAmount() const
    {
        return this->amount;
    }

    string getId() const
    {
        return this->id;
    }

    string getType() const
    {
        return this->type;
    }

    string getDescription() const
    {
        return this->description;
    }

    string getDate() const
    {
        return this->date;
    }

    string getComparableDate() const
    {
        //  dd/mm/yyyy --> yyyy/mm/dd de so sanh
        return date.substr(6, 4) + date.substr(3, 2) + date.substr(0, 2);
    }
};

class TransactionHistory
{
private:
    list<Transaction> a;

public:
    void readFromFile(const string &filename = "GD.txt")
    {
        ifstream file(filename);
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, description, type, date;
            unsigned long long amount;

            // Đọc từng phần tử trong mỗi dòng
            getline(ss, id, '\t');
            getline(ss, description, '\t');
            ss >> amount;
            ss.ignore(1, '\t'); // Bỏ qua ký tự tab sau số tiền
            getline(ss, type, '\t');
            getline(ss, date);

            // Tạo Transaction và thêm vào danh sách
            Transaction transaction(id, description, amount, type, date);
            a.push_back(transaction);
        }
        file.close();
    }

    void updateFile()
    {
        ofstream file("GD.txt");
        if (file.is_open())
        {
            for (const auto &transaction : a)
            {
                file << transaction.getId() << "\t"
                     << transaction.getDescription() << "\t"
                     << transaction.getAmount() << "\t"
                     << transaction.getType() << "\t"
                     << transaction.getDate() << endl;
            }
            file.close();
        }
    }

    void addTransaction(const Transaction &b)
    {
        a.push_back(b);
        updateFile();
    }

    void removeTransaction(const string &id)
    {
        for (auto it = a.begin(); it != a.end(); ++it)
        {
            if (it->getId() == id)
            {
                a.erase(it);
                return;
            }
        }
        updateFile();
    }

    void display() const
    {
        cout << "ID\tMoTa\t\t\t\tSoTien\tLoai\tNgay" << endl;
        cout << "---------------------------------------------------" << endl;
        for (const auto &x : a)
        {
            cout << x << endl;
        }
    }

    void totalIncome() const
    {
        float sum = 0;
        for (const auto &x : a)
        {
            if (x.getType() == "ThuNhap")
            {
                sum += x.getAmount();
            }
        }
        cout << fixed << setprecision(0) << sum << endl;
    }

    void totalExpense() const
    {
        float sum = 0;
        for (const auto &x : a)
        {
            if (x.getType() == "ChiPhi")
            {
                sum += x.getAmount();
            }
        }
        cout << fixed << setprecision(0) << sum << endl;
    }

    void sortTransactions()
    {
        for (auto it1 = a.begin(); it1 != a.end(); ++it1)
        {
            auto minIt = it1;

            auto it2 = it1;
            ++it2;

            for (; it2 != a.end(); ++it2)
            {
                if (it2->getComparableDate() < minIt->getComparableDate())
                {
                    minIt = it2;
                }
            }

            if (minIt != it1)
            {
                iter_swap(it1, minIt);
            }
        }
    }

    Transaction findTransaction(const string &id) const
    {
        for (const auto &x : a)
        {
            if (x.getId() == id)
            {
                return x;
            }
        }
        cout << "KHONG TIM THAY GIAO DICH" << endl;
    }

    void filterByDateRange(const string &startDate, const string &endDate) const
    {
        cout << "Giao dich tu " << startDate << " den " << endDate << ":" << endl;
        cout << left << setw(10) << "ID"
             << setw(20) << "Mo Ta"
             << setw(12) << "So Tien"
             << setw(15) << "Loai"
             << setw(12) << "Ngay" << endl;
        cout << string(69, '-') << endl;
        string ComparableStartDate = startDate.substr(6, 4) + startDate.substr(3, 2) + startDate.substr(0, 2);
        string ComparableEndDate = endDate.substr(6, 4) + endDate.substr(3, 2) + endDate.substr(0, 2);

        for (const auto &x : a)
        {
            // Compare the transaction date with the given range
            if (x.getComparableDate() >= ComparableStartDate && x.getComparableDate() <= ComparableEndDate)
            {
                cout << x;
            }
        }
    }

    Transaction findMaxTransactions()
    {
        Transaction maxTransaction = a.front();
        for (const auto &transaction : a)
        {
            if (transaction.getAmount() > maxTransaction.getAmount())
            {
                maxTransaction = transaction;
            }
        }

        return maxTransaction;
    }

    Transaction findMinTransactions()
    {
        Transaction minTransaction = a.front();
        for (const auto &transaction : a)
        {
            if (transaction.getAmount() < minTransaction.getAmount())
            {
                minTransaction = transaction;
            }
        }

        return minTransaction;
    }
};

class App
{
private:
    TransactionHistory a;

public:
    void run()
    {
        a.readFromFile();
        cout << "---------------------------------------------------" << endl;
        cout << "             QUAN LI GIAO DICH                    " << endl;
        cout << "---------------------------------------------------" << endl;
        int choice;
        do
        {
            cout << "1: Them GD" << endl;
            cout << "2: Xoa GD" << endl;
            cout << "3: Tim GD" << endl;
            cout << "4: Danh sach GD" << endl;
            cout << "5: In giao dich trong khoang ngay" << endl;
            cout << "6: Tim GD lon nhat" << endl;
            cout << "7: Tim GD nho nhat" << endl;
            cout << "8: Tong thu nhap" << endl;
            cout << "9: Tong chi phi" << endl;
            cout << "0: Thoat" << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "Chon thao tac: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                Transaction b;
                cin >> b;
                a.addTransaction(b);
                cout << "Them GD thanh cong!" << endl;
                break;
            }

            case 2:
            {
                string id;
                cout << "Nhap ma GD can xoa: ";
                cin >> id;
                a.removeTransaction(id);
                cout << "Xoa GD thanh cong!" << endl;
                break;
            }

            case 3:
            {
                string id;
                cout << "Nhap ma GD can tim: ";
                cin >> id;
                cout << a.findTransaction(id) << endl;
                break;
            }

            case 4:
            {
                a.sortTransactions();
                a.display();
                break;
            }

            case 5:
            {
                string startDate, endDate;
                cout << "Nhap ngay bat dau (dd/mm/yyyy): ";
                cin >> startDate;
                cout << "Nhap ngay ket thuc (dd/mm/yyyy): ";
                cin >> endDate;
                a.filterByDateRange(startDate, endDate);
                break;
            }

            case 6:
            {
                Transaction maxTrans = a.findMaxTransactions();
                cout << "Giao dich lon nhat: " << maxTrans << endl;
                break;
            }

            case 7:
            {
                Transaction minTrans = a.findMinTransactions();
                cout << "Giao dich nho nhat: " << minTrans << endl;
                break;
            }

            case 8:
            {
                cout << "Tong thu nhap: ";
                a.totalIncome();
                break;
            }

            case 9:
            {
                cout << "Tong chi phi: ";
                a.totalExpense();
                break;
            }

            case 0:
            {
                cout << "Ket thuc chuong trinh!" << endl;
                return;
            }

            default:
                cout << "Lua chon khong hop le!" << endl;
            }
        } while (choice != 0);
    }
};

int main()
{
    App app;
    app.run();
    return 0;
}
