#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <stdio.h>
#include "Task.h"

using namespace std;
class Log
{
    public:
        Log();
        virtual ~Log();

    FILE *fd;
    void readLog();
    bool writeToLog(Task t,int time);

    protected:
    private:
};

#endif // LOG_H
