//
// Utils.cpp for Utils in /home/cerfon_f//taff/src
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Wed Apr 17 11:05:12 2013 florent cerfon
// Last update Sat Jun  8 17:21:33 2013 jordan bettin
//

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <dirent.h>
#include "Utils.hpp"

Waiter::Waiter(int time)
{
  usleep(time);
}

Waiter::~Waiter()
{}

template <typename ptr_1, typename arg_1>
Fork::Fork(const ptr_1 &child_ptr, const arg_1 &child_arg)
{
  if ((this->_pid = fork()) == -1)
    throw Exception("fork failed");
  if (this->_pid == 0)
    {
      child_ptr(child_arg);
      exit (0);
    }
}

int	Fork::get_pid() const
{
  return (this->_pid);
}

/* CLOCK */

void	*clockDecrease(void *object)
{
  Clock	*ClockObj = static_cast<Clock *>(object);

  while (ClockObj->isNull() == false)
    {
      Waiter(1000000);
      ClockObj->decreaseTimer();
    }
  return (0);
}

Clock::Clock(int time)
{
  this->timer = time;
  BasicThread<Clock>(&clockDecrease, this);
}

bool	Clock::isNull()
{
  if (this->timer <= 0)
    return (true);
  return (false);
}

void	Clock::decreaseTimer()
{
  this->timer--;
}

int	Clock::getTimer()
{
  ScopedLock(&(this->_mutex));
  return (this->timer);
}

Clock::~Clock()
{}

/* /CLOCK */

Fork::~Fork()
{}

cout_Mutex::cout_Mutex()
{}

void	cout_Mutex::print(const std::string &msg)
{
  ScopedLock	_lock(&(this->_mutex));
  std::cout << msg;
}

void	cout_Mutex::printn(const std::string &msg)
{
  ScopedLock	_lock(&(this->_mutex));
  std::cout << msg << std::endl;;
}

void	cout_Mutex::operator<<(const std::string &msg)
{
  this->printn(msg);
}

void	cout_Mutex::lock()
{
  this->_mutex.lock();
}

void	cout_Mutex::unlock()
{
  this->_mutex.unlock();
}

cout_Mutex::~cout_Mutex()
{}
