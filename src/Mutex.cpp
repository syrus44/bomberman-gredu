//
// Mutex.cpp for Mutex in /home/cerfon_f//tp/c++/plazza/exo_1
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Fri Apr 19 16:16:08 2013 florent cerfon
// Last update Fri Jun  7 22:27:39 2013 louis cailleux
//

#include <stdlib.h>
#include <iostream>
#include "Mutex.hh"
#include "Exception.hh"

Mutex::Mutex()
{
  pthread_mutex_init(&(this->mutex), 0);
  if (pthread_cond_init(&(this->cond), 0) != 0)
    throw Exception("pthread_cond_init failed");
}

Mutex::~Mutex()
{}

void	Mutex::lock()
{
  if (pthread_mutex_lock(&(this->mutex)) != 0)
    throw Exception("pthread_mutex_lock failed");
}

void	Mutex::unlock()
{
  if (pthread_mutex_unlock(&(this->mutex)) != 0)
    throw Exception("pthread_mutex_unlock failed");
}

bool	Mutex::trylock()
{
  bool	result;

  if ((result = pthread_mutex_trylock(&(this->mutex))) != 0)
    throw Exception("pthread_mutex_trylock failed");
  return (result);
}

void	Mutex::wait()
{
  this->lock();
  pthread_cond_wait(&(this->cond), &(this->mutex));
}
