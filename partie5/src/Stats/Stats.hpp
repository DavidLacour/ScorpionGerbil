#pragma once
#include "../Interface/Drawable.hpp"
//#include  <SFML/Graphics.hpp>
#include <vector>
#include "Graph.hpp"
#include <memory>
#include "../Interface/Updatable.hpp"
#include "../Utility/Vec2d.hpp"
#include <string>
#include <list>
#include <map>


// application-run --cfg=appPPS.json
class Stats: public Drawable,
    public Updatable
{
public:
    Stats();
    ~Stats() {};

    virtual void draw(sf::RenderTarget& target) const override ;

    void setActive(const int&);
    void setActive();
    void focusOn(std::string title);

    /*!
    * @brief add a graph
    Réinitialiser le pointeur sur Graph associé à l'identifiant en paramètre en lui associant un nouveau Graph, alloué dynamiquement (méthode reset des unique_ptr).
    Mettre à jour le titre du graphe associé à l'identifiant, au moyen du titre passé en paramètre.
    Faire en sorte que l'identifiant en paramètre soit répertorié comme l'identifiant actif.

    *
    * @param l'identifiant du graphe
    * @param libellé
    * @param l'ensemble des titres de courbes du graphe
    * @param min
    * @param max
    * @param donnant les dimensions de la fenêtre graphique dans laquelle se font les affichages
    *
    *
    * @return an animal
    */
//void addGraph(std::string const& title, std::vector<std::string> const& series, double min, double max);
    void addGraph( const int&, std::string const& ,std::vector<std::string> const&, const double&,const double&, Vec2d );


    /*
     l'identifiant du graphe, son libellé, l'ensemble des titres de courbes du graphe (un vector de string),
     les valeurs minimales et maximales (min et max) entres lesquelles s'affichent les points de courbes (des double)
      et un Vec2d (size) donnant les dimensions de la fenêtre graphique dans laquelle se font les affichages.
    */

    void reset();
    virtual void update(sf::Time ) override;

private:
    int stats_indentifiant_actif_;
    sf::Time stats_clock_;
    sf::Time stats_clock_refresh_;
    sf::Time stats_time_refresh_rate_;

    std::unordered_map<int,std::unique_ptr<Graph>> stats_map_index_graph_;

    std::unordered_map<int,std::string> stats_map_index_libelle_;
    std::unordered_map<std::string,int> stats_map_libelle_index_;


};

