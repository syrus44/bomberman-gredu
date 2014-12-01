//
// Sound.cpp for Bomberman in /home/petit_p//projets/bomber/svn/bomberman-gredu/trunk/Bomberman
// 
// Made by pierre petit
// Login   <petit_p@epitech.net>
// 
// Started on  Mon May 27 12:42:35 2013 pierre petit
// Last update Sun Jun  9 11:19:05 2013 jordan bettin
//

#include "Sound.hh"

Sound::Sound()
{
  this->_curBackground = 2;

  this->_buttonValidBuffer.LoadFromFile("sound/buttonValid.wav");
  this->_buttonValid.SetBuffer(this->_buttonValidBuffer);
  this->_buttonValid.SetVolume(20.0f);

  this->_bombeBuffer.LoadFromFile("sound/explosion3.wav");
  this->_bombe.SetBuffer(this->_bombeBuffer);
  this->_bombe.SetVolume(80.0f);

  this->_footStepBuffer.LoadFromFile("sound/footstep.wav");
  this->_footStep.SetBuffer(this->_footStepBuffer);
  this->_footStep.SetVolume(30.0f);

  this->_buttonBuffer.LoadFromFile("sound/button.wav");
  this->_button.SetBuffer(this->_buttonBuffer);
  this->_button.SetVolume(20.0f);

  this->_background1Buffer.LoadFromFile("sound/background1.wav");
  this->_background1.SetBuffer(this->_background1Buffer);
  this->_background1.SetVolume(0.0f);
  this->_background1.SetPitch(1.0);
  this->_background1.SetLoop(true);

  this->_background2Buffer.LoadFromFile("sound/background2.wav");
  this->_background2.SetBuffer(this->_background2Buffer);
  this->_background2.SetVolume(50.0f);
  this->_background2.SetPitch(1.0);
  this->_background2.SetLoop(true);

  this->_background3Buffer.LoadFromFile("sound/background3.wav");
  this->_background3.SetBuffer(this->_background3Buffer);
  this->_background3.SetVolume(0.0f);
  this->_background3.SetPitch(1.0);
  this->_background3.SetLoop(true);

  this->_bonusBuffer.LoadFromFile("sound/bonus.wav");
  this->_bonus.SetBuffer(this->_bonusBuffer);
  this->_bonus.SetVolume(20.0f);
}

Sound::~Sound()
{}

void	Sound::playButtonValid()
{
  this->_buttonValid.Play();
}

void	Sound::playBombe()
{
  this->_bombe.Play();
}

void	Sound::playFootStep()
{
  this->_footStep.Play();
}

void	Sound::playBackground()
{
  this->_background1.Play();
  this->_background2.Play();
  this->_background3.Play();
}

void	Sound::playButton()
{
  this->_button.Play();
}

void	Sound::playBonus()
{
  this->_bonus.Play();
}

void	Sound::changeMusic(int music)
{
  switch (music)
    {
    case (Halo):
      this->_curBackground = 1;
      break;
    case (Bf3):
      this->_curBackground = 2;
      break;
    case (MassEffect):
      this->_curBackground = 3;
      break;
    }
}

void	Sound::setVolume(int volume)
{
  switch (volume)
    {
    case (High):
      this->_buttonValid.SetVolume(30.0f);
      this->_bonus.SetVolume(40.0f);
      this->_bombe.SetVolume(100.0f);
      this->_footStep.SetVolume(40.0f);
      switch (this->_curBackground)
	{
	case (1):
	  this->_background1.SetVolume(70.0f);
	  this->_background2.SetVolume(0.0f);
	  this->_background3.SetVolume(0.0f);
	  break;
	case (2):
	  this->_background1.SetVolume(0.0f);
	  this->_background2.SetVolume(70.0f);
	  this->_background3.SetVolume(0.0f);
	  break;
	case (3):
	  this->_background1.SetVolume(0.0f);
	  this->_background2.SetVolume(0.0f);
	  this->_background3.SetVolume(70.0f);
	  break;
	}
      this->_button.SetVolume(30.0f);
      break;
    case (Medium):
      this->_buttonValid.SetVolume(20.0f);
      this->_bonus.SetVolume(20.0f);
      this->_bombe.SetVolume(80.0f);
      this->_footStep.SetVolume(30.0f);
      switch (this->_curBackground)
	{
	case (1):
	  this->_background1.SetVolume(50.0f);
	  this->_background2.SetVolume(0.0f);
	  this->_background3.SetVolume(0.0f);
	  break;
	case (2):
	  this->_background1.SetVolume(0.0f);
	  this->_background2.SetVolume(50.0f);
	  this->_background3.SetVolume(0.0f);
	  break;
	case (3):
	  this->_background1.SetVolume(0.0f);
	  this->_background2.SetVolume(0.0f);
	  this->_background3.SetVolume(50.0f);
	  break;
	}
      this->_button.SetVolume(20.0f);
      break;
    case (Low):
      this->_buttonValid.SetVolume(10.0f);
      this->_bombe.SetVolume(60.0f);
      this->_bonus.SetVolume(20.0f);
      this->_footStep.SetVolume(30.0f);
      switch (this->_curBackground)
	{
	case (1):
	  this->_background1.SetVolume(30.0f);
	  this->_background2.SetVolume(0.0f);
	  this->_background3.SetVolume(0.0f);
	  break;
	case (2):
	  this->_background1.SetVolume(0.0f);
	  this->_background2.SetVolume(30.0f);
	  this->_background3.SetVolume(0.0f);
	  break;
	case (3):
	  this->_background1.SetVolume(0.0f);
	  this->_background2.SetVolume(0.0f);
	  this->_background3.SetVolume(30.0f);
	  break;
	}
      this->_button.SetVolume(10.0f);
      break;
    case (Mute):
      this->_buttonValid.SetVolume(0.0f);
      this->_bonus.SetVolume(0.0f);
      this->_bombe.SetVolume(0.0f);
      this->_footStep.SetVolume(0.0f);
      this->_background1.SetVolume(0.0f);
      this->_background2.SetVolume(0.0f);
      this->_background3.SetVolume(0.0f);
      this->_button.SetVolume(0.0f);
      break;
    }
}
