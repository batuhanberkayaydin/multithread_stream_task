/**
 * @file workerTwo.cpp
 * @author Batuhan
 * @brief Class file for W2 Processing.
 * 
 */
#include "workerTwo.h"

/**
 * @brief Construct a new worker Two::worker Two object
 * 
 */
workerTwo::workerTwo() {

    timeOutMsec_ = 1000000;
    isFrameProcessed_ = false;
    showCurrentFrame_ = false;
    int labColorCode_ = 44; // COLOR_BGR2Lab
    int hsvColorCode_ = 40; // COLOR_BGR2HSV

    imageCropFactor_ = 0.5;
    
}

/**
 * @brief Destroy the worker Two::worker Two object
 * 
 */
workerTwo::~workerTwo(){ }

/**
 * @brief Thread init function that starts timer and creates thread.
 * 
 */
void workerTwo::threadInit(){

    try {

        auto startProcessTime = std::chrono::high_resolution_clock::now();

        workerTwoThread_ = std::make_unique<std::thread>(&workerTwo::workerStarterWithDelay, this);
        workerTwoThread_->detach();
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Generates Random Numbers that between given integers.
 * 
 * @param numberOne 
 * @param numberTwo 
 * @return int 
 */
int workerTwo::randomNumberGenerator(int numberOne, int numberTwo){
    
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(500, 1500);

    return int(distr(gen));
}

/**
 * @brief Starts image stream for W2 worker processing. Processing 1Fps images.
 * 
 * @param image 
 */
void workerTwo::stream(cv::Mat image) {
    
    try {

        std::unique_lock<std::mutex> workerTwoLocker( this->startMutex_, std::try_to_lock );
        processingImage_ = image.clone();
        isFrameProcessed_ = false;
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Take W2 process in loop for taking true results.
 * 
 */
void workerTwo::workerStarterWithDelay() {

    try {
        while(true) {

        process();
        }
    }
    catch(const std::exception& e) {
        
        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Algorithm displays mirrored image according to check some intensitivity ranges.
 * Returns mirrored image or original image.
 *  
 * @param processingImage_ 
 * @param currFrame_ 
 */
void workerTwo::LogitechFrameProcessingMagic(cv::Mat &processingImage_, cv::Mat &currFrame_){

    try {

        cv::cvtColor(processingImage_, convertedFrame_, cv::COLOR_BGR2Lab);

        imageHeight_ = convertedFrame_.rows;
        imageWidth_ = convertedFrame_.cols * imageCropFactor_;
        leftImage_ = processingImage_(cv::Range(0, imageWidth_), cv::Range(0, imageHeight_ ));

        cv::split(convertedFrame_, imageChannels_);
        cv::split(leftImage_, leftImageChannels_);

        channelSum_ = imageChannels_[0] + imageChannels_[1] + imageChannels_[2];
        frameIntensity_ = channelSum_ / channels_;
        
        cv::minMaxLoc(frameIntensity_, &minimum_, &maximum_);        
            
        leftImageIntensity_ = (leftImageChannels_[0] + leftImageChannels_[1] + leftImageChannels_[2]) / channels_;
        leftImageIntensityMean_ = cv::mean(leftImageIntensity_)[0];
        
        std::lock_guard<std::mutex> lock(this->finishMutex_);
        if(leftImageIntensityMean_[0] > (imageCropFactor_ * (minimum_ + maximum_ ))) {

            cv::flip(processingImage_, currFrame_, cv::ROTATE_180);
            std::cout << "Flipped" << std::endl;
        }
        else {

            currFrame_ = processingImage_;
            std::cout << "Image Not Changed!" << std::endl;
        }
        
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Starts looped process
 * 
 * @return true 
 * @return false 
 */
bool workerTwo::process() {
    try {

        auto startProcessTime = std::chrono::high_resolution_clock::now();
    
        std::lock_guard<std::mutex> lock( this->startMutex_ );
        
        if(!processingImage_.empty() || !isFrameProcessed_)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(randomNumberGenerator(500,1500)));

            LogitechFrameProcessingMagic(processingImage_, currFrame_);
        
            auto afterProcessTime = std::chrono::high_resolution_clock::now();
            auto processTime = std::chrono::duration_cast<std::chrono::microseconds>( afterProcessTime - startProcessTime ).count();
            
            if( (timeOutMsec_ - processTime) > 0 ) {

                std::this_thread::sleep_for(std::chrono::microseconds(timeOutMsec_ - processTime));
            }
            
            isFrameProcessed_ = true;
            showCurrentFrame_ = false;
            
            return true;   

        }
        else {

            return false;
        }    
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
}


/**
 * @brief Show processed images with using OpenCV imshow function.
 * 
 */
void workerTwo::show()
{
    try
    {
        if( !currFrame_.empty()) {

            std::lock_guard<std::mutex> lock(this->finishMutex_);
            cv::namedWindow("Worker2", cv::WINDOW_KEEPRATIO);
            cv::imshow( "Worker2", currFrame_ );
            showCurrentFrame_ = true;
        }
        else {

            std::cout << "Frame cannot showing!" << std::endl;
        }
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
    

}

