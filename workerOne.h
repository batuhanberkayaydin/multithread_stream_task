/**
 * @file workerOne.h
 * @author Batuhan
 * @brief Header file for W1 Processing.
 * 
 */
#ifndef WORKER_ONE_H
#define WORKER_ONE_H

#include "libraries.h"

class workerOne {

public:

    workerOne();
    ~workerOne();

    void show();    
    void threadInit();
    void stream(cv::Mat frame);

private:

    void workerOneProcess();
    void rotationWayFinder(int counter);

    int bufferSize_;
    int rotationAngle_;
    int counter_;
    int rotateChecker_;
    
    void rotateImagesWithCounter();
    
    bool stopProcess_;
    bool passSecondFrame_;
    bool isFrameProcessed_;
    bool showCurrentFrame_;

    cv::Mat currentFrame_;
    std::queue <cv::Mat> frameQueue_;

    std::mutex startMutex_;
    std::mutex finishMutex_;
    std::unique_ptr<std::thread> workerOneThread_;        
};

#endif // WORKER_ONE_H