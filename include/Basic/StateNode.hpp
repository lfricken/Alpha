#ifndef STATE_H
#define STATE_H

#include "stdafx.hpp"

enum class State
{
    Nominal,
    Disabled,
    Destroyed,
};

class StateNode
{
public:
    StateNode();
    StateNode(State ourState, const std::map<State, bool>& rConnections, float minTime);
    virtual ~StateNode();
    StateNode(const StateNode& rOther);
    StateNode& operator=(const StateNode& rOther);


    void addConnection(State node);//add a connection

    bool hasConnectionTo(State node) const;//do we have a connection pointing at that state
    State getState() const;//what is our state?
    float getMinTime() const;//how much time should we spend in this state?

protected:
private:
    State m_state;//this is our state
    std::map<State, bool> m_connections;//list of nodes we can GO TO, not necessarily come from
    float m_minTime;//the minimum time we can spend in this state
};

#endif // STATE_H
