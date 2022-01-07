#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip> 
#include <vector>

using namespace std;

vector<int> f_width = { 20, 15, 40, 15, 15, 15, 15, 15 };

void read_csv_line(string line) {
    stringstream ss(line);
    int i = 0;
    while (ss.good()) {
        string field;
        getline(ss, field, ',');
        cout << std::setw(f_width[i]) << field << " | ";
        ++i;
    }
    cout << "\n";
}

void read_csv_file(string fileName) {

    ifstream myfile(fileName);

    string line;
    while (getline(myfile, line)) {
        read_csv_line(line);
    }

}

int main()
{
    string file = "C:\\Users\\dolphin\\Downloads\\addresses.csv";

    read_csv_file(file);
    std::cout << "Hello World!\n";
}
