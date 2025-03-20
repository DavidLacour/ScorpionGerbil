#pragma once
#include "../Gerbil.hpp"
#include "../../Application.hpp"
class WaveGerbil : public Gerbil
{
public:
    ~WaveGerbil() {}

    /*!
    * @brief create an WaveGerbil
    *
    * @param Position

    * @return an WaveGerbil
    */
    WaveGerbil(const Vec2d&);

    /*!
    * @brief create a WaveGerbil
    *
    * @param Position
    * @param size
    * @param energie
    *
    * @return an WaveGerbil
    */
    WaveGerbil(const Vec2d&, const double& , const bool& );

    /*!
    * @brief create a WaveGerbil
    *
    * @param Position
    *
    * @return an WaveGerbil
    */
    WaveGerbil(const Vec2d&, const double& , const bool&, const sf::Time& );



    /*!
    * @brief create a WaveBaby Gerbil
    *
    * @param Position
    * @param direction mum
    * @param pointer on mum
    *
    * @return an WaveBaby Gerbil
    */
    WaveGerbil(const Vec2d& ,const Vec2d&, OrganicEntity* ) ; // BABY and MUM


    virtual void update(sf::Time ) override;

protected:
    /*!
    * @brief make a wave
    *
    * @param time
    */
    void waveGerbilWaving(sf::Time );

private:
    sf::Time wave_gerbil_frequency_;
    sf::Time wave_gerbil_clock_;


};
