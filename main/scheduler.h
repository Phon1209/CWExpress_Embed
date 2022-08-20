#ifndef __SCHEDULER_H_
#define __SCHEDULER_H_

#include <TaskScheduler.h>
#include <RingBuf.h>
#include "monitor.h"

#define MAX_QUEUE_SIZE 5

struct CWTask
{
  int _data = 0;
  bool _done = true;
} currentTask;

Scheduler taskScheduler;
RingBuf *taskQueue = RingBuf_new(sizeof(CWTask), MAX_QUEUE_SIZE);

bool createTask(CWTask &newTask, String &msg)
{
  int cmdIndex = msg.indexOf(' ');
  String cmd = msg.substring(0, cmdIndex);

  if (cmd == String("on"))
  {
    // Type: blink
    String amt = msg.substring(cmdIndex + 1);
    newTask._data = atoi(amt.c_str());

    newTask._done = false;
    Serial.println("New Blink Task created!");
    return true;
  }
  else if (cmd == String("qr"))
  {
    // Type: QR
    String qrRaw = msg.substring(cmdIndex + 1);

    showQrImage(qrRaw);

    return false;
  }
  else
    return false;
}

#endif