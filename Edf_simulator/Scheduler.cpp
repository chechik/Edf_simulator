#include "Scheduler.h"

using namespace std;

Scheduler::Scheduler()
{

    this->current_time = START_TIME;
    this->loop_times = LOOP_TIMES;
    this->BURN_MODE = OFF;
    this->min_deadline = MIN_DEADLINE;
    this->max_prio = MAX_TASK_PRIO;

}

Scheduler::~Scheduler()
{
    //dtor
}

void Scheduler::initializeEDF(list<Task> lst,int n)
{
    /**< initialize scheduler, before it can proceed to a loop run.
    Task table initialization.
    */
     cout << "i'am in schedInit"<<endl;


    num_of_tasks = n;
    num_of_ready = n;

    int task_index = 0;
    for (list<Task>::iterator it = lst.begin(); it!=lst.end(); ++it)
    {
        task_table[task_index] = *it;
        task_table[task_index].state = READY;
        task_index++;
    }

    cout<<"Task table"<<endl;
    cout << "ID :: execution time :: period  ::  state  ::  time to dead" << endl;

    for(task_index = 0;task_index<num_of_tasks;task_index++)
    {
        cout << task_table[task_index].id<<"            "<<
       task_table[task_index].exec_time <<"          "<<
       task_table[task_index].period<<"           "<<
       task_table[task_index].state<<"          "<<
       task_table[task_index].time_to_deadline<< endl;
    }

    if(setCurrTaskOnStart()!=true)
    {
        cerr << "setCurrTask in initEDF failed" << endl;
        exit(EXIT_FAILURE);
    }

}

bool Scheduler::setCurrTaskOnStart()
{
    int task_index = 0;
    max_prio = MAX_TASK_PRIO;

    cout << "i'am in setCurrTask" <<endl;

    //!< get new current task
    for(;task_index<num_of_tasks;task_index++)
        if((task_table[task_index].period - task_table[task_index].exec_time) <= max_prio)
        {
            max_prio = task_table[task_index].period - task_table[task_index].exec_time;
            current_task = task_index;
        }

    task_table[current_task].state = CURRENT;
    num_of_ready--;
    cout << "For current Task was choosen "<< task_table[current_task].id<<endl;

// suppose to be an error check var,but currently hardcoded
    return SUCCESS;
}

bool Scheduler::setCurrTask()
{
    int task_index = 0;
    min_deadline = MIN_DEADLINE;

    /**< get new current task */
    for(;task_index<num_of_tasks;task_index++)
        if((task_table[task_index].state == READY) && (task_table[task_index].time_to_deadline <= min_deadline))
        {
            min_deadline = task_table[task_index].time_to_deadline;
            current_task = task_index;
        }

    task_table[current_task].state = CURRENT;
    num_of_ready --;
    //cout << "For current Task was choosen "<< task_table[current_task].id<<endl;

//!< suppose to be an error check var,but currently hardcoded
    return SUCCESS;
}

void Scheduler::mainLoop(Cpu cpu)
{
    //!< run for loop_times*preemption milliseconds
    cout << "i'am in mainLoop "<< endl;
    while(loop_times)
    {
        cout << "----------- Time : "<< current_time << " -----------" << endl;
        switch (BURN_MODE)
        {
        case OFF:
            cout << "CurrTask is "<< task_table[current_task].id<<endl;
            cout << "BURN OFF "<<endl;
            task_table[current_task].time_in_cpu++;

            //!< execution of current task is here
            Sleep(cpu.preemption);
            //!< end

            //!< scheduling tasks updates
            updateTasks();
            if(task_table[current_task].time_in_cpu == task_table[current_task].exec_time)
            {
                reschedule();
            }

            break;

        case ON:
            //!< scheduling tasks updates for BURN_MODE
            //!< then check if there is any task has appeared in ready queue
            cout << "BURN ON "<<endl;
            //!< execution of DUMMY IDLE task
            Sleep(cpu.preemption);
            //!< end

            updateTasks();
            if(num_of_ready!=0)
            {

                reschedule();
                BURN_MODE = OFF;
            }

            break;
        }

        loop_times--;
        current_time+=PREEMPTION;

    }

}

void Scheduler::updateTasks()
{
    //cout << "i'am in updateTasks"<< endl;

    //!< update times in task table
    for(int i = 0;i<num_of_tasks;i++)
    {
        task_table[i].time_to_deadline--;
        if(task_table[i].state == READY && task_table[i].time_to_deadline == 0)
        {
            cerr << "task"<<task_table[i].id<<"################# missed deadline at time:"<< current_time << endl;
            exit(EXIT_FAILURE);
        }
    }

    num_of_ready = 0;

    for(int i = 0;i<num_of_tasks;i++)
    {
        if(task_table[i].state == SUSPENDED && task_table[i].time_to_deadline==0)
        {
            task_table[i].time_to_deadline = task_table[i].period;
            task_table[i].time_in_cpu = 0;
            task_table[i].state = READY;
        }

        if(task_table[i].state == READY)
            num_of_ready ++;
    }

}

bool Scheduler::reschedule()
{

    //!< !!!!!!remove the current task from cpu
    if(task_table[current_task].time_to_deadline == 0)
    {
        //!< insert current task back to ready queue
        task_table[current_task].time_to_deadline = task_table[current_task].period;
        task_table[current_task].time_in_cpu = 0;
        task_table[current_task].state=READY;
        num_of_ready++;

    }
    else
    {
        //!< suspend current task until it's period will get to the end
        task_table[current_task].time_in_cpu = 0;
        if(BURN_MODE == ON)
            task_table[current_task].state=READY;
        else
            task_table[current_task].state=SUSPENDED;
    }

    if(num_of_ready == 0)
    {
        BURN_MODE = ON;
        cout << "all tasks are in SUSP state" << endl;
    }
    else
    {
        if(setCurrTask()==FAILURE)
        {
            cerr << "######################### setCurrTask in resched failed" << endl;
            exit(EXIT_FAILURE);
        }
        //!< context switch is here
    }

    //!< currently hardcoded to true
    return SUCCESS;
}
