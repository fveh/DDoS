#include "obfuscation.h"
#include <random>
#include <openssl/evp.h>

std::vector<unsigned char> Obfuscation::obfuscate(std::vector<unsigned char>& packet, ObfuscationSettings& settings) {
    std::vector<unsigned char> obfuscated = packet;
    
    // IP spoofing
    if (settings.spoof_source_ip) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 254);
        
        // Generate random IP (in position 12-15 of IP header)
        obfuscated[12] = distrib(gen);
        obfuscated[13] = distrib(gen);
        obfuscated[14] = distrib(gen);
        obfuscated[15] = distrib(gen);
    }
    
    // Payload encryption
    if (!settings.encryption_key.empty()) {
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        const EVP_CIPHER* cipher = EVP_aes_256_cbc();
        unsigned char iv[16];
        RAND_bytes(iv, 16);
        
        // Encrypt the payload portion (assuming IP header is 20 bytes)
        int out_len = 0;
        std::vector<unsigned char> ciphertext(packet.size() + 16);
        
        EVP_EncryptInit_ex(ctx, cipher, NULL, 
                          (const unsigned char*)settings.encryption_key.c_str(), iv);
        EVP_EncryptUpdate(ctx, ciphertext.data(), &out_len, 
                         packet.data() + 20, packet.size() - 20);
        
        // Replace payload with encrypted version
        std::copy(ciphertext.begin(), ciphertext.begin() + out_len, 
                 obfuscated.begin() + 20);
    }
    
    return obfuscated;
}
