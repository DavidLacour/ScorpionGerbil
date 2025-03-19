#pragma once
#include "../Obstacle/CircularCollider.hpp"
#include "../Utility/Vec2d.hpp"
#include  <SFML/Graphics.hpp>
#include  "../Environment/Environment.hpp"

class Environment;
class Animal : public CircularCollider
{
public:
    Animal(const Vec2d& position, double vitesse = 0) : CircularCollider( position, ANIMAL_RADIUS), direction_(1,0), vitesse_(vitesse), cible_(1,0)
    {}
    // getter:

    const double& getStandardMaxSpeed() const;
    const double& getMass() const ;
    double getRandomWalkRadius() const ;
    double getRandomWalkDistance() const;
    double getRandomWalkJitter() const ;
    Vec2d getSpeedVector() const ;
    Vec2d force( const Vec2d&) const;
    const double& getViewRange() const;
    const double& getViewDistance()const;
    double getRotation() const  ;
    Vec2d getDirection();
    bool isTargetInSight(const Vec2d&) const ; // cible en vue

    // update et draw
    void update(sf::Time );


    void draw(sf::RenderTarget& targetWindow); // appelle les draws


    void moveToAttributCible(const double&); // déplace attribut cible
    void moveToVec2dForce(const double& deltaT,const Vec2d& ); // déplace avec une force



    void drawVision(sf::RenderTarget& targetWindow); // dessine la vision



    // marche aléatoire et dessin cercle bleu:
    Vec2d randomWalk();
    void drawCercleBleu(sf::RenderTarget& targetWindow);


    Vec2d ConvertToGlobalCoord( Vec2d vec); // converti par rapport à l'animal en coordonée global


protected:
    // setters:
    void setTargetPosition(const Vec2d&);
    void setRotation(const double& );
private:

    // Attributs:
    Vec2d direction_;
    double vitesse_;
    Vec2d cible_; // représente une potenciel cible qui ferait partie des attributs annimal
    Vec2d current_target_; // cible pour randomWalk
    Vec2d target_Cercle_Bleu_; // Attribut pour dessine le cercle en dehors de la fonction randomwalk
    double viewRange_;
    double viewDistance_;


};
