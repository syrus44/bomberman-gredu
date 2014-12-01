//
// Camera.cpp for  in /home/petit_p//projets/bomber
// 
// Made by pierre petit
// Login <petit_p@epitech.net>
// 
// Started on  Mon May  6 11:37:20 2013 pierre petit
// Last update Sat Jun  8 17:15:57 2013 jordan bettin
//

#include "Camera.hh"

Camera::Camera(void)
  : _position(0.0f, 2000.0f, 0.0f), _rotation(90.0f, 0.0f, 0.0f)
{}

void	Camera::initialize(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0f, 800.0f/600.0f, 1.0f, 10000.0f);
  gluLookAt(this->_position.x, this->_position.y, this->_position.z,
	    0.0f, 0.0f, -1.0f,
	    0.0f, 1.0f, 0.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void	Camera::update(gdl::GameClock const __attribute__((unused)) & gameClock, gdl::Input __attribute__((unused)) & input)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0f, 800.0f/600.0f, 1.0f, 10000.0f);
  gluLookAt(this->_position.x + 500, this->_position.y, -this->_position.z + 90,
	    this->_position.x, 0.0f, -this->_position.z + 1,
	    0.0f, 1.0f, 0.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}
