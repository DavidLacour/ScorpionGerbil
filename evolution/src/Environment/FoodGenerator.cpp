//#include "../Utility/Vec2d.hpp"
//#include "../Obstacle/CircularCollider.hpp"
//#include "../Utility/Vec2d.hpp"
//#include <list>
//#include  <SFML/Graphics.hpp>
//#include "../Utility/Vec2d.hpp"
//#include "../Utility/Utility.hpp"
//#include "../Utility/Constants.hpp"
//#include  "../Environment/Environment.hpp"
//#include "Animal.hpp"
//#include <cmath>
//#include "../Random/Uniform.hpp"
//#include "../Utility/Constants.hpp"

#include "../Random/Normal.hpp"
#include "../Application.hpp"
#include "Food.hpp"

void FoodGenerator::update(sf::Time dt)
{

    compteur_ += dt;
    if(compteur_ >= sf::seconds(getAppConfig().food_generator_delta) ) {

        compteur_ = sf::Time::Zero ;
        //  compteur_ = sf::seconds(0);
        getAppEnv().addEntity(new Food(Vec2d(normal( getAppConfig().simulation_world_size/2, getAppConfig().simulation_world_size/4 * getAppConfig().simulation_world_size/4)
                                             ,normal( getAppConfig().simulation_world_size/2, getAppConfig().simulation_world_size/4 * getAppConfig().simulation_world_size/4)))

                             );

    }

} // fait apparaître les fougères selon une distrubtion normal au centre (d'écart type de 1/4?)





































