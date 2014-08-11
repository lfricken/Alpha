#include "StateNode.hpp"

StateNode::StateNode()
{
    m_state = State::Nominal;
    m_minTime = 1.0f;
}
StateNode::StateNode(State ourState, const std::map<State, bool>& rConnections, float minTime)
{
    m_state = ourState;
    m_connections = rConnections;
    m_connections[m_state] = true;
    m_minTime = minTime;
}
StateNode::~StateNode()
{

}
StateNode::StateNode(const StateNode& rOther)
{
    m_state = rOther.m_state;
    m_connections = rOther.m_connections;
    m_minTime = rOther.m_minTime;
}
StateNode& StateNode::operator=(const StateNode& rOther)
{
    m_state = rOther.m_state;
    m_connections = rOther.m_connections;
    m_minTime = rOther.m_minTime;
    return *this;
}
void StateNode::addConnection(State node)
{
    m_connections[node] = true;
}
bool StateNode::hasConnectionTo(State node) const
{
    return (m_connections.find(node) != m_connections.end());
}
State StateNode::getState() const
{
    return m_state;
}
float StateNode::getMinTime() const
{
    return m_minTime;
}
