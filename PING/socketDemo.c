#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc ,char* argv[])
{

	struct sockaddr_in dest;

    int sockfd;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);;

    if(sockfd < 0)
    {
        printf("socket error\n");
        return -1;
    }
    
    bzero((void*)&dest, sizeof(dest));
    
    if(argc == 1)
    {
        dest.sin_addr.s_addr  = inet_addr("127.0.0.1");
        dest.sin_port = htons(9090);        /* fill in socket port  */
    }
    else
    {
        dest.sin_addr.s_addr  = inet_addr(argv[1]);
        dest.sin_port = htons(atoi(argv[2]));        /* fill in socket port  */
    }
       dest.sin_family = AF_INET;
    
    
    //可以看到没有进行大小端转换的话，在wireshark中抓取的包是不一样的。即系统底层没有帮忙做转换。
    
    int send_data = htonl(0x12345678);
    //int send_data = 0x12345678;
    printf("%x\n",send_data);
    
    long ret = sendto(sockfd,&send_data,sizeof(int),0,(struct sockaddr*)&dest,sizeof(dest));
    
    if(ret != sizeof(int))
    {
        printf("data not sent complete\n");
    }
    
	return 0;
}