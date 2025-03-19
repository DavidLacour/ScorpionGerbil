/*
 * infosv
 * jan 2012
 * Marco Antognini
 */

#include "FinalApplication.hpp"
#include <Animal/Gerbil.hpp>
#include <Animal/Scorpion.hpp>
#include <Animal/NeuronalScorpion/NeuronalScorpion.hpp>
#include <Animal/NeuronalScorpion/WaveGerbil.hpp>
#include <Environment/Food.hpp>
#include <Environment/FoodGenerator.hpp>
#include <Environment/Wave.hpp>

IMPLEMENT_MAIN(FinalApplication)

void FinalApplication::onRun()
{
    // Setup stats
    Application::onRun();
    addGraph(s::GENERAL, { s::SCORPIONS, s::GERBILS, s::FOOD,}, 0, 200);
    addGraph(s::WAVES, { s::WAVES}, 0, 100);
    focusOnStat(s::GENERAL);
}
void FinalApplication::onEvent(sf::Event event, sf::RenderWindow& window)
{
    bool const toggle = event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Tab;

    if (toggle) {
        switch (getSimulationMode()) {
        case SimulationMode::PPS:
            setSimulationMode(SimulationMode::NEURONAL);
            focusOnStat(s::GENERAL);
            break;

        case SimulationMode::NEURONAL:
            setSimulationMode(SimulationMode::PPS);
            focusOnStat(s::WAVES);

            break;
        case SimulationMode::TEST :
            /*nothing to do */
            break;
        }
        toggleStats();
    }

    else {
        switch (getSimulationMode()) {
        case SimulationMode::PPS:
            onEventPPS(event, window);
            break;

        case SimulationMode::NEURONAL:
            onEventNeuronal(event, window);
            break;
        case SimulationMode::TEST :
            /*nothing to do */
            break;
        }
    }

}

void FinalApplication::onUpdate(sf::Time dt)
{
    Application::onUpdate(dt);
    switch (getSimulationMode()) {
    case SimulationMode::PPS:
        onUpdatePPS(dt);
        break;

    case SimulationMode::NEURONAL:
        onUpdateNeuronal(dt);
        break;
    case SimulationMode::TEST :
        /*nothing to do */
        break;
    }
}

void FinalApplication::onSimulationStart()
{
    setSimulationMode(SimulationMode::PPS);

    getAppEnv().addGenerator(new FoodGenerator());

    //getAppStats().setData(0, "PPS");
}

void FinalApplication::onEventPPS(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::S:
            getAppEnv().addEntity(new Scorpion(getCursorPositionInView()));
            break;

        case sf::Keyboard::G:
            getAppEnv().addEntity(new Gerbil(getCursorPositionInView()));
            break;

        case sf::Keyboard::F:
            getAppEnv().addEntity(new Food(getCursorPositionInView()));
            break;
        case sf::Keyboard::Q:
            getAppEnv().addGenerator(new FoodGenerator());
            break;
        case sf::Keyboard::A:
            getAppEnv().popGenerator();
            break;
        case sf::Keyboard::X:
            if(event.key.control) {
                Animal* male = new Gerbil(getCursorPositionInView(), 'X', false);
                if (male != nullptr)
                    getAppEnv().addEntity(male);
            }

            else {
                Animal* female = new Gerbil(getCursorPositionInView(), 'X', true);
                if (female != nullptr)
                    getAppEnv().addEntity(female);
            }

            break;
        case sf::Keyboard::Y:
            if(event.key.control) {
                Animal* male= new Scorpion(getCursorPositionInView(), 'Y', false);
                if (male != nullptr)
                    getAppEnv().addEntity(male);
            }

            else {
                Animal* female = new Scorpion(getCursorPositionInView(), 'Y', true);
                if (female != nullptr)
                    getAppEnv().addEntity(female);
            }

            break;
        default:
            break;
        }
    }
}

void FinalApplication::onUpdatePPS(sf::Time)
{
    // Nothing
}

/*
void FinalApplication::onInitNeuronal()
{
    setSimulationMode(SimulationMode::NEURONAL);

    //getAppStats().setData(0, "NEURONAL");
}
*/

void FinalApplication::onEventNeuronal(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::W:
            getAppEnv().addEntity(new WaveGerbil(getCursorPositionInView()));
            break;

        case sf::Keyboard::N:
            getAppEnv().addEntity(new NeuronalScorpion(getCursorPositionInView()));
            break;

        default:
            break;
        }
    }
}

void FinalApplication::onUpdateNeuronal(sf::Time)
{
    // Nothing
}

std::vector<std::string> FinalApplication::getHelperText() const
{
    if (getSimulationMode() == SimulationMode::PPS) {
        return {    "---------------------",
                    "(MP : mouse position)",
                    "R   : Reset the simulation",
                    "Esc : End of program",
                    "C   : Reload config file",
                    "G: Add a gerbil at MP ctrlx male",
                    "S: Add a scorpion ctrly male",
                    "F:food Q:Add A:Pop Fgenerator",

                    "D   : Toggle debug mode",
                    "Tab : Switch macro/micro view",
                    "Z   : Zoom",
                    "->  : Move view to right",
                    "<-  : Move view to left",
                    "Space : Pause"
               };
    } else {
        return  {    "---------------------",
                     "(MP: mouse position)",
                     "R  : Reset the simulation",
                     "Esc : End of program",
                     "C   : Reload config file"
                     "N  : Add a neuronal scorpion",
                     "         at MP",
                     "W  : Add a wave gerbil at MP",
                     "D  : Toggle debug mode",
                     "Tab: Switch macro/micro view",
                     "Z   : Zoom",
                     "->  : Move view to right",
                     "<-  : Move view to left",
                     "Space : Pause"
                };
    }
}
