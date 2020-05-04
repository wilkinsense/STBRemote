#ifndef TIMER_Mgr
#define TIMER_Mgr

#include <functional>
#include <vector>
#include "Timer.h"

class TimerMgr
{
public:
	TimerMgr();

  void createTimer(int milliseconds, std::function<void(void)> fn);
  void tickTimers();

private:
  std::vector<Timer*> m_timers;
};

#endif
