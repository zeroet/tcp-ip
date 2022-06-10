```
#include <sys/socket.h>
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
```
=> 성공시 0  || -1   
sockfd : ip /port 를 할당할 소켓의 fd  
myaddr : 할당하고자 하는 주소정보를 지니는 구조체 변수의 주소값
addrlen : 두 번재 인자로 전달된 구조체 변수의 길이정보

- 서버 초기화 과정
```
int serv_sock;
struct sockaddr_in serv_addr;
char *serv_port = "9190";

//create socket
serv_sock = socket(PF_INET, SOCK_STREAM, 0);

//init addr info
memset(&serv_addr, 0, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(atoi(serv_port));

//allocate addr info
bind(serv_sock, (struct sockaddr&)&serv_addr, sizeof(serv_addr));
```
서버 프로그램 초기화 국룰
