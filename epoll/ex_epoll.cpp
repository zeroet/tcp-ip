#include <cstdio>
#include <iostream>
#include <string.h>
#include <fcntl.h>

using namespace std;

#include <sys/unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#define LISTEN_BACKLOG 15	//�Ϲ����� connection�� setup�� client�� connect()�� �����Ͽ� connection request�� �����ϸ� server�� accept()�� �����Ͽ� connection�� �޾Ƶ��Դϴ�. 
							//�׷��� ���� server�� �ٸ� �۾��� ���� ���̸� accept()�� �� �� ���� ���찡 �߻��ϰ� �� ���� connection request�� queue���� �����ϴµ� backlog�� �̿� ���� accept() ���� ���� ������ connection request�� �ִ� �����Դϴ�. 
							//���� 5������ value�� �����ϸ� ���� ���� ū ���� �����ϸ� kernel�� resource�� �Ҹ��մϴ�.
							//������, ���� ������ Ŭ���̾�Ʈ�� �ִ����� �ƴ� ������ ���ٸ��� Ŭ���̾�Ʈ�� �ִ����Դϴ�

int main()
{
    printf("hello from Leviathan_for_Linux!\n");
	int						error_check;

	// ���� ����
	int						server_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		printf("socket() error\n");
		return 0;
	}

	// server fd Non-Blocking Socket���� ����. Edge Trigger �����ϱ� ���� ����. 
	int						flags = fcntl(server_fd, F_GETFL);
	flags					|= O_NONBLOCK;
	if (fcntl(server_fd, F_SETFL, flags) < 0)
	{
		printf("server_fd fcntl() error\n");
		return 0;
	}

	// ���� �ɼ� ����.
	// Option -> SO_REUSEADDR : ������ ������ �ش� ��Ʈ ������ �����ϵ��� ����
	int						option = true;
	error_check				= setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	if (error_check < 0)
	{
		printf("setsockopt() error[%d]\n", error_check);
		close(server_fd);
		return 0;
	}

	// ���� �Ӽ� ����
	struct sockaddr_in		mSockAddr;
	memset(&mSockAddr, 0, sizeof(mSockAddr));
	mSockAddr.sin_family	= AF_INET;
	mSockAddr.sin_port		= htons(1818);
	mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY : ���밡���� ��ī�� IP ����

	// ���� �Ӽ��� ���� fd ����
	error_check				= bind(server_fd, (struct sockaddr*)&mSockAddr, sizeof(mSockAddr));
	if (error_check < 0)
	{
		printf("bind() error[%d]\n", error_check);
		close(server_fd);
		return 0;
	}

	// ���� ����
	if (listen(server_fd, LISTEN_BACKLOG) < 0)
	{
		printf("listen() error\n");
		close(server_fd);
		return 0;
	}

	// Epoll fd ����
	int						epoll_fd = epoll_create(1024);	// size ��ŭ�� Ŀ�� ���� ������ ������ �Լ�
	if (epoll_fd < 0)
	{
		printf("epoll_create() error\n");
		close(server_fd);
		return 0;
	}

	// server fd, epoll�� ����
	// EPOLLET => Edge Trigger ����
	// ����Ʈ���ſ� ���� Ʈ���Ÿ� ���� ���ۿ� �����ϸ�, ���� ������ ���� �� �������� ���� ������ ������ �Ǵ��ϴ� ����
	// ����Ʈ���� �Դϴ�.�� �о �ش� ó���� �Ͽ��� �ϴ����� �� �о����� ���� �̺�Ʈ�� �߻��ϰ�����.���� ����
	// 1000����Ʈ�� �����ߴµ� 600����Ʈ�� �о��ٸ� ���� Ʈ���ſ����� ���� �̺�Ʈ�� �߻���ŵ�ϴ�.�׷���
	// ����Ʈ���ſ����� 600����Ʈ�� �о��� �ϴ����� �� �̻� �̺�Ʈ�� �߻����� �ʽ��ϴ�.�ֳ��ϸ� ���� ������ ��������
	// ���� ���̻��� ���� ��ȭ�� ���� ��������..LT �Ǵ� ET�� ���� �ɼ����� ���� �����մϴ�.
	// ������ select / poll�� ����Ʈ���Ÿ� �����մϴ�.
	struct epoll_event		events;
	events.events			= EPOLLIN | EPOLLET;
	events.data.fd			= server_fd;
	
	/* server events set(read for accept) */
	// epoll_ctl : epoll�� ������ �����ֱ� �ٶ��� FD�� �� FD���� �߻��ϴ� event�� �����ϴ� �������̽�.
	// EPOLL_CTL_ADD : �����ִ� ���ϵ���ũ��Ʈ �߰�
	// EPOLL_CTL_MOD : ���� ���� ����ũ���͸� ����
	// EPOLL_CTL_DEL : ���� ���� ����ũ���͸� ���� ���Ͽ��� ����
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &events) < 0)
	{
		printf("epoll_ctl() error\n");
		close(server_fd);
		close(epoll_fd);
		return 0;
	}

	// epoll wait.
	// �����ִ� fd�鿡 �������� �Ͼ���� ����.
	// ���ǵ��� ����Ʈ�� epoll_events[]�� �迭�� ����.
	// ���ϰ��� ���ǵ��� ����, ������ �ִ� ������ MAX_EVENTS ��ŭ
	// timeout	-1 		--> ������ ���� ���ٸ�(blocking)
	// 			0  		--> ���� ���ٸ��� ����.
	//			0 < n 	--> (n)ms ��ŭ ����
	int						MAX_EVENTS = 1024;
	struct epoll_event		epoll_events[MAX_EVENTS];
	int						event_count;
	int						timeout = -1;

	while (true)
	{
		event_count			= epoll_wait(epoll_fd, epoll_events, MAX_EVENTS, timeout);
		printf("event count[%d]\n", event_count);

		if (event_count < 0)
		{
			printf("epoll_wait() error [%d]\n", event_count);
			return 0;
		}

		for (int i = 0; i < event_count; i++)
		{
			// Accept
			if (epoll_events[i].data.fd == server_fd)
			{
				int			client_fd;
				int			client_len;
				struct sockaddr_in	client_addr;
				
				printf("User Accept\n");
				client_len	= sizeof(client_addr);
				client_fd	= accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t*)&client_len);

				// client fd Non-Blocking Socket���� ����. Edge Trigger �����ϱ� ���� ����. 
				int						flags = fcntl(client_fd, F_GETFL);
				flags |= O_NONBLOCK;
				if (fcntl(client_fd, F_SETFL, flags) < 0)
				{
					printf("client_fd[%d] fcntl() error\n", client_fd);
					return 0;
				}

				if (client_fd < 0)
				{
					printf("accept() error [%d]\n", client_fd);
					continue;
				}

				// Ŭ���̾�Ʈ fd, epoll �� ����
				struct epoll_event	events;
				events.events	= EPOLLIN | EPOLLET;
				events.data.fd	= client_fd;

				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &events) < 0)
				{
					printf("client epoll_ctl() error\n");
					close(client_fd);
					continue;
				}
			}
			else
			{
				// epoll�� ���� �� Ŭ���̾�Ʈ���� send data ó��
				int			str_len;
				int			client_fd = epoll_events[i].data.fd;
				char		data[4096];
				str_len		= read(client_fd, &data, sizeof(data));

				if (str_len == 0)
				{
					// Ŭ���̾�Ʈ ���� ���� ��û
					printf("Client Disconnect [%d]\n", client_fd);
					close(client_fd);
					epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
				}
				else
				{
					// ���� ���� ��û�� �ƴ� ���� ��û�� ���뿡 ���� ó��.
					printf("Recv Data from [%d]\n", client_fd);
				}

			}

			
		}
	}
}
