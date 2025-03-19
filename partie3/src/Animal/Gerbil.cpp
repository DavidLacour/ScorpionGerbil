#include "Gerbil.hpp"
#include "../Application.hpp"
//#include "../Utility/Utility.hpp"
//#include "../Utility/Constants.hpp"
#include "../Utility/Vec2d.hpp"
//#include  <SFML/Graphics.hpp>
#include "../Random/Uniform.hpp"
#include "Animal.hpp"
Gerbil::Gerbil(const Vec2d& position, const double& energie,
               const bool& femelleOuPas) :
    Animal(position,getAppConfig().gerbil_size, energie, femelleOuPas, getAppConfig().gerbil_longevity, getAppConfig().gerbil_energy_loss_factor, getAppConfig().gerbil_gestation_time)
{}
Gerbil::Gerbil(const Vec2d& position) : Animal(position,getAppConfig().gerbil_size,getAppConfig().gerbil_energy_initial,uniform(0, 1) == 0,
            getAppConfig().gerbil_longevity,
            getAppConfig().gerbil_energy_loss_factor, getAppConfig().gerbil_gestation_time )   {}


Gerbil::Gerbil(const Vec2d& position,const Vec2d& direction) : Animal(position,getAppConfig().gerbil_size,getAppConfig().gerbil_energy_initial,uniform(0, 1) == 0,
            getAppConfig().gerbil_longevity,
            getAppConfig().gerbil_energy_loss_factor, getAppConfig().gerbil_gestation_time,direction)   {}

Gerbil::Gerbil(const Vec2d& position,const Vec2d& direction, OrganicEntity* mum) :
    Animal(position,
           getAppConfig().gerbil_size,
           getAppConfig().gerbil_energy_initial,
           uniform(0, 1) == 0,
           getAppConfig().gerbil_longevity,
           getAppConfig().gerbil_energy_loss_factor,
           getAppConfig().gerbil_gestation_time,direction, mum)
{

//	if(energie_ > getAppConfig().gerbil_energy_initial+ 50 or energie_ < getAppConfig().gerbil_energy_initial - 50 ){
//		energie_ = getAppConfig().gerbil_energy_initial;
//		cout<< " AAAAAAAAAAAAA " << endl;
//	}

} // BUG SOMTIMES INFITE ENERGIE !!!!!!!!!!!!!!!!!!??????????????????????????????


Gerbil::Gerbil(const Vec2d& position, const double& energie,
               const bool& femelleOuPas, const sf::Time& ageLimit =(sf::Time(getAppConfig().gerbil_longevity)
                                                                   )) :
    Animal(position,getAppConfig().gerbil_size, energie, femelleOuPas, ageLimit)
{}


// Gerbil::Gerbil(const Vec2d& position) : Animal(position,getAppConfig().gerbil_size,getAppConfig().gerbil_energy_initial,uniform(0, 1) == 0))  {}


const double& Gerbil::getStandardMaxSpeed() const
{

    return  getAppConfig().gerbil_max_speed;
} // getter vitesse

const double& Gerbil::getMass() const
{
    return  getAppConfig().gerbil_mass;
} //getter masse


const double& Gerbil::getViewRange() const
{
    return getAppConfig().gerbil_view_range;
} // getter portée angle vision

const double& Gerbil::getViewDistance()const
{
    return  getAppConfig().gerbil_view_distance;
} // getter distance vision

const double& Gerbil::getRandomWalkRadius() const
{
    return getAppConfig().gerbil_random_walk_radius;
} // getter rayon de marche aléatoire


const double& Gerbil::getRandomWalkDistance() const
{
    return getAppConfig().gerbil_random_walk_distance;
} // getter distance de marche aléatoire


const double& Gerbil::getRandomWalkJitter() const
{
    return getAppConfig().gerbil_random_walk_jitter;
} // getter de taille de l'aléat

const sf::Texture& Gerbil::getTexture() const
{
    if (getFemelleOuPas()) {
        sf::Texture& texture = getAppTexture(getAppConfig().gerbil_texture_female);
        return texture;
    } else {
        sf::Texture& texture = getAppTexture(getAppConfig().gerbil_texture_male);
        return texture;
    }

} // getter pour annimal::draw selon le sexe

bool Gerbil::eatable(OrganicEntity const* entity) const
{

    return entity->eatableBy(this);
} // peut manger

// est mangeable par:

bool Gerbil::eatableBy(Gerbil const*  ) const
{
    return false;
}
bool Gerbil::eatableBy(Food const*  ) const
{
    return false;
}
bool Gerbil::eatableBy(Scorpion const*  ) const
{
    return true;
}

bool Gerbil::matable(OrganicEntity const* entity   ) const
{

    return entity->canMate(this);
} // peut faire des enfants à
// fait des enfants par:

bool Gerbil::canMate(Gerbil const* G) const
{
    if(getFemelleOuPas()) {
        if( getAge().asSeconds() >= getAppConfig().gerbil_min_age_mating
            and getEnergie() >= getAppConfig().gerbil_energy_min_mating_female
            and !getEnceinte()
            and( getFemelleOuPas() != G->getFemelleOuPas()
               ))
            return true;
    } else {
        if( getAge().asSeconds() >= getAppConfig().gerbil_min_age_mating and getEnergie()>= getAppConfig().gerbil_energy_min_mating_male and !getEnceinte() and( getFemelleOuPas() != G->getFemelleOuPas()
                                                                                                                                                               ))
            return true;
    }
    return false;
}

bool Gerbil::canMate(Food const* ) const
{
    return false;
}
bool Gerbil::canMate(Scorpion const*  ) const
{
    return false;
}
/*
	void Gerbil::GiveBirth(){
	  cout << " DDD " << endl;
		  return this.GiveBirth();
	  }
	  * **/

/*
void Gerbil::giveBirthThis()
{
for (int i (0); i <= getBabies(); ++i ) {
  getAppEnv().addEntity(new Gerbil(getPosition()-getDirection()*getRadius()*2.2,getDirection()));
}
setBabies(0);
}
*/

/*
void Gerbil::giveBirthThis()
{
    for (int i (0); i <= getBabies(); ++i ) {
        getAppEnv().addEntity(new Gerbil(getPosition()-getDirection()*getRadius()*2.2));
    }
    setBabies(0);
}
*/


void Gerbil::giveBirthThis()
{
    for (int i (0); i <= getBabies(); ++i ) {
        OrganicEntity* mum(this);
        Gerbil* baby(new Gerbil(getPosition()-getDirection()*getRadius()*2.2, getDirection(), mum));
        getAppEnv().addEntity(baby);
        organic_entity_kids_.push_back(baby);
    }
    setBabies(0);
}

