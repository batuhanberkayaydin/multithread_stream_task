/**
 * @file workerOne.cpp
 * @author Batuhan
 * @brief Class file for W1 Processing.
 * 
 */
#include "workerOne.h"
#include "config.h"

/**
 * @brief Construct a new worker One::worker One object
 * 
 */
workerOne::workerOne() {
    configParams getConfigParams;
    nlohmann::json w1Params = getConfigParams.getParams(); 

    bufferSize_ = w1Params["bufferSize"];
    rotateChecker_ = w1Params["rotationCheckCount"];
    

    rotationAngle_ = -1 ;
    counter_ = 0 ;

    passSecondFrame_ = false ;
    stopProcess_ = false;
    isFrameProcessed_ = false;
    showCurrentFrame_ = false;
    
}

/**
 * @brief Destroy the worker One::worker One object
 * 
 */
workerOne::~workerOne() { 
    
    stopProcess_ = true;

}

/**
 * @brief Thread init function that starts timer and creates thread.
 * 
 */
void workerOne::threadInit(){
    try {

        workerOneThread_ = std::make_unique<std::thread>(&workerOne::workerOneProcess, this);
        workerOneThread_->detach();
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Show processed images with using OpenCV imshow function.
 * 
 */
void workerOne::show() {
    try {

        if( !showCurrentFrame_ && isFrameProcessed_ ) {

            std::lock_guard<std::mutex> lock(this->finishMutex_);
            cv::cvtColor( currentFrame_, currentFrame_, cv::COLOR_BGR2GRAY );
            cv::namedWindow("Worker1", cv::WINDOW_KEEPRATIO);
            cv::imshow( "Worker1", currentFrame_ );
            showCurrentFrame_ = true;
        }
        else { 

            std::cout << "Frame Skipped!" << std::endl;
        }
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Starts image stream for W1 worker processing. Processing every second images.
 * 
 * @param frame 
 */
void workerOne::stream(cv::Mat frame) {
    try {

        if( !passSecondFrame_ ) {

            std::lock_guard<std::mutex> lock( this-> startMutex_ );
            frameQueue_.push(frame);
            if( frameQueue_.size() > bufferSize_ ) {

                frameQueue_.pop();
            }
        }
        passSecondFrame_ = !passSecondFrame_;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
}

/**
 * @brief Rotate Angle Changes Every 5 Frame according to W1 process.
 * 
 * @param counter 
 */
void workerOne::rotationWayFinder(int counter){
    try {

        if( counter_ > rotateChecker_ ) {

            counter_ = 0;
            rotationAngle_++;

            if (rotationAngle_>2) {

                rotationAngle_ = -1; // No Rotation For cv::rotate
            }
        }
    }
    catch(const std::exception& e) {
        
        std::cerr << e.what() << '\n';
    }    
}

/**
 * @brief Starts worker one process algorithm. Takes every second frame and stores it in queue.
 * Every 5 frames process clockwise rotation.
 * 
 */
void workerOne::workerOneProcess() {

    while( !stopProcess_ ) {
        try {

            if( !frameQueue_.empty()) {

            std::lock_guard<std::mutex> lock_out(this->finishMutex_);
            isFrameProcessed_ = false;
            
            counter_++;
            
            std::lock_guard<std::mutex> lock_in(this-> startMutex_);
            currentFrame_ = frameQueue_.front();
            frameQueue_.pop();

            rotationWayFinder(counter_);     
            cv::rotate( currentFrame_, currentFrame_, rotationAngle_ );
            
            isFrameProcessed_ = true;
            showCurrentFrame_ = false;
        }
        }
        catch(const std::exception& e) {

            std::cerr << e.what() << '\n';
        }
    }
}