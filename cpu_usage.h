#ifndef CPU_USAGE_H
#define CPU_USAGE_H


class cpu_usage
{

public:
    static void init();
    static double getCurrentValue();
    static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
};

#endif // CPU_USAGE_H
