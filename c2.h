#ifndef C2_H
#define C2_H

#include "common.h"

/**
 * @brief Command and Control client functionality
 * 
 * This module handles secure communication with the C2 server,
 * command reception, and session management.
 */
class CommandControl {
public:
    /**
     * @brief Connect to C2 server
     * @param config C2 configuration parameters
     * @return true if connection successful, false otherwise
     */
    bool connectC2(C2Config& config);
    
    /**
     * @brief Send command to C2 server
     * @param cmd Command to send
     */
    void sendCommand(Command& cmd);
};

#endif // C2_H
