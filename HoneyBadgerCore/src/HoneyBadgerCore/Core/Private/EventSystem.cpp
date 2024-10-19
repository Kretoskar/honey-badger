#include "hbpch.h"
#include "HoneyBadgerCore/Core/Public/EventSystem.h"

HoneyBadger::Dispatcher* HoneyBadger::Dispatcher::_instance = nullptr;

void HoneyBadger::Dispatcher::Init()
{
    HoneyBadger::Dispatcher::_instance = new HoneyBadger::Dispatcher();
}

void HoneyBadger::Dispatcher::Cleanup()
{
    delete HoneyBadger::Dispatcher::_instance;
}

void HoneyBadger::Dispatcher::Subscribe(HBString Type, std::function<void(void*)>&& Func)
{
    _observers[Type].push_back(Func);
}

void HoneyBadger::Dispatcher::Post(HBString Type, void* Payload) const
{
    if (_observers.find(Type) == _observers.end())
    {
        return;
    }

    auto&& observers = _observers.at(Type);

    for (auto&& observer : observers)
    {
        observer(Payload);
    }
}