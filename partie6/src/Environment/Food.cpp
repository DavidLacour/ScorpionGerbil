#include "Food.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
//#include "../Utility/Constants.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>
#include "OrganicEntity.hpp"
//#include "../Obstacle/CircularCollider.hpp"
class EG ;
Food::Food(const Vec2d& position ) : OrganicEntity(position,  getAppConfig().food_size,getAppConfig().food_energy) {}


void Food::update(sf::Time )  {} // plus tard

void Food::draw(sf::RenderTarget& targetWindow) const
{
    if(isDebugOn()) CircularCollider::draw(targetWindow);
    sf::Texture& texture = getAppTexture(getAppConfig().food_texture);
    auto image_to_draw(buildSprite( getPosition(),
                                    getRadius()*2,
                                    texture ));

    targetWindow.draw(image_to_draw );

}
// peut manger:
bool Food::eatable(OrganicEntity const* entity)  const
{

    return entity->eatableBy(this);
}



// est mangeable par:

bool Food::eatableBy(Gerbil const* ) const
{
    return true;
}
bool Food::eatableBy(Food const* )  const
{
    return false;
}
bool Food::eatableBy(Scorpion const* )  const
{
    return true;
}

bool Food::matable(OrganicEntity const* entity   ) const
{

    return entity->canMate(this);
} // peut faire des enfants à
// fait des enfants par:

bool Food::canMate(Gerbil const* ) const
{
    return false;
}
bool Food::canMate(Food const* ) const
{
    return false;
}
bool Food::canMate(Scorpion const* ) const
{
    return false;
}
