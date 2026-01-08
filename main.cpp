#include<iostream>
#include<ctime>
#include<fstream>
#include<cstdlib>
#include<algorithm>
#include<conio.h>
using namespace std;

class PersonalAssistent
{
    public:
        void start();
    private:
        void openApp(string prompt);
        void filehandling();
        void showtime();
        void calculate();
        template <typename T>
        void calculateTemplate();
};

class LoginToAssistent : public PersonalAssistent
{ 
    public: 
        bool login();
};

string gethiddenpassword()
{
    string password;
    char ch;
    while(true)
    {
        ch = _getch();
        if(ch == 13)
        {
            break;
        }
        else if(ch == 8)
        {
            if(!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            password.push_back(ch);
            cout << "*";
        }
    }
    cout << endl;
    return password;
}

bool LoginToAssistent :: login()
{
    string userid,pass;
    string Fileid,Filepass;
    cout << "=============LOGIN=============" << endl;
    cout << "USER ID: ";
    cin >> userid;
    cout << "PASSWORD: ";
    pass = gethiddenpassword();
    ifstream file("user.txt");
    if(!file)
    {
        cout << "User database not found" << endl;
        return false;
    }
    while(file >> Fileid >> Filepass)
    {
        if(!Filepass.empty() && Filepass.back() == '\r')
            Filepass.pop_back();
        if(userid == Fileid && pass == Filepass)
        {
            cout << "LOGGED IN SUCCESSFULLY" << endl;
            cin.ignore();
            return true;
        }
    }
    cout << "\nInvalid ID or Password!\n";
    return false;
}

void PersonalAssistent :: openApp(string prompt)
{
    transform(prompt.begin(),prompt.end(),prompt.begin(), :: tolower);
    if(prompt == "open chatgpt")
    {
        system("start https://chatgpt.com/");  //open in place of start for mac 
    }
    else if(prompt == "open youtube")
    {
        system("start https://www.youtube.com/"); //open in place of start for mac 
    }
    else if(prompt == "open chrome") 
    {
        system("start chrome"); //open in place of start for mac 
    }
    else if(prompt == "open calculator")
    {
        system("start calc"); //open in place of start for mac and write Calculator in place of calc
    }
    else if(prompt == "open gemini")
    {
        system("start https://gemini.google.com/app"); //open in place of start for mac
    }
    else 
    {
        cout << "Äpplication not found" << endl;
    }
}

template <typename T>
void PersonalAssistent :: calculateTemplate()
{
    T a,b;
    char op;
    cout << "Enter two numbers for calculation (+,-,*,/) like (5+8): ";
    cin >> a >> op >> b;
    switch(op)
    {
        case '+':
        cout << "Addition of " << a << " and " << b << " is: " << a + b;
        break;
        case '-':
        cout << "Subtraction of " << a << " and " << b << " is: " << a - b;
        break;
        case '*':
        cout << "Multiplication of "<< a << " and " << b << " is: " << a * b;
        break;
        case '/':
        if(b != 0)
        {
            cout << "Division of " << a << " and " << b << " is: " << a / b << endl;
        }
        else 
        {
            cout << "Not divisible by 0";
        }
        break;
        default:
        cout << "Invalid operation!" << endl;
    }
    cin.ignore();
}

void PersonalAssistent :: calculate() 
{
    int choice;
    cout << "Choose data type:\n";
    cout << "1. int" << endl;
    cout << "2. float" << endl;
    cout << "3. double" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    switch (choice)
    {
        case 1:
            calculateTemplate<int>();
            break;
        case 2:
            calculateTemplate<float>();
            break;
        case 3:
            calculateTemplate<double>();
            break;
        default:
            cout << "Invalid choice!\n";
    }
    cin.ignore();
}

void PersonalAssistent :: showtime()
{
    time_t now = time(0);
    cout << "Current date & time: " << ctime(&now);
}

void PersonalAssistent :: filehandling()
{
    ofstream file("notes.txt" , ios::app);
    string note;
    cin.ignore();
    getline(cin,note);
    file << note << endl;
    file.close();
    cout << "Note saved succesfully" << endl;
}

void PersonalAssistent :: start()
{
    string command;
    cout << "=====================\nPersonal Assistent\n=====================" << endl;
    cout << "Commands: " << endl;
    cout << "-open chatgpt" << endl;
    cout << "-open gemini" << endl;
    cout << "-open chrome" << endl;
    cout << "-open youtube" << endl;
    cout << "-open calculator" << endl;
    cout << "-calculate (+,-,*,/)" << endl;
    cout << "-show time" << endl;
    cout << "-write note" << endl;
    cout << "-exit (To exit the personal assistent)" << endl;
    while(true)
    {
        cout << "\n>";
        getline(cin, command);
        transform(command.begin(), command.end(), command.begin(), ::tolower);
        if(command == "exit")
            break;
        else if(command.find("open") != string::npos)
            openApp(command);
        else if(command == "calculate")
            calculate();
        else if(command == "show time")
            showtime();
        else if(command == "write note")
            filehandling();
        else 
            cout << "Unknown Command!" << endl;
    }
    cout << "Goodbye" << endl;
}

int main()
{
    LoginToAssistent assistent;
    if(assistent.login())
    {
        assistent.start();
    }
    else
    {
        cout << "ACCESS DENIED" << endl;
    }
    return 0;
}
