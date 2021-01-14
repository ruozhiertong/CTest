#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 12400

int bufLen = 1024 * 5;
char buf[1024*10];

char *fileName = "recv.data";

int recv_time = 0;
long total_recv = 0;
 
int main()
{
    //1.创建socket对象和IP、端口数据结构。
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    //服务器端IP和端口数据。
    struct sockaddr_in ser_addr;
    ser_addr.sin_family =AF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP); //IP根据server所在主机的IP设定，这里是运行在同一PC端 
    ser_addr.sin_port =htons(SERVER_PORT);


    //2.发送/接收数据。
    strcpy(buf, "hello");
    sendto(sockfd,&buf,strlen(buf),0,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    FILE * fp = fopen(fileName, "wb");
    if(fp == NULL){
        printf("fopen error\n");
        close(sockfd);
        return -1;
    }
    while(1)
    {
        struct sockaddr_in addr;
        socklen_t len=sizeof(addr);
        int n;
        n = recvfrom(sockfd,&buf,bufLen,0,(struct sockaddr*)&addr,&len);
        if(n <= 0)
            break;
        recv_time++;
        total_recv+=n;
        printf("read from sock %d\n", n);
        fwrite(buf,sizeof(char),n,fp);
    }
    fclose(fp);
    close(sockfd); 

    printf("recv_time:%d\n", recv_time);
    printf("total_recv:%ld\n",total_recv);
}
