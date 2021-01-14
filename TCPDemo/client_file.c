#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 12300

int recv_time = 0;
long recv_total = 0;

int bufLen = 1024*5;
char buf[1024*10];

char * fileName ="recv.data";

int main(){
    //1.创建套接字和IP、端口结构。
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  //具体的IP地址
    serv_addr.sin_port = htons(SERVER_PORT);  //端口

    if(sock < 0)
    {
        printf("socket error\n");
        return -1;
    }

    //2.向服务器发起连接。TCP的话，这个阶段会进行三次握手的。
    int ret;
    ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret < 0)
    {
        printf("connect error\n");
        return -1;
    }
    //3. 接收／发送数据。
    //读取服务器传回的数据
    FILE * fp = fopen(fileName, "wb");
    if(fp == NULL){
        printf("fopen error\n");
        close(sock);
        return -1;
    }
    int n;
    n = read(sock, buf, bufLen);
    while(n > 0){
        printf("read from sock %d\n", n);
        fwrite(buf,sizeof(char),n,fp);
        recv_total += n;
        recv_time++;
        n = read(sock, buf, bufLen);
    }
    //关闭套接字
    close(sock);
    fclose(fp);
    printf("recv_total:%ld\n", recv_total);
    printf("recv_time:%d\n", recv_time);
    return 0;
}