#include "OrganicEntity.hpp"
#include "../Application.hpp"
#include "../Random/Normal.hpp"

double OrganicEntity::normalPositif(double valeur, double variance)
{
    double res (normal(valeur,variance));
    if  ( res <= 10) {
        return 10;
    } else {
        return res;
    }
}

double  OrganicEntity::normalPositif(double valeur)
{
    return normalPositif(valeur,valeur*valeur);
}

OrganicEntity::OrganicEntity( const Vec2d& position, const double& taille , const double& energie) : CircularCollider(position,
            normalPositif(taille,taille/15*taille/15)
                                                                                                                         ), energie_(energie),  age_(sf::Time::Zero),
    age_limit_(sf::seconds(10000)), energie_depense_base_(getAppConfig().animal_base_energy_consumption) {}

OrganicEntity::OrganicEntity( const OrganicEntity& OE ) : OrganicEntity( OE.getPosition(),OE.getRadius(),OE.energie_) {}

OrganicEntity::OrganicEntity( const Vec2d& position, const double& taille , const double& energie, const sf::Time& ageLimit)
    : CircularCollider(position, taille), energie_(energie),  age_(sf::Time::Zero), age_limit_(ageLimit), energie_depense_base_(getAppConfig().animal_base_energy_consumption)
{
}

const double& OrganicEntity::getEnergie() const
{
    return energie_;
}

void OrganicEntity::update(sf::Time dt)
{
    age_ += dt;
}

const sf::Time& OrganicEntity::getAge() const
{
    return age_;
}
const sf::Time& OrganicEntity::getAgeLimit() const
{
    return age_limit_;
}

void OrganicEntity::setEnergy(const double& energie)
{
    energie_= energie ;
}
