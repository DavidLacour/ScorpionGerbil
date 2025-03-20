#pragma once
#include "Scorpion.hpp"
#pragma once
#include "Animal.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>


class  EG : public Scorpion
{
    EG(const Vec2d& );



    bool eatableBy(Gerbil const* gerbil ) const override;
    bool eatableBy(Food const* food ) const override;
    bool eatableBy(Scorpion const* scorpion)  const override;
    bool eatable(OrganicEntity const* organicentity ) const override;


    bool canMate(Gerbil const* gerbil ) const override;
    bool canMate(Food const* food ) const override;
    bool canMate(Scorpion const* scorpion)  const override;
    bool matable(OrganicEntity const* organicentity ) const override;

};
