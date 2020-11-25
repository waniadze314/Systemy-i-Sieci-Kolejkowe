#include <iostream>
#include <cmath>
int main(){
int counter = 10000000;
long double sum=0.0;
double lambda = 1.0/12.0;    
long double e_probe, u_probe, prev_u_probe;
long unsigned int prev_seed = (1664525)&0xFFFFFFFFFFFFFFFF, seed;
for(int p=0; p < counter; p++){
    seed = ((prev_seed*1664525)&0xFFFFFFFFFFFFFFFF);
    u_probe = (long double)seed/0xFFFFFFFFFFFFFFFF; //generator jednostajny
    e_probe = -1.0*log((1-((long double)u_probe)))/lambda; //generator eksponencjalny
    prev_seed = seed;
    sum+=e_probe;
}
std::cout<<sum/counter; //obliczenie sredniej wartosci losowanego odestepu

}