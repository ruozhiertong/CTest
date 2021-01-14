#include <stdio.h>
#include <sys/socket.h> // for socket
#include <arpa/inet.h> //for sockaddr_in


#define SERVER_IP   "0.0.0.0" //"127.0.0.1" //
#define SERVER_PORT 12300
#define TIMEOUT_SEC 5
#define LISTEN_NUMS 20


void upperStr(char * str){
    char * ptr = str;
    while(*ptr){
        if(*ptr>='a' && *ptr <= 'z')
            *ptr -= 32;
        ptr++;
    }
}


int main(){
    //1.创建套接字和IP、端口结构。
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

    //2.将套接字和IP、端口绑定
    int ret;
    ret = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if(ret < 0)
    {
        printf("bind error\n");
        return -1;
    }

    //3.进入监听状态，等待用户发起请求
    ret = listen(serv_sock, LISTEN_NUMS);
    if(ret < 0)
    {
        printf("listen error\n");
        return -1;
    }

    //4.循环接收客户端请求。
    while(1)
    {
        //接收客户端请求
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_addr_size);

        while(1){
            char buf[512];
            //可以使用read write，也可以使用recv send ， recvfrom sendto。
            //阻塞。
            int len = read(client_sock, buf, 512);
            if(len == 0)
            {
                printf("client close\n");
                break;
            }
            buf[len] = '\0';
            printf("from %s:%d: %s\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),buf);
            upperStr(buf);
            //向客户端发送数据.
            write(client_sock, buf, len);
        }
        //关闭套接字
        close(client_sock);
    }
    
    close(serv_sock);
    return 0;
}