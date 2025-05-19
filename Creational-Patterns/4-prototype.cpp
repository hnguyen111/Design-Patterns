#include <string>
#include <iostream>

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype {
    protected:
        std::string prototypeName;
        float prototypeField;
    public:
        Prototype() {}
        Prototype(std::string prototypeName_) : prototypeName(prototypeName_) {}
        virtual ~Prototype() {}
        virtual Prototype* clone() const = 0;
        virtual void method(float prototypeField_) {
            prototypeField = prototypeField_;
            std::cout << "Call method from " << prototypeName << " with field: " << prototypeField << std::endl;
        }
};

class ConcretePrototype1 : public Prototype {
    private:
        float concretePrototypeField1;
    public:
        ConcretePrototype1(std::string prototypeName, float concretePrototypeField)
            : Prototype(prototypeName), concretePrototypeField1(concretePrototypeField) {}
        Prototype* clone() const override {
            return new ConcretePrototype1(*this);
        }
};
class ConcretePrototype2 : public Prototype {
    private:
        float concretePrototypeField2;
    public:
        ConcretePrototype2(std::string prototypeName, float concretePrototypeField)
            : Prototype(prototypeName), concretePrototypeField2(concretePrototypeField) {}
        Prototype* clone() const override {
            return new ConcretePrototype2(*this);
        }
};

class PrototypeFactory {
    private:
        std::unordered_map<Type, Prototype*, std::hash<int>> prototypes;
    public:
        PrototypeFactory() {
            prototypes[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1", 10.f);
            prototypes[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2", 20.f);
        }
        ~PrototypeFactory() {
            delete prototypes[Type::PROTOTYPE_1];
            delete prototypes[Type::PROTOTYPE_2];
        }
        Prototype* createPrototype(Type type) {
            return prototypes[type]->clone();
        }
};

void Client(PrototypeFactory& prototypeFactory) {
    std::cout << "Let's create a Prototype1.\n";
    Prototype* prototype = prototypeFactory.createPrototype(Type::PROTOTYPE_1);
    prototype->method(11);
    delete prototype;

    std::cout << "\nLet's create a Prototype2.\n";
    prototype = prototypeFactory.createPrototype(Type::PROTOTYPE_2);
    prototype->method(12);
    delete prototype;
}

int main() {
    PrototypeFactory* prototypeFactory = new PrototypeFactory();
    Client(*prototypeFactory);
    delete prototypeFactory;
}

/* Output:
Let's create a Prototype1.
Call method from PROTOTYPE_1 with field: 11

Let's create a Prototype2.
Call method from PROTOTYPE_2 with field: 12
*/