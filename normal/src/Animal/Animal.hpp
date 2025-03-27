#pragma once
#include "../Environment/OrganicEntity.hpp"
#include "../Utility/Vec2d.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
class Environment;

enum Etat {
    FOOD_IN_SIGHT, // food in sight
    FEEDING,       // eating (at this point it stops moving)
    RUNNING_AWAY,  // fleeing
    MATE_IN_SIGHT, // partner in sight
    MATING,        // private life (meeting with a partner!)
    GIVING_BIRTH,  // giving birth
    WANDERING,     // wandering
    BABY,          // baby state
 };

class Animal : public OrganicEntity
{

public:
    /**
     * @brief Constructor for the Animal class
     * 
     * Initializes an Animal object with the specified position, size, energy, and gender.
     * Sets default values for direction, target, state, and other animal-specific attributes.
     * 
     * @param position The initial 2D position of the animal in the environment
     * @param taille The size of the animal (affects collision detection and possibly other mechanics)
     * @param energie The initial energy level of the animal
     * @param femelleOuPas Boolean indicating the gender of the animal (true = female, false = male)
     *
     * @note The animal is initialized in WANDERING state with default timers for feeding,
     *       mating, gestation, and other activities based on application configuration.
     *       New animals start with no target, are not pregnant, have no babies,
     *       and have no parent reference.
     */
    Animal(const Vec2d& position, const double& taille, const double& energie, const bool& femelleOuPas);

    /**
     * @brief Constructor for Animal with age limit
     * 
     * @param position Initial position vector
     * @param taille Size of the animal
     * @param energie Initial energy level
     * @param femelleOuPas Gender (true = female, false = male)
     * @param ageLimit Maximum lifespan
     * 
     * @return An animal instance
     */
    Animal(const Vec2d& position, const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit);

    /**
     * @brief Constructor for Animal with extended parameters
     * 
     * @param position Initial position vector
     * @param taille Size of the animal
     * @param energie Initial energy level
     * @param femelleOuPas Gender (true = female, false = male)
     * @param ageLimit Maximum lifespan
     * @param energie_depense_facteur Energy consumption rate multiplier
     * @param gestationLimit Duration of pregnancy period
     * 
     * @return An animal instance
     * 
     * Initializes an animal with specified attributes and default movement/state parameters.
     */
    Animal(const Vec2d& position, const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit, const double& energie_depense_facteur, const double& gestationLimit);

    /**
     * @brief Constructor for baby Animal with initial direction
     * 
     * @param position Initial position vector
     * @param taille Size (reduced to 1/3 for baby)
     * @param energie Initial energy level
     * @param femelleOuPas Gender flag
     * @param ageLimit Maximum lifespan
     * @param energie_depense_facteur Energy consumption rate
     * @param gestationLimit Gestation period duration
     * @param direction Initial movement direction
     * 
     * @return An animal instance
     * 
     * Creates a baby animal in BABY state with specified parameters.
     */
    Animal(const Vec2d& position, const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit, const double& energie_depense_facteur, const double& gestationLimit, const Vec2d& direction);

    /**
     * @brief Constructor for baby Animal with parent reference
     * 
     * @param position Initial position
     * @param taille Size (reduced to 1/3 for baby)
     * @param energie Initial energy level
     * @param femelleOuPas Gender (true = female)
     * @param ageLimit Maximum lifespan
     * @param energie_depense_facteur Energy consumption rate
     * @param gestationLimit Gestation duration
     * @param direction Initial movement direction
     * @param mum Pointer to parent entity
     * 
     * @return An animal instance
     * 
     * Creates a baby animal with BABY state and inherited parameters.
     */
    Animal(const Vec2d& position, const double& taille, const double& energie, const bool& femelleOuPas, const sf::Time& ageLimit, const double& energie_depense_facteur, const double& gestationLimit, const Vec2d& direction, OrganicEntity* mum);

    // Destructeur et mémoire:

    // Animal&(const Animal&) = delete;
    //  Animal& operator=(Animal) = delete;

    /**
     * @brief Removes the reference to parent
     * 
     * Sets the organic_entity_mum_ pointer to nullptr
     */
    void oublierMum() override;

    /**
     * @brief Removes the reference to a specific baby
     *
     * @param baby Pointer to organic entity to be forgotten
     * 
     * Sets the corresponding entry in organic_entity_kids_ to nullptr
     */
    void oublierBaby(OrganicEntity* baby) override;

    /**
     * @brief Destructor with memory management
     *
     * Makes babies forget their mother and makes mother forget this baby
     */
    virtual ~Animal()
    {
        if (!organic_entity_kids_.empty())
        {
            for (auto &oe : organic_entity_kids_)
            {
                if (oe != nullptr)
                    oe->oublierMum();
            }
        }

        if (organic_entity_mum_ != nullptr)
        {
            organic_entity_mum_->oublierBaby(this);
        }
    }

    /**
     * @brief Memory management function
     * 
     * Makes babies forget their mother and makes mother forget this animal
     */
    void oublier();

    Vec2d getSpeedVector() const; // returns direction * speed
    
    /**
     * @brief Gets the maximum speed based on current state
     * 
     * Speed is adjusted based on animal state (higher when chasing food or fleeing)
     * and reduced when energy is low
     * 
     * @return Maximum speed value
     */
    double getMaxSpeed() const;
    
    const bool& getFemelleOuPas() const;
    double getRotation() const;
    const int& getBabies() const; // returns number of babies in the womb
    Vec2d getDirection() const;
    const bool& getEnceinte() const;

    virtual const double& getViewRange() const = 0;
    virtual const double& getViewDistance() const = 0;
    virtual const double& getRandomWalkRadius() const = 0;
    virtual const double& getRandomWalkDistance() const = 0;
    virtual const double& getStandardMaxSpeed() const = 0;
    virtual const double& getMass() const = 0;
    virtual const double& getRandomWalkJitter() const = 0;
    virtual const sf::Texture& getTexture() const = 0;

    /**
     * @brief Checks if a target is within the animal's field of view
     * 
     * @param cible Target position to check
     * @return True if target is visible, false otherwise
     */
    bool isTargetInSight(const Vec2d& cible) const;

    /**
     * @brief Generates random movement vector
     * 
     * Implements random walk algorithm for wandering behavior
     * 
     * @return Force vector for movement
     */
    Vec2d randomWalk();
    
    Vec2d ConvertToGlobalCoord(Vec2d vec);

    std::string stringEtat() const; // useful for displaying the state

    bool collisionCible();

    std::list<OrganicEntity*> mangeable(std::list<OrganicEntity*>); // takes a list of OE and returns those that are edible
    std::list<OrganicEntity*> mates(std::list<OrganicEntity*>);     // takes a list of OE and returns those with which to reproduce
    OrganicEntity* plusProche(std::list<OrganicEntity*>);           // takes a list of OE and returns the closest one

protected:
    Vec2d force(const Vec2d&) const;        // returns a force from a Vec2d position
    Vec2d force(OrganicEntity* cible) const; // returns a force from an organic_entity's position
   
    /**
     * @brief Moves the animal according to a force
     * 
     * Updates position, speed and orientation based on applied force
     * 
     * @param deltaT Time elapsed in seconds
     * @param force Force vector to apply
     */
    void moveToVec2dForce(const double& deltaT, const Vec2d& force);
    void moveToVec2dForce(const sf::Time& dt, const Vec2d& force);

    // drawings:
    virtual void draw(sf::RenderTarget&) const;
    void drawCercleBleu(sf::RenderTarget& targetWindow) const; // draw random walk circle
    void drawVision(sf::RenderTarget& targetWindow) const;
    virtual void drawText(sf::RenderTarget&) const;


    /**
     * @brief Updates animal's position and state
     * 
     * Controls animal movement based on current behavior mode:
     * - FOOD_IN_SIGHT: Moves toward food target
     * - WANDERING: Uses random walk algorithm
     * - MATE_IN_SIGHT: Moves toward potential mate
     * - RUNNING_AWAY: Flees from predators
     * - FEEDING: Slows down movement and stays near food
     * - BABY: Follows mother or moves toward nearest non-threatening entity
     * 
     * @param dt Time elapsed since last update
     */
    virtual void update(sf::Time dt) override;
    
    /**
     * @brief Manages the animal's state transitions
     * 
     * Handles the complex state machine governing animal behavior by:
     * - Analyzing the environment to detect food, mates, and predators
     * - Managing pregnancy progression and birth
     * - Prioritizing state transitions based on survival needs
     * - Processing time-dependent state durations
     * 
     * @param dt Time elapsed since the last update
     */
    void UpdateState(sf::Time dt);
    
    /**
     * @brief Updates animal's energy level
     * 
     * Reduces energy based on time elapsed and movement speed
     * 
     * @param dt Time elapsed since last update
     */
    void updateEnergie(sf::Time dt);

    /**
     * @brief Consumes target entity
     * 
     * Animal gains 70% of target's energy and sets target's energy to 0
     */
    void manger();

    /**
     * @brief Handles mating between animals
     * 
     * @param A Pointer to another animal for mating
     * 
     * Manages reproduction between two animals. Changes state to MATING,
     * randomly determines number of babies, updates pregnancy status and
     * adjusts energy levels for both animals based on gender and configuration.
     */
    void meetThis(Animal* A);
    void meet(OrganicEntity*);
    void giveBirth() override;

    int getEtat();
    
    /**
     * @brief Analyzes surrounding environment
     * 
     * Identifies food, mates, and predators in the animal's field of view
     */
    void analyzeEnvironment();

    Vec2d forceFuite(std::list<OrganicEntity*> listeOE);
    std::list<OrganicEntity*> preydateur(std::list<OrganicEntity*>);

    std::list<OrganicEntity*> enVue();

    void setEtat(const int&);
    void setEtat(const std::string&);

    // setterReproduction:
    
    /**
     * @brief Sets pregnancy status
     * 
     * @param b New pregnancy status
     */
    void setEnceinte(const bool& b);
    
    /**
     * @brief Sets number of babies to be born
     * 
     * @param n Number of babies
     */
    void setBabies(const int& n);

    std::list<OrganicEntity*> organic_entity_kids_;

    OrganicEntity* getMangeablePlusProche(); 

private:
    void setRotation(const double&);
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
    sf::Time time_gestation_limit_; // maximum duration of gestation (9 months for humans for example)
    sf::Time time_gestation_; // time elapsed since fertilization
    sf::Time time_running_away_;
    std::list<OrganicEntity*> organic_entity_ItsaMatchs_;
    std::list<OrganicEntity*> organic_entity_Preydators_;
    std::list<OrganicEntity*> organic_entity_FOODs_;
    std::list<OrganicEntity*> organic_entity_Preydators_memory_;
    Vec2d force_fuite_memory_;
    Vec2d organic_entity_cible_memory_;
    OrganicEntity* organic_entity_mum_;
};