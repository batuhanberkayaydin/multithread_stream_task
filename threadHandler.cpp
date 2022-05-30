/**
 * @file threadHandler.cpp
 * @author Batuhan
 * @brief Threading Class File
 * @version 0.1
 * @date 2022-05-24
 * 
 */

#include "threadHandler.h"
#include "workerOne.h"
#include "workerTwo.h"

/**
 * @brief Construct a new thread Invoker::thread Invoker object
 * 
 */
threadHandler::threadHandler() {
    
}

/**
 * @brief Destroy the thread Invoker::thread Invoker object
 * 
 */
threadHandler::~threadHandler() { }


void threadHandler::startWorkers(){
    
    try {

        cv::VideoCapture capture(0);

        if (!capture.isOpened()) {

            std::cout << "Camera Source Not Found!";
        }
        
        workerOne w1;
        w1.threadInit();
        workerTwo w2;
        w2.threadInit();

        capture >> frame_;
        // Could be used clone() but deep copy is faster than clone.
        cv::Mat deepCopied(frame_.size(),frame_.type());

        while(true)
        {
            capture >> frame_;
            frame_.copyTo(deepCopied);

            w1.stream(frame_);
            w1.show();
            
            w2.stream(deepCopied);
            w2.show();

            cv::waitKey(1);
        }    
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
}
