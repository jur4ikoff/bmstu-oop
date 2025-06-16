#include <iostream>

class Component;

using PtrComponent = std::shared_ptr<Component>;
using VectorComponent = std::vector<PtrComponent>;

class Component
{
public:
    using value_type = Component;
    using size_type = size_t;
    using iterator = VectorComponent::const_iterator;
    using const_iterator = VectorComponent::const_iterator;

    virtual ~Component() = default;
    virtual void operation() = 0;

    virtual bool isComposite() const { return false; }
    virtual bool add(std::initializer_list<PtrComponent> comp) { return false; }
    virtual bool remove(const iterator &it) { return false; }
    virtual iterator begin() const { return iterator(); }
    virtual iterator end() const { return iterator(); }
};

class Figure : public Component
{
public:
    virtual void operation() override { std::cout << "Figure method" << std::endl; }
};

class Camera : public Component
{
public:
    virtual void operation() override { std::cout << "Camera method" << std::endl; }
};

class Composite : public Component
{
private:
    VectorComponent vec;

public:
    Composite() = default;
    // Composite(PtrComponent first, ...);
    Composite(std::initializer_list<PtrComponent> list)
    {
        for (auto &elem : list)
        {
            if (elem)
            {
                vec.push_back(elem);
            }
        }
    }

    void operation() override;
    bool isComposite() const override { return true; }
    bool add(std::initializer_list<PtrComponent> list) override;
    bool remove(const iterator &it) override
    {
        vec.erase(it);
        return true;
    }
    iterator begin() const override { return vec.begin(); }
    iterator end() const override { return vec.end(); }
};

#pragma region Methods
// Composite::Composite(PtrComponent first, ...)
// {
//     for (std::shared_ptr<Component> *ptr = &first; *ptr; ptr++)
//     {
//         vec.push_back(*ptr);
//     }
// }

void Composite::operation()
{
    std::cout << "Composite method:" << std::endl;
    for (auto elem : vec)
    {
        elem->operation();
    }
}

bool Composite::add(std::initializer_list<PtrComponent> list)
{
    for (auto elem : list)
    {
        vec.push_back(elem);
    }
    return true;
}

#pragma endregion Methods

int main()
{
    using Default = std::shared_ptr<Component>;
    PtrComponent fig = std::make_shared<Figure>(), cam = std::make_shared<Camera>();
    auto composite_1 = std::make_shared<Composite>(std::initializer_list<PtrComponent>{fig, cam});

    composite_1->add({std::make_shared<Figure>(), std::make_shared<Camera>()});
    composite_1->operation();
    std::cout << std::endl;
}