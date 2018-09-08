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

#ifndef FSM_H
#define FSM_H
#include <vector>
#include <string>
#include <map>
#include "../event/Action.h"
#include "../event/Event.h"
class State;
class Transition{
public:
    virtual ~Transition();
    virtual bool checkTriggered()=0;
    virtual State* GetState()=0;
}
;
class State{
public:
    void OnStart();
    void OnRunning(float dt);
    void OnFinalize();
    std::vector<Action*> inActions;
    std::vector<Action*> actions;
    std::vector<Action*> outActions;
    std::map<std::string,Transition*> transitionMap;
};

class Fsm
{
public:
    /**
     * Default constructor
     */
    Fsm();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Fsm(const Fsm& other);

    /**
     * Destructor
     */
    ~Fsm();
    
    void OnUpdate(float dt);
    void OnTransitionReceived(std::string transitioName);
private:
    std::vector<State*> stateList;
    State* currentState;
};

#endif // FSM_H
