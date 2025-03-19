#include <list>
#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
#include "Environment.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
//#include <memory>
#include <algorithm>
//#include "OrganicEntity.hpp"
//#include "FoodGenerator.hpp"
//#include "../Animal/Animal.hpp"

void Environment::addEntity(OrganicEntity* organicEntity)
{

    if(organicEntity != NULL) {

        organic_entity_.push_back(organicEntity);
    } else {
        cout << " AAAA " << endl;
    }


}


void Environment::addGenerator(FoodGenerator* foodGenerator)
{
    if(foodGenerator != nullptr) {
        food_generator_.push_back(foodGenerator);
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


