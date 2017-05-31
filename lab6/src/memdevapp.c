/******************************************************************************
*Name: memdevapp.c
*Desc: memdev�ַ��豸��������Ĳ��Գ�������memedev�豸д�����ݣ�Ȼ����
* �Ӹ��豸�а����ݶ�������
*Parameter: 
*Return:
*Author: �³�
*Date: 2017-5-31
*Modify: 2017-5-31
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/fcntl.h>

int main()
{
 int fd;
 char buf[]="this is a example for character devices driver by yoyoba!";//д��memdev�豸������

 char buf_read[4096];//memdev�豸�����ݶ��뵽��buf��

 
 if((fd=open("/dev/memdev",O_RDWR))==-1)//��memdev�豸

  printf("open memdev WRONG��/n");
 else
  printf("open memdev SUCCESS!/n");
  
 printf("buf is %s/n",buf);

 write(fd,buf,sizeof(buf));//��buf�е�����д��memdev�豸

 
 lseek(fd,0,SEEK_SET);//���ļ�ָ�����¶�λ���ļ���ʼ��λ��

 
 read(fd,buf_read,sizeof(buf));//��memdev�豸�е����ݶ��뵽buf_read��

 
 printf("buf_read is %s/n",buf_read);
 
 return 0;
}