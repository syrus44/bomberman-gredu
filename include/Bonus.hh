//
// Bonus.hh for Bonus in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 14:47:54 2013 jordan bettin
// Last update Sun Jun  9 11:11:09 2013 jordan bettin
//

#ifndef BONUS_HH
#define BONUS_HH

#include <map>
#include <utility>
#include <cstdlib>
#include "GameClock.hpp"
#include "Input.hpp"
#include "Image.hpp"
#include "APlayers.hh"

class	Bonus : public AObjects
{
private:
  gdl::Image    _texture;

public:
  Bonus(int, int);
  Bonus(const Bonus &);
  Bonus & operator=(const Bonus &);
  ~Bonus();
  virtual int	getScore() const;
  virtual void	setScore(int);
  virtual void	destroyObject();
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
  virtual void  setTexture(int);
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual void  randomBonus(AObjects *);
  virtual void  addBomb(APlayers *);
  virtual void  incRange(APlayers *);
  virtual void  speedUp(APlayers *);
  virtual int   getBonusType() const;
  virtual void  setBonusTexture(std::string);
  virtual APlayers::typeObject  getType() const;
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
  void	call(APlayers *, void (Bonus::*fctType)(APlayers *));
  virtual void	pause() {};
  virtual void	unpause() {};
};

typedef void (Bonus::*fctType)(APlayers *);

#endif
