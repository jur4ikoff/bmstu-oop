#pragma once
#include "DirectorCreator.h"

// DirectorBase - базовый класс директора
// DirectorProd - конкретный производный класс директора
// Концепты:
// NotAbstract<DirectorProd> - DirectorProd не должен быть абстрактным классом
// Derivative<DirectorProd, DirectorBase> - DirectorProd должен наследоваться от DirectorBase
// Constructible<DirectorProd, Args...> - DirectorProd должен быть конструируемым из Args...
template <typename DirectorBase, typename DirectorProd, typename... Args>
    requires NotAbstract<DirectorProd> && Derivative<DirectorProd, DirectorBase> && Constructible<DirectorProd, Args...>
std::shared_ptr<DirectorBase> DirectorCreator<DirectorBase, DirectorProd, Args...>::Create(Args &&...args)
{
    return std::make_shared<DirectorProd>(args...);
}