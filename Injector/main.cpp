#include <iostream>
#include <string>
#include <ctype.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

int getProcessId(const std::string& p_name);
bool injectLibrary(const int &pid, const std::string &DLL_Path);

int main(int argc, char ** argv)
{
	printf("%s", argv[1]);
	if (argc != 2)
	{
		std::cout << "Usage: Injector.exe <DLL Path>" << std::endl;
		return 1;
	}

	if (PathFileExists(argv[1]) == FALSE)
	{
		std::cerr << "Library path does not exist!" << std::endl;
		return 1;
	}

	injectLibrary(getProcessId("csgo.exe"), argv[1]);

	return 0;
}

int getProcessId(const std::string& p_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 structprocsnapshot = { 0 };

	structprocsnapshot.dwSize = sizeof(PROCESSENTRY32);

	if (snapshot == INVALID_HANDLE_VALUE)return 0;
	if (Process32First(snapshot, &structprocsnapshot) == FALSE)return 0;

	while (Process32Next(snapshot, &structprocsnapshot))
	{
		if (!strcmp(structprocsnapshot.szExeFile, p_name.c_str()))
		{
			CloseHandle(snapshot);
			
			return structprocsnapshot.th32ProcessID;
		}
	}
	CloseHandle(snapshot);

	std::cerr << "Unable to find csgo.exe" << std::endl;

	return 0;
}

bool injectLibrary(const int &pid, const std::string &path)
{
	long dll_size = path.length() + 1;
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (hProc == NULL)
		return false;

	LPVOID MyAlloc = VirtualAllocEx(hProc, NULL, dll_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (MyAlloc == NULL)
		return false;

	int IsWriteOK = WriteProcessMemory(hProc, MyAlloc, path.c_str(), dll_size, 0);
	if (IsWriteOK == 0)
		return false;

	DWORD dWord;
	LPTHREAD_START_ROUTINE addrLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibrary("kernel32"), "LoadLibraryA");

	HANDLE ThreadReturn = CreateRemoteThread(hProc, NULL, 0, addrLoadLibrary, MyAlloc, 0, &dWord);
	if (ThreadReturn == NULL)
		return false;

	if ((hProc != NULL) && (MyAlloc != NULL) && (IsWriteOK != ERROR_INVALID_HANDLE) && (ThreadReturn != NULL))
	{
		std::cout << "Injected library" << std::endl;
		return true;
	}

	return false;
}