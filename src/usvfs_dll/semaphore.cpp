#include "semaphore.h"
#include <spdlog.h>
//#include <scopeguard.h>


RecursiveBenaphore::RecursiveBenaphore()
	: m_mutex()
	//  , m_Counter(0)
	//  , m_OwnerId(0UL)
	//,m_Recursion(0)
{
	InitializeCriticalSection(&m_mutex);
	//m_Semaphore = CreateSemaphoreW(nullptr, 1, 1, nullptr);
}

RecursiveBenaphore::~RecursiveBenaphore()
{
	//CloseHandle(m_Semaphore);
	DeleteCriticalSection(&m_mutex);
}

//void RecursiveBenaphore::wait(DWORD timeout)
//{
//	const auto tid = GetCurrentThreadId();
//
//	if (_InterlockedIncrement(&m_Counter) > 1)
//	{
//		if (tid != m_OwnerId)
//		{
//			auto tries = 3;
//			while (WaitForSingleObject(m_Semaphore, timeout) != WAIT_OBJECT_0)
//			{
//				auto owner = OpenThread(SYNCHRONIZE, FALSE, m_OwnerId);
//				ON_BLOCK_EXIT([owner]() { ::CloseHandle(owner); });
//				if (tries <= 0 || WaitForSingleObject(owner, 0) == WAIT_OBJECT_0)
//				{
//					// owner has quit without releasing the semaphore!
//					m_Recursion = 0;
//					spdlog::get("usvfs")
//						->error("thread {} never released the mutex", m_OwnerId);
//					break;
//				}
//				--tries;
//			}
//		}
//	}
//	m_OwnerId = tid;
//	++m_Recursion;
//}
//
//void RecursiveBenaphore::signal()
//{
//	if (m_Recursion == 0)
//	{
//		return;
//	}
//	// no validation the signaling thread is the one owning the lock
//	const DWORD recursion = --m_Recursion;
//	if (recursion == 0)
//	{
//		m_OwnerId = 0;
//	}
//	const DWORD result = _InterlockedDecrement(&m_Counter);
//	if (result > 0)
//	{
//		if (recursion == 0)
//		{
//			ReleaseSemaphore(m_Semaphore, 1, nullptr);
//		}
//	}
//}

void RecursiveBenaphore::lock()
{
	EnterCriticalSection(&m_mutex);
}

void RecursiveBenaphore::unlock()
{
	LeaveCriticalSection(&m_mutex);
}
