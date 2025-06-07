#ifndef OBFUSCATION_H
#define OBFUSCATION_H

#include "common.h"

/**
 * @brief Provides packet obfuscation capabilities
 * 
 * This module handles source IP spoofing, proxy chaining, and payload encryption
 * to conceal attack origins and characteristics.
 */
class Obfuscation {
public:
    /**
     * @brief Obfuscate a packet
     * @param packet Reference to the packet data
     * @param settings Obfuscation settings to apply
     * @return Obfuscated packet
     */
    std::vector<unsigned char> obfuscate(std::vector<unsigned char>& packet, ObfuscationSettings& settings);
};

#endif // OBFUSCATION_H
