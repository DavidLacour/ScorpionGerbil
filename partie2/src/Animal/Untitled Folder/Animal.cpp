#include "../Utility/Vec2d.hpp"

#include "../Obstacle/CircularCollider.hpp"
#include "../Utility/Vec2d.hpp"
#include <list>

#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"

#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "../Obstacle/CircularCollider.hpp"
#include "../Utility/Constants.hpp"
#include  "../Environment/Environment.hpp"
#include "Animal.hpp"
#include <cmath>
#include <Tests/GraphicalTests/ChasingTest.hpp>
#include "../Tests/GraphicalTests/ChasingTest.hpp"
#include <list>
#include "../Random/Uniform.hpp"

const double& Animal::getStandardMaxSpeed() const
{

    return ANIMAL_MAX_SPEED ;
}

const double& Animal::getMass() const
{
    return ANIMAL_MASS;
}


void Animal::setTargetPosition(const Vec2d& v)
{
    cible_= v;
}


Vec2d Animal::getSpeedVector() const
{
    return direction_*vitesse_;
}

void Animal::update(sf::Time dt)
{
    //  if(!(getAppEnv().getTargetsInSightForAnimal.empty(this))) { // si la pas de cible la liste est vide

    list<Vec2d> listeCibles = getAppEnv().getTargetsInSightForAnimal(this);

    if  (!(listeCibles.empty())) {

        // cible_= cibleProche; // poursuit la cible la plus proche

        cible_ = listeCibles.back(); // poursuit la dernière cible
        // cible_ = listeCibles.front(); // poursuit la première cible
        listeCibles.clear();

        moveToTarget(dt.asSeconds());

    } else {

        randomWalk();
        moveToTarget(dt.asSeconds());

    }


}

// update et appelle la fonction move qui déplace l'animal

void Animal::moveToTarget(const double& deltaT)
{

    Vec2d acceleration=force(0.6)/getMass();
//	cout << force() << endl ;

    Vec2d vitesse_courante = vitesse_*direction_;

//	cout << "vitesse_courante = vitesse_*direction_   x =  " << vitesse_courante.x << " Y = " << vitesse_courante.y << " " << vitesse_ << " x " << direction_.x <<" y " << direction_.y << endl;

    Vec2d nouvelle_vitesse= vitesse_courante+acceleration*deltaT;


    // nouvelle_vitesse.x+=acceleration.x*dt.asSeconds();
    // nouvelle_vitesse.y+=acceleration.y*dt;

    direction_=nouvelle_vitesse.normalised();
    if (nouvelle_vitesse.length() > getStandardMaxSpeed()) nouvelle_vitesse=direction_*getStandardMaxSpeed();
    setPosition(getPosition()+nouvelle_vitesse*deltaT);
    vitesse_=nouvelle_vitesse.length();




} // Appelle la fonction force() et fait bouger le ChasingAutomaton.


Vec2d Animal::force(double d)
{

    double speed;
    if (!isEqual(directionTo(cible_).length(),0)) {
        if(directionTo(cible_).length()/((double)d*0.1) <= getStandardMaxSpeed()) {
            speed = directionTo(cible_).length()/(0.1*(double)d) ;
        }

        else {
            speed = getStandardMaxSpeed() ;
        }

        Vec2d vitesse_souhait = directionTo(cible_)/directionTo(cible_).length()*speed;


        return vitesse_souhait-vitesse_*direction_;
    }
    return direction_;
} // Return la force d'attraction.



void Animal::draw(sf::RenderTarget& targetWindow)
{
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite( getPosition(),
                                    getRadius()*2,
                                    texture));

    //     auto cible(buildCircle( cible_, 5, sf::Color(255, 0, 0)));
    /*
    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    Arc arc(buildArc((getRotation()-getViewRange()/2)/DEG_TO_RAD,(getRotation()+getViewRange()/2)/DEG_TO_RAD, getViewDistance() , getPosition() , color));
    targetWindow.draw(arc);

    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    Arc arc(buildArc(45,135, 200, getPosition() , color));
    targetWindow.draw(arc);
    */

    // targetWindow.draw(cible );
    targetWindow.draw(image_to_draw );
    drawVision(targetWindow);
    drawCercleBleu(targetWindow);



}


void Animal::drawVision(sf::RenderTarget& targetWindow)
{

    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    Arc arc(buildArc( (getRotation()-getViewRange()/2)/DEG_TO_RAD,
                      (getRotation()+getViewRange()/2)/DEG_TO_RAD,
                      getViewDistance(), getPosition() , color));
    targetWindow.draw(arc);

}

const double& Animal::getViewRange()
const

{
    return ANIMAL_VIEW_RANGE;
}
const double& Animal::getViewDistance()const
{
    return ANIMAL_VIEW_DISTANCE;
}

double Animal::getRotation() const
{
    return direction_.angle();
}

void Animal::setRotation(const double& angle )
{
    direction_.x = cos(angle);
    direction_.y= sin(angle);
}

bool Animal::isTargetInSight(const Vec2d& cible) const
{


    if ( (cible-getPosition()).lengthSquared() <= (getViewDistance()*getViewDistance())) {
        if(direction_.dot((cible-getPosition()).normalised()) >= cos((getViewRange()+0.001)/2)) {
            return true;
        }

    }
    if (isEqual(0,distanceTo(cible))) return true;
    return false;
}


double Animal::getRandomWalkRadius() const
{
    return ANIMAL_RANDOM_WALK_RADIUS;

}



double Animal::getRandomWalkDistance() const
{
    return ANIMAL_RANDOM_WALK_DISTANCE;
}


double Animal::getRandomWalkJitter() const
{
    return ANIMAL_RANDOM_WALK_JITTER;

}

void Animal::randomWalk()
{
    Vec2d current_target = cible_;
    Vec2d random_vec(uniform(-1.0,1.0),uniform(-1.0,1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised()*getRandomWalkRadius();
    Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);
    target_Cercle_Bleu_=moved_current_target;

    current_target= ConvertToGlobalCoord(moved_current_target)-getPosition();
    cible_=current_target;

}

void Animal::drawCercleBleu(sf::RenderTarget& targetWindow)
{

    Vec2d centre(getPosition()+getRandomWalkDistance()*getDirection());
    list<Vec2d> listeCibles = getAppEnv().getTargetsInSightForAnimal(this);

    if  (listeCibles.empty()) {
        targetWindow.draw((buildAnnulus( centre, getRandomWalkRadius() , sf::Color(255, 150, 0), 2 )));
        targetWindow.draw( buildCircle( centre + cible_.normalised()*getRandomWalkRadius() , 5, sf::Color(0, 0, 255)) );
    }
}

Vec2d Animal::getDirection()
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



/*
    double dmin(100000000); // on devrait mettre la constante worldSize
    Vec2d cibleProche(0,0);
    for (auto cible : listeCibles) {
        if (distanceTo(clamping(cible)) <= dmin) {
            dmin=distanceTo(cible);
            cibleProche = cible;
        }

    } */
