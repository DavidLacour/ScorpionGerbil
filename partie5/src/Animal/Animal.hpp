#pragma once
//#include "../Obstacle/CircularCollider.hpp"
#include "../Environment/OrganicEntity.hpp"
#include "../Utility/Vec2d.hpp"
#include  <SFML/Graphics.hpp>
//#include  "../Environment/Environment.hpp"
//#include "../Random/Uniform.hpp"
//#include <list>
#include <iostream>
class Environment;

enum Etat {
    FOOD_IN_SIGHT, // nourriture en vue
    FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
    RUNNING_AWAY,  // en fuite
    MATE_IN_SIGHT, // partenaire en vue
    MATING,        // vie privée (rencontre avec un partenaire!)
    GIVING_BIRTH,  // donne naissance
    WANDERING,     // déambule
    BABY,
};

class Animal : public OrganicEntity
{


public:
    // constructeur:
    Animal(const Vec2d& ,const double& , const double& , const bool& );

    /*!
     * @brief create an animal
     *
     * @param Position
     * @param size
     * @param energie
     * @param femelle ou pas
     *
     * @return an animal
     */

    Animal(const Vec2d& ,const double& , const double& , const bool&, const sf::Time& );


    /*!
    * @brief create an animal
    *
    * @param Position
    * @param size
    * @param energie
    * @param femelle ou pas
    * @param age limit
    *
    * @return an animal
    */
//	Animal(const Vec2d& ,const double& , const double& , const bool&, const sf::Time&, const double& );

    Animal(const Vec2d&,const double&, const double& , const bool& , const sf::Time&, const double& , const double& );
    /*!
    * @brief create an animal
    *
    * @param Position
    * @param size
    * @param energie
    * @param femelle ou pas
    * @param age limit
    * @param facteur perte énergie
    * @param temps de gestation
    *
    * @return an animal
    */
    Animal(const Vec2d&,const double&, const double& , const bool& , const sf::Time&, const double& , const double&, const Vec2d& );
    // à utiliser plus tard pour créer des bébés sans maman ne fonctionne pas
    /*!
    * @brief create a Baby animal
    *
    * @param Position
    * @param size
    * @param energie
    * @param femelle ou pas
    * @param age limit
    * @param facteur perte énergie
    * @param temps de gestation
    * @param direction du bébé à la naissance
    *
    * @return an animal
    */


    Animal(const Vec2d&,const double&, const double& , const bool& , const sf::Time&, const double& , const double&, const Vec2d&,  OrganicEntity* );
// Fait un bébé qui suit la maman
    /*!
    * @brief create a Baby animal
    *
    * @param Position
    * @param size
    * @param energie
    * @param femelle ou pas
    * @param age limit
    * @param facteur perte énergie
    * @param temps de gestation
    * @param direction du bébé à la naissance
    * @param vecteur qui pointe sur la maman
    *
    * @return an animal
    */


// Destructeur et mémoire:

//Animal&(const Animal&) = delete;
// Animal& operator=(Animal) = delete;

    void oublierMum() override;
    /*!
    * @brief pointeur organity_entity_mum_ becomes nullptr
    */

    void oublierBaby(OrganicEntity*) override;
    /*!
    * @brief baby in organity_entity_kids_ becomes nullptr
    *
    * @param pointer on Organic entity to find the right baby to forget
    *
    */


    /*!
    * @brief destructor and memory gestion
    *
    */
    virtual  ~Animal()
    {
        if(!organic_entity_kids_.empty()) {
            for (auto& oe: organic_entity_kids_) {
                if(oe != nullptr ) oe->oublierMum();

            }
        }

        if( organic_entity_mum_!= nullptr) {
            organic_entity_mum_->oublierBaby(this);

        }

    }


    /*!
    * @brief memory managing
    * loop on kids to make them forget their mum
    * and on the mum to make her forget her kid
    *
    */
    void oublier();



    Vec2d getSpeedVector() const ; // retourne direction * vitesse
    double getMaxSpeed() const;
    const bool& getFemelleOuPas() const ;
    double getRotation() const  ;
    const int& getBabies() const ; // retourne le nombre de bébé dans le ventre
    Vec2d getDirection() const;
    const bool& getEnceinte() const;

    virtual const double& getViewRange()const = 0;
    virtual const double& getViewDistance()const = 0;
    virtual const double& getRandomWalkRadius() const  = 0;
    virtual const  double& getRandomWalkDistance() const = 0;
    virtual const double& getStandardMaxSpeed() const = 0;
    virtual const double& getMass() const = 0;
    virtual const double& getRandomWalkJitter() const = 0;
    virtual const sf::Texture& getTexture() const = 0;



    bool isTargetInSight(const Vec2d&) const ;

    Vec2d randomWalk();
    Vec2d ConvertToGlobalCoord( Vec2d vec);


    std::string stringEtat() const; // utile pour afficher l'etat

    bool collisionCible();


    std::list<OrganicEntity*> mangeable(std::list <OrganicEntity*> ); // prend un liste OE et retourne ceux qui sont mangeable
    std::list<OrganicEntity*> mates(std::list <OrganicEntity*> ); // prend une liste OE et retourne ceux avec qui ont peut faire des enfants
    OrganicEntity* plusProche(std::list<OrganicEntity*> );   // prend une liste OE et retourne la plus proche


protected:
    Vec2d force( const Vec2d&) const; // retrourne une force à partir d'un Vec2d position
    Vec2d force(  OrganicEntity* cible ) const; // retrourne une force à partir d'un Vec2d organic_enity  et get_position
    //Vec2d force( const OrganicEntity& cible ) const;




//	void moveToTarget(const double&);
    void moveToVec2dForce(const double& ,const Vec2d& ); // déplace avec un temps et une force
    void moveToVec2dForce(const sf::Time& ,const Vec2d& ); // déplace avec un temps et une force


    // dessins:
    virtual void draw(sf::RenderTarget&) const ;
    void drawCercleBleu(sf::RenderTarget& targetWindow) const ; // dessin rdm walk
    void drawVision(sf::RenderTarget& targetWindow) const;
    virtual void drawText( sf::RenderTarget&  ) const;





//	Vec2d ConvertToAnimalCoord( Vec2d vec);
    // void updateState(sf::Time dt);


    virtual void update(sf::Time ) override;
    void UpdateState(sf::Time dt); // lance Analyze environment, change l'etat en fonction du champs de vision et temps écoulé
    // updateSate lance giveBirth et manger () on pourrait faire une fonction meetAll qui gère toute les rencontres et la metre dans update().
    void updateEnergie( sf::Time dt);

    void manger();		// manger la cible, gagner 70% de son énergie et mettre son énergie à 0

    void meetThis(Animal*); 		// 	doubleDispatch reproduction
    void meet(OrganicEntity*);		// 	doubleDispatch reproduction
    void giveBirth() override ;

    int getEtat();


    //void setEtat(Etat); // fonction à faire et à utiliser
    // Etat getEtat();



    //std::list<OrganicEntity*> listeOrganicEntityEnVue();
    //std::list<OrganicEntity*> ANlisteCiblesMangeables();
    void analyzeEnvironment();


    Vec2d forceFuite( std::list<OrganicEntity*> listeOE );
    std::list<OrganicEntity*> preydateur(std::list <OrganicEntity*> );



    std::list<OrganicEntity*> enVue();


    void setEtat(const int&);
    void setEtat(const std::string&);

    // setterReproduction:
    void setEnceinte(const bool&);
    void setBabies(const int&);




    std::list <OrganicEntity*> organic_entity_kids_;

    OrganicEntity* getMangeablePlusProche(); // juste pour ne pas avoir std::list<OrganicEntity*> organic_entity_FOODs_; en protected.

private:
    void setRotation(const double& );
    Vec2d direction_;
    double vitesse_;
    Vec2d current_target_;
    bool femelle_ou_pas_;
    double energie_depense_facteur_;

    Vec2d target_Cercle_Bleu_;
    double viewRange_;

    double viewDistance_;

    sf::Time time_pause_feeding_;
    Etat etat_;
    OrganicEntity* organic_entity_cible_;
    bool enceinte_;
    int babies_;
    sf::Time time_pause_mise_en_bas_;
    sf::Time time_pause_mating_;
    sf::Time time_gestation_limit_; ; // durée maximal de gestation (9 mois pour les humains par exemple)
    sf::Time time_gestation_;	// temps écoulé depuis la fécondation
    sf::Time time_running_away_;
    std::list<OrganicEntity*> organic_entity_ItsaMatchs_;
    std::list<OrganicEntity*> organic_entity_Preydators_;
    std::list<OrganicEntity*> organic_entity_FOODs_;
    std::list<OrganicEntity*> organic_entity_Preydators_memory_;
    Vec2d force_fuite_memory_;
    Vec2d organic_entity_cible_memory_;

    OrganicEntity* organic_entity_mum_;
};
