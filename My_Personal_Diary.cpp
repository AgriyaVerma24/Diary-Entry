#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class Diary {
private:
    string fileName;
    string DT() { 
        time_t now = time(0);
        tm* ltm = localtime(&now);
        return to_string(1900 + ltm->tm_year) + "-" + 
               to_string(1 + ltm->tm_mon) + "-" + 
               to_string(ltm->tm_mday) + " " + 
               to_string(ltm->tm_hour) + ":" + 
               to_string(ltm->tm_min); 
    }

public:
    Diary() : fileName("DiaryEntry.txt") {} 

    void addEntry() {
        ofstream outFile;
        outFile.open(fileName, ios::app); 
        if (!outFile) {
            cout << "Oops! Couldn't open the file!" << endl;
            return; 
        }
        string entry;
        cout << "\nWrite your diary entry (type 'END' when done):\n";
        cout << "-------------------------------------------\n";
        getline(cin, entry);
        while (entry != "END") {
            outFile << DT() << " - " << entry << endl; 
            cout << "Got more to say? Type it or 'END' to stop\n";
            getline(cin, entry);
        }
        outFile.close();
        cout << "Sweet! Entry saved!\n"; 
    }

    void displayEntries() {
        ifstream inFile;
        inFile.open(fileName);
        if (!inFile) {
            cout << "Hey, no entries yet! Start writing!\n";
            return; 
        }
        string line;
        cout << "\nYour Diary Entries:\n";
        cout << "-------------------\n";
        while (getline(inFile, line)) {
            cout << line << endl; 
        }
        inFile.close();
    }

    void searchEntry() {
        ifstream inFile;
        inFile.open(fileName);
        if (!inFile) {
            cout << "No entries to search, add some first!\n";
            return;
        }
        string searchDate;
        cout << "\nType a date to search (YYYY-MM-DD): ";
        cin.ignore(); 
        getline(cin, searchDate);
        string line;
        bool found = false;
        cout << "\nSearch Results:\n";
        cout << "--------------\n";
        while (getline(inFile, line)) {
            if (line.find(searchDate) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Hmm, nothing found for " << searchDate << "!\n";
        }
        inFile.close();
    }
};

int main() {
    Diary diary; 
    int choice;
    while (true) {
        cout << "\n=== Personal Diary Manager ===\n";
        cout << "1. Add New Entry\n";
        cout << "2. Display All Entries\n";
        cout << "3. Search Entry by Date\n";
        cout << "4. Exit\n";
        cout << "What do you wanna do? Pick a number: ";
        cin >> choice;
        cin.ignore(); 
        switch (choice) {
            case 1:
                diary.addEntry();
                break;
            case 2:
                diary.displayEntries();
                break;
            case 3:
                diary.searchEntry();
                break;
            case 4:
                cout << "Catch you later! Keep writing!\n";
                return 0;
            default:
                cout << "Whoops, wrong number! Try again.\n";
        }
    }
    return 0;
}