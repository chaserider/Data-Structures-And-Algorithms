#include <iostream>

//桶的状态
enum State
{
	STATE_UNUSE,//从未使用
	STATE_USING,//正在使用
	STATE_DEL,//删除
};

//桶的类型
struct Bucket
{
	Bucket(int key = 0, State state = STATE_UNUSE)
		:_key(key)
		, _state(state)
	{}
	int _key;//数据
	State _state;//状态
};

//线性探测哈希表
class HashTable
{
public:
	HashTable(int size = primes_Table[0], double loadFactor = 0.75)
		:useBucketNum(0)
		, load_Factor(loadFactor)
		, prime_Idx(0)
	{
		//调整用户传入的size
		if (size != primes_Table[0])
		{
			for (; prime_Idx < PRIME_SIZE; prime_Idx++)
			{
				if (primes_Table[prime_Idx] > size)
					break;
			}
			if (prime_Idx == PRIME_SIZE)
				prime_Idx--;
		}
		table_size = primes_Table[prime_Idx];
		table = new Bucket[table_size];

	}
	~HashTable()
	{
		delete[]table;
		table = nullptr;
	}

public:
	//插入
	bool insert(int key)
	{
		//考虑扩容
		double factor = useBucketNum * 1.0 / table_size;
		if (factor > load_Factor)
		{
			expand();
		}
		int idx = key % table_size;
		int i = idx;
		do
		{
			if (table[i]._state != STATE_USING)
			{
				table[i]._state = STATE_USING;
				table[i]._key = key;
				useBucketNum++;
				return true;
			}
			i = (i + 1) % table_size;
		} while (i != idx);
		return false;
	}

	//删除
	bool erase(int key)
	{
		int idx = key % table_size;
		int i = idx;
		do
		{
			if (table[i]._state == STATE_USING && table[i]._key == key)
			{
				table[i]._state = STATE_DEL;
				useBucketNum--;
			}
			i = (i + 1) % table_size;
		} while (i != idx && table[i]._state != STATE_UNUSE);
		return true;
	}

	//查询
	bool find(int key)
	{
		int idx = key % table_size;
		int i = idx;
		do
		{
			if (table[i]._state == STATE_USING && table[i]._key == key)
			{
				return true;
			}
			i = (i + 1) % table_size;
		} while (i != idx && table[i]._state != STATE_UNUSE);
		return false;
	}

private:
	void expand()
	{
		++prime_Idx;
		if (prime_Idx == PRIME_SIZE)
			throw "Hash Table too large can not expand anymore";
		Bucket* new_Table = new Bucket[primes_Table[prime_Idx]];
		for (int i = 0; i < table_size; i++)
		{
			if (table[i]._state == STATE_USING)
			{
				int idx = table[i]._key % primes_Table[prime_Idx];
				int k = idx;

				do {
					if (new_Table[k]._state != STATE_USING)
					{
						new_Table[k]._key = table[i]._key;
						new_Table[k]._state = STATE_USING;
						break;
					}
					k = (k + 1) % primes_Table[prime_Idx];
				} while (k != idx);
			}
		}
		delete[]table;
		table = new_Table;
		table_size = primes_Table[prime_Idx];
	}
private:
	Bucket* table;//动态开辟的哈希表
	int table_size;//哈希表大小
	int useBucketNum;//已经使用的桶个数
	double load_Factor;//装载因子

	static const int PRIME_SIZE = 10;//素数表大小
	static int primes_Table[PRIME_SIZE];//素数表
	int prime_Idx;//当前使用的素数
};
int HashTable::primes_Table[PRIME_SIZE] = { 3,7,23,47,97,251,443,911,1471,42773 };

int main()
{
	HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);
	htable.insert(15);


	std::cout << htable.find(21) << std::endl;
	htable.erase(21);
	std::cout << htable.find(21) << std::endl;
	std::cin.get();
}

