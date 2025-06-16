#include <iostream>

class BaseAdaptee
{

public:
    virtual ~BaseAdaptee() = default;

    virtual void specificRequest() = 0;
};

class ConAdaptee : public BaseAdaptee
{
public:
    void specificRequest() override
    {
        std::cout << "Method ConAdaptee" << std::endl;
    }
};

class Adapter
{
public:
    virtual ~Adapter() = default;
    virtual void request() = 0;
};

class ConAdapter : public Adapter
{
private:
    std::shared_ptr<BaseAdaptee> adaptee;

public:
    ConAdapter(std::shared_ptr<BaseAdaptee> ad) : adaptee(ad) {}
    virtual void request() override;
};

#pragma region Methods
void ConAdapter::request()
{
    std::cout << "Adapter";
    if (adaptee)
    {
        adaptee->specificRequest();
    }
    else
        std::cout << "Empty" << std::endl;
}

#pragma endregion Methods

int main()
{
    std::shared_ptr<BaseAdaptee> adaptee = std::make_shared<ConAdaptee>();
    std::shared_ptr<Adapter> adapter = std::make_shared<ConAdapter>(adaptee);

    adapter->request();
}