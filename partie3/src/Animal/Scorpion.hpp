#pragma once
#include "Animal.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>


class Food;
class Gerbil;
class Scorpion : public Animal
{

public:
    // constructeur:
    Scorpion(const Vec2d& position, const double& energie) ;
    Scorpion(const Vec2d&, const double&, const bool&);
    Scorpion(const Vec2d&, const double&, const bool&, const sf::Time&);
    Scorpion(const Vec2d&);
    // void draw(sf::RenderTarget& targetWindow) const override ;
    Scorpion(const Vec2d& position,const Vec2d& direction) ;
    //  void GiveBirth() override ;
    void giveBirthThis()  override ;

    ~Scorpion() {}


    // getters:
    virtual const double& getViewRange() const override;
    virtual const double& getViewDistance()const override;
    virtual const double& getRandomWalkRadius() const override;
    virtual const  double& getRandomWalkDistance() const override;
    virtual const double& getStandardMaxSpeed() const override;
    virtual const double& getMass() const override;
    virtual const  double& getRandomWalkJitter() const override ;

    virtual const sf::Texture& getTexture() const override; // getter pour draw

    // bool peut manger et mangeable:
    /*
    bool eatableBy(Gerbil const* ) const override;
    bool eatableBy(Food const* ) const override;
    bool eatableBy(Scorpion const*) const override;
    bool eatable(OrganicEntity const* ) const override;
    */

    bool eatableBy(Gerbil const* gerbil ) const override;
    bool eatableBy(Food const* food ) const override;
    bool eatableBy(Scorpion const* scorpion)  const override;
    bool eatable(OrganicEntity const* organicentity ) const override;

    /*
    bool preydator(OrganicEntity const* organicentity ) const override;
    bool preydatorBy(Gerbil const* gerbil ) const override;
    bool preydatorBy(Food const* food ) const override;
    bool preydatorBy(Scorpion const* scorpion)  const override;
    */

    bool canMate(Gerbil const* gerbil ) const override;
    bool canMate(Food const* food ) const override;
    bool canMate(Scorpion const* scorpion)  const override;
    bool matable(OrganicEntity const* organicentity ) const override;


};
