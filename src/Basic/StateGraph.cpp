#include "StateGraph.hpp"

StateGraph::StateGraph()
{

}
StateGraph::~StateGraph()
{

}
void StateGraph::addNode(const StateNode& rNode)
{
    m_nodes[rNode.getState()] = rNode;
}
bool StateGraph::canChangeTo(State s) const//can we change our current state to this right now?
{
    auto it = m_nodes.find(m_currentNode);
    if(it == m_nodes.end())
        return false;
    else
        return (m_timer.isTimeUp() and it->second.hasConnectionTo(s) and hasNodeFor(s));
    //if timeUpOnThisState    and      weCanGoToThatState       and         weHaveThatState
}
void StateGraph::changeTo(State s)
{
    m_currentNode = s;
    m_timer.setCountDown(m_nodes[m_currentNode].getMinTime());
    m_timer.restartCountDown();
}
bool StateGraph::hasNodeFor(State s) const//do we have a node for that state
{
    return (m_nodes.find(s) != m_nodes.cend());
}
State StateGraph::getState() const
{
    return m_currentNode;
}
