#ifndef __COMMON_H__
#define __COMMON_H__
#include <QString>
#include <QMutex>
#include <QWaitCondition>

#define LOG_MSG_LEN		256									//��־�ַ����ĳ���
const int MAX_HOST_NUM = 256;

//������־�ĵȼ�
enum LOG_LEVEL
{
	ZCFATAL = 0,		//��������
	ZCERROR,			//����
	ZCWARN,				//����
	ZCINFO,				//��ʾ��Ϣ
	ZCDEBUG				//����		
};

struct Connections{
	char displayName[32];
	char displayPassword[32];
	char externalAddress[32];
	char internalAddress[32];
};

struct ControlServer{
	char externalAddress[32];
	char internalAddress[32];
};

struct Ports 
{
	int protocol;//Э��:0����Э��;1TCP;2DUP
	char port[8];//��Ҫ���ŵĶ˿�
	char server_port[8];//�������˿�
	char outer_port[8];//ӳ�䵽�����Ķ˿�
};

struct HostMessage
{
	char id[64];//Ψһ��ʶ
	char host_name[256];//������
	int type;//���ͣ�1��Ӫ������;2����������;3�ն��û�����
	char account[32];
	char password[32];
	int cpu_core;//cpu��������
	int cpu_usage;
	int memory;//�ڴ�
	int memory_usage;
	int sys_disk;//ϵͳ��������
	int sys_disk_usage;
	int data_disk;//���ݴ�������
	int data_disk_usage;
	int bandwidth;//�������
	int is_auto_startup;//�Ƿ��Զ�����:1��;2��
	int running_status;//����״̬:1�ػ�;2����
	int status;//״̬:1����;2ͣ��;3Ƿ��
	int region; // 1: ����,2���ɶ�,3������,4�����
	char inner_ip[32];//������ص�ַIP
	char inner_port[8];//������ص�ַ�˿�
	char outer_ip[32];//������ص�ַIP
	char outer_port[8];//����������ַ�˿�
	char sysImageName[32]; /*ϵͳ���� Ҫģ��ƥ�� windows7 windows2003 windows2008 windows2012 centos */
	char inactivate_time[32]; //ͣ��ʱ�䣬��ʽΪyyyyMMddHHmmssSSS

	int portsNum;
	Ports ports[1];//ÿ�������Ķ˿ڸ�������
};

//��֤�󷵻ص����ݣ��ýṹ�����
struct LoginAuth{
	char status[16];
	char message[256];
	int connectionsNum;
	ControlServer server;
	Connections connections[1];
};

//��������Ϣ
struct TotalHostMessage
{
	char status[16];
	char message[256];
	int hostNum;
	HostMessage hostmsg[1];//��������������
	//HostMessage hostmsg[MAX_HOST_NUM];
};

//��������
enum ZcCommandType
{
	Auth = 1,					//��Ȩ����
	GetHostInfo = 2,			//��ȡ��������Ϣ
	UpdateHostInfo = 3,			//������������Ϣ
	StartHost = 4,				//����������
	StopHost = 5,				//�ر�������
	RestartHost = 6,			//����������
	ModifyHostConfig = 7,		//�޸�����������
	ForceStopHost = 8,			//ǿ�ƹر�������
	QueryHostPrice = 9,			//��ѯ�����޸�����ʱ�۸�
	QueryLastVersion = 10,		//��ѯ���°汾��
	FirstQueryHostPrice = 11,	//ÿ�ν�������ҳ���ѯ�������۸�
	UpdateHostInfo2				//����һֱ������������Ϣ
};

//�������������ص�����
struct ControlHostMsg{
	char status[16];
	char message[256];
};

enum RETURNCMD{
	INVALIDPASSWORD = 1,
	UNKNOWURI,
	NORMALCLOSE,
	VIRTSTARTSUCC,
};
struct remote_viewer_data
{
	char ip_str[64];
	char host_name[64];
	int hostIndex;
	enum RETURNCMD mark;
	char dispalay_password[64];
};
//��ȡ��������ǰ���õļ۸�
struct Price{
	double monthlyPrice;	//��ǰ����һ���µļ۸�
	double balance;			//��ǰ�����
};
struct HostPrice{
	char status[16];
	char message[256];
	Price price;
};
/*
ģ��ƥ�������ַ���
windows7
windows2003
windows2008
windows2012
centos
*/
enum SysImageType{
	SysUnknow = -1,
	SysWindows7 = 1,
	SysWindows2003 = 2,
	SysWindows2008 = 3,
	SysWindows2012 = 4,
	SysCentos =5,
	SysCentos6_4 = 6,
	SysCentos6_5 = 7,
	SysUbuntu =8,
	SysUbuntu12_04 = 9,
	SysUbuntu14_04 = 10

};
struct Versions
{
	char updateinfo[2024];//������Ϣ��־����
	char name[64]; //���°汾��
	char path[256]; //�����������ַ
	//char update_process_address[256];//���³����ַ

};
struct ProgressVersion
{
	char status[16];
	char message[256];
	Versions versions;
};

#endif