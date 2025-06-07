#ifndef VOLUME_H
#define VOLUME_H

#include "common.h"

/**
 * @brief Implements volumetric flooding attacks
 * 
 * This module provides UDP, ICMP, and GRE flooding capabilities
 * designed to saturate network bandwidth.
 */
class VolumeAttacks {
public:
    /**
     * @brief Execute a volumetric attack
     * @param target Configuration of the target
     * @param params Attack parameters (packet count, size, etc.)
     */
    void runVolumeAttack(TargetConfig& target, AttackParams& params);
    
private:
    void udpFlood(TargetConfig& target, AttackParams& params);
    void icmpFlood(TargetConfig& target, AttackParams& params);
    void greFlood(TargetConfig& target, AttackParams& params);
};

#endif // VOLUME_H
