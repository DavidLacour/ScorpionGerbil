#pragma once
#include "../Scorpion.hpp"
#include "Sensor.hpp"
#include <list>
#include "../../Utility/Vec2d.hpp"
#include <cmath>
#include <vector>

// Les fonctions ne respectent pas toujours l'énoncé. J'ai directement fait des soustractions et additions vectoriels plutot que d'utiliser les angles pour régler la position des angles et estimmer la position de la cible.

class NeuronalScorpion : public Scorpion
{
    enum NeuronalEtat {

        IDLE, // au repos (dans cet état il est réceptif aux ondes éventuellement émises par les gerbilles);
        WANDERING, // déambulant au hasard;
        TARGET_IN_SIGHT,  // un proie est entrée dans son champs de vision;
        MOVING, // il ne voit pas encore la proie mais l'a perçue au travers d'ondes émises (et s'oriente alors en conséquence).
    };
public:
    ~NeuronalScorpion()
    {
        for (auto sen : neuronal_scorpion_vector_sensors_) {
            delete sen;
        }
    }


    /*!
    * @brief create a NeuronalScorpion
    *
    * @param Position
    * @param energie
    *
    * @return an NeuronalScorpion
    */
    NeuronalScorpion(const Vec2d& position, const double& energie) ;
    /*!
    * @brief create a NeuronalScorpion
    *
    * @param Position
    * @param size
    * @param energie
    *
    * @return an NeuronalScorpion
    */
    NeuronalScorpion(const Vec2d&, const double&, const bool&);

    /*!
    * @brief create a NeuronalScorpion
    *
    * @param Position
    * @param size
    * @param energie
    * @param ageLimit
    *
    * @return an NeuronalScorpion
    */
    NeuronalScorpion(const Vec2d&, const double&, const bool&, const sf::Time&);


    /*!
    * @brief create a NeuronalScorpion
    *
    * @param Position
    *
    * @return an NeuronalScorpion
    */
    NeuronalScorpion(const Vec2d&);


    virtual void update(sf::Time ) override;
    void UpdateState(sf::Time dt);




    void draw(sf::RenderTarget&) const override;


    /*!
    * @brief rotate a vector
    *
    * @param vector
    * @param angle radian
    *
    * @return a rotated vector
    */
    Vec2d neuronalScorpionRotateVec2dAngle(const Vec2d& vecteur, const double& angle);

    /*!
    * @brief inhibit a chosen sensor depending of a score
    *
    * @param index of the sensor {18, 54, 90, 140, -140, -90, -54, -18}
    * @param score
    *
    */
    void neuronalScorpionInhibitSensorIndexScore(const size_t&, const double& );

    /*!
    * @brief inhibit a chosen sensor depending of a score (not tested)
    *
    * @return position of the sensor
    *
    */
    Vec2d neuronalScorpionGetPositionOfSensor(const size_t&);

    /*!
    * @brief set position of the sensors acording to the Scorpion
    *
    */
    void neuronalScorpionSetPositionOfSensors();

    /*!
    * @brief is the sensor actif?
    *
    * @return true or false
    *
    */
    bool neuronalScorpionOneSensorActif();

    /*!
    * @brief Update the sensors of the scorpion
    *
    */
    void neuronalUpdateSensors(sf::Time dt);


protected:

    /*!
    * @brief Estimate the position of a target acording to sensors
    *
    * @return estimation of the target
    *
    */
    Vec2d neuronalScorpionEstimateTarget();

    /*!
    * @brief add all the sensors to the scorpion( new sensors might have been done without pointers since we want it to exist as long as the scorpion is alive)
    *
    * @return estimation of the target
    *
    */
    void neuronalScorpionAddSensors();

    /*!
    * @brief reset the sensor (not activated, score = 0, inhibitior = 0)

    *
    */
    void neuronalScorpionSensorsReset();

    /*!
    * @brief write the current etat as a string
    *
    *@return current etat
    *
    */
    std::string stringEtat() const;
    void drawText( sf::RenderTarget&  ) const override;
private:

    std::vector<Sensor*>neuronal_scorpion_vector_sensors_;
    // Vec2d neuronal_vec2d_target_estimation_;
    sf::Time neuronal_scorpion_time_idle_;
    sf::Time neuronal_scorpion_time_moving_;

    sf::Time neuronal_scorpion_time_reception_;
    sf::Time neuronal_scorpion_clock_etat_;
    sf::Time neuronal_scorpion_clock_sensors_;
    NeuronalEtat neuronal_scorpion_neuronal_etat_; // J'aurais du masquer l'état ou aggrandir l'état dans l'animal...
    Vec2d neuronal_scorpion_target_;
};



//  {18, 54, 90, 140, -140, -90, -54, -18}

