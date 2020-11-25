#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>

// #define BUILTIN_RANDOM

long double rand_U(double sigma){
    long double u_probe;
    #ifndef BUILTIN_RANDOM
        static long unsigned int prev_seed = (1664525)&0xFFFFFFFF;
        long unsigned int seed = ((prev_seed*1664525 + 1013904223)&0xFFFFFFFF);
        prev_seed = seed;
        return u_probe = ((long double)seed/0xFFFFFFFF)*sigma;
    #else    
        static bool start = false;
        if(start == false){
            srand(time(0));
            start = true;
        }
        double tmp_probe;
        tmp_probe = (double)rand()/RAND_MAX;
        u_probe = (long double)tmp_probe*sigma;
    return u_probe;

    #endif
}

long double rand_N(double median, double sigma){
    long double n_probe = sqrt(-2*log(rand_U(1.0)))*sin(2*M_PI*(rand_U(1.0)));
    return n_probe*sigma + median;    
}

long double rand_E(double sigma){
    const double lambda = 1.0/sigma;
    long double e_probe;
    e_probe = -1.0*log(1-rand_U(1.0))/lambda; 
    return e_probe;
}

int main(){
    long double time = 0.0;
    int counter = 10000000;
    int previous_client_end_time = 0.0;
    long double Tb = 0.0;
    long double wait_time = 0.0;
    for(int p=0; p < counter; p++){
        time+=rand_E(120.0); //czas pojawienia sie nowego zgloszenia
        if(previous_client_end_time <= time) wait_time = 0.0;
        else wait_time = (previous_client_end_time - time);
        previous_client_end_time = time + wait_time + 60.0; //czas obslugi const
        // previous_client_end_time = time + wait_time + rand_U(120.0); //czas obslugi rand_U
        // previous_client_end_time = time + wait_time + rand_E(60.0); //czas obslugi rand_E
        // previous_client_end_time = time + wait_time + rand_N(60.0, 20.0); //czas obslugi rand_N
        Tb+=wait_time;
    }
    Tb /= (long double)counter;
    std::cout<<std::setprecision(9)<<"Sredni czas przebywania w kolejce: "<<Tb<<"s"<<std::endl;
}
