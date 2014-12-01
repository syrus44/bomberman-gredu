//
// Ashes.hh for Bomberman in /home/caille_l//Documents/sparw
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Wed May 22 13:56:00 2013 louis cailleux
// Last update Sat Jun  8 19:00:10 2013 florent cerfon
//

#ifndef ASHES_HH_
# define ASHES_HH_

#include "Map.hh"
#include "Timer.hpp"
#include "AObjects.hh"

class	Ashes : public AObjects
{
private:
  Map		*_map;
  gdl::Image    _texture;

public:
  Ashes(Map *, int, int);
  Ashes(const Ashes &);
  Ashes & operator=(const Ashes &);
  ~Ashes();
  virtual int getScore() const;
  virtual void setScore(int);
  virtual int getRange() const;
  virtual void	destroyObject();
  virtual void	setTimer();
  virtual void	setMap(Map *);
  virtual Map	*getMap() const;
  virtual void	initialize(void);
  virtual void	update(gdl::GameClock const &, gdl::Input &);
  virtual void	draw(void);
  virtual void	setVecX(float);
  virtual void	setVecY(float);
  virtual void	setVecZ(float);
  virtual float	getVecX() const;
  virtual float	getVecY() const;
  virtual float	getVecZ() const;
  virtual int getPosX() const;
  virtual int getPosY() const;
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual void  setTexture(int);
  virtual void  randomBonus(AObjects *);
  virtual AObjects::typeObject  getType() const;
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
  virtual void	endGame();
  virtual void	pause() {};
  virtual void	unpause() {};
};

void	farewell(void *);

#endif
