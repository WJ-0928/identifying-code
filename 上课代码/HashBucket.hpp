#pragma once
#include "Common.h"


template<class T>
struct HBNode
{
	HBNode(const T& data = T())
	: _data(data)
	, _pNext(nullptr)
	{}

	T _data;
	HBNode<T>* _pNext;
};


// 假设：哈希桶中的元素时唯一的
template<class T>
class HashBucket
{
	typedef HBNode<T> Node;

public:
	HashBucket(size_t capacity = 10)
		: _table(GetNextPrime(capacity))
		, _size(0)
	{}

	bool Insert(const T& data)
	{
		// 1. 通过哈希函数计算data所在的桶号
		size_t bucketNo = HashFunc(data);

		// 2. 检测该元素是否在bucketNo桶中
		//    本质：检测链表中是否存在data的节点
		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return false;

			pCur = pCur->_pNext;
		}

		// 插入新节点
		pCur = new Node(data);
		pCur->_pNext = _table[bucketNo];
		_table[bucketNo] = pCur;
		++_size;
		return true;
	}

	Node* Find(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (data == pCur->_data)
				return pCur;

			pCur = pCur->_pNext;
		}

		return nullptr;
	}

	bool Erase(const T& data)
	{
		size_t bucketNo = HashFunc(data);
		Node* pCur = _table[bucketNo];
		Node* pPre = nullptr;

		while (pCur)
		{
			if (data == pCur->_data)
			{
				// 删除
				if (_table[bucketNo] == pCur)
				{
					// 删除第一个节点
					_table[bucketNo] = pCur->_pNext;
				}
				else
				{
					// 删除的不是第一个节点
					pPre->_pNext = pCur->_pNext;
				}

				delete pCur;
				--_size;
				return true;
			}

			pPre = pCur;
			pCur = pCur->_pNext;
		}

		return false;
	}

	void Swap(HashBucket<T>& ht)
	{
		_table.swap(ht._table);
		swap(_size, ht._size);
	}

	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
##if 0
			HashBucket<T> ht(_size*2);

			// 将旧哈希桶中的元素向新哈希桶中进行搬移
			// 搬移所有旧哈希桶中的元素
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* pCur = _table[i];
				while (pCur)
				{
					ht.Insert(pCur->_data); // new 节点
					pCur = pCur->_pNext;
				}
			}

			Swap(ht);
#endif
			HashBucket<T> ht(GetNextPrime(_size));

			// 将旧哈希桶中的节点直接向新哈希桶中搬移
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* pCur = _table[i];
				while (pCur)
				{
					// 将pCur节点从旧哈希桶搬移到新哈希桶
					// 1. 将pCur节点从旧链表中删除
					_table[i] = pCur->_pNext;

					// 2. 将pCur节点插入到新链表中
					size_t bucketNo = ht.HashFunc(pCur->_data);

					// 3. 插入节点--->头插
					pCur->_pNext = ht._table[bucketNo];
					ht._table[bucketNo] = pCur;
				}
			}

			this->Swap(ht);
		}
	}

private:
	size_t HashFunc(const T& data)
	{
		return data%_table.capacity();
	}

private:
	vector<Node*> _table;
	size_t _size;
};