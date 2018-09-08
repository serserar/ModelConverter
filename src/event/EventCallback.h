/*
 * Copyright 2018 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef EVENTCALLBACK_H
#define EVENTCALLBACK_H

/**
 * @todo write docs
 */
class IEventCallback
{
public:
    virtual void operator() () = 0;
    virtual bool operator == (IEventCallback* other) = 0;
};

template<typename T>
class EventCallback : public IEventCallback
{
public:
    EventCallback(T* instance, void (T::*function)())
        : instance(instance), function(function) {}

    void operator () () {
        (instance->*function)();
    }
    virtual bool operator == (IEventCallback* other) override
    {
        EventCallback* otherEventCallback = dynamic_cast<EventCallback*>(other);
        if (otherEventCallback == nullptr)
            return false;

        return 	(this->function == otherEventCallback->function) &&
                (this->instance == otherEventCallback->instance);
    }
    /**
     * Destructor
     */
    ~EventCallback();
private:
    void (T::*function)();
    T* instance;
};

#endif // EVENTCALLBACK_H
