//
// Bomb.hh for Bomb in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 14:30:15 2013 jordan bettin
// Last update Sat Jun  8 18:51:12 2013 florent cerfon
//

#ifndef BOMB_HH
#define BOMB_HH

#include "Timer.hpp"
#include "APlayers.hh"
#include "Map.hh"

template <typename T> class Timer;

class	Bomb : public AObjects
{
private:
  Map		*_map;
  gdl::Image    _texture;
  Timer<Bomb>	*_detonator;
  APlayers	*_bomber;
  gdl::Clock	_clock;
  float		timeBeforeDetonation;
  bool		running;

public:
  Bomb(Map *, Vector3f const &, std::pair<int, int> const &, APlayers *);
  Bomb(const Bomb &);
  Bomb & operator=(const Bomb &);
  ~Bomb();
  virtual int	getScore() const;
  virtual void	setScore(int);
  virtual void	destroyObject();
  virtual void	setMap(Map *);
  virtual Map	*getMap() const;
  virtual APlayers* getBomber() const;
  virtual void	initialize(void);
  virtual void	update(gdl::GameClock const &, gdl::Input &);
  virtual void	draw(void);
  virtual void	setVecX(float);
  virtual void	setVecY(float);
  virtual void	setVecZ(float);
  virtual float	getVecX() const;
  virtual float	getVecY() const;
  virtual float	getVecZ() const;
  virtual int   getPosX() const;
  virtual int	getPosY() const;
  virtual int	getRange() const;
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual void  setTexture(int);
  void		setRange(int);
  virtual void  randomBonus(AObjects *);
  virtual AObjects::typeObject  getType() const;
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
  virtual void	pause();
  virtual void	unpause();
};

#endif
