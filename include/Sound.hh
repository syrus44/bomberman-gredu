//
// Sound.hh for Bomberman in /home/petit_p//projets/bomber/svn/bomberman-gredu/trunk/Bomberman
// 
// Made by pierre petit
// Login   <petit_p@epitech.net>
// 
// Started on  Mon May 27 12:40:12 2013 pierre petit
// Last update Sun Jun  9 11:19:22 2013 jordan bettin
//

#ifndef _SOUND_HH_
#define _SOUND_HH_

#include <SFML/Audio.hpp>
#include <iostream>

class	Sound
{
public:
  enum Volume
    {
      Low,
      Medium,
      High,
      Mute
    };
  enum	Music
    {
      MassEffect,
      Halo,
      Bf3,
    };

private:
  sf::SoundBuffer	_buttonValidBuffer;
  sf::SoundBuffer	_bombeBuffer;
  sf::SoundBuffer	_footStepBuffer;
  sf::SoundBuffer	_background1Buffer;
  sf::SoundBuffer	_background2Buffer;
  sf::SoundBuffer	_background3Buffer;
  sf::SoundBuffer	_buttonBuffer;
  sf::SoundBuffer	_bonusBuffer;
  sf::Sound		_buttonValid;
  sf::Sound		_bombe;
  sf::Sound		_footStep;
  sf::Sound		_background1;
  sf::Sound		_background2;
  sf::Sound		_background3;
  sf::Sound		_button;
  sf::Sound		_bonus;
  int			_curBackground;

public:
  Sound();
  ~Sound();
  void	playButtonValid();
  void	playBombe();
  void	playFootStep();
  void	playBackground();
  void	playButton();
  void	playBonus();
  void	setVolume(int);
  void	changeMusic(int);
};

#endif /*_SOUND_HH_*/
