#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>
#include <stdlib.h>

using namespace std;
using json = nlohmann::json;

class User {
    public:
        string username;
        string password;
        bool isNewUser;
        bool accessGranted;
        json j;
    User() {
        isNewUser = true;
        accessGranted = false;

        ifstream inFile("users.json");
        inFile >> this->j;
    }

    void request() {
        /**
        * In charge of asking and storing the username and password
        **/
        string name;
        string pass;
        
        // Get username
        cout << "Username: ";
        getline(cin, name);
        boost::to_lower(name);

        // Get password
        cout << "Password: ";
        getline(cin, pass);

        this->username = name;
        this->password = pass;
    }

    void checkIfUser() {
        /**
        * Checks if the user already exists with correct credentials 
        **/ 
        string wantsNewAccount;

        ifstream inFile("users.json");
        inFile >> this->j;

        // Check to see if the file already has the username in it
        while (this->isNewUser) {
            if (this->j.contains(this->username)) {
                // if the username exists and the password is correct, grant the user access
                if (this->j[this->username] == this->password) {
                    cout << "\033[32m Access Granted \033[0m" << endl;
                    this->isNewUser = false;
                    this->accessGranted = true;
                } else {
                    // Incorrect password. Allow user to try again
                    cout << "Incorrect username or password, please try again" << endl;
                    this->request();
                }
            } else {
                // Notify that the username doesn't exist
                cout << "The username does not exist. Would you like to create an account? (y/n) " << endl;
                cin >> wantsNewAccount;

                if (wantsNewAccount == "y") {
                    // Create new account. 
                    this->createNewAccount();
                    this->checkIfUser();

                    this->isNewUser = false;
                } else {
                    cout << "\033[31m Access denied. \033[0m Exiting" << endl;
                    this->accessGranted = false;
                    break;
                }
            }
        }
    }

    void createNewAccount() {
        // creates new account using user's credentials
        bool uniqueUsername;
        string newUsername;
        string newPassword;

        while (!uniqueUsername) {

            cout << "Enter new username: ";
            cin.ignore();
            getline(cin, newUsername);

            if (!this->j.contains(newUsername)) {
                cout << "Create your own password: ";
                getline(cin, newPassword);

                this->j[newUsername] = newPassword;
                this->username = newUsername;
                this->password = newPassword;

                ofstream outFile("users.json");
                outFile << this->j << endl;
                
                uniqueUsername = true;
            } else {
                cout << newUsername << " is already taken. Please try a different username" << endl;
                uniqueUsername = false;
            }
        }
    }
};