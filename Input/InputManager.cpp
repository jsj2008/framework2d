#include "InputManager.h"
InputManager g_InputManager;
using namespace std;
InputManager::InputManager()
{
    //ctor
    /*currentState = new InputState;
    inputStates.push_back(InputStateHistory(currentState,0));
    globalEventsSizeWhenSeen = &inputStates[0].globalEventsSizeWhenSeen;*/
    currentState = NULL;
}

InputManager::~InputManager()
{
    //dtor
}
void InputManager::changeResolution(const Vec2i newResolution)
{
    if (currentState != NULL)
        currentState->changeResolution(newResolution);
    for (unsigned int i = 0; i < inputStates.size(); i++)
    {
        inputStates[i].state->changeResolution(newResolution);
    }
}
void InputManager::registerEvent(EventListener* event, InputActions action)
{
    if (currentState != NULL)
    {
        currentState->registerEvent(event,action);
    }
}
void InputManager::registerGlobalEvent(EventListener* event, InputActions action)
{
    globalEvents.push_back(pair<EventListener*,InputActions>(event,action));
    if (currentState != NULL)
    {
        currentState->registerEvent(event,action);
        (*globalEventsSizeWhenSeen)++;
    }
}
void InputManager::setInputState(InputState* _currentState)
{
    unsigned int lastSeenSize = 0;
    currentState = _currentState;
    for (unsigned int i = 0; i < inputStates.size(); i++)
    {
        if (currentState == inputStates[i].state)
        {/// This one has been seen before
            lastSeenSize = inputStates[i].globalEventsSizeWhenSeen;
            inputStates[i].globalEventsSizeWhenSeen = globalEvents.size();
            globalEventsSizeWhenSeen = &inputStates[i].globalEventsSizeWhenSeen;
            break;
        }
    }
    for (unsigned int i = lastSeenSize; i < globalEvents.size(); i++)
    {
        currentState->registerEvent(globalEvents[i].first, globalEvents[i].second);
    }
}
void InputManager::render()
{
    currentState->render();
}
bool InputManager::processInput()
{
    return currentState->processInput();
}
































