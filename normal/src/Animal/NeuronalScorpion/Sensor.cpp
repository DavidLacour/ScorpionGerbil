

#include "Sensor.hpp"
#include "../../Application.hpp"
#include "NeuronalScorpion.hpp"
#include "../../Utility/Utility.hpp"








class NeuronalScorpion;
Sensor::Sensor(const Vec2d& position, NeuronalScorpion* neuronalScorpion, const size_t& index) :
    sensor_position_(position)
    ,sensor_neuronal_scorpion_(neuronalScorpion)
    ,sensor_index_(index)
    ,sensor_etat_(false)
    ,sensor_score_(0.0)
    ,sensor_inhibitor_(0.0)
    ,sensor_intensity_threshold_(getAppConfig().sensor_intensity_threshold)

    ,sensor_inhibitor_factor_(getAppConfig().sensor_inhibition_factor)
{}


void Sensor::update(sf::Time dt)
{
    sensorActivation();
    sensorUpdateScore();
    sensorInhibit();
}


Vec2d Sensor::getPosition() const
{
    return sensor_position_;
}

void Sensor::sensorTemper()
{
    sensor_score_ += (2.0*(1- sensor_inhibitor_));

}

void Sensor::sensorActivation()
{
    // if (wav->waveIsPointTouching(getPositionOfSensor())){
    if (sensor_etat_==false) {
        if 	( getAppEnv().envSensorActivationIntensityCumulated(this) >= sensor_intensity_threshold_) {
            sensor_etat_ = true;


        }


    }

}

void Sensor::sensorUpdateScore()
{
    if (sensor_etat_==true) {
        sensor_score_ += 2.0 * (1.0 - sensor_inhibitor_) ;
    }
}


void Sensor::sensorInhibit()
{
    if (sensor_etat_==true) {
        for (size_t i(3); i<6; ++i) {
            sensor_neuronal_scorpion_->neuronalScorpionInhibitSensorIndexScore((sensor_index_ + i) % 8, sensor_score_);
        }
    }
    /* Supposons que les senseurs soient numérotés de 0 à 7, chaque senseur i va inhiber les 3 senseurs (index + i) % 8 où index varie dans l'ensemble {3,4,5}
    */


}
void Sensor::sensorInhibitedByScore(const double& score)
{
    sensor_inhibitor_ += score*sensor_inhibitor_factor_;
}

void Sensor::sensorReset()
{
    sensor_etat_ = false;
    sensor_score_=0;
    sensor_inhibitor_=0;

}

double Sensor::sensorGetScore()
{

    return sensor_score_;
}

void Sensor::sensorSetPosition(const Vec2d& position)
{
    sensor_position_= position;
}

bool Sensor::sensorGetActif()
{
    return sensor_etat_;

}

void Sensor::draw(sf::RenderTarget& target) const
{
    sf::Color color;
    if (sensor_etat_ == true and sensor_inhibitor_ > 0.2) {
        color =  sf::Color::Magenta;
    } else if (sensor_etat_ == false and sensor_inhibitor_ > 0.2) {
        color =  sf::Color::Blue;
    } else if (sensor_etat_ == true and sensor_inhibitor_ < 0.2) {
        color =  sf::Color::Red;
    } else {
        color = sf::Color::Green;
    }
    target.draw(buildCircle(getPosition(), sensor_neuronal_scorpion_->getRadius()/4, color));
}
/*
    en magenta si le senseur est actif et a un degré d'inhibition supérieur à 0.2;
    en bleu s'il est inactif et a un degré d'inhibition supérieur à 0.2;
    en rouge s'il a un degré d'inhibition inférieur à 0.2 et est actif
    en vert autrement
*/


/*
 * Indication : location appartient à un arc donné, si l'angle (location - origin).angle(), où origin est l'origine de l'onde,
 * est contenu dans l'arc (supérieur ou égal au début de l'arc et inférieur ou égal à sa fin).
 *  Pensez à modulariser vos traitements compte tenu de ce que vous avez déjà eu à coder précédemment.
 *
 *
 * /
*/
/*
bool Animal::isTargetInSight(const Vec2d& cible) const
{


    if(isEqual(distanceTo(cible),0 )) return false; // should not target himself
    if ( (cible-getPosition()).lengthSquared() <= (getViewDistance()*getViewDistance())) {
        if(direction_.dot((cible-getPosition()).normalised()) >= cos((getViewRange()+0.001)/2)) {
            return true;
        }

    }
    */
