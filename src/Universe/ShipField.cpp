#include "ShipField.h"
#include "globals.h"
#include "Ship.h"

using namespace std;

ShipField::ShipField(Ship* parent) : m_rWorld(game.getGameUniverse().getWorld()), m_worldQuery(parent->getBody())
{
    m_pParent = parent;
    m_worldQuery.setFilter(ClassType::CHUNK);
    m_strength = 0.5;
    m_radius = 8;
    m_pParentBody = m_pParent->getBody();

}

ShipField::~ShipField()
{

}
void ShipField::setup()
{
 //   game.getGameUniverse().getFields().push_back(m_pParent->getField());
}
void ShipField::repulse()
{
    if(m_pParent != NULL)
    {
        m_ourCoords = m_pParentBody->GetWorldCenter();
        m_fieldBounds.upperBound = b2Vec2(m_radius+m_ourCoords.x, m_radius+m_ourCoords.y);
        m_fieldBounds.lowerBound = b2Vec2(-m_radius+m_ourCoords.x, -m_radius+m_ourCoords.y);
        m_rWorld.QueryAABB(&m_worldQuery, m_fieldBounds);
        vector<b2Body*>& rBodyList = m_worldQuery.getBodyList();


        for(vector<b2Body*>::iterator it = rBodyList.begin(); it != rBodyList.end(); ++it)
        {
            /**COMPUTE DISTANCES AND DIRECTIONS**/
            m_theirCoords = (*it)->GetWorldCenter();
            m_usToThem = b2Vec2(m_theirCoords.x-m_ourCoords.x, m_theirCoords.y-m_ourCoords.y);
            m_distance = sqrt(pow(m_usToThem.x, 2) + pow(m_usToThem.y, 2));
            if(m_distance < m_radius)
            {

                (*it)->ApplyForceToCenter(b2Vec2(m_strength*m_pParentBody->GetMass(), m_strength*m_pParentBody->GetMass()), true);

            //m_pParentBody->ApplyForceToCenter(b2Vec2(m_strength*(*it)->GetMass(), m_strength*(*it)->GetMass()),
             //                                true);
            }
        }
        m_worldQuery.getBodyList().clear();
    }
}
void ShipField::disconnect()
{
    m_pParent = NULL;
    m_pParentBody = NULL;
}
