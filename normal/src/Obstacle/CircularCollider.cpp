//#include <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
//
#include "../Application.hpp"
#include "CircularCollider.hpp"

//#include <iostream>


#include "../Utility/Utility.hpp"


CircularCollider::CircularCollider(Vec2d const& v, double const& r)
    :
    v_(clamping(v)),
    r_(r/2)

{
    if( r < 0 ) {
        std::cerr << "rayon negatif" << std::endl ;
        throw 1 ;
    }
    ;
}

const Vec2d& CircularCollider::getPosition() const
{
    return v_;
}


const double& CircularCollider:: getRadius() const
{
    return r_;
}



CircularCollider::CircularCollider(const CircularCollider& c)
    :CircularCollider(c.v_,c.r_)
{}

CircularCollider&  CircularCollider::operator=(const CircularCollider& c)
{
    v_=clamping(c.v_);
    r_=c.r_;
    return *this;
}
/*			// INUTILE
Vec2d CircularCollider::clamping(c Vec2d& v){
	double worldSize = getAppConfig().simulation_world_size;
  auto width  = worldSize; // largeur
  auto height = worldSize; // hauteur
	Vec2d v2;
	 v2.x= v.x;
	 v2.y= v.y;
	if( v.x < 0 ) v2.x += width;
    if(v.x> width) v2.x -= width;
    if(v.y>height ) v2.y -= height;
    if (v.y < 0) v2.y += height;

    if ( not(v.x < 0) and not(v.x> width)) {
        v2.x= v.x;
    }
    if (not(v.y>height ) and not(v.y < 0)) {
        v2.y= v.y;
    }


 //   cout << v.x << " y " << v.y << "devient " << v2.x << " y "  << v2.y << endl;
    return v2;
}

//  INUTILE fait tourner en rond dans monde torique méthode pas vérifier
*/


/*!
* @brief  Il y a 9 candidats possibles pour le vecteur le plus proche dans le monde torique :

to lui même;
to augmenté du vecteur {0 , +/-height}, dans toutes les combinaisons possibles;
to augmenté du vecteur {+/-width, 0}, dans toutes les combinaisons possibles;
to augmenté du vecteur {+/- width, +/- height}, dans toutes les combinaisons possibles.
choisit le plus proche.
*/
Vec2d CircularCollider::directionTo(const Vec2d& to1) const
{
    Vec2d to= clamping(to1);
    double min(10000);
    Vec2d vector;
    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize; // largeur du monde
    auto height = worldSize; // hauteur du monde
    for( int i(-1); i<=1; ++i) {
        for (int j(-1); j<=1; ++j) {
            if (distance(v_,Vec2d(to.x+i*width,to.y+j*height)) < min) {
                min = distance(v_,Vec2d(to.x+i*width,to.y+j*height));
                vector = (Vec2d(to.x+i*width,to.y+j*height)-v_);
            }
        }

    }
    return vector;
}



Vec2d CircularCollider::directionTo( const CircularCollider& c) const
{
    return (directionTo(c.v_));
}



double CircularCollider::distanceTo(const Vec2d& to) const
{
    return directionTo(to).length();
}

double CircularCollider::distanceTo(const CircularCollider& to) const
{


    return directionTo(to.v_).length();
}


void CircularCollider::move(const Vec2d& dx)  // déplace != setPosition()
{
    v_=clamping(v_+dx);
}

CircularCollider& CircularCollider::operator+=(const Vec2d& dx)
{
    this->move(dx);
    return *this;
}




bool	CircularCollider::isCircularColliderInside( const CircularCollider& other) const
{


    if (( r_ >= other.r_ ) and ( distanceTo(other) <= (    r_ - other.r_  ) )) return true;

    return false;
}


/*!
 * une méthode isColliding prenant en argument un CircularCollider, other, et retournant true si other est en collision avec
 *  l'instance courante et false sinon. Soient deux CircularCollider, a et b, a est en collision avec b si la distance entre
 * les centres de a et b est inférieure ou égale à la somme des rayons de a et b;
 * */
bool CircularCollider::isColliding( const CircularCollider& other) const
{
    if(distanceTo(other)<=(r_+other.r_)) return true;
    return false;

}


/*!

 une méthode isPointInside prenant en argument un point (de type Vec2d) et retournant true si le point est à l'intérieur de l'instance courante et false sinon.
 *  Un point p est à l'intérieur d'un CircularCollider body si la distance entre p et body est inférieure ou égale au rayon de body;

l'opérateur > utilisable comme suit :

body1 > body2

retournant true si body2 est à l'intérieur de body1 et false sinon. Les objets body1 et body2 sont de type CircularCollider;


*/
bool	CircularCollider::isPointInside(const Vec2d& v) const
{
    if (distanceTo(v)<= r_) return true;
    return false;
}


bool operator>(CircularCollider c1,const CircularCollider& c2)
{
    return c1.isCircularColliderInside( c2 ) ;
}

bool  operator>( CircularCollider c,const Vec2d& v)
{
    return c.isPointInside(v) ;
}


/*!
 * l'opérateur | utilisable comme suit :
body1 | body2

retournant true si body2 est en collision avec body1 et false sinon. Les objets body1 et body2 sont de type CircularCollider;

l'opérateur > utilisable comme suit :

body > point

retournant true si point est à l'intérieur de body et false sinon. Les objets body est de type CircularCollider et point est de type Vec2d;
*/
bool operator|( CircularCollider c1,const CircularCollider& c2 )
{
    return c1.isColliding(c2);
}



/*!
 * Monde torique si la postion dépace l'environment elle est ramenée de l'autre côté
*/
Vec2d clamping(const Vec2d& v)
{
    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize; // largeur
    auto height = worldSize; // hauteur
    Vec2d v2;
    v2.x= v.x;
    v2.y= v.y;
    if( v.x < 0 ) v2.x += width;
    if(v.x> width) v2.x -= width;
    if(v.y>height ) v2.y -= height;
    if (v.y < 0) v2.y += height;

    return v2;
}


std::ostream& operator<<(std::ostream& s, CircularCollider const& c)
{

    s << "CircularCollider: position = <";
    s <<c.getPosition() ;
    s <<  "> radius = <";
    s << c.getRadius();
    s << ">" ;
    s << std::endl;
    return s;
}

void CircularCollider::setPosition(const Vec2d& v)
{
    v_= clamping(v);
}
// cout << " X " << CircularCollider::clamping(b2).x << " Y " << CircularCollider::clamping(b2).y << endl;

/*
void CircularCollider::drawCircularCollider(sf::RenderTarget& targetWindow ){
	targetWindow.draw(buildCircle(getPosition(), getRadius(), sf::Color(255, 255, 255)));

}
* */
void  CircularCollider::draw(sf::RenderTarget&  targetWindow) const
{
    targetWindow.draw(buildCircle(getPosition(), getRadius(), sf::Color(255, 255, 255)));


}


void CircularCollider::grandir()
{
    r_=r_*3;

}

void CircularCollider::setRadius(const double& radius)
{
    r_= radius;
}


