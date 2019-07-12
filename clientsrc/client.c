#include "head.h"

int main(int argc,char *argv[]) // ./client 同桌的IP 50000 
{
	if(argc != 2)
	{
		printf("please ./project port\n");
		return -1;
	}
	char bmp[10][10];
	strcpy(bmp[0],"1.bmp");
	strcpy(bmp[1],"2.bmp");
	strcpy(bmp[2],"3.bmp");
	strcpy(bmp[3],"4.bmp");
	strcpy(bmp[4],"5.bmp");
	strcpy(bmp[5],"6.bmp");
	strcpy(bmp[6],"7.bmp");
	//1. 创建一个TCP协议的未连接套接字
	int sockfd = socket(AF_INET,SOCK_STREAM,0); //sockfd是未连接套接字
	//2. 准备对方的IP地址，端口号
	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr,len);
	
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&srvaddr.sin_addr);
	
	//3. 发起连接
	connect(sockfd,(struct sockaddr *)&srvaddr,len);

	char buf[50];
	int n;
	show_bmp(bmp[0]);
	sleep(1);
	char rcvbuf[10];
	char adbuf[10];
	int ret;
	while(1)
	{
		printf("****************************************************************************\n");
		printf("1.User   2.Query    3.Quicky query     4.Administrators       5. closeserver       6.exit\n");
		printf("****************************************************************************\n");
		show_bmp(bmp[3]);
		//主界面功能选择
		n = jiemian_touch();
		sprintf(buf, "%d",n);
		send(sockfd,buf,strlen(buf),0);
		switch(n)
		{
			case 1:	
					{//用户界面
						while(1)
						{	
							show_bmp(bmp[4]);
							printf("****************************************************************************\n");
							printf("1.registe   2.sign_in     3.searching_password          4.exit              \n");
							printf("****************************************************************************\n");
							
							n=denglu_jiemian_touch();
							sprintf(buf, "%d",n);
							send(sockfd,buf,strlen(buf),0);
							bzero(rcvbuf,10);
							if(n == 2)  //登录成功
							{
								recv(sockfd,rcvbuf,10,0);
								if(strncmp(rcvbuf,"yes",3)==0)
								{
									//显示用户功能界面
									printf("****************************************************************************\n");
									printf("1.buy_ticket    2.query_buy_ticket                                          \n");
									printf("3.exit_ticket   4.change_ticket                                             \n");
									printf("5.exit          6.invest_money       7.modify_mima                          \n");
									printf("****************************************************************************\n");
									show_bmp(bmp[5]);
									while(1)
									{
										n=user_jiemian_touch();
										sprintf(buf, "%d",n);
										send(sockfd,buf,strlen(buf),0);
										if(n==5)
										{
											show_bmp(bmp[4]);
											break;
										}
									
									}
								}
								if(strncmp(rcvbuf,"no",2)==0) //登录失败
								{
									break; 
								}
							}
							if(n == 4) //退出
								break;
						}	
						break;
					}
				
			case 2:
					{
						//查询
						sprintf(buf, "%d",n);
						send(sockfd,buf,strlen(buf),0);
						break;
					}
			case 3:
					{
						//快速查询
						sprintf(buf, "%d",n);
						send(sockfd,buf,strlen(buf),0);
						break;
					}
				
			case 4:
					{
						//登录管理员
						usleep(500000);
						bzero(adbuf,10);
						recv(sockfd,adbuf,10,0);
						printf("adbuf = %s\n",adbuf);
						if(strncmp(adbuf,"yes",3)==0)  //成功
						{
							printf("*******************************************************************\n");
							printf("1.Increase flights    2.Delete flights   3.Change Password   4.exit\n");
							printf("*******************************************************************\n");
							show_bmp(bmp[6]);
							while(1)
							{
								n=ad_jiemian_touch();
								sprintf(buf, "%d",n);
								send(sockfd,buf,strlen(buf),0);	
								if(n == 4)
									break;
							}
						}
						if(strncmp(adbuf,"no",2)==0)  //失败
						{
							break;
						}
						break;
					}
				
			case 5:     //退出客户端
				{		
					show_end();	
					return;
				}
			case 6:     //退出
				{	
					show_end();			
					return;
				}
			default:
				break;
		}
		
	}
	
	close(sockfd);
}
	