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
    void update(sf::Time dt);
    void draw(sf::RenderTarget& targetWindow);
    void clean();
    std::list<OrganicEntity*> getEntitiesInSightForAnimal(Animal*)const ;
    //std::list<OrganicEntity> getEntitiesInSightForAnimal(Animal*)const ;
    //Vec2d ConvertToGlobalCoord( Animal* animal,Vec2d);
    void morte(OrganicEntity*);
    void reset();

    ~Environment()
    {
        clean();
    }
private:


    std::list<OrganicEntity*> organic_entity_;
    std::list<FoodGenerator*> food_generator_;
    std::list<OrganicEntity*> listTuer_;
};





using namespace std;

/*
	std::list<std::unique_ptr<OrganicEntity>> organic_entity_;
	std::list<std::unique_ptr<FoodGenerator>> food_generator_;
	*/ // unique_ptr
