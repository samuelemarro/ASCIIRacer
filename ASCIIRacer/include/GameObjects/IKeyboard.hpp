#pragma once

#include <vector>

#include "Engine/KeyboardStatus.hpp"
#include "KeyboardPriority.hpp"

class IKeyboard
{
public:
    /**
     * @brief La priorità con cui questo oggetto riceverà le informazioni sulla tastiera.
     * 
     */
    KeyboardPriority priority;

    /**
     * @brief Permette di gestire gli input della tastiera.
     * 
     * @param status Lo stato della tastiera.
     * @return true Continua la gestione dell'input.
     * @return false Interrompi la gestione dell'input.
     */
    virtual bool keyUpdate(KeyboardStatus status) = 0;
};