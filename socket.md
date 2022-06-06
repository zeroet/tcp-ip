## socket functions

---

```
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```
domain : 소켓이 사용할 프로토콜 체계 Protocol Family 전달
type : 소켓의 데이터 전송방식에 대한 정보 전달
int : 두 컴퓨터간 통신에 사용되는 프로토콜 정보 전달

Protocol Family
소켓 통신에 사용하는 프로토콜의 부류정보 "프로토콜 체계"
PF_INET IPv4 인터넷 프로토콜 체계

TYPE
연결 지향형 소켓 (SOCK_STREAM)
