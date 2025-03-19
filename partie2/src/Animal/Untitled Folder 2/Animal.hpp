#pragma once
#include "../Obstacle/CircularCollider.hpp"
#include "../Utility/Vec2d.hpp"
#include  <SFML/Graphics.hpp>
#include  "../Environment/Environment.hpp"

class Environment;
class Animal : public CircularCollider
{
public:
    Animal(const Vec2d& position, double vitesse = 0) : CircularCollider( position, ANIMAL_RADIUS), direction_(1,0), vitesse_(vitesse), cible_(1,0), current_target_(1,0)
    {}
    const double& getStandardMaxSpeed() const;
    const double& getMass() const ;

    Vec2d force( const Vec2d&) const;


    Vec2d getSpeedVector() const ;

    void update(sf::Time );
    void draw(sf::RenderTarget& targetWindow);
    void moveToTarget(const double&, const Vec2d& );

    const double& getViewRange() const;
    const double& getViewDistance()const;
    double getRotation() const  ;

    void drawVision(sf::RenderTarget& targetWindow);

    bool isTargetInSight(const Vec2d&) const ;

    double getRandomWalkRadius() const ;
    double getRandomWalkDistance() const;
    double getRandomWalkJitter() const ;
    void randomWalk();
    void drawCercleBleu(sf::RenderTarget& targetWindow);
    Vec2d getDirection();
    Vec2d ConvertToGlobalCoord( Vec2d vec);
protected:

    void setTargetPosition(const Vec2d&);
    void setRotation(const double& );
private:


    Vec2d direction_;
    double vitesse_;
    Vec2d cible_;
    Vec2d current_target_;
    Vec2d target_Cercle_Bleu_;
    double viewRange_;

    double viewDistance_;


};
