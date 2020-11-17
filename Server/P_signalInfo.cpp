#include "P_signalInfo.h"

SignalInfo::SignalInfo() : signal(0),order_num(0){}

void SignalInfo::set_signal(int signal)
{
    this->signal = signal;
}

void SignalInfo::set_order_num(int order_num)
{
    this->order_num = order_num;
}

int SignalInfo::get_signal() const
{
    return signal;
}

int SignalInfo::get_order_num() const
{
    return order_num;
}