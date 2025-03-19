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
} // getter limite vitesse

const double& Animal::getMass() const
{
    return ANIMAL_MASS;
} // getter masse


void Animal::setTargetPosition(const Vec2d& v)
{
    cible_= v;
} // change la cible de l'animal (en attribut)


Vec2d Animal::getSpeedVector() const
{
    return direction_*vitesse_;
} // getter pour la direction fois la vitesse peut être utile

void Animal::update(sf::Time dt)
{
    //  if(!(getAppEnv().getTargetsInSightForAnimal.empty(this))) { // si la pas de cible la liste est vide

    list<Vec2d> listeCibles = getAppEnv().getTargetsInSightForAnimal(this);

    if  (!(listeCibles.empty())) {

        // cible_= cibleProche; // poursuit la cible la plus proche

        cible_ = listeCibles.back(); // poursuit la dernière cible
        // cible_ = listeCibles.front(); // poursuit la première cible
        listeCibles.clear();

        moveToAttributCible(dt.asSeconds());

    } else {


        moveToVec2dForce(dt.asSeconds(),randomWalk());

    }


} // update et appelle la fonction  moveToAttributCible  qui déplace l'animal vers un attribut cible et moveToVec2dForce qui bouge l'animal selon une force d'attraction.


void Animal::moveToAttributCible(const double& deltaT)
{

    Vec2d acceleration=force(cible_)/getMass();
    Vec2d vitesse_courante = vitesse_*direction_;
    Vec2d nouvelle_vitesse= vitesse_courante+acceleration*deltaT;
    direction_=nouvelle_vitesse.normalised();
    if (nouvelle_vitesse.length() > getStandardMaxSpeed()) nouvelle_vitesse=direction_*getStandardMaxSpeed();
    setPosition(getPosition()+nouvelle_vitesse*deltaT);
    vitesse_=nouvelle_vitesse.length();
} //  Appelle la fonction force(), Déplace l'animal, change la vitessse et change l'orientation vers l'attribut cible.


void Animal::moveToVec2dForce(const double& deltaT,const Vec2d& force)
{

    Vec2d acceleration=force/getMass();
    Vec2d vitesse_courante = vitesse_*direction_;
    Vec2d nouvelle_vitesse= vitesse_courante+acceleration*deltaT;
    direction_=nouvelle_vitesse.normalised();
    if (nouvelle_vitesse.length() > getStandardMaxSpeed()) nouvelle_vitesse=direction_*getStandardMaxSpeed();
    setPosition(getPosition()+nouvelle_vitesse*deltaT);
    vitesse_=nouvelle_vitesse.length();
} // Déplace l'animal selon une force d'atraction, change la vitessse et change l'orientation.


Vec2d Animal::force( const Vec2d& cible ) const
{


    if (!isEqual(directionTo(cible_).length(),0)) {
        double deceleration(0.6);
        double speed;
        if(directionTo(cible_).length()/(deceleration) <= getStandardMaxSpeed()) {
            speed = directionTo(cible).length()/(deceleration) ;
        }

        else {
            speed = getStandardMaxSpeed() ;
        }

        Vec2d vitesse_souhait = directionTo(cible)/directionTo(cible).length()*speed;


        return vitesse_souhait-vitesse_*direction_;

    }
    return direction_;
} // Return la force d'attraction selon une position en Vec2d.



void Animal::draw(sf::RenderTarget& targetWindow)
{
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite( getPosition(),
                                    getRadius()*2,
                                    texture));
    targetWindow.draw(image_to_draw );
    drawVision(targetWindow);
    drawCercleBleu(targetWindow);



} // appelle les fonctions qui dessine l'animal, son champs de vision et le cercle bleu de randomWalk.


void Animal::drawVision(sf::RenderTarget& targetWindow)
{

    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    Arc arc(buildArc( (getRotation()-getViewRange()/2)/DEG_TO_RAD,
                      (getRotation()+getViewRange()/2)/DEG_TO_RAD,
                      getViewDistance(), getPosition() , color));
    targetWindow.draw(arc);

} // dessine la vision

const double& Animal::getViewRange()
const

{
    return ANIMAL_VIEW_RANGE;
} // getter portée angle vue
const double& Animal::getViewDistance()const
{
    return ANIMAL_VIEW_DISTANCE;
} // getter distance du champs de vision

double Animal::getRotation() const
{
    return direction_.angle();
} // getter de la direction de l'animal en radiant.

void Animal::setRotation(const double& angle )
{
    direction_.x = cos(angle);
    direction_.y= sin(angle);
} // fait tourner l'animal selon un angle

bool Animal::isTargetInSight(const Vec2d& cible) const
{


    if ( (cible-getPosition()).lengthSquared() <= (getViewDistance()*getViewDistance())) {
        if(direction_.dot((cible-getPosition()).normalised()) >= cos((getViewRange()+0.001)/2)) {
            return true;
        }

    }
    if (isEqual(0,distanceTo(cible))) return true;
    return false;
} // bool si la cible est en vue.


double Animal::getRandomWalkRadius() const
{
    return ANIMAL_RANDOM_WALK_RADIUS;

} // getter rayon pour marche aléatoire



double Animal::getRandomWalkDistance() const
{
    return ANIMAL_RANDOM_WALK_DISTANCE;
} // getter distance pour marche aléatoire


double Animal::getRandomWalkJitter() const
{
    return ANIMAL_RANDOM_WALK_JITTER;

} // getter taille de l'aléat

Vec2d Animal::randomWalk()
{
    Vec2d random_vec(uniform(-1.0,1.0),uniform(-1.0,1.0));
    current_target_ += random_vec * getRandomWalkJitter();
    current_target_ = current_target_.normalised()*getRandomWalkRadius();
    Vec2d moved_current_target = current_target_ + Vec2d(getRandomWalkDistance(), 0);
    target_Cercle_Bleu_= ConvertToGlobalCoord(moved_current_target);

    return   ConvertToGlobalCoord(moved_current_target)-getPosition();
} // retourne une force d'attraction aléatoire.

void Animal::drawCercleBleu(sf::RenderTarget& targetWindow)
{

    Vec2d centre(getPosition()+getRandomWalkDistance()*getDirection());
    list<Vec2d> listeCibles = getAppEnv().getTargetsInSightForAnimal(this);

    if  (listeCibles.empty()) {
        targetWindow.draw((buildAnnulus( centre, getRandomWalkRadius() , sf::Color(255, 150, 0), 2 )));
        //targetWindow.draw( buildCircle( centre + target_Cercle_Bleu_.normalised()*getRandomWalkRadius() , 5, sf::Color(0, 0, 255)) );
        targetWindow.draw(buildCircle(target_Cercle_Bleu_, 5, sf::Color(0, 0, 255)));
    }
}  // dessine le cercle bleu aléatoire

Vec2d Animal::getDirection()
{
    return direction_;
} // getter direction.

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
    //   	 cout << vec << "     " << matTransform.transformPoint(vec) << endl;
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

    } */ // squelettte pourrait utilse plus à modifier pour retourner la cible la plus proche
