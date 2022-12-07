//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <main.hpp>
#include <socket.hpp>

int mail_stat = 0;
int rcpt_user_num = 0;
char from_user[64] = "";
char rcpt_user[MAX_RCPT_USR][30] = {""};

void quit(int sig) {
	std::cerr << "Caught signal (" << sig << "). Mail server shutting down..." << std::endl;
	std::exit(sig);
}

int main(int argc, const char** argv) {
	signal(SIGINT, quit);  //go to MiniWebQuit when Ctrl+C key pressed.
	signal(SIGTERM, quit); //terminal signal

	Socket sock;
	sock.bindSock();
	sock.connectSock();
}