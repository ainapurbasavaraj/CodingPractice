// templatePattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;


class GreetingCardTemplate {
protected:
    virtual string intro(string to) {
        return "Hello! " + to;
    }

    virtual string occassion() {
        return "\nJust saying hi\n";
    }

    virtual string closing(string from) {
        return "Sincerely, \n " + from + "\n";
    }
public:
    string generatecard(string from, string to) {
        return intro(to) + occassion() + closing(from);
    }
};

class BirthdayTemplate:public GreetingCardTemplate {
protected:
    string intro(string to) override {
        return "Dear " + to;
    }

    string occassion() override {
        return "\nHappy Birthday!!\n";
    }
};
int main()
{
    GreetingCardTemplate gtc;
    BirthdayTemplate btc;

    cout << gtc.generatecard("basu", "shweta") << endl;
    cout << btc.generatecard("Shweta", "Basu") << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
