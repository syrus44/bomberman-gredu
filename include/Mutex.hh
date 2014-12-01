//
// Mutex.hh for Mutex in /home/cerfon_f//tp/c++/plazza/exo_1
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Fri Apr 19 16:16:03 2013 florent cerfon
// Last update Sun Apr 21 05:24:18 2013 florent cerfon
//

#ifndef MUTEX_HH
#define	MUTEX_HH

#include <pthread.h>

class Mutex
{
private:
  pthread_mutex_t	mutex;
  pthread_cond_t	cond;
public:
  Mutex();
  ~Mutex();
  void			lock();
  void			unlock();
  void			wait();
  bool			trylock();
};

#endif
