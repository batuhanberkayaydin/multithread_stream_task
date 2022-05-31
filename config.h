/**
 * @file onfig.h
 * @author Berkay
 * @brief Parameter loader header file for processes
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "libraries.h"

class configParams
{

public:
    configParams();
    ~configParams();
    void readParams();
    nlohmann::json jsonData_;

    nlohmann::json getParams();
    
private:


};


#endif // CONFIG_H