// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "GlobalConstants.hpp"

#include "Game.hpp"
#include "State.hpp"
#include "StateMaschine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "SongsData.hpp"
#include "HitParticles.hpp"
#include "Misc.hpp"

#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "OptionsState.hpp"
#include "KeyBindingState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "EndGameState.hpp"

#include <utility>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <stack>
#include <random>
#include <fstream>

#endif //PCH_H
