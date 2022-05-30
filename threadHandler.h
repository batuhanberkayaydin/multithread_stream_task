/**
 * @file threadHandler.h
 * @author Batuhan
 * @brief Threading Header File
 * @version 0.1
 * @date 2022-05-24
 * 
 */

#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

#include "libraries.h"

class threadHandler {

public:
    threadHandler();
    ~threadHandler();

    void startWorkers();
    
private:

    cv::Mat frame_;


};


#endif // THREAD_HANDLER_H