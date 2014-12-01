//
// Camera.hh for  in /home/petit_p//projets/bomber
// 
// Made by pierre petit
// Login   <petit_p@epitech.net>
// 
// Started on  Mon May  6 11:34:35 2013 pierre petit
// Last update Sat Jun  8 17:10:07 2013 jordan bettin
//

#ifndef	_CAMERA_HH_
#define	_CAMERA_HH_

#include <GL/gl.h>
#include <GL/glu.h>

#include "GameClock.hpp"
#include "Input.hpp"
#include "Vector3f.hh"

class	Camera
{
public:
  Camera(void);

public:
  void		initialize(void);
  void		update(gdl::GameClock const &, gdl::Input &);

public:
  Vector3f	_position;
  Vector3f	_rotation;
};

#endif /*_CAMERA_HH_*/
