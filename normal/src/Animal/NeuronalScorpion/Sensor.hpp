#pragma once
#include "../../Obstacle/CircularCollider.hpp"
#include "../../Interface/Updatable.hpp"
#include "../../Interface/Drawable.hpp"
#include "../../Environment/Wave.hpp"
class NeuronalScorpion;
class Sensor
    : public Updatable , public Drawable
{
public:
    ~Sensor() {}

    Sensor(const Vec2d&, NeuronalScorpion*, const size_t&);
    void update(sf::Time dt) override;
    /*!
    * @brief create a Sensor
    *
    * @param Position
    * @param size
    *
    * @return an Sensor
    */

    void draw(sf::RenderTarget& targetWindow) const override;
    Vec2d getPosition() const ;
    void sensorActivation();

    void sensorTemper();
    void sensorTemper(const double&);
    void sensorUpdateScore();
    void sensorInhibit();
    void sensorInhibitedByScore(const double& score);
    void sensorReset();
    double sensorGetScore();
    void sensorSetPosition(const Vec2d&);
    bool sensorGetActif();
//bool wavePointIsInsideArc(const double&,const pairdouble&);
//bool wavePointIsArc(const double&,const pairdouble&);
protected:


private:
    Vec2d sensor_position_;
    NeuronalScorpion* sensor_neuronal_scorpion_;
    size_t sensor_index_;

    bool sensor_etat_;
    double sensor_score_;

    double sensor_inhibitor_;
    double sensor_intensity_threshold_;
    // double sensor_intensity_cumulated_;
    double sensor_inhibitor_factor_;

//	std::list<Wave*> sensor_waves_felt_;
};


// double sensor_margin_;
