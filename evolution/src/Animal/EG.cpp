#include "EG.hpp"
#include "Scorpion.hpp"
#include "../Application.hpp"
//#include "../Utility/Utility.hpp"
//#include "../Utility/Constants.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>
#include "../Random/Uniform.hpp"
#include "../Random/Normal.hpp"

EG::EG(const Vec2d& position) : Scorpion(position)
{
    setRadius(normalPositif(getRadius()));
}

bool EG::eatable(OrganicEntity const* entity   ) const
{

    return entity->eatableBy(this);
}

bool EG::eatableBy(Gerbil const* ) const
{
    return false;
}
bool EG::eatableBy(Food const* ) const
{
    return false;
}

bool EG::eatableBy(Scorpion const* scorp ) const
{
    if (scorp->getRadius()>(this->getRadius()*2)) return true;
    return false;
}



bool EG::matable(OrganicEntity const* entity   ) const
{

    return entity->canMate(this);
}


bool EG::canMate(Gerbil const* ) const
{
    return false;
}
bool EG::canMate(Food const* ) const
{
    return false;
}
bool EG::canMate(Scorpion const*  ) const
{

    return false;
}
