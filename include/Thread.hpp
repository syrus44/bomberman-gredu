//
// Thread.hpp for Thread in /home/cerfon_f//tp/c++/plazza/exo_1
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Thu Apr 18 12:36:28 2013 florent cerfon
// Last update Wed Jun  5 12:33:53 2013 florent cerfon
//

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <list>
#include "Mutex.hh"
#include "Exception.hh"

enum	thread_status 
  {
    NotYetStarted,
    Running,
    Dead
  };

template <class T>
struct		thread_arg
{
  Mutex		*mutex;
  pthread_t	thread;
  T		var;
};

// Cette classe est construite dans un hpp
// En effet, cela permet d'éviter de reproduire X fois le prototype du constructeur
// Pour tous les types différents.
// Cela permet donc un code plus générique.
// pthread_mutex_init renvoit toujours 0 : il n'est donc pas vérifié.

template <class T>
class BasicThread
{
public:
  BasicThread(void *(*ptr)(void *), T *arg)
  {
    pthread_t	thread;
    if (pthread_create(&(thread), NULL, ptr, arg) != 0)
      throw Exception("pthread_create failed");
  }
  ~BasicThread() {}
};

template <class T>
class ThreadPool
{
  // variables privates

private:
  std::list<thread_arg <T> *>	thread_list;
  thread_status			status;
public:

  // Fonctions membres publiques

  ThreadPool(void *(*ptr)(void *), T arg, int n)
  {
    Mutex		*global_mutex = new Mutex;

    this->status = NotYetStarted;
    while (n-- > 0)
      {
	thread_arg<T>	*thread_st = new thread_arg <T>;

	thread_st->mutex = global_mutex;
	thread_st->var = arg;
	if (pthread_create(&(thread_st->thread), NULL, ptr, thread_st) != 0)
	  throw Exception("pthread_create failed");
	this->status = Running;
	this->thread_list.push_back(thread_st);
      }
  }

  void	thread_joining()
  {
    typename std::list<thread_arg <T> *>::iterator it = this->thread_list.begin();

    for (it ; it != this->thread_list.end() ; ++it)
      {
	if (pthread_join((*it)->thread, NULL) != 0)
	  throw Exception("pthread_join failed\n");
	this->status = Dead;
      }
  }

  thread_status	get_status() const
  {
    return (this->status);
  }

  ~ThreadPool()
  {}

  // !Fonctions membres publiques

};

#endif
