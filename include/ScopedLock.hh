//
// ScopedLock.hh for ScopedLock in /home/cerfon_f//tp/c++/plazza/exo_1
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Fri Apr 19 17:39:50 2013 florent cerfon
// Last update Sun Apr 21 22:31:23 2013 florent cerfon
//

#ifndef	_SCOPEDLOCK_HH
#define _SCOPEDLOCK_HH

#include "Mutex.hh"

class	ScopedLock
{
private:
  Mutex *mutex;
public:
  ScopedLock(Mutex *);
  ~ScopedLock();
};

#endif
