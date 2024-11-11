//一致性哈希   分布式系统负载均衡的首选算法   服务器项目开发比如nginx/lvs
// 一个良好的分布式哈希方案应该具有良好的单调性，即服务节点的增减变不会造成大量哈希的重新定位
// 一个客户端永远被映射到一台指定的服务器上
//服务器反向代理负载均衡算法有 轮询算法  哈希算法、权重比算法、最少连接算法
//缓存负载服务  缓存本身进行集群



//一致性哈希算法思路、
//将整个哈希值空间理解成一个环   取值范围为0-2^32-1（unsigned int）共4G的空间
//将所有服务器进行哈希（md5 server_ip） 最终落到一致性哈希环上
//进行负载时，先哈希输入得到一致性哈希环上的一个哈希值，让后沿着顺时针，遇到的第一台服务器就是最终的服务器
//虚拟节点  把一个服务器看成多个虚拟主机分散在一致性哈希环上 防止主机过少，导致哈希处理后挤在一个服务器上

#include <iostream>
#include <string>
#include <set>//红黑树
#include<list>
#include "md5.h"
#include <map>
using namespace std;

using uint = unsigned int;
class PhscialHost;
//虚拟节点
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
	uint md5_;//一致性哈希环上的位置
	PhscialHost* phscialHost;
};
//物理节点
class PhscialHost
{
private:
	string _ip;//物理机器的ip地址
	list<VirtualHost> virtualHosts;//虚拟节点列表
public:
	PhscialHost(string ip, int virtualnum)
		:_ip(ip)
	{
		for (int i = 0; i < virtualnum; i++)
		{
			//虚拟节点需要一个ip，还需要记录属于哪个物理节点
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
//一致性哈希
class ConsistentHash
{
public:
	//在一致性哈希环上加主机
	void addHost(PhscialHost& host)
	{
		//获取物理主机所有的虚拟列表
		auto list = host.getVirtualHosts();
		for (auto& host : list)
		{
			consistentHash.insert(host);
		}
	}
	void delHost(PhscialHost& host)
	{
		//获取物理主机所有的虚拟列表
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
	//返回负载的物理节点IP信息
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
		//转了一圈没找到，映射到从0开始遇见的第一个虚拟节点
		return consistentHash.begin()->getPhscialHost()->getIP();
	}

private:
	set<VirtualHost> consistentHash;
	
};


//测试一致性哈希的功能
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
		cout << "物理主机" << pair.first << endl;
		cout << "客户端映射数量" << pair.second.size() << endl;
		for (auto &ip : pair.second)
		{
			cout << ip << endl;
		}
		cout << "----------------------" << endl;
		cout << "----------------------" << endl;
	}
}