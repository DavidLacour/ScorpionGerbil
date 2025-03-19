#include "WaveGerbil.hpp"

// WaveTest-run --cfg=appTest.json
// application-run --cfg=appTest.json
WaveGerbil::WaveGerbil(const Vec2d& position):
    Gerbil(position),wave_gerbil_frequency_(sf::seconds(1.0/getAppConfig().wave_gerbil_frequency)),wave_gerbil_clock_(sf::Time::Zero)

{
}

WaveGerbil::WaveGerbil(const Vec2d& position, const double& energie,
                       const bool& femelleOuPas) : Gerbil(position,energie,femelleOuPas),wave_gerbil_frequency_(sf::seconds(1.0/getAppConfig().wave_gerbil_frequency)),wave_gerbil_clock_(sf::Time::Zero) {}

// WaveGerbil::WaveGerbil(const Vec2d& position,const Vec2d& direction) : Gerbil(position,direction), wave_gerbil_frequency_(sf::seconds(1.0/getAppConfig().wave_gerbil_frequency)),wave_gerbil_clock_(sf:Time:Zero){}

WaveGerbil::WaveGerbil(const Vec2d& position,const Vec2d& direction, OrganicEntity* mum) : Gerbil(position,direction,mum),
    wave_gerbil_frequency_(sf::seconds(1.0/getAppConfig().wave_gerbil_frequency)),wave_gerbil_clock_(sf::Time::Zero) {}
/*
WaveGerbil::WaveGerbil(const Vec2d& position, const double& energie,
               const bool& femelleOuPas, const sf::Time& ageLimit =(sf::Time(getAppConfig().gerbil_longevity)):
               Gerbil(postion,energie, femelleOuPas, ageLimit)
               ,wave_gerbil_frequency_(sf::seconds(1.0/getAppConfig().wave_gerbil_frequency)),wave_gerbil_clock_(sf::Time::Zero){}
*/
void WaveGerbil::update(sf::Time dt)
{
    Animal::update(dt);
    waveGerbilWaving(dt);
}



void WaveGerbil::waveGerbilWaving(sf::Time dt)
{
    if ( getEtat() != 7) {
        wave_gerbil_clock_ += dt;
        if (wave_gerbil_clock_ >= wave_gerbil_frequency_) {
            wave_gerbil_clock_= sf::Time::Zero;
            getAppEnv().addWave(new Wave(this->getPosition(), getAppConfig().wave_default_energy, getAppConfig().wave_default_radius, getAppConfig().wave_default_mu, getAppConfig().wave_default_speed));
        }
    }
}

