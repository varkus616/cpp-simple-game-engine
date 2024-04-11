#pragma once
#include "ComponentBase.hpp"
#include "../AI.hpp" 

struct AIComponent : ComponentBase
{
    AI ai; 
    void clear() {
        ComponentBase::clear();
        ai.deactivate();
    
    }
};
