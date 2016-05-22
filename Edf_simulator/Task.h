#ifndef TASK_H
#define TASK_H
#include <iostream>

#define MAX_TASK_PRIO 10000
#define MIN_DEADLINE 10000

#define SUSPENDED 0     //probably missed it's deadline
#define READY     1     //waiting in ready queue
#define CURRENT   2     //currently running on cpu

#define EMPTY -1

using namespace std;

class Task
{
public:

    int id;
    int exec_time;
    int period;
    int state;
    int time_in_cpu;
    int time_to_deadline;
    // ---

    int start_time;
    Task();
    Task(int id,int time,int p);
    ~Task();
    bool isLegal();
    void printInfo();
};


#endif // TASK_H
