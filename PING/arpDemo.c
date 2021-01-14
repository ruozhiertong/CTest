#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> //for htons
//#include <net/ethernet.h>  // for ETHERTYPE_ARP
#include <stdlib.h> //for exit()
#include <string.h> // for memcpy




#define EPT_IP   0x0800    /* type: IP */
#define EPT_ARP   0x0806    /* type: ARP */
#define EPT_RARP 0x8035    /* type: RARP */
#define ARP_HARDWARE 0x0001    /* Dummy type for 802.3 frames */
#define ARP_REQUEST 0x0001    /* ARP request */
#define ARP_REPLY 0x0002    /* ARP reply */

#define ETH_P_ALL 0x3


#define DBG_LVL_NONE   0x00
#define DBG_LVL_DBG   0x01
#define DBG_LVL_INFO   0x02
#define DBG_LVL_ERR    0x04
#define DBG_LVL_ALL    0xFF


#define OK 1
#define ERROR -1
#define NET_DEVICE_NAME "en1"
#define RAW_PACKET_LEN_MAX 1514
#define RAW_PACKET_LEN_MIN 14
#define ETH_ALEN 6
#define IP_ALEN 4
#define BROADCAST_MAC_ADDR "FF:FF:FF:FF:FF:FF"
#define ETH_P_ARP 0x0806
#define ARPHRD_ETHER 1
#define ETH_P_IP 0x0800
#define ARPOP_REQUEST 6
#define DPRINT_DBG(fmt, ...)   DBG_PRINT(DBG_LVL_DBG, fmt, ##__VA_ARGS__)
#define DPRINT_ERR(...)
// #define dfree(p) \
// 	do \
// 	{\
// 	if (p) \
// 		{ \
// 		DPRINT_DBG("free mem, p = %p\n", p); \
// 		free(p); \
// 		p = NULL; \
// 		} \
// 	}while (0)


typedef struct ether_addr{
	unsigned char ether_addr_octet[ETH_ALEN];
}ETH_ADDR;


typedef struct ether_header{
	unsigned char  ether_dhost[ETH_ALEN]; /* destination eth addr */
	unsigned char  ether_shost[ETH_ALEN]; /* source ether addr */
	unsigned short ether_type;                 /* packet type ID field */
}ETH_HEADER;

typedef struct _ARP_HDR
{
	unsigned short int ar_hrd;		/* Format of hardware address.  */    
	unsigned short int ar_pro;		/* Format of protocol address.  */    
	unsigned char ar_hln;		/* Length of hardware address.  */    
	unsigned char ar_pln;		/* Length of protocol address.  */    
	unsigned short int ar_op;		/* ARP opcode (command).  */

	unsigned char ar_sha[ETH_ALEN];	/* Sender hardware address.  */    
	unsigned char ar_sip[4];		/* Sender IP address.  */    
	unsigned char ar_tha[ETH_ALEN];	/* Target hardware address.  */    
	unsigned char ar_tip[4];		/* Target IP address.  */
}ARP_HDR;


typedef struct _RAW_DATA
{
	int		len;		/* 原始数据长度 */
	char		*data;	/* 原始数据起始地址 */
}RAW_DATA;



// //定义以太网首部
// typedef struct ehhdr 
// {
// unsigned char eh_dst[6];   /* destination ethernet addrress */
// unsigned char eh_src[6];   /* source ethernet addresss */
// unsigned short eh_type;   /* ethernet pachet type */
// }EHHDR, *PEHHDR;

// //定义以太网arp头部
// typedef struct arphdr
// {
// 	unsigned short arp_hrd;    /* format of hardware address */
// 	unsigned short arp_pro;    /* format of protocol address */
// 	unsigned char arp_hln;    /* length of hardware address */
// 	unsigned char arp_pln;    /* length of protocol address */
// 	unsigned short arp_op;     /* ARP/RARP operation */

// 	unsigned char arp_sha[6];    /* sender hardware address */
// 	unsigned long arp_spa;    /* sender protocol address */
// 	unsigned char arp_tha[6];    /* target hardware address */
// 	unsigned long arp_tpa;    /* target protocol address */
// }ARPHDR, *PARPHDR;

// //定义整个arp报文包，总长度42字节
// typedef struct arpPacket
// {
// 	EHHDR ehhdr;
// 	ARPHDR arphdr;
// } ARPPACKET, *PARPPACKET;





int send_arp()
{

	return 0;
}

int recv_arp_reply()
{
	return 0;
}



/****************************************************************************
* Function   : 	mac_string2mac_hex
* Description: 	将字符串形式的MAC地址转换为十六进制形式

* Input      : 	mac_str : MAC地址字符串形式指针
mac_hex : MAC地址十六进制形式指针

* Output     : 	N/A
* Return     :	成功返回OK，出错返回ERROR
****************************************************************************/
int mac_string2mac_hex(char *mac_str, ETH_ADDR *mac_hex)
{
	int tmp[ETH_ALEN] = {0};

	int i;

	if (!mac_str || !mac_hex)
	{
		return ERROR;
	}

	sscanf(mac_str, "%x%*[:-]%x%*[:-]%x%*[:-]%x%*[:-]%x%*[:-]%x", 
		&tmp[0], &tmp[1], &tmp[2], &tmp[3], &tmp[4], &tmp[5]);

	for (i = 0; i < ETH_ALEN; i++)
	{
		mac_hex->ether_addr_octet[i] = tmp[i];
	}

	return OK;
}

/****************************************************************************
* Function   : 	eth_header_init
* Description: 	以太网头部初始化

* Input      : 	fbuf     : 帧缓存
dmac_str : 目的MAC地址
smac_str : 源MAC地址
pt  : 协议类型

* Output     : 	N/A
* Return     :	成功返回OK，出错返回ERROR
****************************************************************************/
int eth_header_init(char *fbuf, char *dmac_str, char *smac_str, unsigned short pt)
{
	ETH_ADDR dmac_hex;
	ETH_ADDR smac_hex;
	int ret;
	ETH_HEADER *eth = NULL;

	if (!fbuf || !dmac_str || !smac_str)
	{
		return ERROR;
	}

	memset(&smac_hex, 0, sizeof(ETH_ADDR));
	mac_string2mac_hex(dmac_str, &dmac_hex);
	mac_string2mac_hex(smac_str, &smac_hex);

	/* 填充以太网头部 */
	eth = (ETH_HEADER *)fbuf;

	memcpy((void *)eth->ether_dhost, (void *)dmac_hex.ether_addr_octet, ETH_ALEN);
	memcpy((void *)eth->ether_shost, (void *)smac_hex.ether_addr_octet, ETH_ALEN);

	eth->ether_type = htons(pt);

	return OK;
}




/****************************************************************************
* Function   : 	raw_socket_init
* Description: 	创建原始套接字，并设置为非阻塞模式，并绑定到指定设备
仅用于协议族PF_PACKET

* Input      : 	protocol : 协议类型
dev      : 设备名称 

* Output     : 	N/A
* Return     :	成功返回socket文件描述符，出错返回ERROR
****************************************************************************/
int raw_socket_init(int protocol, char *dev)
{
	int rawsock;
	int ret;
	/* 创建原始套接字 */
	if ((rawsock = socket(PF_INET, SOCK_RAW, htons(protocol))) < 0){
		perror("socket");
		return ERROR;
	}
	/* 将套接字与设备绑定 */
	// ret = bind_to_device(rawsock, protocol, dev);
	// if (ERROR == ret)
	// {
	// 	DPRINT_ERR("set socket nonblocking failed\n");
	// 	close(rawsock);
	// 	return ERROR;
	// }
	return rawsock;
}



/****************************************************************************
* Function   : 	raw_data_send
* Description: 	用原始套接字将数据发送出去
约定数据长度不得大于1500字节，不得小于14字节

* Input      : 	rawsock : 套接字
rawdata : 数据缓存结构指针

* Output     : 	N/A
* Return     :	成功返回OK，出错返回ERROR
****************************************************************************/
int raw_data_send(int rawsock, RAW_DATA *rawdata)
{
	int ret;
	if (rawdata->len < RAW_PACKET_LEN_MIN || rawdata->len > RAW_PACKET_LEN_MAX)
	{
		return ERROR;
	}
	struct sockaddr_in dest;//被ping主机的ip

 	memset(&dest,0,sizeof dest);  //将dest中前sizeof(dest)个字节替换为0并返回s,此处为初始化,给最大内存清零
    dest.sin_family=PF_INET;  //PF_INET为IPV4，internet协议，在<netinet/in.h>中，地址族
    dest.sin_port=ntohs(0);   //端口号,ntohs()返回一个以主机字节顺序表达的数。
    dest.sin_addr.s_addr  = inet_addr("192.168.43.1");

	ret = sendto(rawsock, (const char*)rawdata->data, rawdata->len, 0, (const struct sockaddr *)&dest, sizeof dest);

	printf("send %d %d bytes\n", ret,rawdata->len);
	//ret = send(rawsock, (const char*)rawdata->data, rawdata->len, 0);
	if (ret != rawdata->len)
	{
		return ERROR;
	}
	return OK;
}


int send_arp_request(int rawsock, char *smac, char *sip, char *tip)
{
	RAW_DATA rawdata;
	ETH_ADDR des_hex;
	ETH_ADDR src_hex;

	ARP_HDR *ah = NULL;

	char *frame = NULL;

	int ret;

	/* 分配帧缓存 */
	frame = (char *)calloc(RAW_PACKET_LEN_MAX, sizeof(char));
	if (!frame)
	{
		DPRINT_ERR("calloc frame buf error\n");
		return ERROR;
	}


	ret = eth_header_init(frame, BROADCAST_MAC_ADDR, smac, ETH_P_ARP);
	if (ret != OK)
	{
		DPRINT_ERR("eth header init failed\n");
		goto error;
	}

	ah = (ARP_HDR *)(frame + sizeof(ETH_HEADER));

	ah->ar_hrd = htons(ARPHRD_ETHER);
	ah->ar_pro = htons(EPT_IP);//htons(ETH_P_IP);
	ah->ar_hln = ETH_ALEN;
	ah->ar_pln = IP_ALEN;
	ah->ar_op = htons(ARPOP_REQUEST);

	/* 发送方MAC */
	mac_string2mac_hex(smac, &src_hex);
	memcpy(ah->ar_sha, &src_hex, ETH_ALEN);

	/* 发送方IP */
	*((unsigned int *)ah->ar_sip) = inet_addr(sip);

	/* 目的方MAC置0 */
	memset(ah->ar_tha, 0, ETH_ALEN);

	/* 目的方IP */
	*((unsigned int *)ah->ar_tip) = inet_addr(tip);

	char * hello = (char*)(frame + sizeof(ETH_HEADER) + sizeof(ARP_HDR));


	strcpy(hello,"helloworld");

	rawdata.data = (void *)frame;
	rawdata.len = sizeof(ETH_HEADER) + sizeof(ARP_HDR) + strlen("helloworld");


	ret = raw_data_send(rawsock, &rawdata);
	printf("%d\n", ret);
	if (ret != OK)
	{
		DPRINT_ERR("raw data send error\n");
		goto error;
	}


	//dfree(frame);

	free(frame);

	return OK;

error:
	//dfree(frame);
	free(frame);

	return ERROR;
}




/****************************************************************************
* Function   : 	send_gratuitous_arp
* Description: 	通过发送GARP来使局域网内的主机更新ARP缓存

* Input      :	smac_str : 源MAC地址
sip_str  : 源IP地址
retry    : 发送次数

* Output     : 	N/A
* Return     :	发送成功返回OK,出错返回ERROR
****************************************************************************/
int send_gratuitous_arp(char *smac_str, char *sip_str, int retry)
{
	int rawsock;
	ETH_ADDR src_hex;
	RAW_DATA rawdata;

	int ret , i;

	if (!smac_str || !sip_str)
	{
		DPRINT_ERR("invalid argument\n");
		return ERROR;
	}

	mac_string2mac_hex(smac_str, &src_hex);

	/* 初始化原始套接字 */
	rawsock = raw_socket_init(ETH_P_ARP, NET_DEVICE_NAME);
	if (ERROR == rawsock)
	{
		DPRINT_ERR("raw socket init error\n");
		return ERROR;
	}

	/* 发送ARP请求 */
	for (i = 0; i < retry; i++)
	{
		ret = send_arp_request(rawsock, smac_str, sip_str, sip_str);
		if (ret != OK)
		{
			DPRINT_ERR("send arp request failed\n");
#ifdef _WIN32
			closesocket(rawsock);
#else

			close(rawsock);
#endif
			return ERROR;
		}
	}

#ifdef _WIN32
	closesocket(rawsock);
#else

	close(rawsock);
#endif

	return OK;
}




int main()
{
	int sockfd;
	//因为使用PF_INET, 而第三参数用ETH_P_ARP 是不起作用的。 因为PF_INET是在网络层及以上的，就算用的是链路层协议的选项ETH_P_ARP，也不起作用，会默认用到网络层的基本数据格式的，
	//因此最后抓包发现的是IP数据报格式的。 如包 socket1.pcapng
	sockfd = socket(PF_INET,SOCK_RAW,ETH_P_ARP);
	

	//由于MacOS中没有AF_PACK，而是bpf。 bpf 见 arpDemo2_bpf.c
	//https://stackoverflow.com/questions/7284853/af-packet-equivalent-under-mac-os-x-darwin
	//https://www.cnblogs.com/diligenceday/p/6246786.html?utm_source=tuicool&utm_medium=referral
	//sockfd = socket(AF_PACK, SOCK_RAW , ETH_P_ARP);
	//raw_socket_init(ETH_P_ARP, "en0");
	if(sockfd<0)
	{
		perror("raw socket created error");
        exit(1);
	}
	
	send_arp_request(sockfd,"20:c9:d0:cb:f2:e2","192.168.43.102","192.168.43.1");
	
	return 0;
}

