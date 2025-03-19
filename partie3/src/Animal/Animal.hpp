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


class Animal : public OrganicEntity
{
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
    * @brief destructor and memory gestion
    *
    */

    void oublier();
    /*!
    * @brief memory managing
    * loop on kids to make them forget their mum
    * and on the mum to make her forget her kid
    *
    */

    // Autres fonction;

    Vec2d force( const Vec2d&) const; // retrourne vec2d une force à partir d'un Vec2d position
    Vec2d force(  OrganicEntity* cible ) const; //  // retrourne vec2d une force à partir d'un Vec2d organic_enity get_position
    //Vec2d force( const OrganicEntity& cible ) const;
    Vec2d getSpeedVector() const ; // retourne direction * vitesse



    void moveToTarget(const double&);
    void moveToVec2dForce(const double& ,const Vec2d& ); // déplace avec un temps et une force
    void moveToVec2dForce(const sf::Time& ,const Vec2d& );


    // dessins:
    virtual void draw(sf::RenderTarget&) const ;  // ATTENTION  radius * 2 ici
    void drawCercleBleu(sf::RenderTarget& targetWindow) const ; // dessin rdm walk
    void drawVision(sf::RenderTarget& targetWindow) const;
    void drawText( sf::RenderTarget&  ) const;

    // getter:
    double getMaxSpeed() const;
    const bool& getFemelleOuPas() const ; // getter sexe
    double getRotation() const  ;
    const int& getBabies() const ; // retourne le nombre de bébé dans le ventre

    Vec2d getDirection() const;
    // getter virtuels:
    virtual const double& getViewRange()const = 0;
    virtual const double& getViewDistance()const = 0;
    virtual const double& getRandomWalkRadius() const  = 0;
    virtual const  double& getRandomWalkDistance() const = 0;
    virtual const double& getStandardMaxSpeed() const = 0;
    virtual const double& getMass() const = 0;
    virtual const double& getRandomWalkJitter() const = 0;
    const bool& getEnceinte() const;

    virtual const sf::Texture& getTexture() const = 0;



    bool isTargetInSight(const Vec2d&) const ;

    Vec2d randomWalk();

    Vec2d ConvertToGlobalCoord( Vec2d vec);
//	Vec2d ConvertToAnimalCoord( Vec2d vec);
    // void updateState(sf::Time dt);


    virtual void update(sf::Time ) ;
    void UpdateState(sf::Time dt); // lance Analyze environment, check le temps de temps de Gestation et autres temps d'etats (pause_feeding), change l'etat en fonction du champs de vision
    // A Changer plus tard updateSate lance giveBirth et manger () on peut faire une fonction meetAll et la metre dans update().
    void updateEnergie( sf::Time dt); // descend l'énergie selon dt
    void manger();		// manger la cible, gagner 70% de son énergie et mettre son énergie à 0
    void meetThis(Animal*); 		// appelle meetThis pour la reproction
    void meet(OrganicEntity*);		// reproduction selon la race
    void giveBirth() override ;




    std::string stringEtat() const; // utile pour afficher l'etat


    //void setEtat(Etat); // fonction à faire et à utiliser
    // Etat getEtat();

    bool collisionCible(); // true si la cible est en collision avec organic_entity_cible


    //std::list<OrganicEntity*> listeOrganicEntityEnVue();
    //std::list<OrganicEntity*> ANlisteCiblesMangeables();
    void analyzeEnvironment();

    std::list<OrganicEntity*> mangeable(std::list <OrganicEntity*> ); // prend un liste OE et retourne ceux qui sont mangeable
    std::list<OrganicEntity*> mates(std::list <OrganicEntity*> ); // prend une liste OE et retourne ceux avec qui ont peut faire des enfants
    OrganicEntity* plusProche(std::list<OrganicEntity*> );   // prend une liste OE et retourne la plus proche

    Vec2d forceFuite( std::list<OrganicEntity*> listeOE );
    std::list<OrganicEntity*> preydateur(std::list <OrganicEntity*> );
protected:


    std::list<OrganicEntity*> enVue();

protected:

    // setterReproduction:
    void setEnceinte(const bool&);
    void setBabies(const int&);

    std::list <OrganicEntity*> organic_entity_kids_;
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
