#include "NeuronalScorpion.hpp"
#include "../../Utility/Vec2d.hpp"
#include "../../Application.hpp"
#include "../../Utility/Utility.hpp"
#include "Sensor.hpp"
#include <vector>

// WaveTest-run --cfg=appTest.json
// application-run --cfg=appTest.json

class Sensor;

NeuronalScorpion::NeuronalScorpion(const Vec2d& position, const double& energie,
                                   const bool& femelleOuPas) : Scorpion(position,energie,femelleOuPas)
    ,neuronal_scorpion_time_idle_(sf::seconds(getAppConfig().neuronalscorpion_idlemax))
    ,neuronal_scorpion_time_moving_(sf::seconds(getAppConfig().neuronalscorpion_movingmax))
    ,neuronal_scorpion_time_reception_(sf::seconds(getAppConfig().sensor_activation_duration))
    ,neuronal_scorpion_clock_etat_((sf::Time::Zero))
    ,neuronal_scorpion_clock_sensors_(sf::Time::Zero)
    ,neuronal_scorpion_neuronal_etat_(WANDERING)
    ,neuronal_scorpion_target_(1,0)
{
    neuronalScorpionAddSensors();
}

NeuronalScorpion::NeuronalScorpion(const Vec2d& position) : Scorpion(position)
    ,neuronal_scorpion_time_idle_(sf::seconds(getAppConfig().neuronalscorpion_idlemax))
    ,neuronal_scorpion_time_moving_(sf::seconds(getAppConfig().neuronalscorpion_movingmax))
    //         ,neuronal_scorpion_time_moving_(sf::seconds(50))
    ,neuronal_scorpion_time_reception_(sf::seconds(getAppConfig().sensor_activation_duration))
    ,neuronal_scorpion_clock_etat_((sf::Time::Zero))
    ,neuronal_scorpion_clock_sensors_(sf::Time::Zero)
    ,neuronal_scorpion_neuronal_etat_(WANDERING)
    ,neuronal_scorpion_target_(1,0)
{

    neuronalScorpionAddSensors();
}
NeuronalScorpion::NeuronalScorpion(const Vec2d& position, const double& energie,
                                   const bool& femelleOuPas, const sf::Time& ageLimit= sf::Time(getAppConfig().scorpion_longevity)) : Scorpion(position, energie, femelleOuPas, ageLimit)
    ,neuronal_scorpion_time_idle_(sf::seconds(getAppConfig().neuronalscorpion_idlemax))
    ,neuronal_scorpion_time_moving_(sf::seconds(getAppConfig().neuronalscorpion_movingmax))
    //     ,neuronal_scorpion_time_moving_(sf::seconds(10))
    ,neuronal_scorpion_time_reception_(sf::seconds(getAppConfig().sensor_activation_duration))
    ,neuronal_scorpion_clock_etat_((sf::Time::Zero))
    ,neuronal_scorpion_clock_sensors_(sf::Time::Zero)
    ,neuronal_scorpion_neuronal_etat_(WANDERING)
    ,neuronal_scorpion_target_(1,0)
{
    neuronalScorpionAddSensors();
}

/*!
* @brief Ici, le Scorpion est inactif (IDLE) pendant le temps nécessaire à l'activation correct des senseurs lorsqu'un senseur est activé,
* ensuite il passe en moving pendant un certain temps puis en wandering.
* L'état TARGET_IN_SIGHT prime sur le reste si une cible est en vue.
*
*  L'horloge des senseurs est gérée ici.
*/
void NeuronalScorpion::update(sf::Time dt )
{
    neuronalUpdateSensors(dt);
    analyzeEnvironment();

    /*
    organic_entity_FOODs_.clear();
    organic_entity_FOODs_ = mangeable(enVue());


    if ( !organic_entity_FOODs_.empty()) {
        neuronal_scorpion_neuronal_etat_ = TARGET_IN_SIGHT;
        neuronal_scorpion_target_ = plusProche(organic_entity_FOODs_)->getPosition();
    }
    */ //  if organic_entity_FOODs_ protected
    if ( getMangeablePlusProche() != nullptr) {
        neuronal_scorpion_neuronal_etat_ = TARGET_IN_SIGHT;
        neuronal_scorpion_target_ = getMangeablePlusProche()->getPosition();
    }

    else  {


        if (neuronal_scorpion_neuronal_etat_ != MOVING) {
            if(neuronalScorpionOneSensorActif()) {
                neuronal_scorpion_clock_sensors_ += dt;
                neuronal_scorpion_neuronal_etat_ = IDLE;
                if (neuronal_scorpion_clock_sensors_ >= neuronal_scorpion_time_reception_) {
                    neuronal_scorpion_target_ = neuronalScorpionEstimateTarget();
                    neuronal_scorpion_clock_sensors_= sf::Time::Zero;
                    neuronalScorpionSensorsReset();
                    neuronal_scorpion_neuronal_etat_ = MOVING;
                }
            }
        }
    }
    UpdateState(dt);
    switch(neuronal_scorpion_neuronal_etat_) {
    case WANDERING:
        moveToVec2dForce(dt,randomWalk());
        break;
    case IDLE:
        break;
    case MOVING:
        // moveToVec2dForce(dt,force(neuronal_scorpion_target_));
        moveToVec2dForce(dt,neuronal_scorpion_target_);
        break;
    case TARGET_IN_SIGHT:
        //	moveToVec2dForce(dt,force())
        moveToVec2dForce(dt,force(neuronal_scorpion_target_));
        //	moveToVec2dForce(dt,neuronal_scorpion_target_);

        break;

    }
    //	cout << neuronal_scorpion_target_.x << "   " << neuronal_scorpion_target_.y << endl;
    //	moveToVec2dForce(dt,force(neuronal_scorpion_target_+getPosition()));

}
/*!
* @brief L'horloge moving est géré ici. L'horloge d'activation des senseurs est gérée dans update.
* 		Les Senseurs sont déplacés et mis à jours.
*/
void NeuronalScorpion::UpdateState(sf::Time dt)
{
    switch( neuronal_scorpion_neuronal_etat_) {
    case IDLE :
        /*
        	neuronal_scorpion_clock_etat_ += dt;
            if (neuronal_scorpion_clock_etat_ >= neuronal_scorpion_time_idle_)
            {neuronal_scorpion_neuronal_etat_= WANDERING;
            neuronal_scorpion_clock_etat_ = sf::Time::Zero;}
           */
        break;
    case WANDERING:
        //  neuronal_scorpion_clock_ += dt;
        //   if (neuronal_scorpion_clock_ >= neuronal_scorpion_time_moving_) neuronal_scorpion_neuronal_etat_= IDLE;
        // neuronal_scorpion_clock_ = sf::Time::Zero;
        break;
    case MOVING :
        neuronal_scorpion_clock_etat_ += dt;
        if (neuronal_scorpion_clock_etat_ >= neuronal_scorpion_time_moving_) {
            neuronal_scorpion_neuronal_etat_= WANDERING;
            neuronal_scorpion_clock_etat_ = sf::Time::Zero;
            //    neuronalScorpionSensorsReset();
        }
        break;
    case TARGET_IN_SIGHT:
        break;
    }


}

void NeuronalScorpion::neuronalUpdateSensors(sf::Time dt)
{
    neuronalScorpionSetPositionOfSensors();
    for (auto& sen : neuronal_scorpion_vector_sensors_) {
        sen.update(dt);
    }
}



// {18, 54, 90, 140, -140, -90, -54, -18} neuronal_scorpion_list_sensors_.push_back()

Vec2d NeuronalScorpion::neuronalScorpionRotateVec2dAngle(const Vec2d& vecteur, const double& angle)
{
    return Vec2d ( cos(angle)*vecteur.x - sin(angle)*vecteur.y , sin(angle)*vecteur.x + cos(angle)*vecteur.y);


}

void NeuronalScorpion::neuronalScorpionAddSensors()
{
    std::vector<double> listeAngles{18, 54, 90, 140, -140, -90, -54, -18};
    size_t index(0);
    for (auto& angle : listeAngles) {
        neuronal_scorpion_vector_sensors_.emplace_back(
            getPosition() + getAppConfig().scorpion_sensor_radius * 
            neuronalScorpionRotateVec2dAngle(getDirection(), angle * DEG_TO_RAD),
            this, index
        );
        index += 1;
    }
}

void NeuronalScorpion::neuronalScorpionInhibitSensorIndexScore(const size_t& i, const double& score)
{
    neuronal_scorpion_vector_sensors_[i].sensorInhibitedByScore(score);
}



Vec2d NeuronalScorpion::neuronalScorpionGetPositionOfSensor(const size_t& i)
{
    return neuronal_scorpion_vector_sensors_[i].getPosition();
}


Vec2d NeuronalScorpion::neuronalScorpionEstimateTarget()
{
    Vec2d res(0.0, 0.0);
    for (auto& sen : neuronal_scorpion_vector_sensors_) {
        res += (sen.getPosition() - getPosition()) * sen.sensorGetScore();
    }
    return res;
}

void NeuronalScorpion::neuronalScorpionSetPositionOfSensors()
{
    std::vector<double> listeAngles{18, 54, 90, 140, -140, -90, -54, -18};
    for (size_t i(0); i < listeAngles.size(); ++i) {
        neuronal_scorpion_vector_sensors_[i].sensorSetPosition(
            getPosition() + getAppConfig().scorpion_sensor_radius * 
            neuronalScorpionRotateVec2dAngle(getDirection(), listeAngles[i] * DEG_TO_RAD)
        );
    }
}


bool NeuronalScorpion::neuronalScorpionOneSensorActif()
{
    for (auto& sen : neuronal_scorpion_vector_sensors_) {
        if (sen.sensorGetActif()) return true;
    }
    return false;
}

void NeuronalScorpion::draw(sf::RenderTarget& target) const
{
    Animal::draw(target);
    if (isDebugOn()) {
        for (const auto& sen : neuronal_scorpion_vector_sensors_) {
            sen.draw(target);
        }
    }
}

std::string NeuronalScorpion::stringEtat() const
{
    std::string humeurString;
    switch ( neuronal_scorpion_neuronal_etat_)

    {

    case   WANDERING :
        humeurString = " WANDERING";
        break;
    case IDLE :
        humeurString = "IDLE" ;
        break;
    case TARGET_IN_SIGHT:
        humeurString = "TARGET_IN_SIGHT";
        break;
    case MOVING:
        humeurString = "MOVING";
        break ;
    }
    return humeurString;
}


void NeuronalScorpion::neuronalScorpionSensorsReset()
{
    for (auto& sen : neuronal_scorpion_vector_sensors_) {
        sen.sensorReset();
    }
}
void NeuronalScorpion::drawText( sf::RenderTarget& target  ) const
{
    auto text1 = buildText( NeuronalScorpion::stringEtat(),
                            getPosition()+getDirection()*80 ,
                            getAppFont(),
                            getAppConfig().default_debug_text_size,
                            sf::Color::Red,
                            (getRotation()/DEG_TO_RAD+90)
                          );
    target.draw(text1);

}
