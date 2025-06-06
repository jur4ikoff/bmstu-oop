#include <iostream>
#include <initializer_list>
#include <memory>
#include <map>

using namespace std;

class Product;

class Creator
{
public:
    virtual std::unique_ptr<Product> createProduct() = 0;
};

template <typename TProd>
class ConCreator : public Creator
{
public:
    virtual std::unique_ptr<Product> createProduct() override
    {
        return std::unique_ptr<Product>(new TProd());
    }
};

#pragma region Product
class Product
{
public:
    virtual ~Product() = default;
    virtual void run() = 0;
};

class ConProd1 : public Product
{
public:
    ConProd1()
    {
        std::cout << "Calling the conprod1 constructor" << std::endl;
    }
    virtual ~ConProd1() override
    {
        cout << "Calling ConProd1 destructor" << std::endl;
    }
    virtual void run() override
    {
        std::cout << "calling ConProd1 running" << std::endl;
    }
};

class ConProd2 : public Product
{
public:
    ConProd2()
    {
        std::cout << "Calling the conprod2 constructor" << std::endl;
    }
    virtual ~ConProd2() override
    {
        cout << "Calling ConProd2 destructor" << std::endl;
    }
    virtual void run() override
    {
        std::cout << "calling ConProd2 running" << std::endl;
    }
};

#pragma endregion Product

class CrCreator
{
public:
    template <typename TProd>
    static std::unique_ptr<Creator> createConCreator()
    {
        return std::unique_ptr<Creator>(new ConCreator<TProd>());
    }
};

class Solution
{
    using CreateCreator = std::unique_ptr<Creator> (*)();
    using CallBackMap = std::map<size_t, CreateCreator>;

public:
    Solution() = default;
    Solution(std::initializer_list<pair<size_t, CreateCreator>> list);

    std::unique_ptr<Creator> create(size_t id);

    bool registration(size_t id, CreateCreator createfun);
    bool check(size_t id)
    {
        return callbacks.erase(id) == 1;
    }

private:
    CallBackMap callbacks;
};

#pragma region Solutions
Solution::Solution(std::initializer_list<pair<size_t, CreateCreator>> list)
{
    for (auto elem : list)
    {
        this->registration(elem.first, elem.second);
    }
}

bool Solution::registration(size_t id, CreateCreator createfun)
{
    return callbacks.insert(CallBackMap::value_type(id, createfun)).second;
}

std::unique_ptr<Creator> Solution::create(size_t id)
{
    CallBackMap::const_iterator it = callbacks.find(id);

    if (it == callbacks.end())
    {
    }

    return std::unique_ptr<Creator>((it->second)());
}
#pragma enderegion Solutions

int main()
{
    std::shared_ptr<Solution> solution(new Solution({{1, &CrCreator::createConCreator < ConProd1>}}));
    solution->registration(2, &CrCreator::createConCreator<ConProd2>);

    shared_ptr<Creator> cr(solution->create(2));
    shared_ptr<Product> ptr = cr->createProduct();

    ptr->run();
}