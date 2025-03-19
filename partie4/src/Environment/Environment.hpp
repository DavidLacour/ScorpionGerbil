#pragma once
#include <list>
#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
#include <memory>
#include "FoodGenerator.hpp"
//#include "OrganicEntity.hpp"
#include "../Animal/Animal.hpp"
//class Animal; // ou #include ??
//class OrganicEntity;
//class FoodGenerator;
//#include "OrganicEntity.hpp"
class Animal;
class OrganicEntity;
class WaveGerbil;
class Sensor;
//#include "../Animal/NeuronalScorpion/WaveGerbil.hpp"
#include "Wave.hpp"
#include "../Obstacle/Rock.hpp"
#include "../Obstacle/CircularCollider.hpp"
//typedef CircularCollider Obstacle;
//class Wave;

//class FoodGenerator;
//class Scorpion;
//class Food;
//class Gerbil;


class Environment
{

public:
    Environment() {};
    Environment( const Environment&) = delete;
    Environment& operator=( const Environment&) = delete;
    void addEntity(OrganicEntity*);
    void addGenerator(FoodGenerator*);
    void addWave(Wave*);
    void addRock(Rock*);
    void addObstacle(CircularCollider*);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow);
    void clean();
    std::list<OrganicEntity*> getEntitiesInSightForAnimal(Animal*)const ;
    std::list<CircularCollider*> getIsColliding(CircularCollider*);
    void morte(OrganicEntity*);
    void reset();

    double envSensorActivationIntensityCumulated(Sensor*);

    ~Environment()
    {
        clean();
    }
private:


    std::list<OrganicEntity*> organic_entity_;
    std::list<FoodGenerator*> food_generator_;
    std::list<OrganicEntity*> listTuer_;
    std::list<Wave*> env_list_waves_;
    std::list<Rock*> env_list_rocks_;
    std::list<CircularCollider*> env_list_obstacles_;
};





using namespace std;
