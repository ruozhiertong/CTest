#include <stdio.h>
#include <sys/socket.h> // for socket
#include <arpa/inet.h> //for sockaddr_in

//抓包测试 一次send。
//1.小于MTU大小。 2.大于MTU。
//如果小于MTU可能会将几个send合并称一个包一起发送。 （粘包）
//如果大于MTU,一次send在底层被分片分组的，在接收端会重新重组。
//两端的send 和 recv 没有任何的一对一关系的。

//127的只接收本机的连接。 0.0.0.0可以接受任何的连接请求。
#define SERVER_IP   "0.0.0.0"//"127.0.0.1" 
#define SERVER_PORT 12300
#define TIMEOUT_SEC 5
#define LISTEN_NUMS 20


int send_time = 0;
int total_send = 0;
char *fileName = "data.mp4";

int bufLen = 1024 * 10;
char buf[1024*10];

int main(){
    //1.创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    //2.创建IP 端口。
    struct sockaddr_in serv_addr;
    //bzero(&server_addr, sizeof(server_addr)); 
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  //具体的IP地址
    serv_addr.sin_port = htons(SERVER_PORT);  //端口

    if(serv_sock < 0)
    {
        printf("socket error\n");
        return -1;
    }

    //3.将套接字和IP、端口绑定
    int ret;
    ret = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if(ret < 0)
    {
        printf("bind error\n");
        return -1;
    }

    //4.进入监听状态，等待用户发起请求
    ret = listen(serv_sock, LISTEN_NUMS);
    if(ret < 0)
    {
        printf("listen error\n");
        return -1;
    }

    //5.循环接收客户端请求。
    while(1)
    {
        //接收客户端请求
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_addr_size);
        FILE *fp = fopen(fileName,"rb");
        if(fp == NULL){
            printf("fopen error\n");
            close(client_sock);
            continue;
        }
        int n;
        n = fread(buf,sizeof(char),bufLen,fp);
        while(n>0 && send_time < 10){
            printf("fread from file %d\n", n);
            write(client_sock, buf, n);
            send_time++;
            total_send += n;
            n = fread(buf,sizeof(char),bufLen, fp);
        }
        fclose(fp);
        //关闭套接字
        close(client_sock);
        printf("total send :%d\n", total_send);
        printf("send_time :%d\n",send_time);
    }
    
    close(serv_sock);
    return 0;
}