// #include <iostream>
// #include <map>
// #include <string>
// #include <memory>
// #include <chrono>
// #include <bits/stdc++.h>
// using namespace std;
// #ifdef _WIN32
// #include <windows.h>
// #else
// #endif

// #include <regex>
// #include <windows.h>
// using namespace std;

// class User
// {
// private:
//     string username;
//     string password;
//     string name;
//     string state;
//     string address;
//     string referenceLocation;
//     string preference;

// public:
//     User(string uname, string pwd, string nm, string st, string addr, string refLoc, string pref) : username(uname), password(pwd), name(nm), state(st), address(addr), referenceLocation(refLoc), preference(pref) {}

//     string getUsername() const
//     {
//         return username;
//     }

//     bool checkCredentials(const string &uname, const string &pwd) const
//     {
//         return (username == uname && password == pwd);
//     }
// };

// class FoodApp
// {
// private:
//     vector<User> users;

// public:
//     void signUp()
//     {
//         string uname, pwd, name, state, address, referenceLocation, preference;
//         cout << "Enter name: ";
//         cin.ignore();
//         getline(cin, name);
//         cout << "Enter state: ";
//         getline(cin, state);
//         cout << "Enter address: ";
//         getline(cin, address);
//         cout << "Enter reference location: ";
//         getline(cin, referenceLocation);
//         cout << "Set username: ";
//         cin >> uname;
//         cout << "Set password: ";
//         cin >> pwd;
//         cout << "Enter preference (veg/nonveg): ";
//         cin >> preference;

//         users.push_back(User(uname, pwd, name, state, address, referenceLocation, preference));
//         cout << "Signed up successfully!\n";
        // ofstream userFile("admin.txt", ios::app); // Open file in append mode
        // if (userFile.is_open())
        // {
        //     userFile << "Username: " << uname << endl;
        //     userFile << "Name: " << name << endl;
        //     userFile << "State: " << state << endl;
        //     userFile << "Address: " << address << endl;
        //     userFile << "Reference Location: " << referenceLocation << endl;
        //     userFile << "Preference: " << preference << endl
        //              << endl;
        //     userFile.close(); // Close the file after writing
        //     cout << "Signed up successfully!\n";
        // }
        // else
        // {
        //     cout << "Error: Unable to open user_data.txt for writing." << endl;
        // }
//     }

//     bool login()
//     {
//         string uname, pwd;
//         cout << "Enter username: ";
//         cin >> uname;
//         cout << "Enter password: ";
//         cin >> pwd;

//         for (const auto &user : users)
//         {
//             if (user.checkCredentials(uname, pwd))
//             {
//                 cout << "Login successful!\n";
//                 return true;
//             }
//         }

//         cout << "Invalid username or password. Please try again.\n";
//         return false;
//     }

//     void displayUsernames() const
//     {
//         cout << "Registered usernames:\n";
//         for (const auto &user : users)
//         {
//             cout << user.getUsername() << endl;
//         }
//     }
// };

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <chrono>
#include <bits/stdc++.h>
using namespace std;
#ifdef _WIN32
#include <windows.h>
#else
#endif

#include <regex>
#include <windows.h>
using namespace std;

class User
{
private:
    string username;
    string password;
    string name;
    string state;
    string address;
    string referenceLocation;
    string preference;
public:
    User(string uname, string pwd, string nm, string st, string addr, string refLoc, string pref) : username(uname), password(pwd), name(nm), state(st), address(addr), referenceLocation(refLoc), preference(pref) {}

    string getUsername() const
    {
        return username;
    }

    bool checkCredentials(const string &uname, const string &pwd) const
    {
        return (username == uname && password == pwd);
    }
};

class FoodApp
{
private:
    vector<User> users;

public:
    void signUp()
    {
        string uname, pwd, name, state, address, referenceLocation, preference;
        cout << "Enter name: ";

        cin.ignore();
        getline(cin, name);
        if(name.empty()|| all_of(name.begin(), name.end(), ::isdigit)){
            cout<<"Invalid user input !!"<<endl;
            cout<<"Enter valid input:"<<endl;
            getline(cin, name);

        }
        cout << "Enter state: ";
        getline(cin, state);
        if(state.empty()|| all_of(state.begin(), state.end(), ::isdigit)){
            cout<<"Invalid user input !!"<<endl;
            getline(cin, state);
            
        }
        cout << "Enter address: ";
        getline(cin, address);
        if(address.empty()|| all_of(address.begin(), address.end(), ::isdigit)){
            cout<<"Invalid address input !!"<<endl;
            getline(cin, address);
        }
        cout << "Enter reference location: ";
        getline(cin, referenceLocation);
        if(referenceLocation.empty()|| all_of(referenceLocation.begin(), referenceLocation.end(), ::isdigit)){
            cout<<"Invalid reference location !!"<<endl;
            getline(cin, referenceLocation);
        }
        cout << "Set username: ";
        cin >> uname;
        if(uname.empty()|| all_of(uname.begin(), uname.end(), ::isdigit)){
            cout<<"Invalid username !!"<<endl;
            cin >> uname;
        }
        cout << "Set password: ";
        cin >> pwd;
        cout << "Enter preference (veg/nonveg): ";
        cin >> preference;
        if(preference.length()==0){
            cout<<"invalid"<<endl;
        }

        users.push_back(User(uname, pwd, name, state, address, referenceLocation, preference));
        cout << "Signed up successfully!\n";

        ofstream userFile("admin.txt", ios::app); // Open file in append mode
        if (userFile.is_open())
        {
            userFile << "Username: " << uname << endl;
            userFile << "Name: " << name << endl;
            userFile << "State: " << state << endl;
            userFile << "Address: " << address << endl;
            userFile << "Reference Location: " << referenceLocation << endl;
            userFile << "Preference: " << preference << endl
                     << endl;
            userFile.close(); // Close the file after writing
            cout << "Signed up successfully!\n";
        }
        else
        {
            cout << "Error: Unable to open user_data.txt for writing." << endl;
        }
    }

    bool login()
    {
        string uname, pwd;
        cout << "Enter username: ";
        cin >> uname;
        cout << "Enter password: ";
        cin >> pwd;

        for (const auto &user : users)
        {
            if (user.checkCredentials(uname, pwd))
            {
                cout << "Login successful!\n";
                return true;
            }
        }

        cout << "Invalid username or password. Please try again.\n";
        return false;
    }

    void displayUsernames() const
    {
        cout << "Registered usernames:\n";
        for (const auto &user : users)
        {
            cout << user.getUsername() << endl;
        }
    }
};


