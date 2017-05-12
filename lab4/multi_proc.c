/* multi_proc.c文件 */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>

int g_val = 100;
int main()
{
	pid_t childC1,childC2,child;
	
	/*先创建子进程C1*/
	childC1=fork();
	/*子进程C1的出错处理*/
	if(childC1==-1)
	{
		printf("Child C1 fork error:%s\n",strerror(errno));
		exit(1);  /*异常退出*/
	}
	/*在子进程C1中调用execlp()函数*/
	else if(childC1==0)
	{
		g_val = 200;
		printf("I am child C1, pid = %d, g_val = %d, &g_val = %p\n", getpid(), g_val, &g_val);
		sleep(3);
		exit(1);
		
	}
	/*在父进程中再创建进程C2,然后等待两个子进程的退出*/
	else
	{
		printf("I am father, pid = %d, g_val = %d, &g_val = %p\n", getpid(), g_val, &g_val);
		childC2=vfork();
		/*子进程C2的出错处理*/
		if(childC2==-1)
		{
			printf("Child C2 fork error:%s\n",strerror(errno));
			exit(1);
		}
		/*在子进程C2中使其暂停5s*/
		else if(childC2==0)
		{
			g_val = 200;
			printf("I am child C2, pid = %d, g_val = %d, &g_val = %p.I will sleep for 5 seconds!\n", getpid(), g_val, &g_val);
			sleep(5);
			printf("I am child C2, pid = %d, g_val = %d, &g_val = %p.I have awaked and I will exit!\n", getpid(), g_val, &g_val);
 			exit(1);
		}

		printf("I am father, pid = %d, g_val = %d, &g_val = %p\n", getpid(), g_val, &g_val);
		child=waitpid(childC1,NULL,0);/*阻塞式等待*/
		if(child==childC1)
		{
			printf("I am father, pid = %d, g_val = %d, &g_val = %p progress.I get child C1 exit code:%d\n", getpid(), g_val, &g_val,child);
		}
		else
		{
			printf("Error occured!\n");
		}

		do
		{
			child=waitpid(childC2,NULL,WNOHANG);/*非阻塞式等待*/
			if(child==0)
			{
				printf("I am father, pid = %d, g_val = %d, &g_val = %p progress.The child C2 progress has not exited!\n", getpid(), g_val, &g_val);
				sleep(1);
			}
		}while(child==0);

		if(child==childC2)
		{
			printf("I am father, pid = %d, g_val = %d, &g_val = %p progress.I get child C2 exit code:%d\n", getpid(), g_val, &g_val,child);
		}
		else
		{
			printf("Erroe occured!\n");
		}
	}
	exit(0);
	return 0;
}
