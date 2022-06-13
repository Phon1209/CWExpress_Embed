#ifndef __SCHEDULER_H_
#define __SCHEDULER_H_

#include <TaskScheduler.h>
#include <RingBuf.h>

struct CWTask
{
  int _amount;
  boolean _done = false;
} currentTask;

Scheduler taskScheduler;
RingBuf *taskQueue = RingBuf_new(sizeof(CWTask), 10);

bool createTask(CWTask &newTask, String &msg)
{
  int cmdIndex = msg.indexOf(' ');
  String cmd = msg.substring(0, cmdIndex);

  if (cmd != String("on"))
    return false;

  String amt = msg.substring(cmdIndex + 1);
  newTask._amount = atoi(amt.c_str());
  newTask._done = false;
  Serial.println("New Task created!");
  return true;
}

#endif