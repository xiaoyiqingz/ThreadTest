#include <iostream>
#include <Windows.h>

DWORD WINAPI ThreadFuc(LPVOID);

#define  THREAD_POOL_SIZE 3
#define  MAX_THREAD_INDEX	THREAD_POOL_SIZE - 1
#define  NUM_TASK 6

int main()
{
	HANDLE hThread[THREAD_POOL_SIZE];
	DWORD ThreadId;
	DWORD ExitCode;
	int slot = 0;

	for	(int i = 0; i < NUM_TASK; i++) {
		if (i > THREAD_POOL_SIZE) {
			WaitForSingleObject(hThread[slot], INFINITE);
			GetExitCodeThread(hThread[slot], &ExitCode);
			printf("Slot %d terminated\n", ExitCode);
			CloseHandle(hThread[slot]);
		}

		hThread[slot] = CreateThread(NULL, 0, ThreadFuc,
			(LPVOID)slot, 0, &ThreadId);
		printf("Launched thread #%d (slot %d)\n", i, slot);
		if (++slot > MAX_THREAD_INDEX)
			slot = 0;
	} 

	for (slot = 0; slot < THREAD_POOL_SIZE; slot++) {
		WaitForSingleObject(hThread[slot], INFINITE);
		CloseHandle(hThread[slot]);
	}
	printf("All slots terminated\n");

	return 0;
}

DWORD WINAPI ThreadFuc(LPVOID n)
{
	srand(GetTickCount());
	
	Sleep((rand() % 8)*500+500);
	printf("Slot %d idle\n",n);

	return ((DWORD)n);
}
