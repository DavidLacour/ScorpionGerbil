#include "Scorpion.hpp"
#include "../Application.hpp"
//#include "../Utility/Utility.hpp"
//#include "../Utility/Constants.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>
#include "../Random/Uniform.hpp"
Scorpion::Scorpion(const Vec2d& position, const double& energie,
                   const bool& femelleOuPas) :
    Animal(position,getAppConfig().scorpion_size, energie, femelleOuPas, getAppConfig().scorpion_longevity, getAppConfig().scorpion_energy_loss_factor, getAppConfig().scorpion_gestation_time )
{}
Scorpion::Scorpion(const Vec2d& position) : Animal(position,getAppConfig().scorpion_size,getAppConfig().scorpion_energy_initial,uniform(0, 1) == 0,getAppConfig().scorpion_longevity,
            getAppConfig().scorpion_energy_loss_factor,
            getAppConfig().scorpion_gestation_time)   {}
// Scorpion::Scorpion(const Vec2d& position,const Vec2d& direction) : Animal(position,getAppConfig().scorpion_size,getAppConfig().scorpion_energy_initial,uniform(0, 1) == 0,direction)   {}




Scorpion::Scorpion(const Vec2d& position, const double& energie,
                   const bool& femelleOuPas, const sf::Time& ageLimit= sf::Time(getAppConfig().scorpion_longevity)) :


    Animal(position,getAppConfig().scorpion_size, energie, femelleOuPas, ageLimit)
{}



// Scorpion::Scorpion(const Vec2d& position) : Animal(position,getAppConfig().scorpion_size,getAppConfig().scorpion_energy_initial,uniform(0, 1) == 0) {}

//
const double& Scorpion::getStandardMaxSpeed() const
{

    return  getAppConfig().scorpion_max_speed;
} // getter vitesse

const double& Scorpion::getMass() const
{
    return  getAppConfig().scorpion_mass;
} //getter masse


const double& Scorpion::getViewRange() const
{
    return getAppConfig().scorpion_view_range;
} // getter portée angle vision

const double& Scorpion::getViewDistance()const
{
    return  getAppConfig().scorpion_view_distance;
} // getter distance vision

const double& Scorpion::getRandomWalkRadius() const
{
    return getAppConfig().scorpion_random_walk_radius;
} // getter rayon de marche aléatoire


const double& Scorpion::getRandomWalkDistance() const
{
    return getAppConfig().scorpion_random_walk_distance;
} // getter distance de marche aléatoire


const double& Scorpion::getRandomWalkJitter() const
{
    return getAppConfig().scorpion_random_walk_jitter;
} // getter de taille de l'aléat

const sf::Texture& Scorpion::getTexture() const
{
    sf::Texture& texture = getAppTexture(getAppConfig().scorpion_texture);
    return texture;

}; // getter pour annimal::draw


bool Scorpion::eatable(OrganicEntity const* entity   ) const
{

    return entity->eatableBy(this);
} // peut manger



// est mangeable par:

bool Scorpion::eatableBy(Gerbil const* ) const
{
    return false;
}
bool Scorpion::eatableBy(Food const* ) const
{
    return false;
}
bool Scorpion::eatableBy(Scorpion const*  ) const
{
    return false;
}



bool Scorpion::matable(OrganicEntity const* entity   ) const
{

    return entity->canMate(this);
} // peut faire des enfants à
// fait des enfants par:

bool Scorpion::canMate(Gerbil const* ) const
{
    return false;
}
bool Scorpion::canMate(Food const* ) const
{
    return false;
}
bool Scorpion::canMate(Scorpion const* S ) const
{
    if(getFemelleOuPas()) {
        if( getAge().asSeconds() >= getAppConfig().scorpion_min_age_mating
            and getEnergie() >= getAppConfig().scorpion_energy_min_mating_female
            and !getEnceinte()
            and( getFemelleOuPas() != S->getFemelleOuPas()
               ))
            return true;
    } else {
        if( getAge().asSeconds() >= getAppConfig().scorpion_min_age_mating and getEnergie()>= getAppConfig().scorpion_energy_min_mating_male and !getEnceinte()
            and( getFemelleOuPas() != S->getFemelleOuPas()
               ))
            return true;
    }
    return false;
}
/*
void Scorpion::giveBirthThis()
{

    for( int i(0); i <= getBabies(); ++ i) {
        getAppEnv().addEntity(new Scorpion(getPosition()-getDirection()*getRadius()*1.2, getDirection()));
    }
    setBabies(0);
}
	*/

void Scorpion::giveBirthThis()
{

    for( int i(0); i <= getBabies(); ++ i) {
        getAppEnv().addEntity(new Scorpion(getPosition()-getDirection()*getRadius()*1.2));
    }
    setBabies(0);
}
