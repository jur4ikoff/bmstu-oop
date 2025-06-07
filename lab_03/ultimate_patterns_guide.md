## Здесь описаны все паттерны которые наиболее часто встречались в 3 лабораторной работе и которые Тассов сам рекоммендовал 




### UML class-dependency understanding
- https://habr.com/ru/articles/511798/
- https://prog-cpp.ru/uml-classes/


### Информация о паттернах
https://refactoring.guru/design-patterns
https://y2kot.gitbook.io

Основы UML:
- зависимость - это слабая связь между классами, которая показывает, что один класс временно использует другой, но не владеет им.
- ассоциация - это более сильная связь, которая показывает, что один класс "знает" о другом и может использовать его.
- агрегация - это особый вид ассоциации, который показывает отношение "часть-целое", но с независимым жизненным циклом частей.
- композиция - это более сильный вид агрегации, где части не могут существовать без целого.
наследование делится на реализацию и обобщение - цель паттернов уход от реализации 
- реализация 
- обобщение




## Порождающие паттерны

### Фабричный метод 
![alt text](./assets/image-2.png)

Идея - создать иерархию обьектов, отвечающих за создание обьектов, делегировать создание классу Creator который в свою очередь будет порождать
N concrete-creator которые будут создавать конкретный продукт



Кароче идея фабричного метода:

Имеем 
```cpp

class CarCreator
{
public:
    virtual ~CarCreator() = default;
    virtual unique_ptr<Car> create() const = 0;
};

template <Derivative<Car> TCar>
requires NotAbstract<TCar> && DefaultConstructible<TCar>
class ConcreteCarCreator : public CarCreator
{
public:
    unique_ptr<Car> create() const override
    {
        return make_unique<TCar>();
    }
}; 
```

просто базовый creator и какое то семейство конкретных создателей какого то вида авто, затем идут конкретные продукты

```cpp
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
        
        cout << "Driving sedan" << endl;
    }
};

```

shared_ptr<Product> ptr = make_shared<ConProduct>();

в результате мы избегаем проблему (строка выше) - вынуждены созадавать конкретный продукт, нам нужно создать конкретный продукт и везде это строчка постоянные изменения ну кароче хуйня оч серезбеная проблема - реверсионность ну пиздец кароче проблем дохуя строим фабрику и все пиздато






Проблема - в коде создавать обьекты конкретных классов задача подменить один обьект на другой.


Как решить проблему? - см выше ебик (создать Creator)


значит так идиома NVI - non virtual interface это вообще песня, если посмотреть пример то гении додумались вызывать виртуальный метод внутри родителя те папа становится мамой, пример тассов приводит на лекции но поверьте на слово долбоебизм это полнейший




В 3 лабе главная цель - убрать создание конкретных классов, кароче везде юзать фабричный метод


создание семсейства обьектов связанных между собой - использование дохуища Фабричных методов? - хуйня, абстрактная фабрика - решение



### Абстрактная фабрика

![alt text](./assets/image-1.png)

```cpp
# include <iostream>
# include <memory>

using namespace std;

class Image {};
class Color {};

class BaseGraphics
{
public:	virtual ~BaseGraphics() = 0;
};
BaseGraphics::~BaseGraphics() {}

class BasePen {};
class BaseBrush {};

class QtGraphics : public BaseGraphics
{
public:
	QtGraphics(shared_ptr<Image> im) { cout << "Calling the QtGraphics constructor;" << endl; }
	~QtGraphics() override { cout << "Calling the QtGraphics destructor;" << endl; }
};

class QtPen : public BasePen {};
class QtBrush : public BaseBrush {};

class AbstractGraphFactory
{
public:
	virtual ~AbstractGraphFactory() = default;

	virtual unique_ptr<BaseGraphics> createGraphics(shared_ptr<Image> im) = 0;
	virtual unique_ptr<BasePen> createPen(shared_ptr<Color> cl) = 0;
	virtual unique_ptr<BaseBrush> createBrush(shared_ptr<Color> cl) = 0;
};

class QtGraphFactory : public AbstractGraphFactory
{
public:
	unique_ptr<BaseGraphics> createGraphics(shared_ptr<Image> im) override
	{
		return make_unique<QtGraphics>(im);
	}

	unique_ptr<BasePen> createPen(shared_ptr<Color> cl) override
	{
		return make_unique<QtPen>();
	}

	unique_ptr<BaseBrush> createBrush(shared_ptr<Color> cl) override
	{
		return make_unique<QtBrush>();
	}
};

class User
{
public:
	void use(shared_ptr<AbstractGraphFactory>& cr)
	{
		shared_ptr<Image> image = make_shared<Image>();
		auto graphics = cr->createGraphics(image);
	}
};

int main()
{
	shared_ptr<AbstractGraphFactory> grfactory = make_shared<QtGraphFactory>();

	unique_ptr<User> us = make_unique<User>();
}
```

Собственно есть абстрактная фабрика и на основе нее создается QtFactory, где создаются обьекты семейства 

семейства нужно определять на этапе копиляции CRTP - welcome
- проблема протаскивания фабрики по всей иерархии 

- решение - создать копию обьекта ! идея простая и нихуя не понятная 

вообщем следующий паттерн Прототип


### Прототип
![alt text](./assets/image-3.png)
```cpp
# include <iostream>
# include <memory>

using namespace std;

class BaseObject
{
public:
	virtual ~BaseObject() = default;

	virtual unique_ptr<BaseObject> clone() = 0;
};

class Object1 : public BaseObject
{
public:
	Object1() { cout << "Calling the default constructor;" << endl; }
	Object1(const Object1& obj) { cout << "Calling the Copy constructor;" << endl; }
	~Object1() override { cout << "Calling the destructor;" << endl; }

	unique_ptr<BaseObject> clone() override
	{
		return make_unique<Object1>(*this);
	}
};

class User
{
public:
	void use(shared_ptr<BaseObject>& obj)
	{
		auto obj1 = obj->clone();
	}
};

int main()
{
	shared_ptr<BaseObject> obj = make_shared<Object1>();

	User{}.use(obj);
}
```

Проблема - если забыли определить clone - что же делать еп твою мать, вызовется clone родителя и будет пиздец мамочка по попе надает - решение использовать NVI



### Строитель

Поэтапное создание сложного этапа - цель, обьеденить это все в один этап.

прораб запрягает чурок собирать обьект

![alt text](./assets/image.png)


```cpp
# include <iostream>
# include <memory>

using namespace std;

# pragma region Product
class Product
{
public:
	virtual ~Product() = default;

	virtual void run() = 0;
};

class ConProd1 : public Product
{
public:
	ConProd1() { cout << "Calling the ConProd1 constructor;" << endl; }
	~ConProd1() override { cout << "Calling the ConProd1 destructor;" << endl; }

	void run() override { cout << "Calling the run method;" << endl; }
};

# pragma endregion

# pragma region Builder
class Builder
{
public:
	virtual ~Builder() = default;

	virtual bool buildPart1() = 0;
	virtual bool buildPart2() = 0;

	shared_ptr<Product> getProduct();

protected:
	virtual shared_ptr<Product> createProduct() = 0;

	shared_ptr<Product> product{ nullptr };
	size_t part{ 0 };
};

class ConBuilder : public Builder
{
public:
	bool buildPart1() override
	{
		if (!part)
			++part;

		if (part != 1) return false;

		cout << "Completed part: " << part << ";" << endl;
		return true;
	}
	bool buildPart2() override
	{
		if (part == 1)
			++part;

		if (part != 2) return false;

		cout << "Completed part: " << part << ";" << endl;
		return true;
	}

protected:
	shared_ptr<Product> createProduct() override;
};

# pragma endregion

# pragma region Creator
class Creator
{
public:
	virtual ~Creator() = default;

	virtual shared_ptr<Product> create() = 0;
};

class Director : public Creator
{
public:
	Director(shared_ptr<Builder> builder) : br(builder) {}

	shared_ptr<Product> create() override
	{
		if (br->buildPart1() && br->buildPart2()) return br->getProduct();

		return nullptr;
	}

private:
	shared_ptr<Builder> br;
};

# pragma endregion

# pragma region Methods
shared_ptr<Product> Builder::getProduct()
{
	if (!product) { product = createProduct(); }

	return product;
}

shared_ptr<Product> ConBuilder::createProduct()
{
	if (part == 2) { product = make_shared<ConProd1>(); }

	return product;
}

# pragma endregion

class User
{
public:
	void use(shared_ptr<Creator>& cr)
	{
		shared_ptr<Product> prod = cr->create();

		if (prod)
			prod->run();
	}
};

int main()
{
	shared_ptr<Builder> builder = make_shared<ConBuilder>();
	shared_ptr<Creator> cr = make_shared<Director>(builder);
}
```


### Singleton (Одиночка)


в целом тут ничего сложного просто использование статических полей и мтеодов и сокрытие конструктора (private) что гарантирует - обьект нельзя создать извне

суть в том что обьект создается внутри класса с помощью Proxy
```cpp
# include <iostream>
# include <memory>

using namespace std;

class Product
{
public:
	static shared_ptr<Product> instance()
	{
		class Proxy : public Product {};

		static shared_ptr<Product> myInstance = make_shared<Proxy>();

		return myInstance;
	}
	~Product() { cout << "Calling the destructor;" << endl; }

	void f() { cout << "Method f;" << endl; }

	Product(const Product&) = delete;
	Product& operator =(const Product&) = delete;

private:
	Product() { cout << "Calling the default constructor;" << endl; }
};

int main()
{
	shared_ptr<Product> ptr(Product::instance());

	ptr->f();
}
```



## Структурные паттерны
Выделяется категория роль - мы студенты, в зависимости от того в какой роли выступаем ук нас другое окржение мы предлагаеми другой интерфейс. 
Далее введение в понятие интерфейс...... (все pure virtual)


Каждую роль можно развивать. Надо разделять обьект. предоставить нужный интерфейс чепрез обьект посредник - каждая роль - обьект посредник

Обьект оч простой - только методы get и set на основе этих методов мы формируем нужный нам интерфейс необходимый для данной роли

(Конечно же нужно было сказать о геттерах и сеттерах на лекции ну сука не удосужиться привести это в примере)

### Адаптер
![alt text](././assets/image-9.png)

```cpp
# include <iostream>
# include <memory>

using namespace std;

class BaseAdaptee
{
public:
	virtual ~BaseAdaptee() = default;

	virtual void specificRequest() = 0;
};

class ConAdaptee : public BaseAdaptee
{
public:
	virtual void specificRequest() override { cout << "Method ConAdaptee;" << endl; }
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
	shared_ptr<BaseAdaptee>  adaptee;

public:
	ConAdapter(shared_ptr<BaseAdaptee> ad) : adaptee(ad) {}

	virtual void request() override;
};

# pragma region Methods
void ConAdapter::request()
{
	cout << "Adapter: ";

	if (adaptee)
	{
		adaptee->specificRequest();
	}
	else
	{
		cout << "Empty!" << endl;
	}
}

# pragma endregion

int main()
{
	shared_ptr<BaseAdaptee> adaptee = make_shared<ConAdaptee>();
	shared_ptr<Adapter> adapter = make_shared<ConAdapter>(adaptee);
}

```


вот тут мы просто обернули ConAdaptee кароче просто работаем с базовой сущностью через адаптер (не трогая основную сущность) 
для взаимодействия с самой сущностью используются геттеры и (сеттеры?) сеттер вроде как трогает сущность но да и хуй бы с ним


когда на сущность возлагается несколько ролей то роль скидываем на адаптер и все чики пуки

когда создаем абстракную фабрику для взаимодействия с библиотекой хорошо бы построить адаептер(потому что penы везде разные drawLine тоже)



### Главный вопрос на экзамене - как бороться с реализацией?

Ответ: Адаптер добавлять новый функционал можем добавлять не только к одной сущности но и к целой иерархии но при работе с библиотекой возможно дохуища адаптеров так что тут аккуратно. как с девочкой.

Классов дохуя - Тассову нравится. Зато бля структура гибкая дохуя ну да пиздато че давай на каждый метод хуярить по 50 адаптеров а то вдруг там кто то подрочит не там


но тут вот через 5 минут - мы должны бороться с дублированием кода. Проблема рекурсивной иерархии - создадут себе проблем и давай решать. А главное то нахуя вот что ты решаешь то, так ладно проблему рекурсивной иерархии решает декоратор


### Декоратор

![alt text](./assets/image-4.png)

На самом деле удобно, то чем хотим расширить добавляем в декоратор -> код не дублируется. Декоратор хранит указатель на базу (агрегация). Напоминаю что композиция это хранение копии

```cpp
# include <iostream>
# include <memory>

using namespace std;

class Component
{
public:
	virtual ~Component() = default;

	virtual void operation() = 0;
};

class ConComponent : public Component
{
public:
	void operation() override { cout << "ConComponent; "; }
};

class Decorator : public Component
{
protected:
	shared_ptr<Component> component;

public:
	Decorator(shared_ptr<Component> comp) : component(comp) {}
};

class ConDecorator : public Decorator
{
public:
	using Decorator::Decorator;

	void operation() override;
};

# pragma region Method
void ConDecorator::operation()
{
	if (component)
	{
		component->operation();

		cout << "ConDecorator; ";
	}

}

# pragma endregion

int main()
{
	shared_ptr<Component> component = make_shared<ConComponent>();
	shared_ptr<Component> decorator1 = make_shared<ConDecorator>(component);

	decorator1->operation();
	cout << endl;

	shared_ptr<Component> decorator2 = make_shared<ConDecorator>(decorator1);
}
```


вот тут мы добавили 
```
void operation()
```

декоратор убирает разрастание иерархии и дублирование кода


минусы - полиморфизм увеличивает времся выполнения как и вся эта залупа с паттернами

Инсайд к 3 лабораторной 

у меня есть несколько карскассных моделей и я хочу повернуть все  как мне это сделать - сделать менеджер обьектов - над каждым сделать поворот - хуевый подход

с контейнерными классами напрямую не работать - работать с ними через адаптеры 

Итак следующий паттерн композит

### Композит
![alt text](./assets/image-5.png)

итак у нас много компонент, мы можем обьединять компоненты и тд и тп тк мы связаем сущности разных классов и хотим выполнять над ними групповые операции - для этого нужен композит - является производным от компонента. Композит по своей сути это контейнер и мы должны создать под него интерфейс 


Идея : выпихнуть на уровень базовой асбтрации интерфейс производного класса те композит конкретные компоненты не могут переопределять данные методы ибо теряется вся суть
для этого есть метод isComposit() чтобы случайно не переопределять эти методы в производных классов

```cpp
# include <iostream>
# include <initializer_list>
# include <memory>
# include <vector>

using namespace std;

class Component;

using PtrComponent = shared_ptr<Component>;
using VectorComponent = vector<PtrComponent>;

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
	virtual bool add(initializer_list<PtrComponent> comp) { return false; }
	virtual bool remove(const iterator& it) { return false; }
	virtual iterator begin() const { return iterator(); }
	virtual iterator end() const { return iterator(); }
};

class Figure : public Component
{
public:
	virtual void operation() override { cout << "Figure method;" << endl; }
};

class Camera : public Component
{
public:
	virtual void operation() override { cout << "Camera method;" << endl; }
};

class Composite : public Component
{
private:
	VectorComponent vec;

public:
	Composite() = default;
	Composite(PtrComponent first, ...);

	void operation() override;

	bool isComposite() const override { return true; }
	bool add(initializer_list<PtrComponent> list) override;
	bool remove(const iterator& it) override { vec.erase(it); return true; }
	iterator begin() const override { return vec.begin(); }
	iterator end() const override { return vec.end(); }
};

# pragma region Methods
Composite::Composite(PtrComponent first, ...)
{
	for (shared_ptr<Component>* ptr = &first; *ptr; ++ptr)
		vec.push_back(*ptr);
}

void Composite::operation()
{
	cout << "Composite method:" << endl;
	for (auto elem : vec)
		elem->operation();
}

bool Composite::add(initializer_list<PtrComponent> list)
{
	for (auto elem : list)
		vec.push_back(elem);

	return true;
}

# pragma endregion

int main()
{
	using Default = shared_ptr<Component>;
	PtrComponent fig = make_shared<Figure>(), cam = make_shared<Camera>();
	auto composite1 = make_shared<Composite>(fig, cam, Default{});

	composite1->add({ make_shared<Figure>(), make_shared<Camera>() });
	composite1->operation();
	cout << endl;

	auto it = composite1->begin();

	composite1->remove(++it);
	composite1->operation();
	cout << endl;

	auto composite2 = make_shared<Composite>(make_shared<Figure>(), composite1, Default());
}
```


Композит - адаптер контейнерного класса, композит это список компонент



### Мост

```
крайне тяжелый паттерн - разделение обьявление и реализации
```
![alt text](./assets/image-6.png)


суть в том что если меняется сущность то мы можем отдельно менять реализацию, например каркасс может состоять н из точек и ребер а .obj 

```cpp
# include <iostream>
# include <memory>

using namespace std;

class Implementor
{
public:
	virtual ~Implementor() = default;

	virtual void operationImp() = 0;
};

class Abstraction
{
protected:
	shared_ptr<Implementor> implementor;

public:
	Abstraction(shared_ptr<Implementor> imp) : implementor(imp) {}
	virtual ~Abstraction() = default;

	virtual void operation() = 0;
};

class ConImplementor : public Implementor
{
public:
	virtual void operationImp() override { cout << "Implementor;" << endl; }
};

class Entity : public Abstraction
{
public:
	using Abstraction::Abstraction;

	virtual void operation() override { cout << "Entity: "; implementor->operationImp(); }
};

int main()
{
	shared_ptr<Implementor> implementor = make_shared<ConImplementor>();
	shared_ptr<Abstraction> abstraction = make_shared<Entity>(implementor);

	abstraction->operation();
}
```

далее идет прокси класс не ебу зачем он нужен сам Тассов сказал что в 3 лабе он не используется так что скип



### Фасад

как адаптер только скрывает внутреннюю реализацию из вне мы не можем нарушить целостность 

и вот он самый сука важный паттерн но тассов решил лучше рассказать про вырожденный мост. 
![alt text](./assets/image-7.png)

примеров на него тоже нет так что вообще песня


## Поведенческие паттерны 

### Стратегия
![alt text](./assets/image-11.png)
обернуть функцию в класс - план для реализации какой то целии

реализация какого то одног метода может быть несколько методов и для каждого метода своя стратегия классов дохуя зато какая гибкость!


### Команда 

каждый запрос - переносчик данных когда формируем команду надо знать к какому классу относится адресат формируем запрос и кто то эту команду выполняет
![alt text](./assets/image-8.png)


можно составялть составные команды - по сути это тоже контейнер но интерфейс по нему делать не надо

Стратегия вызывается из метода самого класса те обьект знает о стратегии (имеет указатель)



```cpp
# include <iostream>
# include <memory>
# include <vector>
# include <initializer_list>

using namespace std;

class Command
{
public:
	virtual ~Command() = default;

	virtual void execute() = 0;
};

template <typename Reseiver>
class SimpleCommand : public Command
{
	using Action = void(Reseiver::*)();
	using Pair = pair<shared_ptr<Reseiver>, Action>;

private:
	Pair call;

public:
	SimpleCommand(shared_ptr<Reseiver> r, Action a) : call(r, a) {}

	void execute() override { ((*call.first).*call.second)(); }
};

class CompoundCommand : public Command
{
	using VectorCommand = vector<shared_ptr<Command>>;

private:
	VectorCommand vec;

public:
	CompoundCommand(initializer_list<shared_ptr<Command>> lt);

	virtual void execute() override;
};

# pragma region Methods
CompoundCommand::CompoundCommand(initializer_list<shared_ptr<Command>> lt)
{
	for (auto&& elem : lt)
		vec.push_back(elem);
}

void CompoundCommand::execute()
{
	for (auto com : vec)
		com->execute();
}

# pragma endregion

class Object
{
public:
	void run() { cout << "Run method;" << endl; }
};

int main()
{
	shared_ptr<Object> obj = make_shared<Object>();
	shared_ptr<Command> command = make_shared<SimpleCommand<Object>>(obj, &Object::run);

	command->execute();

	shared_ptr<Command> complex(new CompoundCommand
		{
			make_shared<SimpleCommand<Object>>(obj, &Object::run),
			make_shared<SimpleCommand<Object>>(obj, &Object::run)
		});

	complex->execute();
}
```


### Цепочка обязанностей

мы можем из тех кто может обработать запрос сформировать список 
отвязываемся от конкретного обьекта



### Подписчик
суть - подписчик издатель издатель хранит адрес(ул Пушкина дом Колотушкина) и имя (кому отправить) издатель должен сообщить подсписчику вызвать какой то его метод держит паару (обьект и метод)
можем рассматривать подписчика как базу

![alt text](./assets/image-10.png)

```cpp
# include <iostream>
# include <memory>
# include <vector>

using namespace std;

class Subscriber;

using Reseiver = Subscriber;

class Publisher
{
	using Action = void(Reseiver::*)();
	using Pair = pair<shared_ptr<Reseiver>, Action>;
private:
	vector<Pair> callback;

	int indexOf(shared_ptr<Reseiver> r);

public:
	bool subscribe(shared_ptr<Reseiver> r, Action a);
	bool unsubscribe(shared_ptr<Reseiver> r);
	void run();
};

class Subscriber
{
public:
	virtual ~Subscriber() = default;

	virtual void method() = 0;
};

class ConSubscriber : public Subscriber
{
public:
	void method() override { cout << "method;" << endl; }
};

# pragma region Methods Publisher
bool Publisher::subscribe(shared_ptr<Reseiver> r, Action a)
{
	if (indexOf(r) != -1) return false;

	Pair pr(r, a);

	callback.push_back(pr);

	return true;
}

bool Publisher::unsubscribe(shared_ptr<Reseiver> r)
{
	int pos = indexOf(r);

	if (pos != -1)
		callback.erase(callback.begin() + pos);

	return pos != -1;
}

void Publisher::run()
{
	cout << "Run:" << endl;
	for (auto elem : callback)
		((*elem.first).*(elem.second))();
}

int Publisher::indexOf(shared_ptr<Reseiver> r)
{
	int i = 0;
	for (auto it = callback.begin(); it != callback.end() && r != (*it).first; i++, ++it);

	return i < callback.size() ? i : -1;
}

# pragma endregion

int main()
{
	shared_ptr<Subscriber> subscriber1 = make_shared<ConSubscriber>();
	shared_ptr<Subscriber> subscriber2 = make_shared<ConSubscriber>();
	shared_ptr<Publisher> publisher = make_shared<Publisher>();

	publisher->subscribe(subscriber1, &Subscriber::method);
	if (publisher->subscribe(subscriber2, &Subscriber::method))
		publisher->unsubscribe(subscriber1);

	publisher->run();
}
```

мы подписались на событие и если событие происходит то издатель дергает метод подсписчика

тут конечно проблема, что подписчиков много и они разные можно в целом вынести все связи на один обьект (или использовать множественное наследование но это пиздец)




### Визитор 

Цель обьекдинения стратегий, для каждой сущности опредлеление своего метода

По сути это фабрика стратегий
![alt text](./assets/image-12.png)

суть в том что мы используем перегрузки, те в зависимости от переданного обьекта вызывается соответствующая стратегия

Кароче как это работает, мы можем вызвать visit где то в глубине иерархии и visitor посредством перегрузки сам найдет стратегию которую надо вызвать в зависимости от переданного обьекта

### Опекун

Возврат, идея вынести обязанность отката на другое обьект

Опекун это просто снимок должен быть кто то кто ответственный за состояниями
(careTaker)


careTaker это контейнер, просто хранит все состояния и выполняет откат или добавление (обертка стека грубо говоря) можно хранить не все снимки, определяя при этом закон сохранения снимков кароче тк это контейнер на нем можно нагородить с три короба (2 лаба все то за один балл...) 

![alt text](./assets/image-13.png)



### Шаблонный метод

класс который содержит определенны=е жэтапы что то передаем на вход что то получаем навыходе получение промежуточных результатов 


https://y2kot.gitbook.io