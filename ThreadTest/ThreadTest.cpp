#include <iostream>
#include <Windows.h>

DWORD WINAPI ThreadFuc(LPVOID);
DWORD WINAPI ThreadFuc1(LPVOID);

int main()
{
	HANDLE hThread,hThread1;
	DWORD ThreadId;
	DWORD ThreadId1;
	DWORD ExitCode;
	bool GetExit;

	hThread1 = CreateThread(NULL,0, ThreadFuc1, 0, 0, &ThreadId1);
	hThread = CreateThread(NULL, 0, ThreadFuc, 0, 0, &ThreadId);
	std::cout << ThreadId1 << "Thread1 Running" << std::endl;
	std::cout <<  ThreadId <<"Thread running" << std::endl;

	WaitForSingleObject(hThread1, INFINITE);

	while(1) {
		GetExit = GetExitCodeThread(hThread, &ExitCode);

		if (GetExit == true && ExitCode == STILL_ACTIVE) {
			std::cout << "Thread is still alive" << std::endl;
		} else {
			CloseHandle(hThread);
//			ExitThread(4);
			std::cout << "Exit Thread" << std::endl;
			break;
		}
	}
	
	std::cout << "Main Begin Sleep" << std::endl;
	Sleep(2000);
	std::cout << "Main Stop Sleep" << std::endl;

	CloseHandle(hThread1);
	return 0;
}

DWORD WINAPI ThreadFuc(LPVOID hThread1)
{
//	WaitForSingleObject(hThread1, INFINITE);  WaitForSingleObject放在哪哪个线程等待
	for (int i = 0; i < 100; i++) {
		std::cout << i << "Thread Begin" << std::endl;
	}	
	ExitThread(0);

	std::cout <<  "Thread Exit" << std::endl;
	return 0;
}

DWORD WINAPI ThreadFuc1(LPVOID)
{
	for (int i = 0; i < 50; i++) {
		std::cout << i << "Thread1 Begin" << std::endl;
	}

	return 0;
}