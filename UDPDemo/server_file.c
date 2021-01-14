#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define SERVER_IP   "0.0.0.0"
#define SERVER_PORT 12400

int bufLen = 1024 * 5;
char buf[1024*10];

char *fileName = "../TCPDemo/data.mp4";

int send_time = 0;
long total_send = 0;

 
int main()
{
    //1.创建socket对象和IP、端口数据。
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    //创建网络通信对象
    struct sockaddr_in addr;
    addr.sin_family =AF_INET;
    addr.sin_addr.s_addr=inet_addr(SERVER_IP);
    addr.sin_port =htons(SERVER_PORT);


    //2.绑定socket对象与通信链接.
    int ret =bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(0>ret)
    {
     printf("bind\n");
     return -1;

    }

    //3.接收／发送数据。
    struct sockaddr_in cli;
    socklen_t len=sizeof(cli);
    int n;
    n = recvfrom(sockfd,&buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
    buf[n] ='\0';
    printf("recv: %d,%s\n", n,buf);

    FILE *fp = fopen(fileName,"rb");
    if(fp == NULL){
        printf("fopen error\n");
        close(sockfd);
        return -1;
    }
    n = fread(buf,sizeof(char),bufLen,fp);
    while(n>0 && send_time < 10){
        printf("fread from file %d\n", n);
        sendto(sockfd,&buf,n,0,(struct sockaddr*)&cli,len);
        send_time++;
        total_send += n;
        n = fread(buf,sizeof(char),bufLen, fp);
    }
    // 告诉客户端结束了。否则客客户端会傻傻等待 recvfrom。 因为不像TCP那样可以有close，所以这里自己send一个空的过去
    sendto(sockfd,&buf,0,0,(struct sockaddr*)&cli,len);
    fclose(fp);
    close(sockfd);
    printf("send_time:%d\n", send_time);
    printf("total_send:%ld\n",total_send);
}
