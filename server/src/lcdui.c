#include "head.h"
#include "kernel_list.h"

 //界面功能触摸
int jiemian_touch()
{
	int n,t;
	//1.访问触摸屏设备
	int fd_event=open("/dev/input/event0",O_RDWR);
	if(fd_event==-1)
		printf("K;LKL!\n");
	
	//2.访问数据
	struct input_event buf;
	bzero(&buf, sizeof(buf));
	
	int x,y;
	
	while(1)
	{
		t = fd_select(STDIN_FILENO,fd_event);
		if(t == 2)
		{
			read(fd_event,&buf,sizeof(buf));
			if(buf.type==EV_ABS&&buf.code==ABS_X)
			{
				x=buf.value;
			}
			else if(buf.type==EV_ABS&&buf.code==ABS_Y)
			{
				y=buf.value;
			}
			else if(buf.type == EV_KEY && buf.code == BTN_TOUCH  && buf.value == 0)
			{
				if(x<230&&y<240)
					return 1;
				if(245<=x&&x<=480&&y<240)
					return 2;
				if(x>490&&y<240)
					return 3;
				if(x<230&&y>240)
					return 4;
				if(240<=x&&x<480&&y>240)
					return 5;
				if (x>490 && y>240)
					return 6;
			}
		}
		else
		{
			scanf("%d",&n);
			return n;
		}
	}

}

//登录界面功能触摸
int denglu_jiemian_touch()
{
	int n,t;
	//1.访问触摸屏设备
	int fd_event=open("/dev/input/event0",O_RDWR);
	if(fd_event==-1)
		printf("K;LKL!\n");
	
	//2.访问数据
	struct input_event buf;
	bzero(&buf, sizeof(buf));
	
	int x,y;
	
	while(1)
	{
		//如果lcd屏幕有操作就响应lcd
		t=fd_select(STDIN_FILENO,fd_event);
		if(t==2)
		{
			read(fd_event,&buf,sizeof(buf));
			if(buf.type==EV_ABS&&buf.code==ABS_X)
			{
				x=buf.value;
			}
			else if(buf.type==EV_ABS&&buf.code==ABS_Y)
			{
				y=buf.value;
			}
			else if(buf.type == EV_KEY && buf.code == BTN_TOUCH  && buf.value == 0)
			{
				if(x<200&&100<y)
					return 1;
				if(200<=x&&x<400&&100<y)
					return 2;
				if(400<=x&&x<600&&100<y)
					return 3;
				if(600<=x&&x<800&&100<y)
					return 4;
			}
		}
		else
		{
			scanf("%d",&n);
			return n;
		}	
	}
}

//用户功能界面触控
int user_jiemian_touch()
{
	int n,t;
	//1.访问触摸屏设备
	int fd_event=open("/dev/input/event0",O_RDWR);
	if(fd_event==-1)
		printf("K;LKL!\n");
	
	//2.访问数据
	struct input_event buf;
	bzero(&buf, sizeof(buf));
	
	int x,y;
	
	while(1)
	{
		//如果lcd屏幕有操作就响应lcd
		t = fd_select(STDIN_FILENO,fd_event);
		if(t == 2)
		{
			read(fd_event,&buf,sizeof(buf));
			if(buf.type==EV_ABS&&buf.code==ABS_X)
			{
				x=buf.value;
			}
			else if(buf.type==EV_ABS&&buf.code==ABS_Y)
			{
				y=buf.value;
			}
			else if(buf.type == EV_KEY && buf.code == BTN_TOUCH  && buf.value == 0)
			{
				if(x<200&&60<=y&&y<270)
					return 1;
				if(200<=x&&x<400&&60<=y&&y<270)
					return 2;
				if(400<=x&&x<600&&60<=y&&y<270)
					return 3;
				if(600<=x&&x<800&&60<=y&&y<270)
					return 4;
				if(x<200&&270<=y)
					return 5;
				if(200<=x&&x<400&&270<=y)
					return 6;
				if(600<=x&&x<800&&270<=y)
					return 7;
			}
		}
		
		else
		{
			scanf("%d",&n);
			return n;
		}
	}
	
}

//管理员功能界面触控
int ad_jiemian_touch()
{
	int n,t;
	//1.访问触摸屏设备
	int fd_event=open("/dev/input/event0",O_RDWR);
	if(fd_event==-1)
		printf("K;LKL!\n");
	
	//2.访问数据
	struct input_event buf;
	bzero(&buf, sizeof(buf));
	
	int x,y;
	
	while(1)
	{
		//如果lcd屏幕有操作就响应lcd
		t = fd_select(STDIN_FILENO,fd_event);
		if(t == 2)
		{
			read(fd_event,&buf,sizeof(buf));
			if(buf.type==EV_ABS&&buf.code==ABS_X)
			{
				x=buf.value;
			}
			else if(buf.type==EV_ABS&&buf.code==ABS_Y)
			{
				y=buf.value;
			}
			else if(buf.type == EV_KEY && buf.code == BTN_TOUCH  && buf.value == 0)
			{
				if(x<200&&100<y)
					return 1;
				if(200<=x&&x<400&&100<y)
					return 2;
				if(400<=x&&x<600&&100<y)
					return 3;
				if(600<=x&&x<800&&100<y)
					return 4;
			}
		}
		else
		{
			scanf("%d",&n);
			return n;
		}
	}
}

//显示图片
void show_bmp(char *bmp)
{
	int lcd,ret,i,j,x,y;
	FILE *fp = NULL;
	char bmp_buf[800*480*3];//图片的缓冲区
	char lcd_buf[800*480*4];//液晶屏幕缓冲区
	char show_buf[800*480*4];//颠倒之后的缓冲区
	
	//1. 访问LCD液晶
	lcd = open("/dev/fb0",O_RDWR);
	if(lcd < 0)
		printf("open lcd error!\n");
	
	chdir("./bmp");
	//2. 访问图片文件
	fp = fopen(bmp,"r+");
	if(fp == NULL)
		printf("fopen error!\n");
	
	//3. 跳过54个头数据
	fseek(fp,54,SEEK_SET);
	
	//4. 读取图片内容
	ret = fread(bmp_buf,sizeof(bmp_buf),1,fp);
	if(ret != 1)
		printf("fread error!\n");
	
	//5. 24位转32位
	for(i=0,j=0;i<800*480*4;i+=4,j+=3)
	{
		lcd_buf[i] = bmp_buf[j]; //蓝色
		lcd_buf[i+1] = bmp_buf[j+1]; //绿色
		lcd_buf[i+2] = bmp_buf[j+2]; //红色
		lcd_buf[i+3] = 0x00;//透明度
	}
	
	//6. 上下颠倒
	for(y=0;y<480;y++)//y=0
	{
		for(x=0;x<800*4;x++) //x=0
		{
			show_buf[(479-y)*800*4+x] = lcd_buf[y*800*4+x];
		}
	}
	
	//7. 将图片数据写入LCD液晶屏幕中
	ret = write(lcd,show_buf,sizeof(show_buf)); //800*480*4
	if(ret != sizeof(show_buf))
		printf("write error!\n");
	
	chdir("../");
	//8. 关闭LCD
	close(lcd);
	
	//9. 关闭图片文件
	fclose(fp);
}

//显示结束画面
int show_end()
{
	//1. 访问文件
	int lcd = open("/dev/fb0",O_RDWR);
	if(lcd < 0)
		printf("open lcd error!\n");
	
	//2.根据文件描述符产生映射
	char *p = (char *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd,0);
	
	//3. 填充颜色到内存
	int color = 0x00000000;
	
	int i;
	for(i=0;i<800*480*4;i+=4)
	{
		memcpy(p+i,&color,4);
	}
	
	//3. 撤销映射
	munmap(p,800*480*4);
	
	//4. 关闭文件
	close(lcd);
	
	return 0;
}
