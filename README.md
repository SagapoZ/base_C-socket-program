# 项目说明：
	1.平台：Ubuntu16.04、GEC6818开发板
	2.开发一个简单的航班管理系统，
	利用网络编程socket套接字实现客户端远程控制服务器，操作航班管理系统
# 服务器说明：
	1. 通过make编译，如有改动自行改变makefile文件内容
	2. src：源码
		 - ins：头文件
		 - bin：可执行文件
		 - bmp：界面UI
		 - data：航班信息
		 - usr：用户信息
		 - administrators：管理员信息

	3.开发板运行只需将bmp、data、usr、administrators、可执行文件放在同一目录下即可运行    
     
# 客户端说明：
	1.源码两个.c文件
	2.只需将bmp资源文件放入开发板在运行可执行文件即可
