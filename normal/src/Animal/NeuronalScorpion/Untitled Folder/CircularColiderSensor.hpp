/*
#pragma once
#include "../../Obstacle/CircularCollider.hpp"
class Sensor: public CircularCollider{
	public:
	Sensor(const Vec2d&,const double&);
	/*!
 * @brief create a Sensor
 *
 * @param Position
 * @param size
 *
 * @return an Sensor
 */
private:
bool sensor_etat_;
double sensor_score_;
double sensor_intensity_threshold_;
double sensor_inhibitor_;
};

/*
   "sensor" : {
	   "intensity threshold" : 0.7,
	   "inhibition" : {
	       "factor": 0.01,
	       "max"   : 1
*/
*/
