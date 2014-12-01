//
// Air.hh for Air in /home/bettin_j//SVN/bomberman-gredu/trunk/Bomberman/include
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Wed May 15 17:19:58 2013 jordan bettin
// Last update Sat Jun  8 18:59:58 2013 florent cerfon
//

#ifndef AIR_HH
#define AIR_HH

#include "AObjects.hh"
#include "Image.hpp"

#define	FLOOR_WIDTH_SIZE	150
#define	FLOOR_DEEP_SIZE		100

class	Air : public AObjects
{
private:
  gdl::Image	_texture;

public:
  Air(int, int);
  Air(const Air &);
  ~Air();
  Air & operator=(const Air &);

  virtual void initialize();
  virtual void update(gdl::GameClock const &, gdl::Input &);
  virtual void draw();

  virtual void setVecX(float);
  virtual void setVecY(float);
  virtual void setVecZ(float);
  virtual void setScore(int);

  virtual float getVecX() const;
  virtual float getVecY() const;
  virtual float getVecZ() const;
  virtual int	getScore() const;
  virtual int   getPosX() const;
  virtual int	getPosY() const;
  virtual int	getRange() const;
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual void  setTexture(int);

  virtual void  randomBonus(AObjects *);
  virtual void	destroyObject();
  virtual AObjects::typeObject	getType() const;
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
  virtual void	pause() {};
  virtual void	unpause() {};
};

#endif
