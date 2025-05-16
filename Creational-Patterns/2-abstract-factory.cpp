#include <string>
#include <iostream>

class AbstractProductA {
    public:
        virtual ~AbstractProductA() {};
        virtual std::string usefulFunctionA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA {
    public:
        std::string usefulFunctionA() const override {
            return "The result of the product A1.";
        }
};
class ConcreteProductA2 : public AbstractProductA {
    public:
        std::string usefulFunctionA() const override {
            return "The result of the product A2.";
        }
};

class AbstractProductB {
    public:
        virtual ~AbstractProductB() {}
        virtual std::string usefulFunctionB() const = 0;
        virtual std::string anotherUsefulFunctionB(const AbstractProductA& collaborator) const = 0;
};

class ConcreteProductB1 : public AbstractProductB {
    public:
        std::string usefulFunctionB() const override {
            return "The result of the product B1.";
        }
        std::string anotherUsefulFunctionB(const AbstractProductA& collaborator) const override {
            const std::string result = collaborator.usefulFunctionA();
            return "The result of the B1 collaborating with (" + result + ")";
        }
};
class ConcreteProductB2 : public AbstractProductB {
    public:
        std::string usefulFunctionB() const override {
            return "The result of the product B2.";
        }
        std::string anotherUsefulFunctionB(const AbstractProductA& collaborator) const override {
            const std::string result = collaborator.usefulFunctionA();
            return "The result of the B2 collaborating with (" + result + ")";
        }
};

class AbstractFactory {
    public:
        virtual AbstractProductA* createProductA() const = 0;
        virtual AbstractProductB* createProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory {
    public:
        AbstractProductA* createProductA() const override {
            return new ConcreteProductA1();
        }
        AbstractProductB* createProductB() const override {
            return new ConcreteProductB1();
        }
};
class ConcreteFactory2 : public AbstractFactory {
    public:
        AbstractProductA* createProductA() const override {
            return new ConcreteProductA2();
        }
        AbstractProductB* createProductB() const override {
            return new ConcreteProductB2();
        }
};

void ClientCode(const AbstractFactory& factory) {
    const AbstractProductA* product_a = factory.createProductA();
    const AbstractProductB* product_b = factory.createProductB();
    std::cout << product_b->usefulFunctionB() << "\n";
    std::cout << product_b->anotherUsefulFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1* f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing client code with the second factory type:\n";
    ConcreteFactory2* f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    return 0;
}

/* Output:
Client: Testing client code with the first factory type:
The result of the product B1.
The result of the B1 collaborating with (The result of the product A1.)

Client: Testing client code with the second factory type:
The result of the product B2.
The result of the B2 collaborating with (The result of the product A2.)
*/