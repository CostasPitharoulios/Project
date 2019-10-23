#include "util.hpp"

// a%b but positive
int mod(int a, int b){
    return (a%b + b) % b;
}
