#include "Task.h"


Task::Task()
{
    this->id = EMPTY;
    this->exec_time = EMPTY;
    this->period = EMPTY;
    this->time_to_deadline = EMPTY;
    this->time_in_cpu = EMPTY;
    this->state = SUSPENDED;
}

Task::~Task()
{

}

Task::Task(int id,int time,int p)
{
    //!< will not change during run
    this->id = id;
    this->exec_time = time;
    this->period = p;

    //!< will change during run
    this->time_to_deadline = 0;
    this->time_in_cpu = 0;
    this->state = SUSPENDED;
}

bool Task::isLegal()
{
    if(exec_time>period)
        return false;
    if(exec_time<1 || period<1)
        return false;

    return true;
}

void Task::printInfo()
{
    cout <<"Task info id "<< id<<" tm to dead " << time_to_deadline << " in cpu "<< time_in_cpu << endl;
    return;
}
