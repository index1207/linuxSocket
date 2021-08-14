#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

namespace net {
	using SOCKET = int;

	class Socket {
	public:
			Socket(void) : s(0), family(AF_INET), proto(IPPROTO_TCP) {
				memset(&addr, 0, sizeof(addr)); 
			}

			Socket(u_short af, u_short _proto) : s(0), family(AF_INET), proto(IPPROTO_TCP) {
				memset(&addr, 0, sizeof(addr));
				if (proto == IPPROTO_TCP) {
					s = socket(family, SOCK_STREAM, proto);
				}
				else if (proto == IPPROTO_UDP) {
					s = socket(family, SOCK_DGRAM, proto);
				}
				addr.sin_family = family;
			}
			Socket(const Socket& s) = delete;

			~Socket() {
			close(s);
		}
	public:
		void setAddr(const char* addr) {
			inet_pton(family, addr, &this->addr.sin_addr);
			}
		void setPort(u_short _port) {
			addr.sin_port = htons(_port);
		}

		u_short getPort(void) const {
			return ntohs(addr.sin_port);
		}

		void makeSocket(void) {
			s = socket(family, SOCK_DGRAM, proto);
		}
	public:
		inline operator SOCKET&() {
				return s;
		}
		void operator=(const SOCKET& sock) { 
			this->s = sock; 
		}
		sockaddr_in addr;
	private:
		u_short proto;
		u_short family;
		SOCKET s;
	};
}

