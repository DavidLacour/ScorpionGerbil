#pragma once

#include "../Utility/Vec2d.hpp"
#include "../Obstacle/CircularCollider.hpp"
#include "../Interface/Updatable.hpp"
#include "../Interface/Drawable.hpp"
#include <utility>
#include <list>
typedef std::pair<double,double> pairdouble;
class Wave : public CircularCollider ,
    public Updatable
// public Drawable
{
public:
    virtual ~Wave () {}
    virtual void update(sf::Time dt) override ;

    /*!
    * @brief call waveUpdateClock(dt) waveUpdateRadius()  waveUpdateEnergy() waveUpdateIntensity() waveUpdateListPairAngles()
    *
    * @param time
    */


    virtual void draw(sf::RenderTarget& target) const  override;

    /*!
    * @brief create a wave
    *
    * @param Position
    * @param energy
    * @param starting radius
    * @param speed
    * @param
    * @return a wave
    */
    Wave( const Vec2d&, const double&, const double&, const double&, const double&);


    double waveGetWaveEnergy();
    double waveGetWaveIntensity();




    /*!
    * @brief is position inside one arc?
    *
    * @param position of point
    *
    * @return true or false
    */
    bool waveIsPointInside(const Vec2d&);

    /*!
    * @brief is position touching the Wave with margin?
    *
    * @param position of point
    *
    * @return true or false
    */
    bool waveIsPointTouching(const Vec2d&);
protected:

    /*!
    * @brief wave_clock_ += dt
    */
    void waveUpdateClock(sf::Time dt);

    /*!
     * @brief UpdateRadius with wave_clock_ multiply by wave_speed_ starts from wave_radius_initial_
     */
    void waveUpdateRadius() ;

    /*!
    * @brief decrease exponentialy the energy the more the raidus grow
    */
    void waveUpdateEnergy();


    /*!
    * @brief Intensity is energy divide by perimeter of the wawe
    */
    void waveUpdateIntensity();

    /*!
    * @brief Obstacle Block the Wave from growing further and split wave into arcs
    */
    void waveUpdateListPairAngles();






private:
    double wave_energy_initial_;
    double wave_radius_initial_;
    double wave_mu_;
    double wave_speed_;
    double wave_energy_current_;
    double wave_intensity_;
    sf::Time wave_clock_;
//	double wave_margin_;
    std::list<std::pair<double,double>> wave_list_pair_angles_;
};
