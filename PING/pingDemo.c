#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>   
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netinet/in.h> // for IPPROTO_ICMP
//#include <netinet/ether.h> //not this file
//#include <net/if.h>
//#include <net/in.h> //not this file
#include <net/ethernet.h>  // for ETHERTYPE_ARP
#include <netinet/if_ether.h>


#define _LITTLE_ENDIAN_BITFIELD 0
#define _BIG_ENDIAN_BITFIELD    1

char hostEdian[2][20] = {"little Endian","big Endian"};

//因为自己这台机器是小端的。 （大小端也会影响位域的存储方式）
#ifndef _LITTLE_ENDIAN_BITFIELD
#define _LITTLE_ENDIAN_BITFIELD
#endif


#define IP_HSIZE sizeof(struct iphdr)   //定义IP_HSIZE为ip头部长度
#define IPVERSION  4   //定义IPVERSION为4，指出用ipv4
 
 
 
#define ICMP_ECHOREPLY 0 //Echo应答
#define ICMP_ECHO      8 //Echo请求
 
#define BUFSIZE 1500     //发送缓存最大值
//#define DEFAULT_LEN 56   //ping 消息数据默认大小
#define SENTIMES    4
 
//数据类型别名
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
 
//ICMP消息头部 hdr: header
//我更倾向于 arp是链路层的协议，因为它是以以太网帧进行分装和传输的，即是一个二层数据帧，以太网帧。
//ICMP是网络层的协议，因为它是以IP数据包进行分装和传输的，是一个三层的IP数据包。
//https://blog.csdn.net/cuiweitju/article/details/38761381
//ARP ： https://www.cnblogs.com/laojie4321/archive/2012/04/12/2444187.html
//ICMP: https://blog.csdn.net/u014634338/article/details/48951345
//定义变量占用位数。 https://www.cnblogs.com/time93/p/9347567.html
 
struct icmphdr
{
    u8 type;
    u8 code;
    u16 checksum;
    union
    {
        struct
        {
            u16 id;
            u16 sequence;
        }echo;
        
        u32 gateway;
        struct
        {
            u16 unused;
            u16 mtu;
        }frag; //pmtu发现
    }un;
    
    
    //icmp头部的时间戳不应该那么设计，除非双方都知道你们自己定的规则。 虽然数组方式可以排除大小端问题，但是对方要知道你各个元素的值，再拼接起来，也就是对方要清楚知道你的设计，否则取出的值也会有问题。
    //所以，如果要想通用的，应该按照通用设计。如果是大于1字节的数据，设计大小端，应该按照大小端转换去赋值取值。 即 要求发送方和接收方，对于大于一字节的数据，应该各自去处理，进行大小端转换。
    //所以这里的时间戳，可以直接设计成64位的数据。然后传输的时候，大小端转换。虽然要注意大小端，但是这是大家都知道的规则,所以这是默认的不言自明的规则。
    //u32  icmp_timestamp[2];//时间戳
    unsigned long  icmp_timestamp;
    //ICMP数据占位符
    u8 data[0];
#define icmp_id un.echo.id
#define icmp_seq un.echo.sequence
};
 
#define ICMP_HSIZE sizeof(struct icmphdr)


//字节序。 当处理数据以字节为单位的，当处理的类型大于1字节时，不同的方式的存储就会有字节序的问题。  字节序在 大端 小端的存储方式中是不同。
//比特序。 当处理数据以bit为单位的，当处理的数据大于1bit时，不同的方式的存储就会有比特序的问题。   比特序在 大端 小端的存储方式中是不同。


//大端，就是将数据的高位 存储在  地址的 低位。
//小端， 将数据的低位  存储在   地址的 低位。

//大小端 ，是以数据的哪端 存储在 地址的低位/起始位 的角度命名的。


struct iphdr
{
//我觉的不应该将结构体定死大小端，应该在发送 或 接收数据的时候进行 大小端转换。 虽然可能每次会繁琐，但是这个保证了通信的正确，统一。
//当然如果你确定你就是在大端或小端 机器上，为了避免每次转换的繁琐，可以这么特意定义。(不过，还是按照正常去定义，能保证统一)
#if defined _LITTLE_ENDIAN_BITFIELD
    u8 hlen:4,ver: 4;
#elif defined _BIG_ENDIAN_BITFIELD
    u8 ver:4,hlen:4;
#endif
    //u8 ver:4 ,hlen:4;
    //u8 hlen:4, ver:4;
    u8 tos;
    u16 tot_len;//头部+数据的 全部长度。 理论上应该是IP头部+数据的全部。 不过具体实现中可能会不一样，比如mscos这里的tot_len就只是IP数据部分的长度。
    u16 id;
    u16 frag_off;
    u8 ttl;
    u8 protocol;
    u16 check;
    u32 saddr;
    u32 daddr;
};


/*
 ascii表 是将字符和相应的ASCII码（二进制(内存中存储的值)(网络数据传输的也是二进制)）对应起来。
 ASCII码本质上是存储在内存上的二进制值。可以有多种表现形式，二进制，10进制，8进制，16进制形式0x。
 在字符串中可以用ascii码表示某个字符，可以用\ +八进制 或十六进制表示。 \ddd \0xdd
 */

//系统ping命令 其数据内容 为 08:09:0a:0b:0c:0d:0e:0f:10:11:12:13:14:15:16:17:18:19:1a:1b:1c:1d:1e:1f:20:21:22:23:24:25:26:27:28:29:2a:2b:2c:2d:2e:2f:30:31:32:33:34:35:36:37
//ASCII码值  48字节。
char pingData[] = "\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35\x36\x37";

//int pingData = 0x12345678;
//char hello[]="hello this is  a ping test.";
char hostname[81]; //被ping的主机
int  datalen;//DEFAULT_LEN;//ICMP消息携带的数据长度
char sendbuf[BUFSIZE];
char recvbuf[BUFSIZE];
int nsent = 0;//发送的ICMP消息序号
int send_times = 0; //发四次。
int recv_times = 0;
pid_t pid;//ping程序的进程pid
struct timeval recvtime; //收到ICMP应答的时间戳
struct timeval sendtime;
int sockfd; //发送和接收原始套接字
struct sockaddr_in dest;//被ping主机的ip
struct sockaddr_in from;//发送ping应答消息的主机ip
 
struct sigaction act_alarm;
struct sigaction act_int;
 

 
//函数原型
void alarm_handler(int);//SIGALRM处理程序
void int_handler(int);//SIGINT处理程序
void set_sighandler();//设置信号处理程序
void send_ping();//发送ping消息
void recv_reply();//接收ping应答
u16 checksum(u8 *buf,int len);//计算校验和
int handle_pkt();//ICMP应答消息处理
void get_statistics(int ,int);//统计ping命令的检测结果
void bail(const char *);//错误报告
int checkEndian();
void set_time();
void uninit_time();




// ./a.out www.baidu.com    
int main(int argc,char **argv)  //argc表示隐形程序命令行中参数的数目，argv是一个指向字符串数组指针，其中每一个字符对应一个参数
{
   
//    char *temp = "12";
//    char *temp = {'1','2'};
//    char *temp = {'1','2','\0'};
//    
//    char temp[] = "12";
//    char temp[] = {'1','2'};
//    char temp[] = {'1','2','\0'};

    
    char temp[]="12"; //{'1','2'}; //"12";//{'1','2'};
    
    
    struct icmphdr *icmp_hdr;   //icmphdr为ICMP头部结构体
    icmp_hdr=(struct icmphdr *)(sendbuf);  //字符串指针

    printf("%d\n",strlen(temp));
    memcpy(icmp_hdr->data, temp, strlen(temp));
    printf("%d %s\n",strlen((char*)icmp_hdr->data),icmp_hdr->data);
    
    
    //zero[0]零长数组。 一般放在结构体的最后字段的。 其他地方没什么作用。
    //char zero[0];
    //memcpy(zero, temp, strlen(temp));
    //printf("%d %s\n",strlen((char*)zero),zero);
    
    
    printf("this host is %s\n",hostEdian[checkEndian()]);
    
    struct hostent *host; //该结构体属于include<netdb.h>

    
    if(argc == 1)
    {
        //printf("请输入要ping的网址\n");
        //scanf("%s",hostname);
        strcpy(hostname, "www.baidu.com");
    }
    else //./a.out www.baidu.com 
    {
        strcpy(hostname,argv[1]);//取出地址名
    }

    if((host=gethostbyname(hostname))==NULL)
    {    //gethostbyname()返回对应于给定主机名的包含主机名字和地址信息的结构指针,
        perror("can not understand the host name");   //理解不了输入的地址
        exit(1);
    }
    
    
    setuid(getuid());//getuid()函数返回一个调用程序的真实用户ID,setuid()是让普通用户可以以root用户的角色运行只有root帐号才能运行的程序或命令。
    pid=getpid(); //getpid函数用来取得目前进程的进程识别码
    printf("PID:%d\n",pid);

    
    memset(&dest,0,sizeof dest);  //将dest中前sizeof(dest)个字节替换为0并返回s,此处为初始化,给最大内存清零
    dest.sin_family=PF_INET;  //PF_INET为IPV4，internet协议，在<netinet/in.h>中，地址族
    dest.sin_port= htons(0);//ntohs(0);   //端口号,ntohs()返回一个以主机字节顺序表达的数。
    dest.sin_addr=*(struct in_addr *)host->h_addr_list[0];//host->h_addr_list[0]是地址的指针.返回IP地址，初始化
    
    //指定ICMP协议，这样填充IP头部的协议字段，对方才能处理为ICMP。如果没有设定或者设定其他的，会按照其他的处理的。
    //if((sockfd = socket(PF_INET,SOCK_RAW,0))<0)
    if((sockfd = socket(PF_INET,SOCK_RAW,IPPROTO_ICMP))<0)
    { //PF_INEI套接字协议族，SOCK_RAW套接字类型，IPPROTO_ICMP使用协议，调用socket函数来创建一个能够进行网络通信的套接字。这里判断是否创建成功
        perror("raw socket created error");
        exit(1);
    }
    
    set_sighandler();//对信号处理.
    datalen = (int)strlen(pingData) ;
    //datalen = sizeof(pingData);
    printf("Ping %s(%s): %d bytes data in ICMP packets.\n",hostname,inet_ntoa(dest.sin_addr),datalen);
    
    set_time();
    

    for(;;);
    
    return 0;
}
//发送ping消息
void send_ping()
{
    printf("in send_ping\n");
    //struct iphdr *ip_hdr;   //iphdr为IP头部结构体
    struct icmphdr *icmp_hdr;   //icmphdr为ICMP头部结构体
    int len;
    
    icmp_hdr=(struct icmphdr *)(sendbuf);  //字符串指针
    //不用从ip头开始构造，因为你已经设置了ICMP协议。
    //icmp_hdr=(struct icmphdr *)(sendbuf + sizeof(struct iphdr)); 
    icmp_hdr->type=ICMP_ECHO;    //初始化ICMP消息类型type
    icmp_hdr->code=0;    //初始化消息代码code
    //icmp_hdr->icmp_id=pid;   //把进程标识码初始给icmp_id
    icmp_hdr->icmp_id = htons(pid); //大小端转化后，数据在网络间发送就保持一致了。
    printf("icmp_id %d %d\n", pid, htons(pid));

    printf("icmp_seq %d %d\n", nsent , htons(nsent));
    //icmp_hdr->icmp_seq=nsent++;  //发送的ICMP消息序号赋值给icmp序号
    icmp_hdr->icmp_seq=htons(nsent++);
    gettimeofday(&sendtime, NULL);
    //char[]设计
    //memccpy(icmp_hdr->icmp_timestamp, &sendtime, 1, sizeof(icmp_hdr->icmp_timestamp));
    
    //long设计. 注意大小端转换。一个字节的无所谓。大于一个字节的注意大小端转换。
    icmp_hdr->icmp_timestamp = htonl(sendtime.tv_sec);
    //icmp_hdr->icmp_timestamp = sendtime.tv_sec;
    
    printf("send_ping sendtime:%ld",sendtime.tv_sec);
    printf("send_ping timestamp:%u\n",htonl(sendtime.tv_sec));
    
    //icmp_timestamp总共64位，所以gettimeofday只能获取到结构体timeval前64位也就是秒的值。
    //即timeval的秒赋给timestamp.
    
    //gettimeofday((struct timeval *)icmp_hdr->icmp_timestamp,NULL); // 获取当前时间
    //printf("send time: %lld %d\n",((struct timeval *)icmp_hdr->icmp_timestamp)->tv_sec , ((struct timeval *)icmp_hdr->icmp_timestamp)->tv_usec);
    
    //数据为字符串
    memcpy(icmp_hdr->data, pingData, strlen(pingData));
    len=ICMP_HSIZE+(int)strlen(pingData);
    //数据为int
    //htons htonl 只针对16 32 bit的数据，如果对于像long 64bit的，应该自己写一个转换的。https://blog.csdn.net/yangves/article/details/78085600
    //int tmp = htonl(pingData);
    //memcpy(icmp_hdr->data, &tmp, sizeof(int));
    //len =ICMP_HSIZE+(int)sizeof(int);
    //printf("%x\n",pingData);
    
    icmp_hdr->checksum=0;    //初始化
    
    //TODO: 这里可能本身已经对checksum进行了大小端处理，所以我们如果处理了，反而又退回去了。
    //但是，毋庸置疑的，对于超过一个字节的数据类型是要考虑大小端处理的。 对于字符串因为每次是按一个字节处理的，因此并不需要大小端。
    //http://www.voidcn.com/article/p-bcbputow-wg.html
    //实验出来，对于ICMP协议，其底层对头部和数据 已经做了大小端的处理。即对整个协议包做了大小端的转换的，发包 收包时不用我们管得。
    //我们再处理，反而弄巧成拙，出错。
    // 所以，当你的通信软件要和其他机器上的通信软件（模块）通信时，凡是编解码等地方使用了超过1个字节的数据类型，都最好使用转换函数。在部分socket处理中，也需要加上转换函数（如ipaddr结构的填写等处），另外一部分本身已经包含相关处理，就可以不用加。
    
    //实验出来，底层并没有对ICMP头部和数据 进行大小端处理。 所以，如果涉及超过1字节的数据类型，我们应该要进行大小端处理。
    //默认规范是要进行大小端转换的，因为对方并不知道你到底发了大端还是小端，造成对方困惑。但是如果你按照统一默认规范，都处理成网络字节序（大端），那么对方就可以按照这个统一的规范 规则， 将其转为自己的主机字节序，这样就能保证两边数据的一致性。  当然如果双方知道各自的规则，即如果都要求不做转换，那么接收时也不做转换，收到的数据也是一致的。 不过建议 还是按照业内的主流的方式做，即做大小端的转换，避免沟通成本。
    
    //实验 socket TCP udp 的头部和数据部分。
    //ICMP/TCP/UDP 协议中，基于IP数据报的，IP头部的由底层帮忙处理了大小端(不一定，不同系统还是有不同的处理方式的)。 而我们处理的的是ICMP/UDP/TCP，其头部和数据部分底层是没有进行大小端处理的，需要我们自己处理。
    //ARP协议中，基于以太网帧的。由于底层并没有帮忙处理整个以太网帧，而是全部暴露给我们自己去处理，所以所有的需要大小端处理的需要我们自己去处理。
    //应该这么说，需要我们手动设置的头部和数据部分，如ICMP中ICMP头部字段的值等，如以太网帧中我们设置头部以及IP包(作为以太网帧的数据部分)等，大小端的转换需要我们自己处理。而那些没有我们手动设值的，如TCP协议中IP头部的值等，底层帮我们调用htons等大小端转换啦。
    //在部分socket处理中，也需要加上转换函数（如ipaddr结构的填写等处），另外一部分本身已经包含相关处理，就可以不用加.

    //校验和最好在最后赋值，即等待其他值都赋完值(不管大小端转了没，最好是都大小端处理过的)，再计算checksum。 这个checksum计算出来后不需要再大小端转换了。
    //checksum赋值之后，其他字段不应再赋值或大小端转换。不然这个checksum就错了。
    //校验和并不需要进行大小端转换。 这个比较特殊！因为checksum是对头部的各个数据(已经转换过大小端) 进行checksum的，因此这个值不能也不要转换大小端。
    //https://blog.csdn.net/longhaoyou/article/details/6297380  RFC1071
    //icmp_hdr->checksum=checksum((u8 *)icmp_hdr,len);  //计算校验和
    unsigned short sum = checksum((u8 *)icmp_hdr,len);
    icmp_hdr->checksum = sum;
    printf("checksum %x ", sum);
    printf("%x\n", htons(sum));
    
    ssize_t ret = sendto(sockfd,sendbuf,len,0,(struct sockaddr *)&dest,sizeof (dest)); //经socket传送数据
    
    send_times++;
    printf("%d %ld\n",len, ret);
    
    printf("end send_ping\n");


}
//接收程序发出的ping命令的应答
void recv_reply()
{
    printf("in recv_reply\n");
    long ret_size = 0;
    socklen_t len;
    int errno;
    
    len=sizeof(from);   //发送ping应答消息的主机IP
    
  
    if((ret_size=recvfrom(sockfd,recvbuf,sizeof(recvbuf),0,(struct sockaddr *)&from,&len))<0)
    { //经socket接收数据,如果正确接收返回接收到的字节数，失败返回0.
//        if(errno==EINTR)  //EINTR表示信号中断
//            continue;
        bail("recvfrom error");
    }
    //ret_size 接收的整个IP数据包的长度。  OS收到的最底层的就是以太网帧。 这里接收的三层网络层的全部报文数据，实际是剔除以太网帧头的全部数据,也即以太网真的数据部分。
    printf("receive bytes: %ld\n",ret_size);
    
    printf("sizeof timeval %ld  sizeof long %ld\n",sizeof(struct timeval), sizeof(long));
    
    if(handle_pkt() == 1)
        recv_times++;
    
    printf("end recv_reply\n");

}
//计算校验和
u16 checksum(u8 *buf,int len)
{
    u32 sum=0;
    u16 *cbuf;
    
    cbuf=(u16 *)buf;
    
    while(len>1)
    {
        sum+=*cbuf++;
        len-=2;
    }
    
    if(len)
        sum+=*(u8 *)cbuf;
    
    sum=(sum>>16)+(sum & 0xffff);
    sum+=(sum>>16);
    
    //求反码
    sum = ~sum;
    sum = sum & 0xffff;
    
    return sum;
    //return ~sum;
}
//ICMP应答消息处理
int handle_pkt()
{
    struct iphdr *ip;
    struct icmphdr *icmp;
    
    int ip_hlen;
    u16 ip_datalen; //ip数据长度
    double rtt; // 往返时间
    
    
    gettimeofday(&recvtime,NULL);   //记录收到应答的时间

    
    
    ip=(struct iphdr *)recvbuf;
    
    ip_hlen=ip->hlen << 2; // 长度是以4字节为计算的。 因此*4。
    
    
    //ip_datalen=ntohs(ip->tot_len)-ip_hlen; //不用大小端处理，底层处理了. 显然我们只需关注我们处理的那层数据的大小端，对于下一层的数据，底层会帮忙处理大小端的。 如这里ICMP， 系统本身对IP报文头 做了处理，不用再大小转换了，如ip->total_len.
    //而对于我们处理的层，如ICMP，其头和数据部分都要我们大小端处理。
    //ip_datalen = ip->tot_len - ip_hlen;
    
    //linux中并没有处理这个total_len，这个值还是包含 IP头部分+IP数据部分。这个是比较符合规范的。
    //而且linux中对于ip头部大小端部分，底层并没有做任何处理。大小端需要我们自己处理。
    
    //macos底层中处理这个total_len的时候，是仅仅IP数据部分的长度,并没有包含IP头部的长度。 可以试试linux下的。
    //在这里IP数据部分的长度就是整体ICMP包的长度(ICMP头+ICMP数据)
    
    
    //内置宏： https://blog.csdn.net/Bluechalk/article/details/82490863
    //https://blog.csdn.net/n5/article/details/70143942
#ifdef _WIN32
        //define something for Windows (32-bit and 64-bit, this part is common)
    #ifdef _WIN64
        //define something for Windows (64-bit only)
    #else
        //define something for Windows (32-bit only)
    #endif
#elif __APPLE__
    ip_datalen = ip->tot_len;
    #if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
        //#   error "Unknown compiler"
    #endif
#elif __ANDROID__
    // android
#elif __linux__
    // linux
    ip_datalen = ntohs(ip->tot_len) - ip_hlen;
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif
    

    printf("total_len:%d\n",ip->tot_len);
    printf("total_len:%d\n",ntohs(ip->tot_len));
    
    printf("ip id:%d\n",ip->id);
    printf("ip id:%d\n",ntohs(ip->id));
    
    printf("ver:%x hlen:%x\n",ip->ver,ip->hlen);
    
    
    printf("ip_datalen:%d\n",ip_datalen);

    
    
    icmp=(struct icmphdr *)(recvbuf+ip_hlen);
    
    
    /* wrong!
    //这个checksum 已经被底层大小端转换过了。 实际上是整个ICMP包都被转换过大小端，因此此时再进行函数checksum操作，验证，是没法得出全1的。
    //而且，实际上这个检查工作底层帮忙处理，如果出错，也是不会传到我们这来的。
    //icmp->checksum = ntohs(icmp->checksum);
    wrong!*/
    
    //ip_datalen 也是ICMP包的整体长度。 ICMP的校验和 校验的只是整个包的内容即头部+数据的全部部分。
    u16 sum=(u16)checksum((u8 *)icmp,ip_datalen);
    //u16 sum=ntohs((u16)checksum((u8 *)icmp,ip_datalen));
    printf("The recv pack checksum is:0x%x\n",sum);// 应该全1 或全0(看代码怎么写)   是正确的。
    // ~(A + B) = ~A + ~B   [A  != ~B时]
    // 如果 B = ~A , 则~A + ~B =~A+~(~A) = 1  或  ~(A+B) = ~(A+~A) = 0
    printf("The check sum in  recv pack %x\n",icmp->checksum);
    printf("The check sum in  recv pack %x\n",ntohs(icmp->checksum));
    
    printf("icmp_id %d\n",icmp->icmp_id);
    printf("icmp_id %d\n",ntohs(icmp->icmp_id));

    
    //struct timeval *sendtime;
    //时间戳是s单位。 是从1970.1.1 00:00:00 到现在时间为止的秒。 如果加上时区，如北京 东八区，是从1970.1.1 08:00:00。
    //有的时间戳也有可能是ms级别的。
    
    //    long*ptr = (long*)icmp->icmp_timestamp;
    //    printf("time %lx\n",*ptr);
    //
    //    printf("%ld\n", ntohl(*ptr));
    //    //没有必要大小端转换的，因为这个char的数组。
    //    //*ptr = ntohl(*ptr);
    //    //timeval 是 16字节的，存储s和us。
    //    sendtime=(struct timeval*)(ptr); //发送时间
    
    //实际上不能用这个时间戳的，因为没有达到毫秒级别的。  或者将timeval存为更长空间的数据，放在ICMP的头部的可选项中。这样就可以使用了。
    //sendtime = (struct timeval*)icmp->icmp_timestamp;
    
    printf("recv icmp_timestamp:%ld\n",icmp->icmp_timestamp);
    printf("recv icmp_timestamp ntohl:%uld\n",ntohl(icmp->icmp_timestamp));
    
    
    //    struct timeval* tmp =(struct timeval*)icmp->icmp_timestamp;
    //
    //    printf("tmp time: %ld %d\n",tmp->tv_sec, tmp->tv_usec);
    
    printf("recvtime:%ld %d\n",recvtime.tv_sec, recvtime.tv_usec);
    printf("sendtime:%ld %d\n",sendtime.tv_sec, sendtime.tv_usec);

    
    //int 类型
    //int temp = ntohl(*(int*)icmp->data);
    //printf("pingData in recv: 0x%x\n", temp);

    //char 数组类型。
    printf("%lu size pingData in recv %s\n",strlen((char*)icmp->data), (char*)icmp->data);
    
    
    if(sum != 0xffff && sum != 0x0000) //计算校验和
       return -1;
    
    
    printf("sizeof iphdr %ld\n", sizeof(struct iphdr));
    
    printf("id %d %d pid %d\n",icmp->icmp_id, ntohs(icmp->icmp_id),pid);
    if(ntohs(icmp->icmp_id)!=pid)
        return -1;
//    if(icmp->icmp_id!=pid)
//        return -1;

    if(icmp->type!=ICMP_ECHOREPLY)
        return -1;
    

    //毫秒。   s/ms/us
    rtt=(recvtime.tv_sec-sendtime.tv_sec)*1000+(recvtime.tv_usec-sendtime.tv_usec)/1000.0;// 往返时间
    //打印结果
    printf("%d bytes from %s:icmp_seq=%u ttl=%ld rtt=%.3f ms\n",
           ip_datalen, //IP数据长度
           inet_ntoa(from.sin_addr),    //目的ip地址
           icmp->icmp_seq, //icmp报文序列号
           ip->ttl,  //生存时间
           rtt);    //往返时间
    
    return 1;
}
//设置信号处理程序
void set_sighandler()
{
    //信号触发之后，会有处理信号的处理函数。 SIGALRM 处理函数是alarm_handler。
    //一般 SIGXXX 处理函数就是 xxx_handler
    
    //设置timer信号的处理函数。
    act_alarm.sa_handler=alarm_handler;
    //SIGALRM 为计时器 发出的信号。
    if(sigaction(SIGALRM,&act_alarm,NULL)==-1)  //sigaction()会依参数signum指定的信号编号来设置该信号的处理函数。参数signum指所要捕获信号或忽略的信号，&act代表新设置的信号共用体，NULL代表之前设置的信号处理结构体。这里判断对信号的处理是否成功。
        bail("SIGALRM handler setting fails.");
    
    act_int.sa_handler=int_handler;
    if(sigaction(SIGINT,&act_int,NULL)==-1)
        bail("SIGALRM handler setting fails.");
}
//统计ping命令的检测结果
void get_statistics(int nsent,int nrecv)
{
    printf("--- %s ping statistics ---\n",inet_ntoa(dest.sin_addr)); //将网络地址转换成“.”点隔的字符串格式。
    printf("%d packets transmitted, %d received, %0.0f%% ""packet loss\n",
           nsent,nrecv,1.0*(nsent-nrecv)/nsent*100);
}
//错误报告
void bail(const char * on_what)
{
    fputs(strerror(errno),stderr);  //:向指定的文件写入一个字符串（不写入字符串结束标记符‘\0’）。成功写入一个字符串后，文件的位置指针会自动后移，函数返回值为0；否则返回EOR(符号常量，其值为-1)。
    fputs(":",stderr);
    fputs(on_what,stderr);
    fputc('\n',stderr); //送一个字符到一个流中
    exit(1);
}
 
//SIGINT（中断信号）处理程序
void int_handler(int sig)
{
   
    get_statistics(send_times,recv_times);    //统计ping命令的检测结果
    close(sockfd);  //关闭网络套接字
    exit(1);
}
//SIGALRM（终止进程）处理程序
void alarm_handler(int signo)
{
    if(send_times < SENTIMES)
    {
        //printf("%d\n", signo);
        send_ping();    //发送ping消息
        recv_reply();
        
    }else
    {
        uninit_time();
        get_statistics(send_times,recv_times);    //统计ping命令的检测结果
        exit(1);
    }
}


//验证系统大端还是小端
int checkEndian()
{
    unsigned short data = 0x1234;
    
    char * ptr = (char*)&data;
    
    if(*ptr == 0x12) //数据的高位 在低地址字节
    {
        return _BIG_ENDIAN_BITFIELD;
    }else
    {
        return _LITTLE_ENDIAN_BITFIELD;
    }
}

void set_time()
{
    
    //设置的时间是一个结构体，倒计时设置，重复倒时，超时值设为1秒
    struct itimerval val_alarm;
    
    //it_interval间隔时间。
    //it_value 第一次开始计时器的间隔时间，即第一次使用这个计时器延迟等待的时间。
    //如果it_interval 置为0 ，则只执行一次。 it_value置为0 不执行timmer。
    //settimer工作机制是，第一次先对it_value倒计时，
    //当it_value为零时触发信号，然后重置为it_interval，继续对it_value倒计时，一直这样循环下去。
    /*
     If it_value is non-zero, it indicates the time to the next timer expiration.
     If it_interval is non-zero, it specifies a value to be used in reloading
     it_value when the timer expires.  Setting it_value to 0 disables a timer.
     Setting it_interval to 0 causes a timer to be disabled after its next expi-
     ration (assuming it_value is non-zero).
     */
    
    val_alarm.it_interval.tv_sec = 1;
    val_alarm.it_interval.tv_usec=0;
    val_alarm.it_value.tv_sec=0;
    val_alarm.it_value.tv_usec=1;
    
    
    //设定定时器。 第一个参数表明会触发的信号。
    //The ITIMER_REAL timer decrements in real time.
    //A SIGALRM signal is deliv-ered when this timer expires.
    if((setitimer(ITIMER_REAL,&val_alarm,NULL))==-1) //定时函数
        bail("setitimer fails.");
}

void uninit_time()
{
    struct itimerval value;
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 0;
    
    value.it_interval = value.it_value;
    
    setitimer(ITIMER_REAL, &value, NULL);
}

