#if defined(_WIN32)
#include "wintool.hpp"
#pragma comment(lib, "setupapi.lib")
WinTool::WinTool(){};

void WinTool::getOutput(s &out){
    out = output;
    return;
}
void flash(const s isofile, const int devnum, verbose v) {
    if((v)) {
    HANDLE isoHandle;
    try {
        isoHandle = CreateFileA(
            isofile.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );
    }
    catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl << "fitusb failed at WinTool Flash, at declaring isoHandle.\n" << "WinAPI GetLastError() output: \n" <<GetLastError() << std::endl;
    }
    HANDLE driveHandle;
    try {
        driveHandle = CreateFileA(
            s(DRIVE_PREFIX + std::to_string(devnum)).c_str(),
            GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
        );
    }
    catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl << "fitusb failed at WinTool flash, at declaring driveHandle" << std::endl << "WinAPI GetLastError() output: \n" << GetLastError() << std::endl;

    }
    std::vector<BYTE> bf(BUFFER_SIZE);
    DWORD bytesRead, bytesWritten;
    while (ReadFile(isoHandle, bf.data(), BUFFER_SIZE, &bytesRead, nullptr) && bytesRead > 0) {
        if (!WriteFile(driveHandle, bf.data(), bytesRead, &bytesWritten, nullptr) || bytesWritten != bytesRead) {
            CloseHandle(isoHandle);
            CloseHandle(driveHandle);
            std::cerr << "write to " << s(DRIVE_PREFIX + std::to_string(devnum)) << " failed. " << std::endl << "WinAPI GetLastError(): \n" << GetLastError();
            throw std::errc::io_error;
        }
    }
}
    else {
        HANDLE isoHandle = CreateFileA(
            isofile.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );
  
    
    HANDLE driveHandle = CreateFileA(
        s(DRIVE_PREFIX + std::to_string(devnum)).c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
        );
    
    
    std::vector<BYTE> bf(BUFFER_SIZE);
    DWORD bytesRead, bytesWritten;
    while (ReadFile(isoHandle, bf.data(), BUFFER_SIZE, &bytesRead, nullptr) && bytesRead > 0) {
        if (!WriteFile(driveHandle, bf.data(), bytesRead, &bytesWritten, nullptr) || bytesWritten != bytesRead) {
            CloseHandle(isoHandle);
            CloseHandle(driveHandle);
            return;
        }
    }
    }
}

void WinTool::listDevices(s &out){
    char szPhysicalDrive[32];
    
    for (int i = 0; ; i++) {
        sprintf_s(szPhysicalDrive, "\\\\.\\PhysicalDrive%d", i);
        
        HANDLE hDevice = CreateFileA(
            szPhysicalDrive,
            0,  
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);
        
        if (hDevice == INVALID_HANDLE_VALUE) {
            if (GetLastError() == ERROR_FILE_NOT_FOUND) {
                // No more physical drives
                break;
            }
            continue;
        }

        // Check if this is a removable drive
        STORAGE_PROPERTY_QUERY query;
        memset(&query, 0, sizeof(query));
        query.PropertyId = StorageDeviceProperty;
        query.QueryType = PropertyStandardQuery;

        STORAGE_DEVICE_DESCRIPTOR devd;
        DWORD bytesReturned = 0;
        
        if (DeviceIoControl(
            hDevice,
            IOCTL_STORAGE_QUERY_PROPERTY,
            &query, sizeof(query),
            &devd, sizeof(devd),
            &bytesReturned,
            NULL)) {
            
            if (devd.RemovableMedia) {
                printf("\\\\.\\PhysicalDrive%d - ", i);
                
                // Get disk size
                GET_LENGTH_INFORMATION lengthInfo;
                DWORD bytesReturnedSize = 0;
                
                if (DeviceIoControl(
                    hDevice,
                    IOCTL_DISK_GET_LENGTH_INFO,
                    NULL, 0,
                    &lengthInfo, sizeof(lengthInfo),
                    &bytesReturnedSize,
                    NULL)) {
                    
                    ULONGLONG diskSize = lengthInfo.Length.QuadPart;
                    printf("Size: %.2f GB\n", (double)diskSize / (1024 * 1024 * 1024));
                } else {
                    printf("Size: Unknown (error %lu)\n", GetLastError());
                }
            }
        }
        
        CloseHandle(hDevice);
    }
    
    for (int i = 0; ; i++) {
        sprintf_s(szPhysicalDrive, "\\\\.\\PhysicalDrive%d", i);
        
        HANDLE hDevice = CreateFileA(
            szPhysicalDrive,
            0,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);
        
        if (hDevice == INVALID_HANDLE_VALUE) {
            if (GetLastError() == ERROR_FILE_NOT_FOUND) {
                break;
            }
            continue;
        }

        // Check if this is a removable drive
        STORAGE_PROPERTY_QUERY query;
        memset(&query, 0, sizeof(query));
        query.PropertyId = StorageDeviceProperty;
        query.QueryType = PropertyStandardQuery;

        STORAGE_DEVICE_DESCRIPTOR devd;
        DWORD bytesReturned = 0;
        
        if (DeviceIoControl(
            hDevice,
            IOCTL_STORAGE_QUERY_PROPERTY,
            &query, sizeof(query),
            &devd, sizeof(devd),
            &bytesReturned,
            NULL)) {
            
            if (devd.RemovableMedia) {
                printf("\\\\.\\PhysicalDrive%d - ", i);
                
                GET_LENGTH_INFORMATION lengthInfo;
                DWORD bytesReturnedSize = 0;
                
                if (DeviceIoControl(
                    hDevice,
                    IOCTL_DISK_GET_LENGTH_INFO,
                    NULL, 0,
                    &lengthInfo, sizeof(lengthInfo),
                    &bytesReturnedSize,
                    NULL)) {
                    
                    ULONGLONG diskSize = lengthInfo.Length.QuadPart;
                    printf("Size: %.2f GB\n", (double)diskSize / (1024 * 1024 * 1024));
                } else {
                    printf("Size: Unknown (error %lu)\n", GetLastError());
                }
            }
        }
        
        CloseHandle(hDevice);
    }
}
#endif