// AbstractFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

class view {
public:
    virtual void buildview() {};
    virtual ~view() {};
};

class mountainView :public view {
private:
    string mountains;
    string trees;
    string falls;
public:
    mountainView() {
        buildview();
    }
    void buildview() {
        cout << "building mountain view" << endl;
        mountains = "!/||/!";
        trees = "|^^|";
        falls = "------";
    }
};

class forestview :public view {
private:
    string trees;
    string animals;
public:

    forestview() {
        buildview();
    }
    void buildview() {
        cout << "building forest view" << endl;
        trees = "|^^|";
        animals = "tigers, elephants!";
    }
};

//Abstract factory class
class Level {
public:
    virtual view* createview() = 0;
    //virtual void createActor() = 0;
    virtual ~Level() = 0 {
    }

};

class Level1 :public Level {
public:
    view* createview() {
        return new mountainView();
    }

    virtual ~Level1() {}

};

class Level2 :public Level {
public:
    view* createview() {
        return new forestview();
    }
    virtual ~Level2() {}
};


static Level* getLevel(int level) {
    switch (level) {
    case 1:
        return new Level1();

    case 2:
        return new Level2();

    default:
        return nullptr;

    }
}


int main()
{
    Level* gameLevel = getLevel(2);
    gameLevel->createview();
}

