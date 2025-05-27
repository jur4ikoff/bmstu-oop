// Паттерн подписчик издатель, нужен для лифта

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Subscriber;
using Reseiver = Subscriber; // Reseiver - Получатель

class Publisher
{
private:
    using Action = void (Reseiver::*)();
    using Pair = pair<shared_ptr<Reseiver>, Action>;

    vector<Pair> callback;
    int index_of(shared_ptr<Reseiver> r);

public:
    bool subscribe(shared_ptr<Reseiver> r, Action a);
    bool unsucsribe(shared_ptr<Reseiver> r);
    void run();
};

class Subscriber
{
public:
    virtual ~Subscriber() = default;
    virtual void method() = 0;
};

class ConSubscruber : public Subscriber
{
public:
    ConSubscruber(std::string name) : _name(name) {}

    void method() override
    {
        cout << "name: " << _name << endl;
    }

private:
    std::string _name;
};

#pragma regions Methods_Publisher
bool Publisher::subscribe(shared_ptr<Reseiver> r, Action a)
{
    if (index_of(r) != -1)
        return false;

    Pair pr(r, a);

    callback.push_back(pr);
    return true;
}

bool Publisher::unsucsribe(shared_ptr<Reseiver> r)
{
    int pos = index_of(r);

    if (pos != -1)
        callback.erase(callback.begin() + pos);

    return pos != -1;
}

void Publisher::run()
{
    cout << "Run: " << endl;
    for (auto elem : callback)
    {
        ((*elem.first).*(elem.second))();
    }
}

int Publisher::index_of(shared_ptr<Reseiver> r)
{
    int i = 0;
    for (auto it = callback.begin(); it != callback.end() && r != (*it).first; i++, ++it)
    {
    }
    return i < callback.size() ? i : -1;
}

#pragma endregion Methods_Publisher

int main()
{
    shared_ptr<Subscriber> subscriber_1 = make_shared<ConSubscruber>("first");
    shared_ptr<Subscriber> subscriber_2 = make_shared<ConSubscruber>("second");
    shared_ptr<Subscriber> subscriber_3 = make_shared<ConSubscruber>("third");

    shared_ptr<Publisher> publisher = make_shared<Publisher>();

    publisher->subscribe(subscriber_1, &Subscriber::method);
    if (publisher->subscribe(subscriber_2, &Subscriber::method))
        publisher->unsucsribe(subscriber_1);
    publisher->subscribe(subscriber_3, &Subscriber::method);

    publisher->run();
    return 0;
}