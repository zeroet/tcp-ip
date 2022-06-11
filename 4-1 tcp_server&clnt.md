# listen()  연결요청 대기상태

bind () 함수를 통해서 소켓에 주소를 할당한 이후에, listen 함수를 호출하여 클라이언트의 연결 요청을 받을 수 있는 상태로 전환.  
**listen() 함수 호출 이전에 클라이언트의 connect 함수 호출은 에러** 

```
#include <sys/socket.h>
int listen(int sock, int backlog);
```
sock : 연결요청 대기상태에 두고자 하는 소켓의 FD 전달  - 이 FD가 서버소켓(리스닝 소켓)이 된다.  
backlog : 연결요청 대기 큐의 크기정보 전달, 5가 전달되면 큐의 크기가 5가 되어 클라이언트의 요청을 5개까지 대기시킬 수 있다.(?)  
