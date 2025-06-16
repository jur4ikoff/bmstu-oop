#include <iostream>

class Component
{
public:
    virtual ~Component() = default;
    virtual void operation() = 0;
};

class ConComponent : public Component
{
public:
    void operation() override
    {
        std::cout << "ConComponent" << std::endl;
    }
};

class Decorator : public Component
{
protected:
    std::shared_ptr<Component> component;

public:
    Decorator(std::shared_ptr<Component> comp) : component(comp) {}
};

class ConDecorator : public Decorator
{
public:
    using Decorator::Decorator;
    void operation() override;
};

#pragma region Method
void ConDecorator::operation()
{
    if (component)
    {
        component->operation();
        std::cout << "ConDecorator";
    }
}
#pragma endregion Method

int main()
{
    std::shared_ptr<Component> component = std::make_shared<ConComponent>();
    std::shared_ptr<Component> decorator_1 = std::make_shared<ConDecorator>(component);

    decorator_1->operation();
    std::cout << std::endl;

    std::shared_ptr<Component> decorator_2 = std::make_shared<ConDecorator>(decorator_1);
    decorator_2->operation();
    std::cout << std::endl;
}
