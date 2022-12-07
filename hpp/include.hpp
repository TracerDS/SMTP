#ifndef HPP_INCLUDE
#define HPP_INCLUDE

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <fcntl.h>

#ifdef __linux__
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <dirent.h>
#else
#	define WIN32_LEAN_AND_MEAN
#	include <ws2tcpip.h>
#	include <WinSock2.h>
#	include <tchar.h>
#	pragma comment(lib, "WS2_32.lib")
#endif

#endif