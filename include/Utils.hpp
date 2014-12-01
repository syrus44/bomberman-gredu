//
// Utils.hh for Utils in /home/cerfon_f//taff/src
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Wed Apr 17 11:05:19 2013 florent cerfon
// Last update Fri Jun  7 22:23:12 2013 louis cailleux
//

#ifndef UTILS_HH
#define UTILS_HH

#include "Mutex.hh"
#include "Thread.hpp"
#include "Exception.hh"
#include "ScopedLock.hh"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class	Waiter
{
public:
  Waiter(int);
  ~Waiter();
};

class	cout_Mutex
{
private:
  Mutex	_mutex;
public:
  cout_Mutex();
  ~cout_Mutex();
  void	operator<<(const std::string &msg);
  void	printn(const std::string &);
  void	print(const std::string &);
  void	lock();
  void	unlock();
};

class	Clock
{
public:
  Clock(int);
  ~Clock();
  int	getTimer();
  void	decreaseTimer();
  bool	isNull();
private:
  Mutex	_mutex;
  int	timer;
};

class	Fork
{
private:
  pid_t	_pid;
public:
  template <typename ptr_1, typename arg_1>
  Fork(const ptr_1 &child_ptr, const arg_1 &child_arg);

  template <typename ptr_1, typename arg_1, typename type_class>
  Fork(const ptr_1 &child_ptr, const arg_1 &child_arg, type_class *my_class)
  {
    if ((this->_pid = fork()) == -1)
      throw Exception("fork failed");
    if (this->_pid == 0)
      {
	(*my_class.*child_ptr)(child_arg);
	exit(0);
      }
  }

  int	get_pid() const;
  ~Fork();
};



#endif
