#pragma once
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>
#include "OrganicEntity.hpp"

class Scorpion;

class Gerbil;
class Food : public OrganicEntity
{


public:
// constructeur update draw destructeur
    Food(const Vec2d&  );
    virtual void update(sf::Time )  override;
    virtual void draw(sf::RenderTarget&) const override;
    ~Food() {}

// est manger peut manger:
    /*
    bool eatableBy(Gerbil const*) const override ;
    	bool eatableBy(Food const*) const  override ;
    	bool eatableBy(Scorpion const*) const   override ;
    	bool eatable(OrganicEntity const*s) const  override ;
    	* */


    bool eatableBy(Gerbil const*gerbil) const override ;
    bool eatableBy(Food const* food) const  override ;
    bool eatableBy(Scorpion const* scorpion) const   override ;
    bool eatable(OrganicEntity const* entity) const  override ;


    bool canMate(Gerbil const* gerbil ) const override;
    bool canMate(Food const* food ) const override;
    bool canMate(Scorpion const* scorpion)  const override;
    bool matable(OrganicEntity const* organicentity ) const override;

    bool isGerbil() const override
    {
        return false;
    }
    bool isScorpion( ) const override
    {
        return false;
    }
    bool isFood( ) const override
    {
        return true;
    }
};
