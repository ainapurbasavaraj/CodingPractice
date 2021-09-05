// ChainOfResponsibility.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;


class BaseValidator {
    BaseValidator* nextValidator = nullptr;
public:
    virtual string validate(const string& input) {
        if (nextValidator) {
            return nextValidator->validate(input);
        }
        else {
            return "Validation is successfull.";
        }
    }

    virtual BaseValidator* setNext(BaseValidator* next) {
        nextValidator = next;
        return next;
    }

};

class NullValidate :public BaseValidator {
public:
    string validate(const string& input) {
        cout << "checking for null string" << endl;
        if (input.empty()) 
            return "Enter non empty string";
        else
            return BaseValidator::validate(input);
    }
};

class formatValidator :public BaseValidator {
public:
    string validate(const string& input) {
        cout << "checking for  string format" << endl;
        if (input.empty()) // TO DO check for format
            return "Enter non empty string";
        else
            return BaseValidator::validate(input);
    }
};

int main()
{
    BaseValidator* baseValidator = new BaseValidator();
    NullValidate* nullValidator = new NullValidate();
    formatValidator* formatValidate = new formatValidator();
    baseValidator->setNext(nullValidator)->setNext(formatValidate);

    cout << baseValidator->validate("Basu") << endl;;

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
