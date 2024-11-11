//һ���Թ�ϣ   �ֲ�ʽϵͳ���ؾ������ѡ�㷨   ��������Ŀ��������nginx/lvs
// һ�����õķֲ�ʽ��ϣ����Ӧ�þ������õĵ����ԣ�������ڵ�������䲻����ɴ�����ϣ�����¶�λ
// һ���ͻ�����Զ��ӳ�䵽һָ̨���ķ�������
//��������������ؾ����㷨�� ��ѯ�㷨  ��ϣ�㷨��Ȩ�ر��㷨�����������㷨
//���渺�ط���  ���汾����м�Ⱥ



//һ���Թ�ϣ�㷨˼·��
//��������ϣֵ�ռ�����һ����   ȡֵ��ΧΪ0-2^32-1��unsigned int����4G�Ŀռ�
//�����з��������й�ϣ��md5 server_ip�� �����䵽һ���Թ�ϣ����
//���и���ʱ���ȹ�ϣ����õ�һ���Թ�ϣ���ϵ�һ����ϣֵ���ú�����˳ʱ�룬�����ĵ�һ̨�������������յķ�����
//����ڵ�  ��һ�����������ɶ������������ɢ��һ���Թ�ϣ���� ��ֹ�������٣����¹�ϣ�������һ����������

#include <iostream>
#include <string>
#include <set>//�����
#include<list>
#include "md5.h"
#include <map>
using namespace std;

using uint = unsigned int;
class PhscialHost;
//����ڵ�
class VirtualHost
{
public:
	VirtualHost(string ip, PhscialHost* pHost)
		:_ip(ip),
		phscialHost(pHost) 
	{
		md5_ = ::getMD5(_ip.c_str());
	};
	bool operator<(const VirtualHost& host)
	{
		return md5_ < host.md5_;
	}
	bool operator == (const VirtualHost & host)
	{
		return _ip == host._ip;
	}
	uint getMD5()const
	{
		return md5_;
	}
	const PhscialHost* getPhscialHost()const
	{
		return phscialHost;
	}
private:
	string _ip;
	uint md5_;//һ���Թ�ϣ���ϵ�λ��
	PhscialHost* phscialHost;
};
//����ڵ�
class PhscialHost
{
private:
	string _ip;//���������ip��ַ
	list<VirtualHost> virtualHosts;//����ڵ��б�
public:
	PhscialHost(string ip, int virtualnum)
		:_ip(ip)
	{
		for (int i = 0; i < virtualnum; i++)
		{
			//����ڵ���Ҫһ��ip������Ҫ��¼�����ĸ�����ڵ�
			virtualHosts.emplace_back(ip+"#"+to_string(i),this);
		}
	}
	string getIP()const
	{
		return _ip;
	}
	const list<VirtualHost>& getVirtualHosts()const
	{
		return virtualHosts;
	}
};
//һ���Թ�ϣ
class ConsistentHash
{
public:
	//��һ���Թ�ϣ���ϼ�����
	void addHost(PhscialHost& host)
	{
		//��ȡ�����������е������б�
		auto list = host.getVirtualHosts();
		for (auto& host : list)
		{
			consistentHash.insert(host);
		}
	}
	void delHost(PhscialHost& host)
	{
		//��ȡ�����������е������б�
		auto list = host.getVirtualHosts();
		for (auto& host : list)
		{
			auto it = consistentHash.find(host);
			if (it != consistentHash.end())
			{
				consistentHash.erase(it);
			}

		}

	}
	//���ظ��ص�����ڵ�IP��Ϣ
	string getHost(string clientip)
	{
		uint md5 = getMD5(clientip.c_str());
		for (auto &vhost : consistentHash)
		{
			if (vhost.getMD5() > md5)
			{
				return vhost.getPhscialHost()->getIP();
}
		}
		//ת��һȦû�ҵ���ӳ�䵽��0��ʼ�����ĵ�һ������ڵ�
		return consistentHash.begin()->getPhscialHost()->getIP();
	}

private:
	set<VirtualHost> consistentHash;
	
};


//����һ���Թ�ϣ�Ĺ���
int main()
{
	PhscialHost host1("10.117.124.10", 150);
	PhscialHost host2("10.117.124.00", 150);
	PhscialHost host3("10.117.124.11", 150);
	ConsistentHash chash;
	chash.addHost(host1);
	chash.addHost(host2);
	chash.addHost(host3);

	list<string>  iplists{
	"198.168.1.123",
	"198.168.1.124",
	"198.168.1.1",
	"198.168.1.13",
	"198.168.1.16",
	"198.168.1.23",
	"198.168.1.145",
	"198.168.23.145",
	"198.168.21.145",
	};

	map<string, list<string>> logMap;
	for(auto &ip:iplists)
	{
		string phost=chash.getHost(ip);
		logMap[phost].emplace_back(ip);
	}

	for (auto pair : logMap)
	{
		cout << "��������" << pair.first << endl;
		cout << "�ͻ���ӳ������" << pair.second.size() << endl;
		for (auto &ip : pair.second)
		{
			cout << ip << endl;
		}
		cout << "----------------------" << endl;
		cout << "----------------------" << endl;
	}
}