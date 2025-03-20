#include "Stats.hpp"
#include <string>
#include "../Interface/Drawable.hpp"
//#include  <SFML/Graphics.hpp>
#include <vector>
#include "Graph.hpp"
#include <memory>
#include "../Interface/Updatable.hpp"
#include "../Utility/Vec2d.hpp"
// application-run --cfg=appPPS.json
#include <iostream>
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include <unordered_map>
Stats::Stats() : stats_indentifiant_actif_(-1),stats_clock_(sf::Time::Zero),stats_clock_refresh_(sf::Time::Zero),stats_time_refresh_rate_(sf::seconds(getAppConfig().stats_refresh_rate )) {}

void Stats::update(sf::Time dt)
{
    stats_clock_ += dt;
    stats_clock_refresh_+= dt;
    /*
    std::unordered_map <std::string, double> carte ;


    carte [s::SCORPIONS] = 10;
    carte[s::GERBILS] = 15;
    carte [s::FOOD] = 30 ;



    for (auto elem : carte ){
    std::cout << elem.first << "  " << elem.second << std::endl;
    	*/

    if (stats_clock_refresh_ >= stats_time_refresh_rate_) {
        stats_clock_refresh_= sf::Time::Zero;
        stats_map_index_graph_[stats_indentifiant_actif_]->updateData(
            stats_clock_
            , getAppEnv().fetchData(stats_map_index_libelle_[stats_indentifiant_actif_]));


        //	stats_map_index_graph_[stats_indentifiant_actif_]->updateData(stats_clock_, carte);

    }
}


// stats_map_index_graph_[stats_indentifiant_actif_]->updateData(stats_clock_, getAppEnv().fetchData("general"));
//	stats_map_index_graph_[stats_indentifiant_actif_]->updateData(stats_clock_, {"Scorpions", {0.0}}
//{"Gerbils",  {0.0}}
//{"Food sources",  {0.0}})
//	 stats_map_index_graph_[stats_indentifiant_actif_]->updateData(stats_clock_, getAppEnv().fetchData("Scorpion"));
//	 stats_map_index_graph_[stats_indentifiant_actif_]->updateData(stats_clock_, getAppEnv().fetchData("Food"))



void Stats::draw(sf::RenderTarget& target) const
{
    //for (auto& map : stats_map_index_graph_){
    //	map.second->draw(target);

    if(stats_indentifiant_actif_ >=0) {
        stats_map_index_graph_.at(stats_indentifiant_actif_)->draw(target);
    }


}

void Stats::addGraph( const int& index, std::string const& libelle,std::vector<std::string> const& titles, const double& min,const double& max, Vec2d size)
{

    stats_map_index_graph_[index].reset(new Graph(titles,size,min,max));
    stats_map_index_libelle_[index]= libelle;
    stats_map_libelle_index_[libelle]=index;

}

void Stats::setActive(int const& index)
{
    stats_indentifiant_actif_=index;
}
void Stats::setActive()
{
    if ( stats_indentifiant_actif_ <= 0 and !stats_map_index_graph_.empty()) {
        ++stats_indentifiant_actif_;
    }
    if( stats_indentifiant_actif_ <= int (stats_map_index_graph_.size() ) ) {
        ++ stats_indentifiant_actif_;
    } else {
        stats_indentifiant_actif_=0;
    }
}


void Stats::focusOn(std::string title)
{
    stats_indentifiant_actif_=stats_map_libelle_index_[title];
    stats_map_index_graph_[stats_indentifiant_actif_]->reset();
}


void Stats::reset()
{
    for (auto& map : stats_map_index_graph_) {
        map.second->reset();
    }
}
