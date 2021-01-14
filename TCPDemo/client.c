#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP   "127.0.0.1"
#define SERVER_PORT 12300

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
    while(1)
    {
        //读取服务器传回的数据
        char buffer[512];
        scanf("%s",buffer);
        int inputLen = strlen(buffer);
        printf("len:%d 。%s\n",inputLen,buffer);
        if(strcmp("bye",buffer) == 0)
        {
            break;
        }
        buffer[inputLen++] ='\n'; //加入换行符。
        write(sock,buffer,inputLen); //只需将要传送的长度发送。 结束符可以不用管。结束符只是用于C中字符串的结束标志，在网络中根本不用管。
        int n = read(sock, buffer, sizeof(buffer) -1);
        if (n == 0) //服务器端关闭
        {
            break;
        }
        buffer[n] = '\0';
        printf("Message form server:%s\n",buffer);
    }
    //关闭套接字
    close(sock);

    return 0;
}