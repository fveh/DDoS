#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "common.h"

/**
 * @brief Implements protocol-layer attacks
 * 
 * This module provides SYN flood, RST attack, and fragmentation attack
 * capabilities designed to exploit protocol vulnerabilities.
 */
class ProtocolAttacks {
public:
    /**
     * @brief Execute a protocol-level attack
     * @param target Configuration of the target
     * @param params Protocol-specific parameters
     */
    void runProtocolAttack(TargetConfig& target, ProtocolParams& params);
    
private:
    void synFlood(TargetConfig& target, ProtocolParams& params);
    void rstAttack(TargetConfig& target, ProtocolParams& params);
    void fragmentationAttack(TargetConfig& target, ProtocolParams& params);
};

#endif // PROTOCOL_H
