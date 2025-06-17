#include <iostream>
#include <map>
#include <random>

class Subject
{
public:
    virtual ~Subject() = default;

    virtual std::pair<bool, double> request(size_t index) = 0;
    virtual bool changed() { return true; }
};

class RealSubject : public Subject
{

private:
    bool flag = false;
    size_t counter = 0;

public:
    virtual std::pair<bool, double> request(size_t index) override;
    virtual bool changed() override;
};

class Proxy : public Subject
{
protected:
    std::shared_ptr<RealSubject> realsubject;

public:
    Proxy(std::shared_ptr<RealSubject> real) : realsubject(real) {}
};

class ConProxy : public Proxy
{
private:
    std::map<size_t, double> cache;

public:
    using Proxy::Proxy;
    virtual std::pair<bool, double> request(size_t index) override;
};

#pragma region Method
bool RealSubject::changed()
{
    if (counter == 0)
        flag = true;

    if (++counter == 7)
    {
        counter = 0;
        flag = false;
    }
    return flag;
}

std::pair<bool, double> RealSubject::request(size_t index)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    return std::pair<bool, double>(true, std::generate_canonical<double, 10>(gen));
}

std::pair<bool, double> ConProxy::request(size_t index)
{
    std::pair<bool, double> result;

    if (!realsubject)
    {
        cache.clear();
        result = std::pair<bool, double>(false, 0);
    }
    else if (!realsubject->changed())
    {
        cache.clear();
        result = realsubject->request(index);
        // cache.insert(map<size_t, double>::value_type(index, result.second));
    }
    else
    {
        result = realsubject->request(index);
        // cache.insert
    }
    return result;
}

#pragma endregion Method

int main()
{
    std::shared_ptr<RealSubject> subject = std::make_shared<RealSubject>();
    std::shared_ptr<Subject> proxy = std::make_shared<ConProxy>(subject);

    for (size_t i = 0; i < 21; i++)
    {
        std::cout << "( " << i + 1 << ", " << proxy->request(i % 3).second << " )" << std::endl;
        if ((i + 1) % 3 == 0)
            std::cout << std::endl;
    }
}