/**
 * @file config.cpp
 * @author Berkay
 * @brief Parameter loader class for processes
 *
 */

#include "config.h"


/**
 * @brief Construct a new uvss Params::uvss Params object
 */
configParams::configParams() {

    try {

        std::ifstream file("config.json");
        jsonData_ = nlohmann::json::parse(file);
    }
    catch(const std::exception& e) {

        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief Destroy the uvss Params::uvss Params object
 * 
 */
configParams::~configParams() { 
    jsonData_.clear();
}


nlohmann::json configParams::getParams() {
    return jsonData_;
}