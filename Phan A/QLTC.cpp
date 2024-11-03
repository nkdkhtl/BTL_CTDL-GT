#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;
//Khuc Phuong Nam - 231230845
class Transaction {
private:
    string id;
    string description;
    float amount;
    string type;
    string date;
public:
    Transaction() : id(""), description(""), amount(0.0), type(""), date("") {}
    Transaction(string id , string desc , float amount , string type , string date ) {
        this->id = id;
        this->description = desc;
        this->amount = amount;
        this->type = type;
        this->date = date;
    }

    friend istream& operator>>(istream& inp, Transaction& a) {
        cout << "Nhap ma GD: "; inp >> a.id;
        cout << "Nhap mo ta: "; cin.ignore(); getline(cin, a.description);
        cout << "Nhap so tien: "; inp >> a.amount;
        cout << "Nhap loai GD (ThuNhap hoac ChiPhi): "; inp >> a.type;
        cout << "Nhap ngay GD (dd/mm/yyyy): "; inp >> a.date;
        return inp;
    }

    friend ostream& operator<<(ostream& out, const Transaction& a) {
        out << a.id << "\t" << a.description << "\t" << fixed << setprecision(0) << a.amount << "\t" << a.type << "\t" << a.date << endl;
        return out;
    }

    bool operator<(const Transaction& b) const {
        return this->amount < b.amount;
    }

    float getAmount() const {
        return this->amount;
    }

    string getId() const {
        return this->id;
    }

    string getType() const {
        return this->type;
    }
};

class TransactionList {
private:
    list<Transaction> a;
public:
    void addTransaction(const Transaction& b) {
        a.push_back(b);
    }

    void removeTransaction(const string& id) {
        for (auto it = a.begin(); it != a.end(); ++it) {
            if (it->getId() == id) {
                a.erase(it);
                return;
            }
        }
    }

    void display() const {
    	cout << "ID\tMoTa\tSoTien\tLoai\tNgay" << endl; 
        for (const auto &x : a) {
            cout << x << endl;
        }
    }

    void totalIncome() const {
        float sum = 0;
        for (const auto& x : a) {
            if (x.getType() == "ThuNhap") {
                sum += x.getAmount();
            }
        }
        cout << sum << endl;
    }

    void totalExpense() const {
        float sum = 0;
        for (const auto& x : a) {
            if (x.getType() == "ChiPhi") {
                sum += x.getAmount();
            }
        }
        cout << sum << endl;
    }

    void sortTransactions() {
        a.sort();
    }

    Transaction findTransaction(const string& id) const {
        for (const auto& x : a) {
            if (x.getId() == id) {
                return x;
            }
        }
    }

    Transaction findMaxTransactions() const {
        return *max_element(a.begin(), a.end());
    }

    Transaction findMinTransactions() const {
        return *min_element(a.begin(), a.end());
    }
};

class App {
private:
    TransactionList a;
public:
    void run() {
        int choice;
        do {
            cout << "1: Them GD" << endl;
            cout << "2: Xoa GD" << endl;
            cout << "3: Danh sach GD" << endl;
            cout << "4: Tim GD lon nhat" << endl;
            cout << "5: Tim GD nho nhat" << endl;
            cout << "6: Tong thu nhap" << endl;
            cout << "7: Tong chi phi" << endl;
            cout << "8: Thoat" << endl;
            cout << "Chon thao tac: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    Transaction b;
                    cin >> b;
                    a.addTransaction(b);
                    break;
                }

                case 2: {
                    string id;
                    cout << "Nhap ma GD can xoa: ";
                    cin >> id;
                    a.removeTransaction(id);
                    break;
                }

                case 3: {
                    a.sortTransactions();
                    a.display();
                    break;
                }

                case 4: {
                    Transaction maxTrans = a.findMaxTransactions();
                    cout << "Giao dich lon nhat: " << maxTrans << endl;
                    break;
                }

                case 5: {
                    Transaction minTrans = a.findMinTransactions();
                    cout << "Giao dich nho nhat: " << minTrans << endl;
                    break;
                }

                case 6: {
                    cout << "Tong thu nhap: ";
                    a.totalIncome();
                    break;
                }

                case 7: {
                    cout << "Tong chi phi: ";
                    a.totalExpense();
                    break;
                }

                case 8: {
                    cout << "Ket thuc chuong trinh" << endl;
                    return;
                }

                default:
                    cout << "Lua chon khong hop le!" << endl;
            }
        } while (choice != 8);
    }
};

int main() {
    App app;
    app.run();
    return 0;
}

