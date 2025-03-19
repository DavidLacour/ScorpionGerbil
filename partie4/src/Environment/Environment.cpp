#include <list>
#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
#include "Environment.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
//#include <memory>
#include <algorithm>
//#include "../Obstacle/CircularCollider.hpp"
//#include "OrganicEntity.hpp"
//#include "FoodGenerator.hpp"
//#include "../Animal/Animal.hpp"
#include "../Animal/NeuronalScorpion/Sensor.hpp"
void Environment::addEntity(OrganicEntity* organicEntity)
{

    if(organicEntity != NULL) {

        organic_entity_.push_back(organicEntity);
    }


}

void Environment::addWave(Wave* wa)
{

    if(wa!= NULL) {

        env_list_waves_.push_back(wa);
    }
}



void Environment::addGenerator(FoodGenerator* foodGenerator)
{
    if(foodGenerator != nullptr) {
        food_generator_.push_back(foodGenerator);
    }
}

void Environment::addRock(Rock* roc)
{
    if(roc != nullptr) {
        env_list_rocks_.push_back(roc);
    }
}
void Environment::addObstacle(CircularCollider* roc)
{
    if(roc != nullptr) {
        env_list_obstacles_.push_back(roc);
    }
}


void Environment::update(sf::Time dt)
{

    for( auto FG : food_generator_) {
        FG->update(dt);
    }

    for( auto& organicEntity : organic_entity_) {

        if(organicEntity != nullptr ) {
            organicEntity->update(dt);
            organicEntity->OrganicEntity::update(dt);
        }
    }

    for( auto& wav : env_list_waves_) {

        if(wav != nullptr ) {
            wav->update(dt);
        }
    }



    for (auto& OE : organic_entity_) { // utilise l'atribut list à tuer et une boucle while pour suprimer les vecteus sans faire de for auto delete puis remove pour enlever les nullptr la liste principale.
        if(OE != nullptr ) {
            if ( (OE->getAge() >= OE->getAgeLimit()) or  (OE->getEnergie() <= getAppConfig().animal_min_energy)) {
                listTuer_.push_back(OE);
                OE = nullptr;
            }
        }
    }
    while(!(listTuer_.empty())) {
        delete listTuer_.front();
        listTuer_.pop_front();
    }
    organic_entity_.erase(std::remove(organic_entity_.begin(), organic_entity_.end(), nullptr), organic_entity_.end());

    for(auto& Wav : env_list_waves_) {
        if (Wav != nullptr) {
            if (Wav->waveGetWaveIntensity() <= getAppConfig().wave_intensity_threshold)

            {
                delete Wav;
                Wav = nullptr;
            }
        }
    }

    env_list_waves_.erase(std::remove(env_list_waves_.begin(), env_list_waves_.end(), nullptr), env_list_waves_.end());
}


std::list<OrganicEntity*> Environment::getEntitiesInSightForAnimal(Animal* animal) const
{

    list<OrganicEntity*> listeEntitiesEnVue;

    if (!organic_entity_.empty()) {
        for (auto cible: organic_entity_) {
            if (animal->isTargetInSight(cible->getPosition())) {

                listeEntitiesEnVue.push_back(cible);
            }
        }
        return listeEntitiesEnVue;
    }
    listeEntitiesEnVue.clear();
    return listeEntitiesEnVue;

}



void Environment::draw(sf::RenderTarget& targetWindow)
{
    for (auto organic_entity: organic_entity_) {



        organic_entity->draw(targetWindow);
    }
    for (auto wav : env_list_waves_) {
        wav->draw(targetWindow);
    }

    for (auto roc: env_list_rocks_) {
        roc->draw(targetWindow);
    }
    for (auto roc: env_list_obstacles_) {
        roc->draw(targetWindow);
    }
}




void Environment::clean()
{
    for ( auto organicEntity: organic_entity_ ) {
        delete organicEntity;
    }
    for ( auto food_generator: food_generator_ ) {
        delete food_generator;
    }
    organic_entity_.clear();
    food_generator_.clear();
} // Laver l'environnement: suprimer ce qui est pointé et vidé les listes.

std::list<CircularCollider*> Environment::getIsColliding(CircularCollider* CC)
{
    std::list<CircularCollider*> liste;
    for (auto Ob : env_list_obstacles_) {
        if(Ob != nullptr) {
            if (Ob->isColliding(CircularCollider(CC->getPosition(),CC->getRadius()))) {
                liste.push_back(Ob);
            }
        }
    }
    return liste;
}

double  Environment::envSensorActivationIntensityCumulated(Sensor* sen)
{
    double cumulatedIntensity(0.0);
    for (auto wav : env_list_waves_) {
        if ( wav->waveIsPointTouching(sen->getPosition())) {
            cumulatedIntensity += wav->waveGetWaveIntensity() ;
        }
    }
    return cumulatedIntensity;
}



