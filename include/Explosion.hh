//
// Bomb.hh for Bomb in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 14:30:15 2013 jordan bettin
// Last update Sat Jun  8 18:51:27 2013 florent cerfon
//

#ifndef EXPLOSION_HH
#define EXPLOSION_HH

#include "AObjects.hh"
#include "Map.hh"
#include "Vector3f.hh"

class	Explosion : public AObjects
{
private:
  gdl::Image					_texture;
  std::map<int, std::map<int, AObjects *> >	_map;
  Map						*_mp;
  float						timeBeforeDetonation;
  gdl::Clock					_clock;
  bool						running;

public:
  Explosion(Map *, int, int);
  Explosion(const Explosion &);
  Explosion & operator=(const Explosion &);
  ~Explosion();
  virtual void	pause();
  virtual void	unpause();
  virtual int	getScore() const;
  virtual void	setScore(int);
  virtual int	destroyObject() const;
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
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
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual void	setTexture(int);
  virtual void	randomBonus(AObjects *);
  virtual void	destroyObject();
  virtual int	getRange() const;
  virtual Map	*getMap() const;
  virtual AObjects::typeObject  getType() const;
};

#endif
