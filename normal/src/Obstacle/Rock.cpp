#include "Rock.hpp"
#include "../Random/Uniform.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
//#include "../../res/rock.png"


Rock::Rock(const Vec2d& position):
    CircularCollider(position, rockMax((uniform(double(getAppConfig().simulation_world_size/50),double(2*getAppConfig().simulation_world_size/50))),1.0)),
    rock_angle_(uniform(-PI,PI))
{}

void Rock::draw(sf::RenderTarget& target) const
{

    auto image_to_draw(buildSprite (getPosition(),
                                    getRadius()*2.1,
                                    getTexture(), rock_angle_/DEG_TO_RAD ));

    target.draw(image_to_draw );


//	target.draw(buildCircle(getPosition(), getRadius(), sf::Color(0, 175, 175)));
}



const sf::Texture& Rock::getTexture() const

{
    sf::Texture& texture = getAppTexture(getAppConfig().rock_texture);
    return texture;

};


/*
  "Rock":{
		 "texture":"Rock.png",
		}
		*
 */
double rockMax(double d1, double d2)
{
    if(d1 > d2) return d1;
    return d2;
}
