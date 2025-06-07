#ifndef APPLICATION_H
#define APPLICATION_H

#include "common.h"

/**
 * @brief Implements application-layer attacks
 * 
 * This module provides HTTP flood, Slowloris, and API exhaustion attacks
 * designed to overwhelm application servers.
 */
class ApplicationAttacks {
public:
    /**
     * @brief Execute an application-layer attack
     * @param url Configuration of the target URL
     * @param params Application-specific parameters
     */
    void runAppLayerAttack(TargetConfig& url, AppParams& params);
    
private:
    void httpFlood(TargetConfig& url, AppParams& params);
    void slowloris(TargetConfig& url, AppParams& params);
    void apiExhaustion(TargetConfig& url, AppParams& params);
};

#endif // APPLICATION_H
