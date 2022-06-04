#include "iostream"
#include <memory>
using namespace std;

class coffeeMachine{

public:
	virtual void brew() = 0;
	virtual ~coffeeMachine(){}
};

class simpleCoffeeMachine:public coffeeMachine{

public:
	void brew(){
		cout<<"Brewing simple coffee"<<endl;
	}

};

class RobustCoffeeMachine:public coffeeMachine{

public:
	void brew(){
		cout<<"Brewing Robust coffee"<<endl;
	}
};


class coffee{

public:
	virtual void stir() = 0;
	virtual ~coffee(){}

};

class simpleCoffee:public coffee{

public:
	void stir(){
		cout<<"Stirring simple coffee"<<endl;
	}

};

class robustCoffee:public coffee{

public:
	void stir(){
		cout<<"Stirring robust coffee"<<endl;
	}
};


class coffeeFactory{

public:
	virtual std::unique_ptr<coffeeMachine> createMachine() = 0;
	virtual std::unique_ptr<coffee> createCoffee() = 0;
	virtual ~coffeeFactory(){};

};

class simpleCoffeeFactory:public coffeeFactory{

public:
	std::unique_ptr<coffeeMachine> createMachine(){
		return std::make_unique<simpleCoffeeMachine>();
	}

	std::unique_ptr<coffee> createCoffee(){
		return std::make_unique<simpleCoffee>();
	}

};

class robustCoffeeFactory:public coffeeFactory{

public:
	std::unique_ptr<coffeeMachine> createMachine(){
		return std::make_unique<RobustCoffeeMachine>();
	}

	std::unique_ptr<coffee> createCoffee(){
		return std::make_unique<robustCoffee>();
	}

};



int main()
{

auto factory1 = std::make_unique<simpleCoffeeFactory>();
factory1->createMachine()->brew();
factory1->createCoffee()->stir();

auto factory2 = std::make_unique<robustCoffeeFactory>();
factory2->createMachine()->brew();
factory2->createCoffee()->stir();
return 0;
}
