#include <iostream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

int main() {
    string line;
    map<string, int> vars;
    int step = 1;

    cout << "Enter your code (empty line to stop):" << endl;

    while (true) {
        getline(cin, line);
        if (line == "") break;

        stringstream ss(line);
        string word;
        ss >> word;

        // Declaration → int a = 5;
        if (word == "int") {
            string var, eq;
            int value;

            ss >> var >> eq >> value;

            vars[var] = value;

            cout << "Step " << step++
                 << " -> " << var << " initialized to " << value << endl;
        }

        // Assignment → a = a + 2;
        else {
            string var = word;
            string eq, var2, op;
            int num;

            ss >> eq >> var2 >> op >> num;

            // ❗ Check RHS variable
            if (vars.find(var2) == vars.end()) {
                cout << "Error at Step " << step++
                     << " -> Variable '" << var2 << "' not declared" << endl;
                continue;
            }

            // ❗ Initialize LHS if not declared (optional smart behavior)
            if (vars.find(var) == vars.end()) {
                vars[var] = 0;
            }

            if (op == "+") {
                vars[var] = vars[var2] + num;
            } else if (op == "-") {
                vars[var] = vars[var2] - num;
            } else {
                cout << "Error at Step " << step++
                     << " -> Unsupported operation" << endl;
                continue;
            }

            cout << "Step " << step++
                 << " -> " << var << " updated to " << vars[var] << endl;
        }
    }

    return 0;
}