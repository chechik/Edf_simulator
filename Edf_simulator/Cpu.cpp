#include "Cpu.h"

Cpu::Cpu()
{
    //!< set predefined value
    preemption = PREEMPTION;
}

Cpu::~Cpu()
{
    //dtor
}

void Cpu::setPreemption(int pre)
{
    if(pre<=0)
    {
        cerr << "Preemption value is not legal! Go home!" << endl;
        exit(EXIT_FAILURE);
    }
    this->preemption = pre;
}

int Cpu::getPreemption()
{
    return this->preemption;
}

void printInfo()
{
    cout << "CPU info:\n preemption:"<<PREEMPTION<< endl;
    return;
}
