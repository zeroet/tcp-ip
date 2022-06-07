
IP : 데이터를 송수신 할 목적으로, 컴퓨터에 부여하는 값
PORT: 프로그램상에서 생성되는 소켓을 구분 할 목적으로, 소켓에 부여하는 번호

# IP
- IPv4 : 4바이트 주소체계
- IPv6 : 16바이트 주소체계

IPv4  :  4바이트 IP주소 네트워크 주소 // 호스트 주소로 나누어진다 형태에 따라 ABCD클래스 분류  
     네트워크 주소를 통해 해당 라우터//스위치에 데이터를 전송하고, 호스트 주소에 맞는 호스트에 데이터를 전송  

# PORT
H/W 단의 NIC에서 데이터를 받아 운영체제 단에서 PORT번호를 활용해 알맞은 프로세스에 데이터를 전송한다.  
포트번호는 16비트 단위로 표현되어있다 0~1023까지는 예약되어있다.  
하나의 운영체제 내에서 동일한 PORT번호를 둘이상 할당 불가능 (TCP / UDP는  port번호를 공유하지 않기 때문에 상관없음)  

응용프로그램상에서 IP주소와 PORT번호를 처리하기 위한 구조체가 미리 정의되어있다.
```
struct sockaddr {        // 총 20바이트.
    u_short    sa_family // 주소 패밀리 AF / PF
    char       sa_dat[14] // 기타정보 (ip주소 port 번호등)
```
=> 서버 및 클라이언트에서 주소 정보를 저장하기 위해 사용되는 구조체

```
struct sockaddr_in
{
  sa_family_t      sin_family; // 주소체계(Addres Family)
  uint16_t        sin_port; // 16비트 TCP/UDP PORT번호
  struct in_addr   sin_addr; // 32비트 IP주소
  char           sin_zero[9]; // 사용x
}
```
=> 인터넷 주소 체계 전용 구조체 주소 입력 정보시 편의를 위해 존재하는 구조체
```
struct in_addr
{
  in_addr_t    s_addr; // 32비트 IPv4 인터넷주소
}
```
- sin_family : AF_INET(ipv4) // AF_INET6(ipv6) // AF_LOCAL(local unix protocol)
- sin_port : 16비트의 PORT번호를 저장한다 **네트워크 바이트 순서** 로 저장해야한다
- sin_addr : 32비트의 IP주소정보를 저장한다 **네트워크 바이트 순서** 로 저장해야한다 unit32_t 32비트 정수자료형
- sin_zero : sockaddr_in 의 크기를 구조체 sockaddr 과 일치 시키기위해 삽입된 의미없는 멤버. !반드시 0으로 채워야한다. **sa_data[14]바이트를 맞추기위한 값**

# Byte Order && Network byte order

Network Byte Order = Big-endian (0x1234)  
h(host) to n(network) s(short)//l(long)
Change short type date host to network  
Short = 2byte Port number  
Long = 4byte IP number

