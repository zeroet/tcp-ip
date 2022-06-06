## socket function

---

```
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```
domain : 소켓이 사용할 프로토콜 체계 Protocol Family 전달  
type : 소켓의 데이터 전송방식에 대한 정보 전달  
protocol : 두 컴퓨터간 통신에 사용되는 프로토콜 정보 전달  


* Protocol Family  
  - 소켓 통신에 사용하는 프로토콜의 부류정보 "프로토콜 체계"  
  - PF_INET IPv4 인터넷 프로토콜 체계  

* TYPE  
  - 연결 지향형 소켓 (SOCK_STREAM) : 1:1 소켓연결, 신뢰성있는 순차적인 바이트 기반의 연결지향 데이터 전송방식
    - 중간에 데이터가 소멸되지 않고 목적지로 전송  
    - 전송 순서대로 데이터가 수신
    - 전손되는 데이터의 경계(Bounday) 존재 하지 않음  

  - 비연결 지향형 소켓(SOCK_DGRAM) : 신뢰성과 순차적 데이터 전송을 보장하지않는, 고속의 데이터 전송 목적 소켓
    - 순서에 상관없이 빠른전송
    - 데이터 손실 우려, 파손우려
    - 데이터의 경계가 존재
    - 한번에 전송가능 데이터의 크기 제한

* Protocol
  - 실제 소켓이 사용할 최종 프로토콜의 정보는 socket 함수의 세번째 인자를 통해 전달 ( 첫번째 인자를 통해서 지정한 프로토콜 체계의 범위 내에서 )
  - 하나의 프로토콜 체계 안에 데이터의 전송방식이 동일한 프로토콜이 둘 이상 존재하는 경우
    ```
    int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int udp_socket = socket(PF_INET, SOCK_DGRAM, IPROTO_UDP);
    ```
  
