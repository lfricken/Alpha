#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "StateNode.hpp"
#include "Timer.hpp"

class StateGraph
{
public:
    StateGraph();
    virtual ~StateGraph();

    void addNode(const StateNode& rNode);

    bool canChangeTo(State s) const;//can we change our current state to this right now?
    void changeTo(State s);

    bool hasNodeFor(State s) const;//do we have a node for that state
    State getState() const;

protected:
private:
    State m_currentNode;
    std::map<State, StateNode> m_nodes;

    Timer m_timer;
};

#endif // STATEMANAGER_H
