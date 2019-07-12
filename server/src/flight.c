#include "head.h"
#include "kernel_list.h"

//定义结构体
struct flight_information{
	char number[15];
	char begin[20];
	char end[20];
	char day[30];
	char type[5];
	char time[20];
	int price;
	
	struct list_head list;
};

//定义用户的结构体
struct user_information{
	char user_account[20];
	char user_mima[20];
	char user_name[10];
	char user_age[5];
	char user_gender[5];
	int user_balance;
	int vip;
	char user_buy[50][10];
	int  user_ticket;
	
	struct list_head list;
};

//读出文件夹中文件数量
int file_number(struct dirent *ep,DIR *fp)
{
	int i=0;
	while(1)
	{
		ep=readdir(fp);
		if(ep==NULL)
			break;
		i=i+1;
	}
	return i;
}

//将文件夹内文件名存放到数组
void store_array(char data[][20],struct dirent *ep,DIR *fp,int i)
{
	int n;
	rewinddir(fp);
	for(n=0;n<=i;n++)
	{
		ep=readdir(fp);
		 if(ep==NULL)
			 break;
		 
		strcpy(data[n],ep->d_name);
	}
}

//初始化航班头节点
struct flight_information *init_head(struct flight_information *head)
{
	head=(struct flight_information *)malloc(sizeof(struct flight_information));
	
	INIT_LIST_HEAD(&(head->list));
	return head;
}

//初始化用户的头节点
struct user_information *init_user_head(struct user_information *head2)
{
	head2=(struct user_information *)malloc(sizeof(struct user_information));
	
	INIT_LIST_HEAD(&(head2->list));
	return head2;
}

//欢迎界面
void welcome_jiemian(void)
{
	printf("****************************************\n");
	printf("    welcome to flight enquiry system    \n");
	printf("****************************************\n");
	//sleep(5);
}

//尾插新节点
int add_tail_list(struct flight_information *head,char *number,char *begin,char *end,char *day,char *type,char *time,int price)
{
	struct flight_information *new=NULL;
	new=(struct flight_information *)malloc(sizeof(struct flight_information));
	if(new==NULL)
	{
		printf("Failed to create new node!");
		return -1;
	}
	strcpy(new->number,number);
	strcpy(new->begin,begin);
	strcpy(new->end,end);
	strcpy(new->day,day);
	strcpy(new->type,type);
	strcpy(new->time,time);
	new->price=price;
	
	list_add_tail(&(new->list),&(head->list));
	return 0;
}

//尾插用户信息节点
int add_registe_tail(struct user_information *head2,struct user_information *p)
{
	struct user_information *new=NULL;
	new=(struct user_information *)malloc(sizeof(struct user_information));
	if(new==NULL)
	{
		printf("Failed to create new node!");
		return -1;
	}
	strcpy(new->user_account,p->user_account);
	strcpy(new->user_mima,p->user_mima);
	strcpy(new->user_name,p->user_name);
	strcpy(new->user_age,p->user_age);
	strcpy(new->user_gender,p->user_gender);
	new->user_balance=p->user_balance;
	new->vip=p->vip;
	memcpy(&new->user_buy[0][0],&p->user_buy[0][0],50*10);
	new->user_ticket=p->user_ticket;
	
	
	list_add_tail(&(new->list),&(head2->list));
	
	return 0;
}

//显示注册用户的信息
void show_regist_list(struct user_information *head2)
{
	int i,n;
	struct user_information *p=NULL;
	list_for_each_entry(p,&(head2->list),list)
	{
		printf("%s\n",p->user_account);
		printf("%s\n",p->user_mima);
		printf("%s\n",p->user_name);
		printf("%s\n",p->user_age);
		printf("%s\n",p->user_gender);
		printf("%d\n",p->user_balance);
		i=p->user_ticket;
		for(n=0;n<i;n++)
		{
			printf("%s\n",p->user_buy[n]);
		}
	}
}

//写入数据
int write_data(char data[][20],int n,struct flight_information *head)
{
	struct flight_information *p;
	p=(struct flight_information *)malloc(sizeof(struct flight_information));
	FILE *fp1 = fopen(data[n],"r+");
	if(fp1==NULL)
	{
		printf("open file error!");
		return -1;
	}
	char str[50] = {0};
	fread(str,10,5,fp1);
	
	char seps[] = ","; 
	char *tmp;
	tmp = strtok(str,seps);
	strcpy(p->number,tmp);
	
	tmp = strtok(NULL,seps); 
	strcpy(p->begin,tmp);
	
	tmp = strtok(NULL,seps);;
	strcpy(p->end,tmp);
	
	tmp=strtok(NULL,seps);
	strcpy(p->day,tmp);
	
	tmp = strtok(NULL,seps);
	strcpy(p->type,tmp);

	
	tmp=strtok(NULL,seps);
	strcpy(p->time,tmp);
	
	tmp=strtok(NULL,seps);
	p->price=atoi(tmp);
	
	//尾插到头节点
	add_tail_list(head,p->number,p->begin,p->end,p->day,p->type,p->time,p->price);
	fclose(fp1);
	free(p);
	
	return 0;
}

//读取文件夹内的内容并赋值给p
int read_data(struct flight_information *head,int modify)
{
	int i,n;
	//打开文件夹
	DIR *fp=opendir("./data");
	if(fp==NULL)
	{
		printf("open dir error!");
		return -1;
	}
	
	struct dirent *ep=NULL;
	//判断文件数量
	i=file_number(ep,fp);
	
	char data[i][20];
	
	//存储名字
	store_array(data,ep,fp,i);
	
	if(modify==0)
	{
		chdir("./data");
		for(n=2;n<i;n++)
		{
			write_data(data,n,head);
		}
		chdir("../");
	}
	closedir(fp);
	return 0;
}

//显示信息
void show_list(struct flight_information *head)
{
	struct flight_information *p=NULL;
	printf("*****************************************************************************\n");
	printf("number    begin->end           day               type        time        price         \n");
	list_for_each_entry(p,&(head->list),list)
	{
		printf("%s      %s->%s             %s            %s        %s        %d       \n",p->number,p->begin,p->end,p->day,p->type,p->time,p->price);
	}
	printf("****************************************************************************\n");
	printf("1.User   2.Query    3.Quicky query     4.Administrators       5. closeserver       6.exit\n");
	printf("****************************************************************************\n");
}

//显示航班
void write_message(struct flight_information *head,int modify)
{
	
	//读取文件夹内的内容并赋值给p
	read_data(head,modify);
	
	//显示航班信息
	show_list(head);
}

//根据日期，起飞时间，型号查找航班
void query(struct flight_information *head)
{
	int i=0;
	char buf[20]={0};
	printf("Please enter date or departure time or model number:");
	scanf("%s",buf);
	
	struct flight_information  *p = NULL;
	
	list_for_each_entry(p,&(head->list),list)
	{
		if(strcmp(buf,p->day)==0)
		{
			printf("%s      %s->%s             %s            %s        %s        %d       \n",p->number,p->begin,p->end,p->day,p->type,p->time,p->price);
			i=1;
		}
		else if(strcmp(buf,p->begin)==0)
		{
			printf("%s      %s->%s             %s            %s        %s        %d      \n",p->number,p->begin,p->end,p->day,p->type,p->time,p->price);
			i=1;
		}
		else if(strcmp(buf,p->type)==0)
		{
			printf("%s      %s->%s             %s            %s        %s        %d       \n",p->number,p->begin,p->end,p->day,p->type,p->time,p->price);
			i=1;
		}
	}
	if(i==0)
	{
		printf("No flight information!\n");
	}
}

//快速查询
void quicky_query(struct flight_information *head)
{
	int i=0;
	char buf[20]={0};
	printf("number:");
	scanf("%s",buf);
	
	struct flight_information  *p = NULL;
	
	list_for_each_entry(p,&(head->list),list)
	{
		if(strcmp(buf,p->number)==0)
		{
			printf("%s      %s->%s             %s            %s        %s        %d       \n",p->number,p->begin,p->end,p->day,p->type,p->time,p->price);
			i=1;
		}
	}
	if(i==0)
	{
		printf("No flight information!\n");
	}
	
}

//判断管理员密码用户名
 int judge_admima(int n,char name[][20],char *buf)
{
	chdir("./administrators");
	char mima[20];
	FILE *fp1 = fopen(name[n],"r+");
	if(fp1==NULL)
	{
		printf("open file error!");
		return -1;
	}
	
	char str[50] = {0};
	fread(str,10,5,fp1);
	
	char seps[] = ","; 
	char *tmp;
	tmp = strtok(str,seps);
	
	if(strcmp(buf,tmp)==0)
	{
		printf("Please input a password:");
		scanf("%s",mima);
		tmp = strtok(NULL,seps); 
		if(strcmp(mima,tmp)==0)
		{
			chdir("../");
			fclose(fp1);
			return 1;
			
		}
		else
		{
			chdir("../");
			fclose(fp1);
			return -2;
		}
	}
	
	else
	{
		chdir("../");
		fclose(fp1);
		return 0;
	}
}

//增加航班
void increase_flights(struct flight_information *head)
{
	char number[15];
	char number2[15];
	char number3[15];
	char begin[20];
	char begin2[20];
	char end[20];
	char end2[20];
	char day[30];
	char day2[30];
	char type[5];
	char type2[5];
	char time[20];
	char time2[20];
	int price;
	int i,n,k,j,m;
	
	struct flight_information *p=NULL;
	
	while(1)
	{
		a:printf("please input flight number or intput 5 exit:");
		scanf("%s",number);
		//判断航班号是否存在
		list_for_each_entry(p,&(head->list),list)
		{
			if(strcmp(p->number,number)==0)
			{
				printf("number is existence!\n");
				goto a;
			}
		}
		//判断number格式是否及格
		if(strcmp(&number[0],"5")==0)
		{
			return;
		}
		if(isupper(number[0])==0)
		{
			goto a;
		}
		i=strlen(number);
		for(n=1;n<i;n++)
		{
			if(isdigit(number[n])==0)
			{
				goto a;
			}
		}
		break;
	}
	
	
	b:printf("please input begin or intput  5 exit:");
	scanf("%s",begin);
	k=strlen(begin);
	if(strcmp(&begin[0],"5")==0)
	{
		return;
	}
	for(n=0;n<k;n++)
	{
		if(isupper(begin[n])==0)
		{
			goto b;
		}
	}
	
	c:printf("please input end or intput  5 exit:");
	scanf("%s",end);
	j=strlen(end);
	if(strcmp(&end[0],"5")==0)
	{
		return;
	}
	for(n=0;n<j;n++)
	{
		if(isupper(end[n])==0)
		{
			goto c;
		}
	}
	
	printf("please input day or intput 5 exit:");
	scanf("%s",day);
	if(strcmp(&day[0],"5")==0)
	{
		return;
	}
	
	d:printf("please input types or intput 5 exit:");
	scanf("%s",type);
	if(strcmp(&type[0],"5")==0)
	{
		return;
	}
	m=strlen(type);
	for(n=0;n<m;n++)
	{
		if(isupper(type[n])==0)
		{
			goto d;
		}
	}
	
	printf("please input time or intput 5 exit:");
	scanf("%s",time);	
	if(strcmp(&day[0],"5")==0)
	{
		return;
	}

	printf("please input price:");
	scanf("%d",&price);
	
	chdir("./data");
	
	strcpy(number2,number);
	strcpy(number3,number);
	strcat(number2,",");
	
	strcat(number,".txt");
	FILE *fp=fopen(number,"w+");
	{
		if(fp==NULL)
		{
			printf("open file fail!\n");
			return;
		}
	}

	fwrite(number2,strlen(number2),1,fp);
	
	strcpy(begin2,begin);
	strcat(begin,",");
	fwrite(begin,strlen(begin),1,fp);
	
	strcpy(end2,end);
	strcat(end,",");
	fwrite(end,strlen(end),1,fp);
	
	strcpy(day2,day);
	strcat(day,",");
	fwrite(day,strlen(day),1,fp);
	
	strcpy(type2,type);
	strcat(type,",");
	fwrite(type,strlen(type),1,fp);
	
	strcpy(time2,time);
	strcat(time,",");
	fwrite(time,strlen(time),1,fp);

	fprintf(fp,"%d",price);
	
	add_tail_list(head,number3,begin2,end2,day2,type2,time2,price);
	
	chdir("../");
	fclose(fp);
}

//删除航班
int delete_flights(struct flight_information *head,char *bmp)
{
	struct flight_information *p=NULL;
	char number[10];
	char buf[30];
	while(1)
	{
		a:printf("please input a flight number or input 5 exit:");
		scanf("%s",number);
	
		if(strcmp(&number[0],"5")==0)
		{
			return 0;
		}
		chdir("./data");
		list_for_each_entry(p,&(head->list),list)
		{
			if(strcmp(p->number,number)==0)
			{
				sprintf(buf,"rm %s.txt",p->number);
				system(buf);
				list_del(&(p->list));
				free(p);
				chdir("../");
				return 1;
			}
		}
		chdir("../");
		show_bmp(bmp);
		goto a;
	}
}

//修改用户密码
int change_password(char *buf)
{
	
	char buf1[20];
	char buf2[20];
	char mima[20];
	char mima2[20];
	chdir("./administrators");
	sprintf(buf1,"%s.txt",buf);
	FILE *fd=fopen(buf1,"r+");
	printf("inuput your old mima :");
	scanf("%s",mima);
	
	char str[50] = {0};
	char seps[] = ",";
	fread(str,10,5,fd);
	
	char *tmp;
	tmp = strtok(str,seps);
	tmp = strtok(NULL,seps);
	if(strcmp(tmp,mima)==0)
	{
		fclose(fd);
		FILE *fp=fopen(buf1,"w+");
		printf("inuput your new mima :");
		scanf("%s",mima2);
		sprintf(buf2,"%s,",buf);
		fwrite(buf2,strlen(buf2),1,fp);
		fwrite(mima2,strlen(mima2),1,fp);
		fclose(fp);
		chdir("../");
		return 1;
	}
	printf("mima is error!\n");
	chdir("../");
	return 0;
}

//管理员功能界面
void administrators_fun(struct flight_information *head,char *bmp,char *buf,int flag,int connfd)
{
	
	int i,j,k;
	char rcv_buf[10];
	while(1)
	{
		char bmp2[1][10];
		strcpy(bmp2[0],"7.bmp");
		int n;
		system("clear");
		printf("*******************************************************************\n");
		printf("1.Increase flights    2.Delete flights   3.Change Password   4.exit\n");
		printf("*******************************************************************\n");
		show_bmp(bmp2[0]);
		if(flag == 0)
			n=ad_jiemian_touch();
		if(flag == 1)
		{
			bzero(rcv_buf,10);
			recv(connfd,rcv_buf,10,0);
			n = atoi(rcv_buf);
		}
		
		switch(n)
		{
			case 1:
				increase_flights(head);
				break;
			case 2:
				j=delete_flights(head,bmp);
				if(j==1)
					printf("delete_flights successful!\n");
				break;
			case 3:
				change_password(buf);
				break;
			case 4:
				return;
			default:
				break;
		}
	}
}

//管理员文档的读取
int administrators(struct flight_information *head,char *bmp,int flag,int connfd)
{
	char buf[20];
	char nobuf[10] = "no";
	char yesbuf[10] = "yes";
	int i,n,j;
	j=0;
	//输入账户
	printf("Please enter your ad account:");
	scanf("%s",buf);
	//打开文件夹
	DIR *fp=opendir("./administrators");
	if(fp==NULL)
	{
		printf("open dir error!");
		return -1;
	}
	
	struct dirent *p=NULL;
	
	i=file_number(p,fp);
	char name[i][20];
	
	//写入数组中
	store_array(name,p,fp,i);
	
	for(n=2;n<i;n++)
	{
		j=j+judge_admima(n,name,buf);
	}
	printf("%d",j);
	if(j==0)
	{
		printf("account is error!\n");
		if(flag == 1)
		{
			send(connfd,nobuf,10,0);
		}
	}
	else if(j==-2)
	{
		printf("mima is error!\n");
		if(flag == 1)
		{
			send(connfd,nobuf,10,0);
		}
	}
	else if(j==1)
	{
		//登录成功
		if(flag == 1)
		{
			int ret = send(connfd,yesbuf,10,0);
			printf("ret = %d\n",ret);
			//sleep(1);
		}
		printf("succesful landing!\n");
		administrators_fun(head,bmp,buf,flag,connfd);
	}
	
	closedir(fp);
}

//注册功能
int registe(struct user_information *head2,int modify)
{
	
	int i,n;
	//数据指针
	struct user_information *p=NULL;
	struct user_information *q=NULL;
	DIR *fp=opendir("./usr");
	{
		if(fp==NULL)
		{
			printf("opendir fail!\n");
			return -1;
		}
	}
	struct dirent *ep=NULL;
	
	i=file_number(ep,fp);
	char data[i][20];
	store_array(data,ep,fp,i);
	p=(struct user_information *)malloc(sizeof(struct user_information));
	
	printf("please input your account:");
	scanf("%s",p->user_account);
	if(modify==0)
	{
		i=read_user_information(head2,modify);
	}
	
	list_for_each_entry(q,&(head2->list),list)
	{
		if(strcmp(q->user_account,p->user_account)==0)
		{
			printf("account is existence!\n");
			return 0;
		}
	}
	
	chdir("./usr");
	printf("please input your mima:");
	scanf("%s",p->user_mima);
		
	printf("please input your name:");
	scanf("%s",p->user_name);
		
	printf("please input your age:");
	scanf("%s",p->user_age);	
		
	printf("please input your gender(man 1 women 2):");
	scanf("%s",p->user_gender);
	
	p->user_balance=0;
	p->vip=0;
	p->user_ticket=0;
	
	char buf[20]={0};
	char buf1[20]={0};
	char buf2[20]={0};
	char buf3[20]={0};
	char buf4[20]={0};
	char buf5[20]={0};
	sprintf(buf,"%s.txt",p->user_account);
	FILE *fd=fopen(buf,"w+");
	sprintf(buf1,"%s,",p->user_account);
	fwrite(buf1,strlen(buf1),1,fd);
	
	sprintf(buf2,"%s,",p->user_mima);
	fwrite(buf2,strlen(buf2),1,fd);
	
	sprintf(buf3,"%s,",p->user_name);
	fwrite(buf3,strlen(buf3),1,fd);
	
	sprintf(buf4,"%s,",p->user_age);
	fwrite(buf4,strlen(buf4),1,fd);
	
	sprintf(buf5,"%s,",p->user_gender);
	fwrite(buf5,strlen(buf5),1,fd);
	
	fprintf(fd,"%d,",p->user_balance);
	fprintf(fd,"%d,",p->vip);
	
	add_registe_tail(head2,p);
	
	chdir("../");
	fclose(fd);
	return 1;
}

//写入文件到链表中
int write_user_data(char data[][20],int n,struct user_information *head2)
{
	int i;
	i=0;
	struct user_information *p=NULL;
	p=(struct user_information *)malloc(sizeof(struct user_information));
	FILE *fp1 = fopen(data[n],"r+");
	if(fp1==NULL)
	{
		printf("open file error!");
		return -1;
	}
	
	char str[50] = {0};
	fread(str,10,5,fp1);
	
	char seps[] = ","; 
	char *tmp;
	tmp = strtok(str,seps);
	strcpy(p->user_account,tmp);
	
	tmp = strtok(NULL,seps); 
	strcpy(p->user_mima,tmp);
	
	tmp = strtok(NULL,seps);;
	strcpy(p->user_name,tmp);
	
	tmp=strtok(NULL,seps);
	strcpy(p->user_age,tmp);
	
	tmp = strtok(NULL,seps);
	strcpy(p->user_gender,tmp);

	
	tmp=strtok(NULL,seps);
	p->user_balance=atoi(tmp);
	tmp=strtok(NULL,seps);
	p->vip=atoi(tmp);
	
	for(n=0;tmp!=NULL;n++)
	{
		tmp=strtok(NULL,seps);
		if(tmp ==NULL)
			break;
		strcpy(p->user_buy[n],tmp);
		i=n+1;
	}
	
	p->user_ticket = i;
	
	add_registe_tail(head2,p);
	fclose(fp1);
}

//读取文件夹中的数据并存储到链表中
int read_user_information(struct user_information *head2,int modify)
{
	int i,n;
	//打开文件夹
	DIR *fp=opendir("./usr");
	if(fp==NULL)
	{
		printf("open dir error!");
		return -1;
	}
	
	struct dirent *ep=NULL;
	//判断文件数量
	i=file_number(ep,fp);
	
	char data[i][20];
	
	//存储名字
	store_array(data,ep,fp,i);
	
	chdir("./usr");
	if(modify==0)
	{
		for(n=2;n<i;n++)
		{
			write_user_data(data,n,head2);
		}
	}
	chdir("../");
	if(n==2)
	{
		printf("No user exists!please registe!\n");
		return n;
	}
	closedir(fp);
}

//将数据重新写入到文件中
void write_agin(struct user_information *p,int i)
{
	int k;
	char buf[20]={0};
	char buf1[20]={0};
	char buf2[20]={0};
	char buf3[20]={0};
	char buf4[20]={0};
	char buf5[20]={0};
	char buf6[50][10]={0};
			
	sprintf(buf,"%s.txt",p->user_account);
	FILE *fd=fopen(buf,"w+");
	{
		if(fd==NULL)
			printf("open file fail!\n");
	}
	sprintf(buf1,"%s,",p->user_account);
	fwrite(buf1,strlen(buf1),1,fd);
	
	sprintf(buf2,"%s,",p->user_mima);
	fwrite(buf2,strlen(buf2),1,fd);
	printf("%s\n",buf2);
	
	sprintf(buf3,"%s,",p->user_name);
	fwrite(buf3,strlen(buf3),1,fd);
	
	sprintf(buf4,"%s,",p->user_age);
	fwrite(buf4,strlen(buf4),1,fd);
	
	sprintf(buf5,"%s,",p->user_gender);
	fwrite(buf5,strlen(buf5),1,fd);
	
	fprintf(fd,"%d,",p->user_balance);
	fprintf(fd,"%d,",p->vip);
			
	for(k=0;k<i;k++)
	{
		sprintf(buf6[k],"%s,",p->user_buy[k]);
		fwrite(buf6[k],strlen(buf6[k]),1,fd);
	}
	fclose(fd);
}

//买票功能
int buy_ticket(struct user_information *p,struct flight_information *head)
{
	int i,n;
	char ticket[10];
	char ticket1[10];
	char account[20];
	
	struct flight_information *q=NULL;
	
	printf("Please enter the flight number you want to purchase:");
	scanf("%s",ticket);
	
	i=p->user_ticket;
	for(n=0;n<i;n++)
	{
		if(strcmp(p->user_buy[n],ticket)==0)
		{
			printf("ticket has been purchase!\n");
			return -1;
		}
	}
	list_for_each_entry(q,&(head->list),list)
	{
		if(strcmp(q->number,ticket)==0)
		{
			if(p->user_balance >  q->price)
			{
				chdir("./usr");
				strcpy(p->user_buy[i],ticket);
				if(p->vip==1)
				{
					p->user_balance=p->user_balance-(0.8 * q->price);
				}
				else
				{
					p->user_balance=p->user_balance-q->price;
				}
				p->user_ticket=p->user_ticket+1;
				i=i+1;
				write_agin(p,i);
				chdir("../");
				return 1;
			}
			return -2;
		}
	}
	return 0;
}

//查询买过的票功能
void query_buy_ticket(struct user_information *p)
{
	int i,n;
	i=p->user_ticket;
	for(n=0;n<i;n++)
	{
		printf("%s\n",p->user_buy[n]);
	}
}

//退票
int exit_ticket(struct user_information *p,struct flight_information *head)
{
	struct flight_information *q=NULL;
	int i,n,j,price;
	char ticket[10];
	char account[10];
	printf("Please enter the tickets you have purchased:");
	scanf("%s",ticket);
	i=p->user_ticket;
	for(n=0;n<i;n++)
	{
		if(strcmp(p->user_buy[n],ticket)==0)
		{
			list_for_each_entry(q,&(head->list),list)
			{
				if(strcmp(q->number,ticket)==0)
					price=q->price;
			}
			bzero(p->user_buy[n],sizeof(p->user_buy[n]));
			for(j=n+1;j<i;j++)
			{
				strcpy(p->user_buy[n],p->user_buy[j]);
				n=n+1;
			}
			p->user_ticket=p->user_ticket-1;
			p->user_balance=p->user_balance+0.8 * price;
			i=i-1;
			chdir("./usr");
			write_agin(p,i);
			printf("succesful refund!\n");
			chdir("../");
			return 1;
		}
	}
	printf("refund fail!\n");
	return 0;
}

//改票
int change_ticket(struct user_information *p,struct flight_information *head)
{
	int n,i,price;
	struct flight_information *q=NULL;
	struct flight_information *k=NULL;
	char ticket[10];
	char ticket2[10];
	char account[10];
	printf("Please enter the tickets you have purchased:");
	scanf("%s",ticket);
	i=p->user_ticket;
	for(n=0;n<i;n++)
	{
		if(strcmp(p->user_buy[n],ticket)==0)
		{
			printf("Please enter the tickets you want retund:");
			scanf("%s",ticket2);
			list_for_each_entry(k,&(head->list),list)
			{
				if(strcmp(k->number,ticket)==0)
				{
					price=k->price;
				}
			}
			list_for_each_entry(q,&(head->list),list)
			{
				if(strcmp(q->number,ticket2)==0)
				{
					if(q->price > price)
					{
						if(p->user_balance > (q->price-price))
						{
							p->user_balance=p->user_balance-(q->price-price);
						}
						else
						{
							return -2;
						}
					}
					strcpy(p->user_buy[n],ticket2);
					chdir("./usr");
					write_agin(p,i);
					printf("succesful change!\n");
					chdir("../");
					return 1;
				}
			}
			return 0;
		}
	}
	return -1;
}

//充值功能
int invest_money(struct user_information *p)
{
	int recharged,i,j;
	printf("Please enter the amount to be recharged:");
	scanf("%d",&recharged);
	
	printf("would you like pay 1000 to be vip?yes1 or no2:");
	scanf("%d",&i);
	
	j=p->user_ticket;
	
	if(i==1)
	{
		if((p->user_balance+recharged)<1000)
		{
			p->user_balance=p->user_balance+recharged;
			printf("money is not enough!\n");
			chdir("./usr");
			write_agin(p,j);
			chdir("../");
			return -2;
		}
		else if(p->vip==1)
		{
			p->user_balance=p->user_balance+recharged;
			printf("you have been a vip!\n");
			chdir("./usr");
			write_agin(p,j);
			chdir("../");
			return 0;
		}
		else
		{
			p->user_balance=p->user_balance+recharged-1000;
			p->vip=1;
			chdir("./usr");
			write_agin(p,j);
			printf("Congratulations on becoming VIP!\n");
			chdir("../");
			return 1;
		}
	}
	else
	{
		p->user_balance=p->user_balance+recharged;
		chdir("./usr");
		write_agin(p,j);
		chdir("../");
		return -1;
	}
}

//密码修改功能
int modify_mima(struct user_information *p)
{
	int i;
	char mima[20];
	char mima2[20];
	printf("Please enter the original password:");
	scanf("%s",mima);
	i=p->user_ticket;
	if(strcmp(p->user_mima,mima)==0)
	{
		printf("Please enter the new password:");
		scanf("%s",mima2);
		strcpy(p->user_mima,mima2);
		chdir("./usr");
		write_agin(p,i);
		chdir("../");
		printf("modify mima successful!\n");
		return 1;
	}
	else
	{
		printf("the original password is fail!\n");
		return 0;
	}
}

//用户功能
void user_fun(struct user_information *p,struct flight_information *head,char *bmp,int flag,int connfd)
{
	int n,j,i;
	char buf[10];
	while(1)
	{
		//显示用户功能界面
		char bmp2[1][10];
		strcpy(bmp2[0],"6.bmp");
		printf("****************************************************************************\n");
		printf("1.buy_ticket    2.query_buy_ticket                                          \n");
		printf("3.exit_ticket   4.change_ticket                                             \n");
		printf("5.exit          6.invest_money       7.modify_mima                          \n");
		printf("****************************************************************************\n");
		show_bmp(bmp2[0]);
		if(flag == 0)
		{
			n=user_jiemian_touch();
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
					printf("begin buy_ticket!\n");
					i=buy_ticket(p,head);
					if(i==1)
						printf("buy ticket successful!\n");
					if(i==0)
						show_bmp(bmp);
					if(i==-2)
						printf("money not enough!\n");
					break;
			case 2:
					query_buy_ticket(p);
					break;
			case 3:
					printf("begin exit_ticket!\n");
					exit_ticket(p,head);
					break;
			case 4:
					printf("begin change_ticket!\n");
					j=change_ticket(p,head);
					if(j==-1)
						printf("ticket is not purchase!\n");
					if(j==0)
						printf("ticket is not existence\n");
					if(j==-2)
						printf("money is not enough!\n");
					break;
			case 5:
					return;
			case 6:
					printf("begin invest_money!\n");
					invest_money(p);
					break;
			case 7:
					printf("begin modify_mima!\n");
					modify_mima(p);
					break;
			default:
					break;
		}
	}
}

//登录
int sign_in(struct user_information *head2,int modify,struct flight_information *head,char *bmp,int flag,int connfd)
{
	int i;
	//读取文件夹中的数据并存储到链表中
	if(modify==0)
	{
		i=read_user_information(head2,modify);
	}
	
	if(i==2)
	{
		return 0;
	}

	
	char account[20];
	char mima[20];
	char yesbuf[10] = "yes";
	char nobuf[10] = "no";
	struct user_information *p=NULL;
	printf("input your account:");
	scanf("%s",account);
	//判断用户是否已经注册
	list_for_each_entry(p,&(head2->list),list)
	{
		if(strcmp(p->user_account,account)==0)
		{
			printf("please input your mima:");
			scanf("%s",mima);
			if(strcmp(p->user_mima,mima)==0)
			{
				printf("landing is succesful!\n");
				//登录成功发送消息
				if(flag == 1)
				{
					send(connfd,yesbuf,10,0);
				}
				user_fun(p,head,bmp,flag,connfd);
				show_regist_list(head2);
			}
			else
			{	
				if(flag == 1)
				{
					send(connfd,nobuf,10,0);
				}
				return -1;
			}
		}
		
	}
	return -2;
}

int searching_password(struct user_information *head2,int modify)
{
	int i,j;
	char account[20];
	char name[20];
	char age[5];
	char mima[20];
	struct user_information *p=NULL;
	//读取文件夹中的数据并存储到链表中
	if(modify==0)
	{
		i=read_user_information(head2,modify);
	}
	
	if(i==2)
	{
		return;
	}
	printf("intput your account：");
	scanf("%s",account);
	list_for_each_entry(p,&(head2->list),list)
	{
		if(strcmp(p->user_account,account)==0)
		{
			printf("intput your name：");
			scanf("%s",name);
			if(strcmp(p->user_name,name)==0)
			{
				printf("intput your age：");
				scanf("%s",age);
				if(strcmp(p->user_age,age)==0)
				{
					j=p->user_ticket;
					printf("input your new mima:");
					scanf("%s",mima);
					strcpy(p->user_mima,mima);
					chdir("./usr");
					write_agin(p,j);
					chdir("../");
					return 1;
				}
				return 0;
			}
			return -1;
		}
	}
	return -2;
}

//用户功能
void user(struct user_information *head2,struct flight_information *head,char *bmp,int flag,int connfd)
{
	char bmp2[10][10];
	strcpy(bmp2[0],"5.bmp");
	int n,j,k,l,ret;
	int modify=0;
	char buf[10];
	while(1)
	{
		printf("****************************************************************************\n");
		printf("1.registe   2.sign_in     3.searching_password          4.exit              \n");
		printf("****************************************************************************\n");
		show_bmp(bmp2[0]);
		
		if(flag == 0)
			n=denglu_jiemian_touch();
		if(flag == 1)
		{
			bzero(buf,10);
			recv(connfd,buf,10,0);
			n = atoi(buf);  
		}
		switch(n)
		{
			case 1:
				printf("registe is begin!\n");
				l=registe(head2,modify);
				if(l==0)
					printf("account is existence!\n");
				if(l==1)
					printf("successful regisit!\n");
				modify=1;
				break;
			case 2:
				printf("sign_in is begin!\n");
				k=sign_in(head2,modify,head,bmp,flag,connfd);
				modify=1;
				if(k==-1)
					printf("mima is error!\n");
				if(k==-2)
					printf("account is error!\n");
				break;
		
			case 3:
				printf("searching_password is begin!\n");
				j=searching_password(head2,modify);
				modify=1;
				if(j==1)
					printf("searching successful!\n");
				if(j==0)
					printf("age is error!\n");
				if(j==-1)
					printf("name is error!\n");
				if(j==-2)
					printf("account is error!\n");
				break;
				
			case 4:
				return;
			default:
				break;
		}
	}
}

