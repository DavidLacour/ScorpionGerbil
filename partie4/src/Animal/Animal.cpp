//#include "../Obstacle/CircularCollider.hpp"
//#include  <SFML/Graphics.hpp>
//#include "../Utility/Vec2d.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
//#include "../Utility/Constants.hpp"
//#include  "../Environment/Environment.hpp"
#include "Animal.hpp"
//#include <cmath>
#include <list>
#include "../Random/Uniform.hpp"
//#include "Scorpion.hpp"
//#include "Gerbil.hpp"

#include "Scorpion.hpp"
#include "Gerbil.hpp"
//#include <iostream>
//class Scorpion;
//class Food;
//class Gerbil;

// ReproductionTest-run --cfg=reprod.json

// PPSTest-run --cfg=appTest.json

// !!!!! energie_depense_base_ est pas ici mais dans OrganicEntity
// updateState Fait trop de calcul il faut changer l'ordre des if pour optimiser
// update Copies inutiles

Animal::Animal(const Vec2d& position,const double& taille, const double& energie, const bool& femelleOuPas) :
    OrganicEntity( position, taille, energie),
    direction_(1,0),
    current_target_(1,0),
    femelle_ou_pas_(femelleOuPas),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    etat_(WANDERING),
    organic_entity_cible_(nullptr),
    enceinte_(false),
    babies_(0),
    time_pause_mise_en_bas_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_pause_mating_(sf::seconds(getAppConfig().animal_mating_time)),
    time_gestation_limit_(sf::seconds(10)),
    time_gestation_(sf::Time::Zero) ,
    time_running_away_(sf::seconds(getAppConfig().animal_running_away)),
    organic_entity_mum_(nullptr)
{ } //  position + taille + energie + femelle ou pas


Animal::Animal(const Vec2d& position,const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit, const double& energie_depense_facteur,
               const double&  gestationLimit ) :
    OrganicEntity( position, taille, energie, ageLimit), direction_(1,0), current_target_(1,0),
    femelle_ou_pas_(femelleOuPas),
    energie_depense_facteur_(energie_depense_facteur),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    etat_(WANDERING),
    organic_entity_cible_(nullptr),
    enceinte_(false),
    babies_(0),
    time_pause_mise_en_bas_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_pause_mating_(sf::seconds(getAppConfig().animal_mating_time)),
    time_gestation_limit_(sf::seconds(gestationLimit)),
    time_gestation_(sf::Time::Zero) ,
    time_running_away_(sf::seconds(getAppConfig().animal_running_away)),
    organic_entity_mum_(nullptr)
{ } // position + taille + energie + femelle ou pas + Agelimit + facteur perte energy + gestationlimit



Animal::Animal(const Vec2d& position,const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit, const double& energie_depense_facteur, const double&  gestationLimit, const Vec2d& direction) :
    OrganicEntity( position, taille/3, energie, ageLimit), direction_(direction), current_target_(1,0),
    femelle_ou_pas_(femelleOuPas),
    energie_depense_facteur_(energie_depense_facteur),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    etat_(BABY),
    organic_entity_cible_(nullptr),
    enceinte_(false),
    babies_(0),
    time_pause_mise_en_bas_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_pause_mating_(sf::seconds(getAppConfig().animal_mating_time)),
    time_gestation_limit_(sf::seconds(gestationLimit)),
    time_gestation_(sf::Time::Zero) ,
    time_running_away_(sf::seconds(getAppConfig().animal_running_away)),
    organic_entity_mum_(nullptr)
{ } // position + taille + energie + femelle ou pas + Agelimit + facteur perte energy + gestationlimit BABY



/*
Animal::Animal(const Vec2d& position,const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit, const double& energie_depense_facteur, const double&  gestationLimit, const Vec2d& direction):
 OrganicEntity( position, taille/3, energie, ageLimit), direction_(direction), current_target_(1,0),
  femelle_ou_pas_(femelleOuPas),
  energie_depense_facteur_(energie_depense_facteur),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    etat_(BABY),
    organic_entity_cible_(nullptr),
    enceinte_(false),
    babies_(0),
    time_pause_mise_en_bas_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_gestation_limit_(sf::seconds(gestationLimit)),
    time_gestation_(sf::Time::Zero) ,
    time_running_away_(sf::seconds(getAppConfig().animal_running_away))
{ } // position + taille + energie + femelle ou pas + Agelimit + facteur perte energy + gestationlimit BABY +  MUM
*/

Animal::Animal(const Vec2d& position,const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit, const double& energie_depense_facteur, const double&  gestationLimit, const Vec2d& direction, OrganicEntity* mum) :
    OrganicEntity( position, taille/3, energie, ageLimit), direction_(direction), current_target_(1,0),
    femelle_ou_pas_(femelleOuPas),
    energie_depense_facteur_(energie_depense_facteur),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    etat_(BABY),
    organic_entity_cible_(nullptr),
    enceinte_(false),
    babies_(0),
    time_pause_mise_en_bas_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_pause_mating_(sf::seconds(getAppConfig().animal_mating_time)),
    time_gestation_limit_(sf::seconds(gestationLimit)),
    time_gestation_(sf::Time::Zero) ,
    time_running_away_(sf::seconds(getAppConfig().animal_running_away)),
    organic_entity_mum_(mum)
{ } // position + taille + energie + femelle ou pas + Agelimit + facteur perte energy + gestationlimit BABY +  MUM


/*

Animal::Animal(const Vec2d& position,const double& taille, const double& energie, const bool& femelleOuPas, const Vec2d& direction) : OrganicEntity( position, taille/3, energie), direction_(direction), current_target_(1,0),
	femelle_ou_pas_(femelleOuPas)
	,time_pause_feeding_(sf::seconds(0.5))
	 ,etat_(BABY)
	 ,organic_entity_cible_(nullptr),
	  enceinte_(false),
	  babies_(0),
	  time_pause_mise_en_bas_(sf::seconds(3)),
	  time_gestation_limit_(sf::seconds(10)),
	  time_gestation_(sf::Time::Zero) ,
	  time_running_away_(sf::seconds(2)) // femelle_ou_pas_(uniform(0, 1) == 0)
{ } // baby

*/

Animal::Animal(const Vec2d& position,const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit) :
    OrganicEntity( position, taille, energie, ageLimit), direction_(1,0), current_target_(1,0),
    femelle_ou_pas_(femelleOuPas), time_gestation_limit_(sf::seconds(10)) // feme PPSTest-runlle_ou_pas_(uniform(0, 1) == 0)
{ } // position + taille + energie + femelle ou pas + Agelimit


/*
Animal::Animal(const Vec2d& position,const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit, const double& energie_depense_facteur) :
 OrganicEntity( position, taille, energie, ageLimit), direction_(1,0), current_target_(1,0),
	femelle_ou_pas_(femelleOuPas),  energie_depense_facteur_(energie_depense_facteur), time_gestation_limit_(sf::seconds(10))// femelle_ou_pas_(uniform(0, 1) == 0)
{ } // position + taille + energie + femelle ou pas + Agelimit + facteur perte energy
*/





Vec2d Animal::getSpeedVector() const
{
    return direction_*vitesse_;
} // retourne un vecteur vitesse




void Animal::giveBirth()
{

    return this->giveBirthThis();
}


void Animal::meet(OrganicEntity* O)
{

    etat_= MATING;
    return O->meetThis(this);
}

void Animal::meetThis(Animal* A)   // Appeler par meet permet la reprodution, si femelle met enceinte et descend l'energie selon le nombre de bébé et les constantes.
{
    etat_= MATING;
    int babies(uniform(getAppConfig().gerbil_min_children,getAppConfig().gerbil_max_children));
    if(getFemelleOuPas()) {
        setEnceinte(true);
        setEnergy(getEnergie()+getAppConfig().gerbil_energy_loss_female_per_child*babies);
        setBabies(babies);
    } else {
        setEnergy(getEnergie()-getAppConfig().gerbil_energy_loss_mating_male);
    }
    if( A->getFemelleOuPas()) {
        A->setEnceinte(true);
        A->setEnergy(getEnergie()+getAppConfig().gerbil_energy_loss_female_per_child*babies);
        A->setBabies(babies);
    } else {
        A->setEnergy(getEnergie()-getAppConfig().gerbil_energy_loss_mating_male);
    }
}

void Animal::setEnceinte(const bool& b)  // tomber enceinte
{
    enceinte_ = b;
}
void Animal::UpdateState(sf::Time dt)  // lance Analyze environment, check le temps de temps de Gestation et autres temps d'etats (pause_feeding), change l'etat en fonction du champs de vision
{
    // A Changer plus tard updateSate lance giveBirth et manger () on peut faire une fonction meetAll et la metre dans update().

    analyzeEnvironment();
    if( getEnceinte() ) time_gestation_+= dt;
    if( time_gestation_>= time_gestation_limit_ ) {

        setEnceinte(false);

        time_gestation_=sf::Time::Zero;
        giveBirth();
        etat_ = GIVING_BIRTH;

    }
    if(etat_ != FEEDING and etat_ != MATING and etat_ != GIVING_BIRTH and etat_ != BABY and etat_ != RUNNING_AWAY) { // à optimiser en changeant l'ordre.

        if(!organic_entity_FOODs_.empty()) {
            organic_entity_cible_=plusProche(organic_entity_FOODs_);
            if (collisionCible()) {
                organic_entity_cible_memory_= organic_entity_cible_->getPosition();
                manger();
                etat_ = FEEDING;
                time_pause_feeding_= sf::seconds(1.5);

            } else {
                etat_ = FOOD_IN_SIGHT;
            }
        }
        if(!organic_entity_ItsaMatchs_.empty()) {
            organic_entity_cible_=plusProche(organic_entity_ItsaMatchs_);
            if (collisionCible()) {
                meet(organic_entity_cible_);
                etat_ = MATING;
            } else {
                etat_ = MATE_IN_SIGHT;
            }
        }

        if(!organic_entity_Preydators_.empty()) {
            organic_entity_Preydators_memory_ = organic_entity_Preydators_;
            etat_= RUNNING_AWAY;
        }
    } else if (etat_ == FEEDING ) {
        time_pause_feeding_ -= dt;
        if(time_pause_feeding_<=sf::Time::Zero) etat_ = WANDERING;
    } else if (etat_ == MATING) {
        time_pause_mating_ -= dt;
        if (time_pause_mating_ <= sf::Time::Zero ) etat_= WANDERING;
    }
    if (etat_ == GIVING_BIRTH) {
        time_pause_mise_en_bas_ -= dt;
        if (time_pause_mise_en_bas_ <= sf::Time::Zero ) etat_= WANDERING;
    }

    else if (etat_ == RUNNING_AWAY) {
        time_running_away_ -= dt;
        if (time_running_away_ <= sf::Time:: Zero) {
            time_running_away_ = sf::seconds(getAppConfig().animal_running_away);
            etat_ = WANDERING;
        }
    }

    else if (etat_== BABY) {
        if( age_>=  sf::seconds(getAppConfig().gerbil_min_age_mating)) { // ici La durée de l'enfance est la même que l'age minimal pour se reproduire
            //if( age_>=  sf::seconds(60)){

            grandir();

            if (organic_entity_mum_!= nullptr) organic_entity_mum_->oublierBaby(this);
            oublierMum();
            etat_= WANDERING;
        }
    }

}


void Animal::update(sf::Time dt) // fait des copies inutiles
{


    UpdateState(dt);

    Vec2d forceattraction;



    switch( etat_) {
    case FOOD_IN_SIGHT  : {
        Vec2d cibleTarget ;
        cibleTarget = (organic_entity_cible_->getPosition());
        forceattraction = force(cibleTarget);
        moveToVec2dForce(dt.asSeconds(), forceattraction);
        break;
    }
    case WANDERING  :

        forceattraction= randomWalk();
        moveToVec2dForce(dt.asSeconds(), forceattraction);
        break;
    case MATE_IN_SIGHT: {
        Vec2d cibleTarget ;
        cibleTarget = (organic_entity_cible_->getPosition());
        forceattraction = force(cibleTarget);
        moveToVec2dForce(dt.asSeconds(), forceattraction);
    }
    case RUNNING_AWAY:

        forceattraction = forceFuite(organic_entity_Preydators_memory_);
        moveToVec2dForce(dt.asSeconds(), forceattraction);
        break;
    case FEEDING:
        // forceattraction = ((organic_entity_cible_->getPosition()-getPosition())*-1+getPosition());
        //  moveToVec2dForce(dt.asSeconds(), forceattraction);
        vitesse_ *=0.9;
        moveToVec2dForce(dt.asSeconds(), force(organic_entity_cible_memory_));

        break;
    case BABY: {

        if ((organic_entity_mum_ != nullptr)) {
            moveToVec2dForce(dt.asSeconds(), force(organic_entity_mum_->getPosition())) ;
        } else {



            OrganicEntity* mamanPapa(plusProche(enVue()));
            if(mamanPapa != nullptr) {

                if( (!eatable(mamanPapa)) and !(mamanPapa->eatable(this)))
                    moveToVec2dForce(dt.asSeconds(), force(plusProche(enVue())->getPosition()));
            }

            else {
                moveToVec2dForce(dt.asSeconds(), randomWalk());
            }

        }

    }
    default:
        break;
    }
    updateEnergie(dt);


}
Vec2d Animal::force( const Vec2d& cible ) const
{


    if (!isEqual(directionTo(cible).length(),0)) {
        double deceleration(0.6);
        double speed;
        if(directionTo(cible).length()/(deceleration) <= getMaxSpeed()) {
            speed = directionTo(cible).length()/(deceleration) ;
        }

        else {
            speed = getMaxSpeed() ;
        }

        Vec2d vitesse_souhait = directionTo(cible)/directionTo(cible).length()*speed;


        return vitesse_souhait-vitesse_*direction_;

    }
    return direction_;
} // Return la force d'attraction par rapport a une cible.


Vec2d Animal::force( OrganicEntity* cible ) const
{
    return force(cible->getPosition());
}

void Animal::draw(sf::RenderTarget& targetWindow) const
{


    if(isDebugOn()) {
        CircularCollider::draw(targetWindow);
        drawVision(targetWindow);
        drawCercleBleu(targetWindow);
        drawText(targetWindow);

    }
    auto image_to_draw(buildSprite (getPosition(),
                                    getRadius()*2.1,
                                    getTexture(), getRotation()/DEG_TO_RAD ));

    targetWindow.draw(image_to_draw );


}





void Animal::drawText( sf::RenderTarget& targetWindow ) const
{

    auto text = buildText( stringEtat(),
                           getPosition()+getDirection()*110,
                           getAppFont(),
                           getAppConfig().default_debug_text_size,
                           sf::Color::Red,
                           (getRotation()/DEG_TO_RAD+90)
                         );
    auto text4 = buildText( " Age_limite:" + to_nice_string(age_limit_.asSeconds()) +   " Age:" + to_nice_string(age_.asSeconds()),
                            getPosition()+getDirection()*90,
                            getAppFont(),
                            getAppConfig().default_debug_text_size,
                            sf::Color::Blue,
                            (getRotation()/DEG_TO_RAD+90)
                          );

    if(etat_== GIVING_BIRTH) {
        auto text5 = buildText( "pause GivingBitrh " +
                                to_nice_string(time_pause_mise_en_bas_.asSeconds()),
                                getPosition()+getDirection()*150,
                                getAppFont(),
                                getAppConfig().default_debug_text_size,
                                sf::Color::Cyan,
                                (getRotation()/DEG_TO_RAD+90)
                              );
        targetWindow.draw(text5);

    }

    auto text15 = buildText( " " , // !!!!!!!!!!!!!!!!!!!!! Rajouter ici text à desinner couleur cyan
                             getPosition()+getDirection()*125,
                             getAppFont(),
                             getAppConfig().default_debug_text_size,
                             sf::Color::Cyan,
                             (getRotation()/DEG_TO_RAD+90)
                           );




    auto text3 = buildText("Energie limite:" +
                           to_nice_string(getAppConfig().animal_min_energy) +" Energie:"+ to_nice_string(energie_),
                           getPosition()+getDirection()*70,
                           getAppFont(),
                           getAppConfig().default_debug_text_size,
                           sf::Color::Blue,
                           (getRotation()/DEG_TO_RAD+90)
                          );


    if(getFemelleOuPas()) {
        auto text2 = buildText(   "Femelle  babies:" + to_nice_string(getBabies())+ " Gestation_limit:"+ to_nice_string(time_gestation_limit_.asSeconds()) + " Gestation:" + to_nice_string(time_gestation_.asSeconds()) ,


                                  getPosition()+getDirection()*50,
                                  getAppFont(),
                                  getAppConfig().default_debug_text_size,
                                  sf::Color::Magenta,
                                  (getRotation()/DEG_TO_RAD+90)
                              );
        targetWindow.draw(text2);
    } else {
        auto text2 = buildText(   "Male",

                                  getPosition()+getDirection()*50,
                                  getAppFont(),
                                  getAppConfig().default_debug_text_size,
                                  sf::Color::Blue,
                                  (getRotation()/DEG_TO_RAD+90));
        targetWindow.draw(text2);
    }

    targetWindow.draw(text);
    targetWindow.draw(text3);
    targetWindow.draw(text4);
    targetWindow.draw(text15);
    if (enceinte_== true)  targetWindow.draw((buildAnnulus( getPosition(), 50 , sf::Color::Magenta, 2 )));

}




void Animal::drawVision(sf::RenderTarget& targetWindow) const
{

    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    Arc arc(buildArc( (getRotation()-getViewRange()/2)/DEG_TO_RAD,
                      (getRotation()+getViewRange()/2)/DEG_TO_RAD,
                      getViewDistance(), getPosition() , color));
    targetWindow.draw(arc);

} // dessine la vision


double Animal::getRotation() const
{
    return direction_.angle();
} // donne l'angle de la direction de l'animal

void Animal::setRotation(const double& angle )
{
    direction_.x = cos(angle);
    direction_.y= sin(angle);
} // fait touner l'animal

bool Animal::isTargetInSight(const Vec2d& cible) const
{


    if(isEqual(distanceTo(cible),0 )) return false; // should not target himself
    if ( (cible-getPosition()).lengthSquared() <= (getViewDistance()*getViewDistance())) {
        if(direction_.dot((cible-getPosition()).normalised()) >= cos((getViewRange()+0.001)/2)) {
            return true;
        }

    } // return un bool si la cible et en vue


    if (isEqual(0,distanceTo(cible))) return true; // isEqual mieux que == 0
    return false;
}


Vec2d Animal::randomWalk()
{
    Vec2d random_vec(uniform(-1.0,1.0),uniform(-1.0,1.0));
    current_target_ += random_vec * getRandomWalkJitter()*3;
    current_target_ = current_target_.normalised()*getRandomWalkRadius();
    Vec2d moved_current_target = current_target_ + Vec2d(getRandomWalkDistance(), 0);
    target_Cercle_Bleu_= ConvertToGlobalCoord(moved_current_target);

    return   ConvertToGlobalCoord(moved_current_target)-getPosition();
} // retourne une force d'attraction aléatoire.


void Animal::drawCercleBleu(sf::RenderTarget& targetWindow) const
{
    if(etat_==WANDERING) {
        Vec2d centre(getPosition()+getRandomWalkDistance()*getDirection());
        //  list<Vec2d> listeCibles = getAppEnv().getTargetsInSightForAnimal(this);


        targetWindow.draw((buildAnnulus( centre, getRandomWalkRadius() , sf::Color(255, 150, 0), 2 )));
        //targetWindow.draw( buildCircle( centre + target_Cercle_Bleu_.normalised()*getRandomWalkRadius() , 5, sf::Color(0, 0, 255)) );
        targetWindow.draw(buildCircle(target_Cercle_Bleu_, 5, sf::Color(0, 0, 255)));
    }
}  // dessine le cercle bleu aléatoire


Vec2d Animal::getDirection() const
{
    return direction_;
}

Vec2d Animal::ConvertToGlobalCoord( Vec2d vec)
{
    // create a transformation matrix

    sf::Transform matTransform;

    // first, translate
    matTransform.translate(getPosition());

    // then rotate

    matTransform.rotate((getRotation())/DEG_TO_RAD);

    // now transform the point
    Vec2d global = matTransform.transformPoint(vec);

    return global;
}

const bool& Animal::getFemelleOuPas() const
{
    return femelle_ou_pas_;
} // getter sexe
void Animal::moveToVec2dForce(const sf::Time& dt,const Vec2d& force)
{
    moveToVec2dForce(dt.asSeconds(),force);

}


void Animal::moveToVec2dForce(const double& deltaT,const Vec2d& force)
{

    Vec2d acceleration=force/getMass();
    Vec2d vitesse_courante = vitesse_*direction_;
    Vec2d nouvelle_vitesse= vitesse_courante+acceleration*deltaT;
    direction_=nouvelle_vitesse.normalised();
    if (nouvelle_vitesse.length() > getMaxSpeed()) nouvelle_vitesse=direction_*getMaxSpeed();
    setPosition(getPosition()+nouvelle_vitesse*deltaT);
    vitesse_=nouvelle_vitesse.length();


} // Déplace l'animal selon une force d'atraction, change la vitessse et change l'orientation.

double Animal::getMaxSpeed() const
{
    double  maxSpeed= (double)(getStandardMaxSpeed());
    switch(etat_) {
    case FOOD_IN_SIGHT  :
        maxSpeed *=3;
        break;
    case MATE_IN_SIGHT :
        maxSpeed *=2;
        break;
    case RUNNING_AWAY :
        maxSpeed *=4;
        break;

        return maxSpeed;
    default:
        break;
    }
    // double energie (getEnergie()); if (energie <= 25) maxSpeed*=0.5;
    // src/Animal/Animal.cpp:393:29: error: passing 'const Animal' as 'this' argument discards qualifiers [-fpermissive]
    if (energie_ <= 50) maxSpeed *=0.5;
    return maxSpeed;
}


std::string Animal::stringEtat() const
{
    std::string humeurString;
    switch ( etat_)

    {
    case FOOD_IN_SIGHT:
        humeurString = "FOOD_IN_SIGHT";
        break;
    case  FEEDING :
        humeurString = "FEEDING";
        break;
    case  RUNNING_AWAY :
        humeurString = "RUNNING_AWAY";
        break;
    case  MATE_IN_SIGHT :
        humeurString = "MATE_IN_SIGHT";
        break;
    case MATING :
        break;
        humeurString = "MATING";
        break;
    case  GIVING_BIRTH :
        humeurString = "GIVING_BIRTH";
        break;
    case   WANDERING :
        humeurString = " WANDERING";
        break;
    case BABY:
        humeurString= "BABY";
    }

    return humeurString;
}




void Animal::updateEnergie( sf::Time dt)
{

    double energyLoss(energie_depense_base_+ vitesse_* energie_depense_facteur_* dt.asSeconds());
//double energyLoss(energie_depense_base_+ vitesse_* 0.1 _* dt.asSeconds())
    OrganicEntity::setEnergy(getEnergie()-energyLoss);
}/* La perte d'énergie est fonction du pas de temps écoulé (en secondes) et de la norme de la vitesse (plus l'animal va vite et plus il se fatigue) selon la formule suivante:
perte_energie = depense_energetique_de_base + norme_vitesse * facteur_perte_energie() * dt
depense_energetique_de_base est paramétrable (getAppConfig().animal_base_energy_consumption).
 Le facteur de perte d'énergie se calcule de façon différente pour chaque type d'animaux (getAppConfig().scorpion_energy_loss_factor pour les scorpions par exemple). */


void Animal::manger()
{
    setEnergy(getEnergie()+0.7*organic_entity_cible_->getEnergie());
    organic_entity_cible_->setEnergy(0);
    // organic_entity_cible_->oublier();

}


void Animal::analyzeEnvironment()
{
    organic_entity_ItsaMatchs_.clear();
    organic_entity_Preydators_.clear();
    organic_entity_FOODs_.clear();
    organic_entity_ItsaMatchs_ = mates(enVue());
    organic_entity_FOODs_ = mangeable(enVue());
    organic_entity_Preydators_= preydateur(enVue());
} // Analyse les OE en vue et change les attributs.


std::list<OrganicEntity*> Animal::enVue()
{
    return getAppEnv().getEntitiesInSightForAnimal(this);
} // retourne la liste des OE en vue


std::list<OrganicEntity*> Animal::mangeable(std::list <OrganicEntity*> listeEV)
{
    list<OrganicEntity*> liste;
    if (!listeEV.empty()) {
        for (const auto& OE : listeEV) {
            if(eatable(OE)) liste.push_back(OE);
        }
    }
    return liste;
} // prend un liste OE et retourne ceux qui sont mangeable

std::list<OrganicEntity*> Animal::mates(std::list <OrganicEntity*> listeEV)
{
    list<OrganicEntity*> liste;
    if (!listeEV.empty()) {
        for (const auto& OE : listeEV) {
            if((matable(OE)) and (OE->matable(this))) liste.push_back(OE);
        }
    }
    return liste; // prend une liste OE et retourne ceux avec qui ont peut faire des enfants
}
OrganicEntity* Animal::plusProche(std::list<OrganicEntity*> listeEV)
{
    OrganicEntity* OEproche(nullptr);
    if (!listeEV.empty()) {
        double dmin(getAppConfig().simulation_world_size*2+99900000);
        for (const auto& OE : listeEV) {
            if(distanceTo(OE->getPosition()) <= dmin ) {
                dmin=distanceTo(OE->getPosition());
                OEproche=OE;
            }
        }
    }
    return OEproche;
}


std::list<OrganicEntity*> Animal::preydateur( std::list<OrganicEntity*> env)
{

    std::list<OrganicEntity*> preydateurs;
    for (auto OE : env ) {
        if (OE->eatable(this))
//	this.eatableBy(OE);
            preydateurs.push_back(OE);

    }
    return preydateurs;

}



Vec2d Animal::forceFuite( std::list<OrganicEntity*> listeOE )
{
    Vec2d forceResultante ;
    double facteur1(500);
    double facteur2(1.2) ;
    for (auto OE : listeOE ) {
        forceResultante +=
            ( facteur1*(OE->getPosition() - getPosition())
              /
              ( pow((OE->getPosition()
                     - getPosition()).length(),facteur2))  ) ;
    }
    return -1*forceResultante;
}

const bool& Animal::getEnceinte() const
{
    return enceinte_;

}

bool Animal::collisionCible()
{
    return isColliding(CircularCollider(organic_entity_cible_->getPosition(),organic_entity_cible_->getRadius())) ;

}


const int& Animal::getBabies() const
{
    return babies_;
}
void Animal::setBabies(const int& n)
{
    babies_= n;
}

void Animal::oublierMum()
{
    organic_entity_mum_ = nullptr;
}

void Animal::oublierBaby( OrganicEntity* baby)
{
    if (!organic_entity_kids_.empty()) {
        for ( auto& OE : organic_entity_kids_) {
            if(OE != nullptr ) {
                if( OE == baby ) {
                    OE = nullptr;

                }
            }
        }
    }
}
void Animal::oublier()
{
    if(!organic_entity_kids_.empty()) {
        for (auto& oe: organic_entity_kids_) {
            if(oe != nullptr ) oe->oublierMum();

        }
    }

    if( organic_entity_mum_!= nullptr) {
        organic_entity_mum_->oublierBaby(this);

    }
}

int Animal::getEtat()
{
    return etat_;
}

OrganicEntity* Animal::getMangeablePlusProche()
{
    if ( !organic_entity_FOODs_.empty()) {
        return plusProche(organic_entity_FOODs_);
    }
    return nullptr;

}
/*
void Animal::setEtat(const string& etat)
{
	etat_ = etat;

}

void Animal::setEtat(const string& etat){
switch ( etat){
	case FOOD_IN_SIGHT :
	etat_ = 0;
	case FEEDING :
	etat_= 1;
	case RUNNING_AWAY;
	etat_= 2;
	case MATE_IN_SIGHT;
	etat_= 3;
	case MATING ;
	etat_ = 4;
	case GIVING_BIRTH;
	etat_ = 5 ;
	case WANDERING;
	etat_ = 6;
	case BABY :
	etat_ = 7;
}
}
*/
/*
void Animal::setEtat(const int& etat){
etat_ = etat;
}
* */

/*
 *  FOOD_IN_SIGHT, // nourriture en vue
    FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
    RUNNING_AWAY,  // en fuite
    MATE_IN_SIGHT, // partenaire en vue
    MATING,        // vie privée (rencontre avec un partenaire!)
    GIVING_BIRTH,  // donne naissance
    WANDERING,     // déambule
    BABY,
 *
 * */
/*
void Animal::oublierMumOrKids(){
	while (!(organic_entity_mum_or_kids_.empty())){

		organic_entity_mum_or_kids_.pop_front();
	}
}
*/
/*
enum Etat Animal::getEtat(){ // Ici comment faire une fonction qui rend ou change l'etat_, on doit passer par des ints??
	return
	Etat_;
}
* void Animal::setEtat(Etat etat){
	etat_ = etat;
}

*/

/*

Vec2d Animal::forceRalentir(){


}
*/
