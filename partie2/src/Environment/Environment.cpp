
#include <list>
#include "../Animal/Animal.hpp"
#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
#include "Environment.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

void Environment::addAnimal(Animal* a)
{
    animaux_.push_back(a);
}

void  Environment::addTarget(const Vec2d& v)
{
    cibles_.push_back(v);
}

void Environment::update(sf::Time dt)
{


    for( auto animal : animaux_) {
        animal->update(dt);

    }


    // chaque chose en son temps
    //faire évoluer les animaux de la faune ici:
}

std::list<Vec2d> Environment::getTargetsInSightForAnimal(Animal* animal)
{

    list<Vec2d> listeCiblesEnVue;

    if (!cibles_.empty()) {
        for (auto cible: cibles_) {
            if (animal->isTargetInSight(cible)) {
                listeCiblesEnVue.push_back(cible);

            }


        }
        return listeCiblesEnVue;
    }
    listeCiblesEnVue.clear();
    return listeCiblesEnVue;

}


void Environment::draw(sf::RenderTarget& targetWindow)
{
    // a ameliorer quand les animaux seront plus concret
    /*
     *

    vous remarquerez que la méthode addAnimal prend un pointeur en argument alors que addTarget n'en prend pas. Nous aurons l'occasion de questionner ce choix un peu plus tard dans le projet.
    l'inclusion de <SFML/Graphics.hpp> est nécessaire pour l'accès aux fonctionnalités de la SFML;
    des fonctions utilitaires sont fournies pour le graphisme. Pour dessiner des cercles, vous pouvez utiliser la fonction buildCircle fournie dans Utility/Utily.[hpp][cpp].
    * Un cercle, circle ainsi construit se dessine dans une sf::RenderTarget, target, comme suit: target.draw(circle). Vous pourrez donner la couleur sf::Color(255, 0, 0) (rouge) aux cibles;
    *
    *
    sf::CircleShape buildCircle(Vec2d const& position, double radius, sf::Color color)
    {
    sf::CircleShape circle(radius, 100);
    circle.setOrigin(radius, radius);
    circle.setPosition(position);
    circle.setFillColor(color);

    return circle;
    }
    */

    for (auto animal: animaux_) {
        animal->draw(targetWindow);
    }



    for (auto cible : cibles_) {
        targetWindow.draw( buildCircle( cible , 5, sf::Color(255, 0, 0)) );

    }

}


void Environment::clean()
{
    for ( auto animal: animaux_ )

    {
        delete animal;
    }
    animaux_.clear();
    cibles_.clear();

    /*
    for ( auto cible : cibles_) {
    	cibles_.pop_front();
    	}


     for (auto a : animaux_){

     delete a;
     a = nullptr;

     }
    */

}

/*
 void Environment::clean(){
	 cibles_.pop_front();
 }
 * */
/*
Vec2d Environment::ConvertToGlobalCoord( Animal* animal, Vec2d vec){
 // create a transformation matrix

      sf::Transform matTransform;

      // first, translate
      matTransform.translate(animal->getPosition());

      // then rotate
      matTransform.rotate((animal->getRotation())/DEG_TO_RAD);

      // now transform the point
      Vec2d global = matTransform.transformPoint(vec);
 return global;
}
*/

void Environment::reset()
{
    cibles_.pop_front();
}

// Laver l'environement, faut-il liberer la mémoire

// Environment( Environment const& e) = delete;

// debug-1
// /ddd
