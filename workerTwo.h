/**
 * @file workerTwo.h
 * @author Batuhan
 * @brief Header file for W2 Processing.
 * 
 */

#ifndef WORKER_TWO_H
#define WORKER_TWO_H

#include "libraries.h"


class workerTwo {

public:

    workerTwo();
    ~workerTwo();

    void show();
    void threadInit();
    void stream(cv::Mat image);

private:

    bool process();
    void workerStarterWithDelay();
    void LogitechFrameProcessingMagic(cv::Mat &processingImage_, cv::Mat &currFrame_);
    void LogitechFrameProcessingMagic2(cv::Mat image);
    int randomNumberGenerator(int numberOne, int numberTwo);

    int imageHeight_;
    int imageWidth_;
    int channels_ = 3;
    double imageCropFactor_ ;
    int  timeOutMsec_;
    bool isFrameProcessed_;
    bool showCurrentFrame_;

    std::mutex startMutex_;
    std::mutex finishMutex_;
    std::unique_ptr<std::thread> workerTwoThread_;

    cv::Mat leftImage_;
    cv::Mat currFrame_;
    cv::Mat channelSum_;
    cv::Mat leftImageSum_;
    cv::Mat frameIntensity_;
    cv::Mat convertedFrame_;
    cv::Mat processingImage_;
    cv::Mat imageChannels_[3];
    cv::Mat leftImageIntensity_;
    cv::Mat leftImageChannels_[3];  

    cv::Scalar leftImageIntensityMean_;

    double minimum_;
    double maximum_;
    double intensityVal_;

    int randomStart_;
    int randomEnd_;
    
};

#endif // WORKER_TWO_H