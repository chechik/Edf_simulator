#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include "Task.h"
#include "Cpu.h"
#include <list>
#include <cstdlib>
//#include <unistd.h>
#include <time.h>
#include <stdio.h>

#ifndef UNIX
    #include <conio.h>
    #include <windows.h>
#endif // UNIX


#define MAX_TASKS 10
#define START_TIME 0
#define LOOP_TIMES 50 //!< each loop will take time of preemption
#define SUCCESS true
#define FAILURE false
#define OFF 0
#define ON 1

using namespace std;

class Scheduler
{
    public:

        Scheduler();
        virtual ~Scheduler();
        ///create task table for current group of tasks
        void initializeEDF(list<Task> lst,int n);
        ///main loop of simulator
        void mainLoop(Cpu cpu);
        ///determine the task to load into CPU
        bool setCurrTask();
        ///determine the task to load into CPU on simulator start
        bool setCurrTaskOnStart();

        ///update tasks timing variables on every preemption
        void updateTasks();
        ///
        bool reschedule();

        int num_of_tasks;
        int current_task;
        int num_of_ready;

        int max_prio;
        int min_deadline;

        Task task_table[MAX_TASKS];
        float current_time;
        float step_duration;
        float loop_times;
        bool BURN_MODE;
    protected:
    private:

};

#endif // SCHEDULER_H
