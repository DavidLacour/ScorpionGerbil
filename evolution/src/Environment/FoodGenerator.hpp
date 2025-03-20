#pragma once

class FoodGenerator
{
public:
    FoodGenerator() {}
    void update(sf::Time dt); // faire apparaître la salade
    ~FoodGenerator() {}
private:
    sf::Time compteur_; // compteur remis à zéro chaque fois qu'on fait apparaitre une fougère.
};
