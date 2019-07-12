#include "head.h"
#include "kernel_list.h"


int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("please ./project port\n");
		return -1;
	}
	/**************初始化服务端**************/
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	int connfd,fd;
	//2.本地IP地址绑定到端口号
	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr,len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(atoi(argv[1]));
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sockfd,(struct sockaddr*)&srvaddr,len);
	
	//3.设置监听套接字
	listen(sockfd,5);
	//int sockfd = *(int *)arg;
	//4.不断的接收对方的链接
	struct sockaddr_in cliaddr;  /*用于存储连接对方的地址信息*/
	//socklen_t len = sizeof(cliaddr);
	bzero(&cliaddr,len); 
	
	char bmp[10][10];
	strcpy(bmp[0],"1.bmp");
	strcpy(bmp[1],"2.bmp");
	strcpy(bmp[2],"3.bmp");
	strcpy(bmp[3],"4.bmp");
	//航班信息链表
	struct flight_information *head=NULL;
	//初始化头节点
	head=init_head(head);
	if(head==NULL)
	{
		printf("Initial head node failed!");
	}
	//注册用户信息链表
	struct user_information *head2=NULL;
	//初始化用户头节点
	head2=init_user_head(head2);
	if(head2==NULL)
	{
		printf("Initial user head node failed!");
	}

	show_bmp(bmp[0]);
	sleep(1);
	int flag=0;
	int modify;
	modify=0;
	int n;
	char buf[10];
	printf("Do you want to start the server? 0:no 1:yes\n");
	scanf("%d",&flag);
	if(flag == 1)
	{
		printf("Waiting new connection....\n");
		connfd = accept(sockfd,(struct sockaddr*)&cliaddr,&len);
		if(connfd > 0)
		{
			printf("\nnew connection:%s\n",(char *)inet_ntoa(cliaddr.sin_addr));
		}
		
	}
	
	while(1)
	{
		write_message(head,modify);
		modify=1;
		show_bmp(bmp[3]);
		
		if(flag == 0)
		{
			n = jiemian_touch();
		}			
		if(flag == 1)
		{
			bzero(buf,10);
			recv(connfd,buf,10,0);
			n = atoi(buf); 
		}
		
		switch(n)
		{
			case 1:
				user(head2,head,bmp[2],flag,connfd);
				break;
			case 2:
				query(head);
				break;
			case 3:
				quicky_query(head);
				break;
			case 4:
				administrators(head,bmp[1],flag,connfd);
				break;
			case 5: 
				{
					printf("close server!");
					close(sockfd);
					close(connfd);
					flag = 0;
					break;
				}
			case 6:
			{
				show_end();
				close(sockfd);
				close(connfd);			
				return;
			}
			default:
				break;
		}
	}
	
	
	return 0;
}