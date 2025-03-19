#pragma once
#include "Animal.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>

class Scorpion;
class Food;


class Gerbil : public Animal
{

public:
    // constructeur:

    Gerbil(const Vec2d&, const double& , const bool& );
    Gerbil(const Vec2d&);
    Gerbil(const Vec2d&, const double& , const bool&, const sf::Time& );
    Gerbil(const Vec2d& position,const Vec2d& direction) ; // BABY
    Gerbil(const Vec2d& ,const Vec2d&, OrganicEntity* ) ; // BABY and MUM
    // getters:
    virtual const double& getViewRange() const override;
    virtual const double& getViewDistance()const override;
    virtual const double& getRandomWalkRadius() const override;
    virtual const  double& getRandomWalkDistance() const override;
    virtual const double& getStandardMaxSpeed() const override;
    virtual const double& getMass() const override;
    virtual const  double& getRandomWalkJitter() const override ;
    /*
    bool eatableBy(Gerbil const*) const override ;
    bool eatableBy(Food const* ) const  override ;
    bool eatableBy(Scorpion const*) const   override ;
    bool eatable(OrganicEntity const* ) const  override ;

    */
    bool eatableBy(Gerbil const* gerbil) const override ;
    bool eatableBy(Food const* food) const  override ;
    bool eatableBy(Scorpion const* scorpion) const   override ;
    bool eatable(OrganicEntity const* entity) const  override ;

    bool canMate(Gerbil const* gerbil ) const override;
    bool canMate(Food const* food ) const override;
    bool canMate(Scorpion const* scorpion)  const override;
    bool matable(OrganicEntity const* organicentity ) const override;

    // void GiveBirth(this) override ;
    void giveBirthThis()  override ;
    virtual const sf::Texture& getTexture() const override; // getter pour annimal draw

    ~Gerbil() {}

};
