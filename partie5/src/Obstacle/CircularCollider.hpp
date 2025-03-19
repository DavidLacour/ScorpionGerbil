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

    /*!
    * @brief create a CirCuclarCollider
    *
    * @param Position
    * @param radius have to be positif
    *
    * @return a CircullarCollider
    */
    CircularCollider(const Vec2d&, const double&);

    const Vec2d& getPosition() const;
    const double& getRadius() const;

    CircularCollider(const CircularCollider&);
    CircularCollider& operator=(const CircularCollider&);

    /*!
    * @brief  cherche le chemin le plus court en deux vecteurs dans un monde torique
    *
    * @param vector
    *
    * @return le chemin le plus court en deux vecteurs
    */
    Vec2d directionTo(const Vec2d&) const;

    /*!
    * @brief retourne chemin le plus court vers un Circularcollider
    *
    * @param vector
    *
    * @return Vec2d le chemin le plus court en deux vecteurs
    */
    Vec2d directionTo(const CircularCollider&) const;

    /*!
    * @brief appelle directionto(Vec2d&) et calcul la longueur du vecteur
    *
    * @param Vec2d
    *
    * @return la longueur entre this.position et le CircularColider
    */
    double distanceTo(const Vec2d&)const;

    /*!
    * @brief appelle directionto(CircullarCollider.getPosition()) et calcul la longueur du vecteur
    *
    * @param CircularCollider
    *
    * @return la longueur entre this.position et le CircularColider
    */
    double distanceTo(const CircularCollider&) const;

    /*!
    * @brief déplace d'un vecteur dans un monde torique avec clamping en ajoutant un vecteur
    *
    * @param le Vecteur qu'on veut ajouter à la position actuelle
    *
    */
    void move(const Vec2d&);

    /*!
    * @brief opérateur pour move
    *

    *
    */
    CircularCollider& operator+=( const Vec2d& dx);

    /*!
    * @brief fait grandir les bébés gerbil
    */
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


/*!
 * Monde torique si la postion dépace l'environment elle est ramenée de l'autre côté
*/
Vec2d clamping(const Vec2d& v);

bool  operator>( CircularCollider c1,const CircularCollider& c2);
bool operator|( CircularCollider c1 ,const CircularCollider& c2 );
bool operator>( CircularCollider c ,const Vec2d& v);
std::ostream& operator<<(std::ostream& s , CircularCollider const& c);
