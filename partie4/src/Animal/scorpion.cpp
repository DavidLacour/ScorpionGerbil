#include "Scorpion.hpp"
#include "../Application.hpp"
//#include "../Utility/Utility.hpp"
//#include "../Utility/Constants.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>
#include "../Random/Uniform.hpp"
#include "../Random/Normal.hpp"
Scorpion::Scorpion(const Vec2d& position, const double& energie,
                   const bool& femelleOuPas) :
    Animal(position,getAppConfig().scorpion_size, energie, femelleOuPas, getAppConfig().scorpion_longevity, getAppConfig().scorpion_energy_loss_factor, getAppConfig().scorpion_gestation_time )
{}
Scorpion::Scorpion(const Vec2d& position) : Animal(position,getAppConfig().scorpion_size,getAppConfig().scorpion_energy_initial,uniform(0, 1) == 0,getAppConfig().scorpion_longevity,
            getAppConfig().scorpion_energy_loss_factor,
            getAppConfig().scorpion_gestation_time)   {}





Scorpion::Scorpion(const Vec2d& position, const double& energie,
                   const bool& femelleOuPas, const sf::Time& ageLimit= sf::Time(getAppConfig().scorpion_longevity)) :


    Animal(position,getAppConfig().scorpion_size, energie, femelleOuPas, ageLimit)
{}

const double& Scorpion::getStandardMaxSpeed() const
{

    return  getAppConfig().scorpion_max_speed;
}

const double& Scorpion::getMass() const
{
    return  getAppConfig().scorpion_mass;
}


const double& Scorpion::getViewRange() const
{
    return getAppConfig().scorpion_view_range;
}

const double& Scorpion::getViewDistance()const
{
    return  getAppConfig().scorpion_view_distance;
}

const double& Scorpion::getRandomWalkRadius() const
{
    return getAppConfig().scorpion_random_walk_radius;
}


const double& Scorpion::getRandomWalkDistance() const
{
    return getAppConfig().scorpion_random_walk_distance;
}

const double& Scorpion::getRandomWalkJitter() const
{
    return getAppConfig().scorpion_random_walk_jitter;
}

const sf::Texture& Scorpion::getTexture() const
{
    sf::Texture& texture = getAppTexture(getAppConfig().scorpion_texture);
    return texture;

};


bool Scorpion::eatable(OrganicEntity const* entity   ) const
{

    return entity->eatableBy(this);
}

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
}


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

/* // not ready
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
