#include "OrganicEntity.hpp"
//#include "../Obstacle/CircularCollider.hpp"
//#include <list>
#include "../Application.hpp"
#include "../Random/Normal.hpp"
//#include "../Utility/Utility.hpp"


// !!!!! energie_depense_base_ est ici pas dans Animal

OrganicEntity::OrganicEntity( const Vec2d& position, const double& taille , const double& energie) : CircularCollider(position,
            normal(taille,taille/15*taille/15)
                                                                                                                         ), energie_(energie),  age_(sf::Time::Zero),
    age_limit_(sf::seconds(10000)), energie_depense_base_(getAppConfig().animal_base_energy_consumption) {}



OrganicEntity::OrganicEntity( const OrganicEntity& OE ) : OrganicEntity( OE.getPosition(),OE.getRadius(),OE.energie_) {}

OrganicEntity::OrganicEntity( const Vec2d& position, const double& taille , const double& energie, const sf::Time& ageLimit)
    : CircularCollider(position, taille), energie_(energie),  age_(sf::Time::Zero), age_limit_(ageLimit), energie_depense_base_(getAppConfig().animal_base_energy_consumption)
{
//		if(energie_ > 100000000000 ){ energie_ = 1500 ; }
}

const double& OrganicEntity::getEnergie() const
{
    return energie_;
}

void OrganicEntity::update(sf::Time dt)
{
    age_ += dt;
//	updateEnergie();
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



/*
void OrganicEntity::updateEnergie( sf::Time dt)
{

    double energyLoss(energie_depense_base_+ vitesse_* energie_depense_facteur_* dt.asSeconds());
//double energyLoss(energie_depense_base_+ vitesse_* 0.1 _* dt.asSeconds())
    OrganicEntity::setEnergy(energyLoss*-1+ getEnergie());
}
*/
/* La perte d'énergie est fonction du pas de temps écoulé (en secondes) et de la norme de la vitesse (plus l'animal va vite et plus il se fatigue) selon la formule suivante:
perte_energie = depense_energetique_de_base + norme_vitesse * facteur_perte_energie() * dt
depense_energetique_de_base est paramétrable (getAppConfig().animal_base_energy_consumption).
Le facteur de perte d'énergie se calcule de façon différente pour chaque type d'animaux (getAppConfig().scorpion_energy_loss_factor pour les scorpions par exemple). */

