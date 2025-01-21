#pragma intrinsic(memcmp, memcpy,strcpy,strcmp,_stricmp,strlen)

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>

#include "beacon.h"


WINBASEAPI int WINAPI MSVCRT$snprintf(char* buffer, size_t count, const char* format, ...);

/*
int snprintf(
   char *buffer,
   size_t count,
   const char *format [,
   argument] ...
);
*/

WINBASEAPI int __cdecl MSVCRT$tolower(int _C);

DECLSPEC_IMPORT int __cdecl MSVCRT$_stricmp(const char *string1,const char *string2);

DECLSPEC_IMPORT PCHAR __cdecl MSVCRT$strstr(const char *haystack, const char *needle);

WINBASEAPI FILE* WINAPI MSVCRT$fopen(const char* filename, const char* mode);

WINBASEAPI FILE* WINAPI MSVCRT$fopen(const char* filename, const char* mode);

WINBASEAPI int __cdecl MSVCRT$fclose(FILE *_File);

DECLSPEC_IMPORT char* __cdecl MSVCRT$fgets(char* _Buffer, int _MaxCount, FILE* _File);

DECLSPEC_IMPORT DWORD WINAPI KERNEL32$GetLastError(void);

WINBASEAPI HANDLE WINAPI KERNEL32$FindFirstFileA (char * lpFileName, LPWIN32_FIND_DATA lpFindFileData);

DECLSPEC_IMPORT BOOL WINAPI KERNEL32$FindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);

WINBASEAPI WINBOOL WINAPI KERNEL32$FindClose (HANDLE hFindFile);

DECLSPEC_IMPORT DWORD WINAPI KERNEL32$GetFileAttributesA(LPCWSTR lpFileName);

//main
WINBASEAPI DWORD WINAPI KERNEL32$GetLogicalDriveStringsA(DWORD nBufferLength, LPSTR lpBuffer);
WINBASEAPI UINT WINAPI KERNEL32$GetDriveTypeA(LPCSTR lpRootPathName);
WINBASEAPI int __cdecl MSVCRT$printf(const char * _Format,...);
WINBASEAPI size_t __cdecl MSVCRT$strlen(const char *str);

//WINBASEAPI DWORD KERNEL32$QueryDosDeviceA(LPCSTR lpDeviceName, LPSTR lpTargetPath, DWORD ucchMax);
WINBASEAPI void* WINAPI MSVCRT$strcpy(const char* dest, const char* source);
WINBASEAPI DWORD WINAPI MPR$WNetGetConnectionA(LPCSTR tmpDrive, LPSTR networkPath, LPDWORD bufferSize);

//bofstart + internal_printf + printoutput

WINBASEAPI void *__cdecl MSVCRT$calloc(size_t number, size_t size);
WINBASEAPI int WINAPI MSVCRT$vsnprintf(char* buffer, size_t count, const char* format, va_list arg);
WINBASEAPI void __cdecl MSVCRT$memset(void *dest, int c, size_t count);
WINBASEAPI void* WINAPI MSVCRT$memcpy(void* dest, const void* src, size_t count);
WINBASEAPI HANDLE WINAPI KERNEL32$GetProcessHeap();
WINBASEAPI LPVOID WINAPI KERNEL32$HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
WINBASEAPI void __cdecl MSVCRT$free(void *memblock);
WINBASEAPI BOOL WINAPI KERNEL32$HeapFree(HANDLE, DWORD, PVOID);

