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


// ���裺��ϣͰ�е�Ԫ��ʱΨһ��
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
		// 1. ͨ����ϣ��������data���ڵ�Ͱ��
		size_t bucketNo = HashFunc(data);

		// 2. ����Ԫ���Ƿ���bucketNoͰ��
		//    ���ʣ�����������Ƿ����data�Ľڵ�
		Node* pCur = _table[bucketNo];
		while (pCur)
		{
			if (pCur->_data == data)
				return false;

			pCur = pCur->_pNext;
		}

		// �����½ڵ�
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
				// ɾ��
				if (_table[bucketNo] == pCur)
				{
					// ɾ����һ���ڵ�
					_table[bucketNo] = pCur->_pNext;
				}
				else
				{
					// ɾ���Ĳ��ǵ�һ���ڵ�
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

			// ���ɹ�ϣͰ�е�Ԫ�����¹�ϣͰ�н��а���
			// �������оɹ�ϣͰ�е�Ԫ��
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* pCur = _table[i];
				while (pCur)
				{
					ht.Insert(pCur->_data); // new �ڵ�
					pCur = pCur->_pNext;
				}
			}

			Swap(ht);
#endif
			HashBucket<T> ht(GetNextPrime(_size));

			// ���ɹ�ϣͰ�еĽڵ�ֱ�����¹�ϣͰ�а���
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* pCur = _table[i];
				while (pCur)
				{
					// ��pCur�ڵ�Ӿɹ�ϣͰ���Ƶ��¹�ϣͰ
					// 1. ��pCur�ڵ�Ӿ�������ɾ��
					_table[i] = pCur->_pNext;

					// 2. ��pCur�ڵ���뵽��������
					size_t bucketNo = ht.HashFunc(pCur->_data);

					// 3. ����ڵ�--->ͷ��
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