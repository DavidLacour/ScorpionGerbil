#pragma once
#include "../Utility/Vec2d.hpp"
#include  <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
//#include "../Application.hpp"
//#include "../Environment/Environment.hpp"
// typedef CircularCollider Obstacle;
class CircularCollider : public Drawable
{
public:
    CircularCollider(const Vec2d&, const double&);
    const Vec2d& getPosition() const;
    const double& getRadius() const;
    CircularCollider(const CircularCollider&);

    CircularCollider& operator=(const CircularCollider&);

    Vec2d directionTo(const Vec2d&) const;
    Vec2d directionTo(const CircularCollider&) const;
    double distanceTo(const Vec2d&)const;
    double distanceTo(const CircularCollider&) const;
    void move(const Vec2d&);
    CircularCollider& operator+=( const Vec2d& dx);
    void grandir();
    bool isCircularColliderInside( const CircularCollider& ) const;
    bool isColliding( const CircularCollider&)const;
    bool isPointInside(const Vec2d&) const;
    //void drawCircularCollider(sf::RenderTarget& );
    void setPosition(const Vec2d&);

    virtual ~CircularCollider() {}
    virtual void draw(sf::RenderTarget& target) const override ;
    // Vec2d clamping(Vec2d&);
protected:
    void setRadius(const double&);

private:
    Vec2d v_;
    double r_;
};

Vec2d clamping(const Vec2d& v);

bool  operator>( CircularCollider c1,const CircularCollider& c2);
bool operator|( CircularCollider c1 ,const CircularCollider& c2 );
bool operator>( CircularCollider c ,const Vec2d& v);
// bool operator|( CircularCollider* c1 , CircularCollider* c2 );
std::ostream& operator<<(std::ostream& s , CircularCollider const& c);
