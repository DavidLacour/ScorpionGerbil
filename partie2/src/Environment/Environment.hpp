#pragma once
#include <list>

#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
#include "../Animal/Animal.hpp"

enum class Deceleration : int {
    lente =3,
    moyenne =6,
    forte = 9,

};

class Animal; // ou include #



class Environment
{

public:
    Environment() {};
    Environment( const Environment&) = delete;
    Environment& operator=( const Environment&) = delete;
    void addAnimal( Animal*);
    void  addTarget(const Vec2d&);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow);
    void clean();
    std::list<Vec2d> getTargetsInSightForAnimal(Animal*);

    //Vec2d ConvertToGlobalCoord( Animal* animal,Vec2d);

    void reset();

    ~Environment()
    {
        clean();
    }
private:
    std::list<Animal*> animaux_;
    std::list<Vec2d> cibles_;
};





using namespace std;
