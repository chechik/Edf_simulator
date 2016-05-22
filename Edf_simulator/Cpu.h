#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <cstdlib>
using namespace std;

#define PREEMPTION 100  //!< preemption in ms

class Cpu
{
public:
	Cpu();
	virtual ~Cpu();

	int preemption;
	///set preemption for chosen CPU
	void setPreemption(int pre);
	///get current preemption of the system
	int getPreemption();
	///show CPU settings
	void printInfo();

protected:
private:
};

#endif // CPU_H
