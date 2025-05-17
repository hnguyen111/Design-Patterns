#include <vector>
#include <string>
#include <iostream>

class Product1 {
    public:
        std::vector<std::string> parts_;
        void listParts() const {
            std::cout << "Product parts: ";
            for (size_t i = 0; i < parts_.size(); ++i) {
                if (i == parts_.size() - 1) {
                    std::cout << parts_[i];
                } else {
                    std::cout << parts_[i] << ", ";
                }
            }
            std::cout << "\n\n";
        }
};

class Builder {
    public:
        virtual ~Builder() {}
        virtual void producePartA() const = 0;
        virtual void producePartB() const = 0;
        virtual void producePartC() const = 0;
};

class ConcreteBuilder1: public Builder {
    private:
        Product1* product;
    public:
        ConcreteBuilder1() {
            reset();
        }
        ~ConcreteBuilder1() {
            delete product;
        }
        void reset() {
            product = new Product1();
        }
        void producePartA() const override {
            product->parts_.push_back("PartA1");
        }
        void producePartB() const override {
            product->parts_.push_back("PartB1");
        }
        void producePartC() const override {
            product->parts_.push_back("PartC1");
        }
        Product1* getProduct() {
            Product1* result = product;
            reset();
            return result;
        }
};

class Director {
    private:
        Builder* builder;
    public:
        void setBuilder(Builder* builder) {
            this->builder = builder;
        }
        void buildMinimalViableProduct() {
            builder->producePartA();
        }
        void buildFeaturedProduct() {
            builder->producePartA();
            builder->producePartB();
            builder->producePartC();
        }
};

void ClientCode(Director& director) {
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.setBuilder(builder);

    std::cout << "Standard basic product:\n";
    director.buildMinimalViableProduct();
    Product1* product = builder->getProduct();
    product->listParts();
    delete product;

    std::cout << "Standard fully featured product:\n";
    director.buildFeaturedProduct();
    product = builder->getProduct();
    product->listParts();
    delete product;

    std::cout << "Customized product:\n";
    builder->producePartA();
    builder->producePartC();
    product = builder->getProduct();
    product->listParts();
    delete product;

    delete builder;
}

int main() {
    Director* director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}

/* Output:
Standard basic product:
Product parts: PartA1

Standard fully featured product:
Product parts: PartA1, PartB1, PartC1

Customized product:
Product parts: PartA1, PartC1
*/