// C++ program to demonstrate appending of
// a string using ofstream
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    ofstream of;
    fstream f;

    // opening file using ofstream
    of.open("file.txt", ios::app);
    if (!of)
        cout << "No such file found";
    else
    {
        of << "String";
        cout << "Data appended successfully\n";
        of.close();
        string word;

        // opening file using fstream
        f.open("file.txt");
        while (getline(f, word))
        {
            cout << word << endl;
        }
        f.close();
    }
    return 0;
}
