#pragma once

#include "../Interface/Updatable.hpp"
#include "../Obstacle/CircularCollider.hpp"
//#include  <SFML/Graphics.hpp>

#include <list>
class Animal;
class Scorpion;
class Food;
class Gerbil;
class OrganicEntity : public CircularCollider ,public Updatable
{

public:
    OrganicEntity( const Vec2d& , const double& , const double& );

    /*!
    * @brief create an OrganicEntity
    *
    * @param Position
    * @param size
    * @param energie
    *
    * @return an OrganicEntity
    */

    OrganicEntity( const Vec2d& , const double& , const double&, const sf::Time& );
    /*!
    * @brief create an OrganicEntity
    *
    * @param Position
    * @param size
    * @param energie
    * @param AgeLimit
    *
    * @return an OrganicEntity
    */
    OrganicEntity( const OrganicEntity& );
    /*!
    * @brief copy an OrganicEntity
    * @return an OrganicEntity
    */

    virtual ~OrganicEntity() { }


    virtual void  oublierMum() {}
    /*!
    * @brief memory gestion
    */

    virtual void oublierBaby(OrganicEntity*) {}
    /*!
    * @brief memory gestion
    */
    virtual void oublier() {}
    /*!
    * @brief memory gestion
    */

    void setEnergy(const double&); // public pour être manger pourrait être mieux fait
    virtual void update(sf::Time ) = 0;
    virtual void draw(sf::RenderTarget&) const = 0;


    const double& getEnergie() const ;


    const sf::Time& getAge() const;
    const sf::Time& getAgeLimit() const;


    virtual bool matable(OrganicEntity const* other) const = 0;
    virtual bool canMate(Scorpion const* scorpion) const = 0;
    virtual bool canMate(Gerbil const* gerbil) const = 0;
    virtual bool canMate(Food const* food) const = 0;

    virtual bool eatable(OrganicEntity const* entity) const = 0;
    virtual bool eatableBy(Scorpion  const* scorpion) const = 0;
    virtual bool eatableBy(Gerbil const* gerbil) const = 0;
    virtual bool eatableBy(Food const* food) const = 0;
    virtual void meet(OrganicEntity*) {}
    virtual void meetThis(Animal*) {}



protected:




    virtual  void giveBirth() {}
    virtual  void giveBirthThis() {}
    void updateEnergie( sf::Time dt);


    virtual void addKidMemory( OrganicEntity*) {}
    /*!
    * @brief mum memory gestion of the kid
    */



//	void setEnergy(const double&);
    double energie_;

    sf::Time age_;
    sf::Time age_limit_;
    double energie_depense_base_;


// double depense_energie_facteur; la chez l'animal


//sf::Time age_(sf::Time:zero);
//	bool morte_;


};


