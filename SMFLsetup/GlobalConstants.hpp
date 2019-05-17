#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>

const float SPLASH_ANIMATION_DURATION = 0.04411f;
const float FRAMERATE = 1.f / 60.f;
const float TEMPO_CORRECTION = 1.027f;

const int BOI_ANIMATION_HORIZONTAL = 700 / 4;
const int BOI_ANIMATION_VERTICAL = 162;

const sf::Vector2u WIN_RES{ 1280,720 };

const std::string INTRO_BOI_1_SPRITE_PATH = "./resources/pictures/dance1_1.png";
const std::string INTRO_BOI_2_SPRITE_PATH = "./resources/pictures/dance1_2.png";
const std::string SPLASH_BG_PATH = "./resources/pictures/SplashScreen.png";
const std::string SPLASH_MUSIC_PATH = "./resources/audio/SPLASH_MUSIC.wav";
const std::string TRANSITION_SOUND_PATH = "./resources/audio/TRANSITION_SOUND.wav";
const std::string HIT_SOUND_PATH = "./resources/audio/HIT_SOUND.wav";
const std::string KICK_PATH = "./resources/audio/kick.wav";
const std::string CLAP_PATH = "./resources/audio/clap.wav";
const std::string HAT_PATH = "./resources/audio/hat.wav";
const std::string PERC_PATH = "./resources/audio/perc.wav";

const std::string MAIN_FONT_PATH = "./resources/fonts/zerovelo.ttf";
const std::string MENU_BG_PATH = "./resources/pictures/MenuScreen.png";
const std::string POPSTARS_SONG = "popstars";

const std::string HIT_OFF_PATH = "./resources/pictures/hitmarker_on.png";
const std::string HIT_ON_PATH = "./resources/pictures/hitmarker_off.png";

const std::string DOT_PATH = "./resources/pictures/dot.png";

const std::string SONG1_BOI_1_SPRITE_PATH = "./resources/pictures/dance2_1.png";
const std::string SONG1_BOI_2_SPRITE_PATH = "./resources/pictures/dance2_2.png";
const std::string EMPTY_TEX_PATH = "./resources/pictures/emptyTexture.png";