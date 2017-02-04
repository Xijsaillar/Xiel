//
// Created by xijezu on 04.02.17.
//

#ifndef POKEMON_XICI_STATES_H
#define POKEMON_XICI_STATES_H

#include <SFML/Graphics.hpp>

namespace Interfaces {
    class States {
    public:
        virtual void Update(float deltaTime) = 0;

        virtual void Render(sf::RenderWindow *renderWindow, float deltaTime) = 0;

        virtual void Input(float deltaTime) = 0;
    };
}


#endif //POKEMON_XICI_STATES_H
