#include "utils.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <openssl/sha.h>
#include <wincrypt.h>

Config Utils::loadConfig(std::string filename) {
    Config config;
    std::ifstream file(filename);
    if (file) {
        // Parse configuration from file
        // ...
    }
    return config;
}

void Utils::logEvent(Event& event) {
    event.timestamp = getTimestamp();
    
    // Compute SHA-256 hash of the message
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, event.message.c_str(), event.message.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    event.hash = ss.str();
    
    // Write to log file
    std::ofstream logfile("session.log", std::ios::app);
    if (logfile) {
        logfile << "[" << event.timestamp << "] " 
               << event.message << " | HASH: " << event.hash << "\n";
    }
}

long Utils::getTimestamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}
