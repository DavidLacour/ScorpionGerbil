
class ChasingAutomaton : public CircularCollider
{
public:
    ChasingAutomaton(const Vec2d& position, double vitesse = 0)


        : CircularCollider( position, CHASING_AUTOMATON_RADIUS), direction_(0,0), vitesse_(vitesse), cible_(1,0)
    {
    }
    const double& getStandardMaxSpeed() const;
    const double& getMass() const ;

    Vec2d force( const Vec2d&) const;

    void setTargetPosition(const Vec2d&);

    Vec2d getSpeedVector() const ;

    void update(sf::Time );
    void draw(sf::RenderTarget& targetWindow);
    void move(const double&);







private:

    Vec2d direction_;
    double vitesse_;
    Vec2d cible_;



};


