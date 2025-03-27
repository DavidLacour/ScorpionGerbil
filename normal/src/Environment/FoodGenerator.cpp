#include "../Random/Normal.hpp"
#include "../Application.hpp"
#include "Food.hpp"

void FoodGenerator::update(sf::Time dt)
{

    compteur_ += dt;
    if(compteur_ >= sf::seconds(getAppConfig().food_generator_delta) ) {

        compteur_ = sf::Time::Zero ;
        getAppEnv().addEntity(new Food(Vec2d(normal( getAppConfig().simulation_world_size/2, getAppConfig().simulation_world_size/4 * getAppConfig().simulation_world_size/4)
                                             ,normal( getAppConfig().simulation_world_size/2, getAppConfig().simulation_world_size/4 * getAppConfig().simulation_world_size/4)))
                             );

    }
}





































