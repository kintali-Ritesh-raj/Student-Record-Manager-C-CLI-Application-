#include <bits/stdc++.h>
using namespace std;

struct Student {
    int id;
    string name;
    double gpa;
};

const string DB_FILE = "records.txt";
const char SEP = '|';

// Read all records from file
vector<Student> read_all(const string &fname) {
    vector<Student> v;
    ifstream in(fname);
    if(!in.is_open()) return v;

    string line;
    while (getline(in, line)) {
        if(line.empty()) continue;
        // expected format: id|name|gpa
        size_t p1 = line.find(SEP);
        size_t p2 = string::npos;
        if (p1 != string::npos) p2 = line.find(SEP, p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue; // skip malformed lines
        string id_str = line.substr(0, p1);
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        string gpa_str = line.substr(p2 + 1);
        try {
            int id = stoi(id_str);
            double gpa = stod(gpa_str);
            v.push_back({id, name, gpa});
        } catch (...) {
            // skip lines with parse errors
            continue;
        }
    }
    return v;
}

// Write all records to file (overwrite)
void write_all(const string &fname, const vector<Student>& v) {
    ofstream out(fname, ios::trunc);
    if(!out.is_open()){
        cerr << "Error: unable to write to file: " << fname << "\n";
        return;
    }
    for(const auto &s : v) {
        // id|name|gpa
        out << s.id << SEP << s.name << SEP << fixed << setprecision(2) << s.gpa << "\n";
    }
}

// Add a new record
void add_record(const string &fname) {
    Student s;
    cout << "Enter id (integer): ";
    while(!(cin >> s.id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter integer id: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

    cout << "Enter Name: ";
    getline(cin, s.name);
    if(s.name.find(SEP) != string::npos) {
        cout << "Note: '|' character is not allowed in name. It will be removed.\n";
        s.name.erase(remove(s.name.begin(), s.name.end(), SEP), s.name.end());
    }

    cout << "Enter GPA (e.g., 8.5): ";
    while(!(cin >> s.gpa)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter numeric GPA: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto v = read_all(fname);
    // check duplicate ID
    for(const auto &st : v) {
        if(st.id == s.id) {
            cout << "A record with this ID already exists. Aborting add.\n";
            return;
        }
    }
    v.push_back(s);
    write_all(fname, v);
    cout << "Saved.\n";
}

// List all records
void list_all(const string &fname) {
    auto v = read_all(fname);
    if(v.empty()) {
        cout << "No records found.\n";
        return;
    }
    cout << left << setw(8) << "ID" << setw(30) << "Name" << setw(8) << "GPA" << "\n";
    cout << string(46, '-') << "\n";
    for(const auto &s : v) {
        cout << left << setw(8) << s.id << setw(30) << s.name << setw(8) << fixed << setprecision(2) << s.gpa << "\n";
    }
}

// Search record by id
void search_record(const string &fname) {
    int id;
    cout << "Enter id to search: ";
    while(!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter integer id: ";
    }
    auto v = read_all(fname);
    for(const auto &s : v) {
        if(s.id == id) {
            cout << "Found:\n";
            cout << "ID: " << s.id << "\n";
            cout << "Name: " << s.name << "\n";
            cout << "GPA: " << fixed << setprecision(2) << s.gpa << "\n";
            return;
        }
    }
    cout << "Not found.\n";
}

// Delete by id
void delete_record(const string &fname) {
    int id;
    cout << "Enter id to delete: ";
    while(!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter integer id: ";
    }
    auto v = read_all(fname);
    vector<Student> out;
    bool removed = false;
    for(const auto &s : v) {
        if(s.id == id) removed = true;
        else out.push_back(s);
    }
    if(!removed) {
        cout << "ID not found.\n";
        return;
    }
    write_all(fname, out);
    cout << "Deleted.\n";
}

int main() {
    cout << "=== Student Record Manager ===\n";
    cout << "(records stored in '" << DB_FILE << "')\n";
    while(true) {
        cout << "\n1. Add  2. List  3. Search  4. Delete  5. Exit\nChoose: ";
        int c;
        if(!(cin >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest of line
        switch(c) {
            case 1: add_record(DB_FILE); break;
            case 2: list_all(DB_FILE); break;
            case 3: search_record(DB_FILE); break;
            case 4: delete_record(DB_FILE); break;
            case 5: cout << "Exiting.\n"; return 0;
            default: cout << "Invalid option.\n"; break;
        }
    }
    return 0;
}
