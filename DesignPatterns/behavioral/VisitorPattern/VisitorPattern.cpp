// VisitorPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Visitor pattern allows you to decouple the functionality from the class for which the class is not intended.

example below:

Person or Car need to be written to DB or file.
But its not responsibility of that class itself.

Visitor pattern will implement these (DB or File) functionality and it will be decouple from the Person or Car class.
Person and Car class can use these functionality by adding a method in respective classes.

*/

#include <iostream>
#include <string>
using namespace std;

class Visitor
{
public:
    virtual void handlePerson(const int&age, const string& name) = 0;
    virtual void handleCar(const string&name, const string& model) = 0;
};

class Person {
    int age;
    string name;
public:
    Person(int age, string name) :age(age), name(name) {}
    string getName() { return name; }
    void accept(Visitor* v) {
        v->handlePerson(age, name);
    }

};

class Car {
    string name;
    string model;
public:
    Car(string name, string model) :name(name), model(model) {}
    string getName() { return name; }

    void accept(Visitor* v) {
        v->handleCar(name, model);
    }
};



class WriteToDatabase :public Visitor {
public:
    void handlePerson(const int& age, const string& name) override {
        cout << "writing " + name + " To database.\n";
    }

    void handleCar(const string& name, const string& model) override {
        cout << "Writing " + name + " To database.\n";
    }
};

class WriteToFile :public Visitor {
public:
    void handlePerson(const int& age, const string& name) override {
        cout << "writing " + name + " To File.\n";
    }

    void handleCar(const string& name, const string& model) override {
        cout << "Writing " + name + " To File.\n";
    }
};

int main()
{
    Visitor* dbv = new WriteToDatabase();
    Visitor* fv = new WriteToFile();

    Person p(32, "Basu");
    Car c("Hyundai", "Creta");

    p.accept(dbv);
    p.accept(fv);
    c.accept(dbv);
    c.accept(fv);

    return 0;
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
