#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>
#include <stdlib.h>
#include"user.cpp"

using namespace std;
using json = nlohmann::json;

string getMessage() {
    string m;

    cin.ignore();
    cout << "Please insert your message: " ;
    getline(cin, m);
    return m;
}

void pushMessage(string message) {
    /**
    * Takes the given message and writes it to the file messages.txt
    **/
    ofstream file;
    file.open("messages.csv", ios_base::app);
    file << message;
    file.close();
    cout << "message sent" << endl;
}

void viewAllMessages() {
    ifstream file;
    vector<string> row;
    string line, word, temp;
    vector<string> users = {"samuelc7"};
    map<string, string> userColors;

    string outline = "------------------------------------------------------------------------------------";
    file.open("messages.csv", ios::in);

    cout << outline << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        string user, msg, time;
        getline(ss, user, ',');
        getline(ss, msg, ',');
        getline(ss, time, ',');

        cout << "\033[32m " << user << "\033[0m: " << msg << " \033[31m" << time << "\033[0m" << endl << endl;
    }
    cout << outline;
    file.close();
}

void deleteAll() {
    ofstream file;
    file.open("messages.csv", ios::out | ios::trunc);
    file.close();
    cout << "All messages deleted";
}

void sendMessage(string user) {
    bool another = true;
    while (another) {
        string ans;
        string message = getMessage();

        time_t ttime = time(0);
        char* dt = ctime(&ttime);
        message = user + ", '" + message + "' ," + dt;
        pushMessage(message);
        cout << "Would you like to add another message? (y/n): ";
        cin >> ans;
        if (ans == "y") {
            another = true;
        } else {
            another = false;
        }
    }
}

void deleteMessages() {
    string del;

    cout << "Are you sure you want to delete all messages? (y/n): ";
    cin >> del;

    if (del == "y") {
        deleteAll();
    } else {
        cout << "No messages deleted." << endl;
    }
}

string getAction() {
    // Gets user input to decide what happens next
    string input;
    string optionLayout = "\nWhat would you like to do? ";
    optionLayout += "\n\tSend message (m)";
    optionLayout += "\n\tView Conversation (v)";
    optionLayout += "\n\tDelete all messages (d)";
    optionLayout += "\n\tExit (e)";
    optionLayout += "\nPlease enter letter: ";
    
    cout << optionLayout;
    cin >> input;
    boost::to_lower(input);

    return input;
}


int main() {
    bool switchToMenu = true;
    string input;
    tuple<bool, string> userTuple;
    User user;

    cout << "Welcome to the Jasa Messaging System"<< endl;
    user.request();
    user.checkIfUser();

    if (user.accessGranted) {
        while (switchToMenu) {
            cout << "\nWelcome " << user.username;
            string action = getAction();

            if (action == "m") {
                sendMessage(user.username);
            } else if (action == "v") {
                viewAllMessages();
            } else if (action == "d") {
                deleteMessages();
            } else if (action == "e") {
                cout << "Exiting. Thanks for visiting" << endl;
                return 0;
            }

            cout << "\nWould you like to return to the main menu (r) or exit (e)? ";
            cin >> input;
            if (input == "r") {
                switchToMenu = true;
            } else {
                cout << "Exiting. Thanks for visiting" << endl;
                switchToMenu = false;
            }
        }
    }
    return 0;
}