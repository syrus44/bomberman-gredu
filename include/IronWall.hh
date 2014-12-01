//
// IronWall.hh for IronWall in /home/bettin_j//Dropbox/Epitech/Bomberman/true_include
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Tue May 14 17:57:21 2013 jordan bettin
// Last update Sat Jun  8 18:44:15 2013 florent cerfon
//

#ifndef IRONWALL_HH
#define IRONWALL_HH

#include "AObjects.hh"
#include "Image.hpp"
#include "GameClock.hpp"
#include "Input.hpp"

class	IronWall : public AObjects
{
  gdl::Image	_texture;
  std::map<int, std::map<int, AObjects*> > _map;
  
public:
  IronWall(int, int);
  IronWall(const IronWall &);
  ~IronWall();
  IronWall & operator=(const IronWall &);
  void		initialize(void);
  void		update(gdl::GameClock const &, gdl::Input &);
  void		draw(void);
  virtual void	setVecX(float);
  virtual void	setVecY(float);
  virtual void	setVecZ(float);
  virtual float	getVecX(void) const;
  virtual float	getVecY(void) const;
  virtual float	getVecZ(void) const;
  virtual void	setScore(int);
  virtual int   getPosX() const;
  virtual int	getPosY() const;
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual int	getRange() const;
  virtual int	getScore() const;
  virtual void	destroyObject();
  virtual void  setTexture(int);
  virtual AObjects::typeObject  getType() const;
  virtual void  randomBonus(AObjects *);
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const & m);
  virtual void	pause() {};
  virtual void	unpause() {};
};

#endif
