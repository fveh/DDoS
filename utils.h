#ifndef UTILS_H
#define UTILS_H

#include "common.h"

/**
 * @brief Utility functions for logging, timing, and configuration
 */
class Utils {
public:
    /**
     * @brief Load configuration from file
     * @param filename Path to configuration file
     * @return Config object
     */
    Config loadConfig(std::string filename);
    
    /**
     * @brief Log an event with timestamp and hash
     * @param event Event to log
     */
    void logEvent(Event& event);
    
    /**
     * @brief Get current timestamp
     * @return Current time in milliseconds since epoch
     */
    long getTimestamp();
};

#endif // UTILS_H
