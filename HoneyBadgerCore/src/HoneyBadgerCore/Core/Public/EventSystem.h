#pragma once

#include "hbpch.h"
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "HoneyBadgerCore/Core/Public/HBString.h"

#define HB_BIND_EVENT(type, event) \
HoneyBadger::Dispatcher::GetInstance()->Subscribe(type, \
[this](auto&& PH1) \
{ \
event(std::forward<decltype(PH1)>(PH1)); \
});

#define HB_POST_EVENT(type, payload) \
HoneyBadger::Dispatcher::GetInstance()->Post(type, payload);

namespace HoneyBadger
{
    class Dispatcher
    {
        Dispatcher() {}

    public:
        static void Init();
        static void Cleanup();

        Dispatcher(Dispatcher const&) = delete;
        void operator=(Dispatcher const&) = delete;

        static Dispatcher* GetInstance()
        {
            return _instance;
        }

        void Subscribe(HBString Type, std::function<void(void*)>&& Func);

        void Post(HBString Type, void* Payload) const;

    private:
        static Dispatcher* _instance;
        std::map<HBString, std::vector<std::function<void(void*)>>> _observers;
    };

    namespace MouseButtonEvent
    {
        static HBString Type(int button, int action, int mods)
        {
            static std::map<unsigned, HBString> lookupMap;

            const unsigned lookupKey = button * 100 + action * 10 + mods;
            if (lookupMap.count(lookupKey) == 0)
            {
                char buffer[100];
                sprintf_s(buffer, "MouseButton%i%i%i", button, action, mods);
                lookupMap[lookupKey] = buffer;
            }


            return lookupMap[lookupKey];
        }
    };

    namespace KeyboardEvent
    {
        static HBString Type(int key, int action, int mods)
        {
            static std::map<unsigned, HBString> lookupMap;

            const unsigned lookupKey = key * 100 + action * 10 + mods;
            if (lookupMap.count(lookupKey) == 0)
            {
                char buffer[100];
                sprintf_s(buffer, "Key%i%i%i", key, action, mods);
                lookupMap[lookupKey] = buffer;
            }


            return lookupMap[lookupKey];
        }
    };

    namespace MousePositionEvent
    {
        struct MousePositionEventPayload
        {
            int32_t posX, posY;
        };

        static HBString Type()
        {
            static HBString type = HBString("MousePos");
            return type;
        }
    }

    namespace RemoveComponentEvent
    {
        struct RemoveComponentEventPayload
        {
            HBString typeId;
        };

		static HBString Type()
		{
            return HBString("RemoveComponent");
		}
    }
}