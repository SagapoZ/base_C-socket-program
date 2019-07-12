#include "head.h"


/*使用多路复用,让键盘屏幕同时工作*/
/*
	功能: 那个文件描述符在里面就返回那个
*/

int fd_select(int fd1,int fd2)
{
	int maxfd = fd1 > fd2? fd1 : fd2;
	fd_set rset;
	
	FD_ZERO(&rset);
	FD_SET(fd2,&rset);
	FD_SET(fd1,&rset);
	
	//无限等待
	select(maxfd+1,&rset, NULL,NULL,NULL);
	//判断STDIN_FILENO是否在,在则发消息
	if(FD_ISSET(fd1,&rset))
	{
		return 1;
	}
	if(FD_ISSET(fd2,&rset))   //如果触摸屏在
	{
		return 2;
	}
}



