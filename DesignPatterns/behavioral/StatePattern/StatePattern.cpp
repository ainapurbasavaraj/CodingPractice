// StatePattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class State {
    State* nextState = nullptr;
public:
    virtual ~State() {}
    void setNextState(State* next) { nextState = next; }
    State* getNextState() { return nextState; }
    virtual string execute() = 0;
};

class OrderedState :public State {
public:
    string execute() override {
        return "Processing the order. current state is ORDERED. ";
    }
};

class InTransitState :public State {
public:
    string execute() override {
        return "Processing the order. Current state is IN-TRANSIT" ;
    }
};

class DeliveredStated : public State {
public:
    string execute() override {
        return "delivering your order! It will arrive soon";
    }
};
class purchase {
    State* currentState;
public:
    purchase(State* curState) :currentState(curState) {}
    ~purchase() {}
    string getCurrentState() {
        if (currentState)
            return currentState->execute();
    }

    void goToNextState() {
        if (currentState->getNextState())
            currentState = currentState->getNextState();
        else
            cout << "Order is completed." << endl;
    }
};

int main()
{
    State* initialState = new OrderedState();
    State* InTransit = new InTransitState();
    State* delivered = new DeliveredStated();

    initialState->setNextState(InTransit);
    InTransit->setNextState(delivered);
    delivered->setNextState(nullptr);

    purchase* order = new purchase(initialState);
    cout<< order->getCurrentState()<<endl;
    order->goToNextState();
    cout << order->getCurrentState() << endl;
    order->goToNextState();
    cout << order->getCurrentState() << endl;
    order->goToNextState();

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
