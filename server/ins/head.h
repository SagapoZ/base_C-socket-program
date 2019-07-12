#ifndef _HEAD_H_
#define _HEAD_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/wait.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/select.h>
#include <linux/input.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <sys/socket.h>


/**************************SOCK.c***********************/
//哪个文件描述符在里面就返回哪个
int fd_select(int fd1,int fd2);

/************lcd操作函数***********/
//界面功能触摸
int jiemian_touch();
//登录界面功能触摸
int denglu_jiemian_touch();
//用户功能界面触控
int user_jiemian_touch();
//管理员功能界面触控
int ad_jiemian_touch();
//显示图片
void show_bmp(char *bmp);
//显示结束画面
int show_end();

/********************航班操作函数********************/
//初始化航班头节点
struct flight_information *init_head(struct flight_information *head);
//初始化用户的头节点
struct user_information *init_user_head(struct user_information *head2);
//显示航班
void write_message(struct flight_information *head,int modify);
//用户操作
void user(struct user_information *head2,struct flight_information *head,char *bmp,int flag,int connfd);
//根据日期，起飞时间，型号查找航班
void query(struct flight_information *head);
//快速查询
void quicky_query(struct flight_information *head);
//管理员功能界面
void administrators_fun(struct flight_information *head,char *bmp,char *buf,int flag,int connfd);
//管理员文档的读取
int administrators(struct flight_information *head,char *bmp,int flag,int connfd);
//读取文件夹中的数据并存储到链表中
int read_user_information(struct user_information *head2,int modify);
#endif