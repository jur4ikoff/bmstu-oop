#include <iostream>

class Implementor
{
public:
    virtual ~Implementor() = default;
    virtual void operationImp() = 0;
};

class Abstraction
{
protected:
    std::shared_ptr<Implementor> implementor;

public:
    Abstraction(std::shared_ptr<Implementor> imp) : implementor(imp) {}
    virtual ~Abstraction() = default;

    virtual void operation() = 0;
};

class ConImplementor : public Implementor
{
public:
    virtual void operationImp() override { std::cout << "Implementor;" << std::endl; }
};

class Entity : public Abstraction
{
public:
    using Abstraction::Abstraction;
    virtual void operation() override
    {
        std::cout << "Entity" << std::endl;
        implementor->operationImp();
    }
};

int main()
{
    std::shared_ptr<Implementor> implementor = std::make_shared<ConImplementor>();
    std::shared_ptr<Abstraction> abtraction = std::make_shared<Entity>(implementor);

    abtraction->operation();
}