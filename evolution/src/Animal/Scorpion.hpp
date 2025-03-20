#pragma once
#include "Animal.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>


class Food;
class Gerbil;
class Scorpion : public Animal
{

public:
    Scorpion(const Vec2d& position, const double& energie) ;
    /*!
    * @brief create a Scorpion
    *
    * @param Position
    * @param energie
    *
    * @return an Scorpion
    */
    Scorpion(const Vec2d&, const double&, const bool&);
    /*!
    * @brief create a Scorpion
    *
    * @param Position
    * @param size
    * @param energie
    *
    * @return an Scorpion
    */
    Scorpion(const Vec2d&, const double&, const bool&, const sf::Time&);
    /*!
    * @brief create a Scorpion
    *
    * @param Position
    * @param size
    * @param energie
    * @param ageLimit
    *
    * @return an Scorpion
    */
    Scorpion(const Vec2d&);
    /*!
    * @brief create a Scorpion
    *
    * @param Position
    *
    * @return an Scorpion
    */

    Scorpion(const Vec2d& position,const Vec2d& direction) ; // not ready


    void giveBirthThis()  override ;

    /*!
    * @brief double dispatch to give birth of a scorpion
    */
    void update(sf::Time dt) ;

    ~Scorpion() {}


    virtual const double& getViewRange() const override;
    virtual const double& getViewDistance()const override;
    virtual const double& getRandomWalkRadius() const override;
    virtual const  double& getRandomWalkDistance() const override;
    virtual const double& getStandardMaxSpeed() const override;
    virtual const double& getMass() const override;
    virtual const  double& getRandomWalkJitter() const override ;
    virtual const sf::Texture& getTexture() const override;



    bool eatableBy(Gerbil const* gerbil ) const override;
    bool eatableBy(Food const* food ) const override;
    bool eatableBy(Scorpion const* scorpion)  const override;
    bool eatable(OrganicEntity const* organicentity ) const override;


    bool canMate(Gerbil const* gerbil ) const override;
    bool canMate(Food const* food ) const override;
    bool canMate(Scorpion const* scorpion)  const override;
    bool matable(OrganicEntity const* organicentity ) const override;

protected:
    double normalPositif(double valeur);
    double normalPositif(double valeur, double variance);
};
