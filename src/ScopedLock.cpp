//
// ScopedLock.cpp for ScopedLock in /home/cerfon_f//tp/c++/plazza/exo_1
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Fri Apr 19 17:39:35 2013 florent cerfon
// Last update Sun Apr 21 22:31:20 2013 florent cerfon
//

#include "ScopedLock.hh"

ScopedLock::ScopedLock(Mutex *other) : mutex(other)
{
  other->lock();
}

ScopedLock::~ScopedLock()
{
  this->mutex->unlock();  
}
