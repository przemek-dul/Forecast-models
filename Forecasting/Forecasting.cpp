#include <iostream>
#include "Brown.h"
#include "Holt.h"
#include "Winters.h"
#include <string>

int main()
{
    int a{};
 
    Winters B = Winters({ 1,2,3,4}, 0.8, 0.8, 0.8, 2, "additive");
    B.optimization(0.05);
    B.model_info();
    std::cin >> a;

    
}

