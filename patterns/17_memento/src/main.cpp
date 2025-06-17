#include <iostream>
#include <list>

class Memento;

class CareTaker
{
public:
    std::unique_ptr<Memento> getMemento();
    void setMemento(std::unique_ptr<Memento> memento);

private:
    std::list<std::unique_ptr<Memento>> mementos;
};

class Originator
{
public:
    Originator(int s) : state(s) {}

    const int getState() const { return state; }
    void setState(int s) { state = s; }

    std::unique_ptr<Memento> createMemento() { return std::make_unique<Memento>(*this); }
    void restoreMemento(std::unique_ptr<Memento> memento);

private:
    int state;
};

class Memento
{
    friend class Originator;

public:
    Memento(Originator o) : originator(o) {}

private:
    Originator originator;

    void setOriginator(Originator o) { originator = o; }
    Originator getOriginator() { return originator; }
};

#pragma region Methods
void CareTaker::setMemento(std::unique_ptr<Memento> memento)
{
    mementos.push_back(std::move(memento));
}

std::unique_ptr<Memento> CareTaker::getMemento()
{
    std::unique_ptr<Memento> last = std::move(mementos.back());
    mementos.pop_back();
    return last;
}

void Originator::restoreMemento(std::unique_ptr<Memento> memento)
{
    *this = memento->getOriginator();
}
#pragma endregion Methods

int main()
{
    auto originator = std::make_unique<Originator>(1);
    auto caretaker = std::make_unique<CareTaker>();

    std::cout << "State = " << originator->getState() << std::endl;
    caretaker->setMemento(originator->createMemento());

    originator->setState(2);
    std::cout << "State = " << originator->getState() << std::endl;
    caretaker->setMemento(originator->createMemento());

    originator->restoreMemento(caretaker->getMemento());
    std::cout << "State = " << originator->getState() << std::endl;
    originator->restoreMemento(caretaker->getMemento());
    std::cout << "State = " << originator->getState() << std::endl;
}