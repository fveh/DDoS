#ifndef AMPLIFICATION_H
#define AMPLIFICATION_H

#include "common.h"

/**
 * @brief Implements amplification attacks
 * 
 * This module provides DNS, NTP, SSDP, and Memcached amplification attacks
 * that exploit misconfigured services to generate massive traffic.
 */
class AmplificationAttacks {
public:
    /**
     * @brief Execute an amplification attack
     * @param config Amplification configuration
     */
    void runAmplificationAttack(AmplificationConfig& config);
    
private:
    void dnsAmplification(AmplificationConfig& config);
    void ntpAmplification(AmplificationConfig& config);
    void ssdpAmplification(AmplificationConfig& config);
    void memcachedAmplification(AmplificationConfig& config);
};

#endif // AMPLIFICATION_H
