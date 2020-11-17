#pragma once

class SignalInfo
{
    private:
        int signal;
        int order_num;
    public:
        SignalInfo();
        void set_signal(int signal);
        void set_order_num(int order_num);
        int get_signal() const;
        int get_order_num() const;  
};