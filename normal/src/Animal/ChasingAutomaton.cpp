#include <list>
#include "../Obstacle/CircularCollider.hpp"

#include "../Animal/Animal.hpp"
#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"

#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "ChasingAutomaton.hpp"
#include "../Utility/Constants.hpp"

const double& ChasingAutomaton::getStandardMaxSpeed() const
{
    return CHASING_AUTOMATON_MAX_SPEED;
}

const double& ChasingAutomaton::getMass() const
{
    return CHASING_AUTOMATON_MASS;
}

void ChasingAutomaton::setTargetPosition(const Vec2d& v)
{
    cible_= v;
}

Vec2d ChasingAutomaton::getSpeedVector() const
{
    return direction_*vitesse_;
}

void ChasingAutomaton::update(sf::Time dt)
{
    move(dt.asSeconds());
}

void ChasingAutomaton::move(const double& deltaT)
{
    Vec2d acceleration = force(cible_)/getMass();
    Vec2d vitesse_courante = vitesse_*direction_;
    Vec2d nouvelle_vitesse = vitesse_courante+acceleration*deltaT;
    direction_ = nouvelle_vitesse.normalised();
    if (nouvelle_vitesse.length() > getStandardMaxSpeed()) nouvelle_vitesse = direction_*getStandardMaxSpeed();
    setPosition(getPosition()+nouvelle_vitesse*deltaT);
    vitesse_ = nouvelle_vitesse.length();
}

Vec2d ChasingAutomaton::force(const Vec2d& cible) const
{
    double deceleration(0.6);
    double speed;
    if(directionTo(cible_).length()/(deceleration) <= getStandardMaxSpeed()) {
        speed = directionTo(cible).length()/(deceleration);
    }
    else {
        speed = getStandardMaxSpeed();
    }

    Vec2d vitesse_souhait = directionTo(cible)/directionTo(cible).length()*speed;
    return vitesse_souhait-vitesse_*direction_;
}

void ChasingAutomaton::draw(sf::RenderTarget& targetWindow)
{
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite(getPosition(),
                                   getRadius()*2,
                                   texture));

    auto cible(buildCircle(cible_, 5, sf::Color(255, 0, 0)));

    targetWindow.draw(cible);
    targetWindow.draw(image_to_draw);
}