#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include "Task.h"
#include "Cpu.h"
#include "Scheduler.h"

using namespace std;

void isSchedulable(list<Task> lst);

int main()
{
	list<Task> TL;
	int num_of_tasks;

	cout << "EDF simulator for real time system scheduling!" << endl;
	cout << "Enter number of tasks" << endl;
	cin >> num_of_tasks;

	if (num_of_tasks <= 0)
	{
		cerr << "Go home..." << endl;
		exit(EXIT_FAILURE);
	}

	if (num_of_tasks == 1)
	{
		cout << "Are you kidding? You should use another scheduling policy...So go home..." << endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i<num_of_tasks; i++)
	{
		Task t(i, -1, -1);
		cout << "Enter execution time and period for T" << i << endl;
		cin >> t.exec_time >> t.period;
		t.time_to_deadline = t.period;
		if (!t.isLegal())
		{
			cerr << "task " << i << " is illegal!" << endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			cout << "task " << t.id << " created!" << endl;
			TL.push_back(t);
		}
	}

	isSchedulable(TL);

	//!< set preemption of 1000ms.
	//!< I mean each rescheduling will occur after 1000ms
	Cpu cpu;
	cpu.setPreemption(PREEMPTION);

	Scheduler sched;
	sched.initializeEDF(TL, num_of_tasks);
	sched.mainLoop(cpu);

	cout << sched.current_time << " " << sched.loop_times << endl;

	return 0;
}

void isSchedulable(list<Task> lst)
{
	float utilization_rate = 0;

	for (list<Task>::iterator it = lst.begin(); it != lst.end(); ++it)
	{
		Task& temp = *it;
		utilization_rate += (float)temp.exec_time / temp.period;
	}

	if (utilization_rate>1)
	{
		cout << "Current set of tasks is NOT schedulable.\nUtilization factor is: " << utilization_rate << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "Current set of tasks is schedulable.\nUtilization factor is: " << utilization_rate << endl;
}
