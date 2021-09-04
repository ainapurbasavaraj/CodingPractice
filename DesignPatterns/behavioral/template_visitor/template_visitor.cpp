// template_visitor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*

THis is combination of visitor and Template pattern.

usecase is : Generating greetingcard from person.

Template pattern --> Generating the card with template method

Visitor Pattern:
Instead of adding the generatecard functionality to Person class.
Create visitor which Person can visit to to generate the greeting card as its not responsibility of the person.

*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Visitor
{
public:
    virtual void handlePerson(std::string from) = 0;
};

class Person {
    int age;
    string name;
public:
    Person(int age, string name) :age(age), name(name) {}
    string getName() { return name; }
    void sendCards(Visitor* v) {
        v->handlePerson(name);
    }

};


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

class BirthdayTemplate :public GreetingCardTemplate {
protected:
    string intro(string to) override {
        return "Dear " + to;
    }

    string occassion() override {
        return "\nHappy Birthday!!\n";
    }
};


class GenerateCard :public Visitor {
    GreetingCardTemplate* tempate;
    //vector<Person*> persons;
    string to;
public:
    GenerateCard(string to) :to(to) {}
    void setTemplate(GreetingCardTemplate* gtp) { tempate = gtp; }
    /*void addPerson(Person* person) {
        persons.push_back(person);
    }*/

    void handlePerson(string name) {
        cout << tempate->generatecard(name, to);
    }

};
int main()
{
    Person* p1 = new Person(32, "Basu");
    GenerateCard* grc = new GenerateCard("Shweta");
    GreetingCardTemplate* bt = new BirthdayTemplate();
    grc->setTemplate(bt);
    //grc->addPerson(p1);

    p1->sendCards(grc);
    delete p1;
}