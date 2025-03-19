#pragma once

#include "../Interface/Updatable.hpp"
#include "../Obstacle/CircularCollider.hpp"
//#include  <SFML/Graphics.hpp>

#include <list>
class Animal;
class Scorpion;
class Food;
class Gerbil;
class OrganicEntity : public CircularCollider ,public Updatable
{

    // Dotez la classe OrganicEntity d'un constructeur prenant en paramètre une position, une taille et un niveau d'énergie (dans cet ordre).
    // Le paramètre relatif à la taille servira à initialiser le rayon de l'entité en tant que CircularCollider (la taille fournie en paramètre sera considérée comme étant le double du rayon).
public:
    virtual void  oublierMum() {}
    virtual void oublierBaby(OrganicEntity*) {}
    virtual void oublier() {}
    virtual ~OrganicEntity() { }
    OrganicEntity( const Vec2d& , const double& , const double& );
    OrganicEntity( const Vec2d& , const double& , const double&, const sf::Time& );
    const double& getEnergie() const ;

    OrganicEntity( const OrganicEntity& );
    const sf::Time& getAge() const;
    const sf::Time& getAgeLimit() const;


    virtual bool matable(OrganicEntity const* other) const = 0;
    virtual bool canMate(Scorpion const* scorpion) const = 0;
    virtual bool canMate(Gerbil const* gerbil) const = 0;
    virtual bool canMate(Food const* food) const = 0;
    virtual void meet(OrganicEntity*) {}
    virtual void meetThis(Animal*) {}

    virtual  void giveBirth() {}
    virtual  void giveBirthThis() {}
    void updateEnergie( sf::Time dt);
    /*
    virtual const bool& getFemelleOuPas() ;
    virtual const int& getBabies() const ;
    virtual void setBabies(const int&);
    virtual void setEnceinte(const int&);
    * */
    /*
    Vec2d OEdirectionTo(const OrganicEntity&) const;
     Vec2d OEdirectionTo( OrganicEntity*)const;
    double OEdistanceTo(const OrganicEntity&) const;
    double OEdistanceTo( OrganicEntity*)const;

    */
    /*
    	std::list<OrganicEntity> listeCiblesMangeables(std::list<OrganicEntity> );
    	OrganicEntity OrganicEntityLaPlusProche(std::list<OrganicEntity> ) ;
     std::list<OrganicEntity> listeCiblesMangeables();
    */

    //std::list<OrganicEntity*> listeCiblesMangeables(std::list<OrganicEntity*> );
    //OrganicEntity* OrganicEntityLaPlusProche(std::list<OrganicEntity*> ) ;
    // std::list<OrganicEntity*> listeCiblesMangeables();

    virtual void update(sf::Time ) = 0;
    virtual void draw(sf::RenderTarget&) const = 0;
    //void setEnergy(const double&);

//	void	LaverOrganicEntityCible();
    // est manger peut manger virtuel pures:

    virtual bool eatable(OrganicEntity const* entity) const = 0;
    virtual bool eatableBy(Scorpion  const* scorpion) const = 0;
    virtual bool eatableBy(Gerbil const* gerbil) const = 0;
    virtual bool eatableBy(Food const* food) const = 0;

    /*

    virtual bool preydator(OrganicEntity const* entity) const = 0;
    virtual bool preydatorBy(Scorpion  const* scorpion) const = 0;
    virtual bool preydatorBy(Gerbil const* gerbil) const = 0;
    virtual bool preydatorBy(Food const* food) const = 0;
    	*/
    //void morte();

//	void setEnergy(const double&);
    void setEnergy(const double&);

protected:

    //	void setEnergy(const double&);

    double energie_;
    virtual void addKidMemory( OrganicEntity*) {}
    sf::Time age_;
    sf::Time age_limit_;


    double energie_depense_base_;
    // double depense_energie_facteur; la chez l'animal


    //sf::Time age_(sf::Time:zero);
//	bool morte_;


};


