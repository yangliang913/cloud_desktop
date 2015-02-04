/*
 * @file	singleton.h
 * @brief	����ģʽ��ʵ��
 *
 * @author	yangliang
 * @version 1.0
 * @date	2014-3-24
*/
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <assert.h>
#include <memory>
using namespace std;

template <typename T>
class Singleton
{
public:
	//��ʼ������
	Singleton(void)
	{
	}
	~Singleton(void)
	{

	}

	//����ʵ��
	static T& Instance(void)
	{
		if (NULL == _pInstance)
		{
			_pInstance = new T;
		}
		return (*_pInstance);
	}

	//����ʵ��ָ��
	static T* InstancePtr(void)
	{
		if (NULL == _pInstance)
		{
			_pInstance = new T;
		}
		return _pInstance;
	}

	static void DeleteObj()
	{
		if (NULL != _pInstance)
		{
			delete _pInstance;
			_pInstance = NULL;
		}
	}
protected:
	//���ڱ���ʵ��ָ��
	static T* _pInstance;
};

template <typename T> T* Singleton<T>::_pInstance = NULL;
#endif