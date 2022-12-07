#pragma once
#ifndef HPP_SOCKET
#define HPP_SOCKET

#include <config.hpp>
#include <vector>
#include <thread>

#ifndef _WIN32

int __stdcall WSACleanup() {}

#endif

class Socket {
public:
#ifdef _WIN32
	using sockType = SOCKET;
#else
	using sockType = int;
#endif
	Socket() {
#ifdef _WIN32
		WSAData wsaData;
		
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
			std::exit(err("Initialization error"));
		}
#endif
		mainSock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (mainSock == INVALID_SOCKET) {
			int errCode = err("Error creating socket");
			WSACleanup();
			std::exit(errCode);
		}
#	ifdef _DEBUG
		std::cout << "Created socket!" << std::endl;
#	endif
	}
	void bindSock() {
		sockaddr_in service{};
		service.sin_family = AF_INET;
		service.sin_port = htons(PORT);

		inet_pton(AF_INET, IP_ADDR, &service.sin_addr.s_addr);
		if (::bind(mainSock, (sockaddr*)&service, sizeof(service)) == SOCKET_ERROR) {
			int errCode = err("bind() failed");
			::closesocket(mainSock);
			std::exit(errCode);
		}
	}
	void connectSock() {
		if (::listen(mainSock, 1) == SOCKET_ERROR) {
			std::exit(err("Error listening on socket"));
		}

#	ifdef _DEBUG
		std::cout << "Waiting for a client to connect..." << std::endl;
#	endif
		this->__waitForClients();
	}
private:
	static inline int err(const char* msg) {
		int err = errno;
		std::cerr << msg << std::endl;
		std::cerr << "Error code: " << err << std::endl;
		return err;
	}
	sockType mainSock;

	std::vector<std::pair<sockType,std::thread>> clients{};

	void __waitForClients() {
		sockType acceptSocket;
		sockaddr_in clientAddr;
		socklen_t length = sizeof(sockaddr_in);

		while ((acceptSocket = accept(mainSock, (sockaddr*) &clientAddr, (socklen_t*) &length)) > 0) {
			std::cout << "Client connected" << std::endl;
			
			std::thread clientThread = std::thread([](Socket::sockType* sock, sockaddr_in* clientAddr) {
				char buff[1024] = "";
				int bytesRecv;
				while ((bytesRecv = ::recv(*sock, buff, sizeof(buff), 0)) != SOCKET_ERROR) {
					std::cout << "Bytes received: " << bytesRecv << std::endl;
					std::cout << "Received text: " << buff << std::endl;
				}
			}, &acceptSocket, &clientAddr);

			clients.emplace_back(std::make_pair(std::move(acceptSocket), std::move(clientThread))).second.detach();
		}
	}
};


#endif