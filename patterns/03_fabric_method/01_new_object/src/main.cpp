#include <iostream>
#include <memory>
#include <concepts>

using namespace std;

template <typename Derived, typename Base>
concept Derivate = is_abstract_v<Base> && is_base_of_v<Base, Derived>;

template <typename T>
concept NotAbstract = !is_abstract_v<T>;

template <typename T>
concept DefaultConstructible = is_default_constructible_v<T>;

class Car;

class CarCreator
{
public:
    virtual ~CarCreator() = default;
    virtual unique_ptr<Car> create() const = 0;
};

template <Derivate<Car> TCar>
    requires NotAbstract<TCar> && DefaultConstructible<TCar>
class ConcreteCarCreator : public CarCreator
{
public:
    unique_ptr<Car> create() const override
    {
        return make_unique<TCar>();
    }
};

#pragma region Car
class Car
{
public:
    virtual ~Car() = default;
    virtual void drive() = 0;
};

class Sedan : public Car
{
public:
    Sedan()
    {
        cout << "Sedan constructor called" << endl;
    }
    ~Sedan() override
    {
        cout << "Sedan destructor called" << endl;
    }

    void drive() override
    {
        cout << "Driving Sedan" << endl;
    }
};

#pragma endregion Car

// template <Derivative<Car> TCar>
// requires

int main()
{
    shared_ptr<CarCreator> creator = make_shared<ConcreteCarCreator<Sedan>>();

    shared_ptr<Car> car = creator->create();
    car->drive();

    return 0;
}