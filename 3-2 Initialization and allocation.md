# IP주소 to 네트워크 바이트순서 정수 변환

IP주소 "201.211.214.36"을 big endian 32비트 정수값으로 변환하는 함수  

```
#include <arpa/inet.h>

in_addr_t inet_addr(const char* string);  
```
=> 성공시 big endian 32비트 정수값, 실패시 INADDR_NONE  
정수 최대크기 255를 넘어 갈 경우 오류 반환

```
#include <arpa/inet.h>

int inet_aton(const char* string, struct in_addr* addr);
```
=> 성공시 1 실패시 0
string : 변환할 IP 주소를 담고있는 문자열 주소값
addr : 변환된 정보를 저장할 in_addr구조체 변수의 주소값

**inet_addr 함수의 경우 sockaddr_in에 선언된 in_addr 구조체 변수에 대입하는 과정을 거쳐야하지만, inet_aton의 경우 대입과정이 필요없다.**  


