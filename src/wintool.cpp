#if defined(_WIN32)
#include "wintool.hpp"

WinTool::WinTool(){};

void WinTool::flash(const s isofile, const int devnum, verbose v) {
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
    std::ostringstream outstrs;
    char szPhysicalDrive[32];
    int foundDrives = 0;
    
    outstrs << "Listing removable physical drives:\n";
    outstrs << "--------------------------------\n";

    for (int i = 0; ; i++) {
        sprintf_s(szPhysicalDrive, "\\\\.\\PhysicalDrive%d", i);
        
        HANDLE hDevice = CreateFileA(
            szPhysicalDrive,
            FILE_READ_ATTRIBUTES,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (hDevice == INVALID_HANDLE_VALUE) {
            DWORD err = GetLastError();
            if (err == ERROR_FILE_NOT_FOUND) {
                break; 
            }
            
            hDevice = CreateFileA(
                szPhysicalDrive,
                GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                NULL,
                OPEN_EXISTING,
                0,
                NULL);

            if (hDevice == INVALID_HANDLE_VALUE) {
                outstrs << "Could not access \\\\.\\PhysicalDrive" << i 
                       << " (Error: " << GetLastError() << ")\n";
                continue;
            }
        }

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
                foundDrives++;
                outstrs << "Drive #" << foundDrives << ": \\\\.\\PhysicalDrive" << i << "\n";


                STORAGE_HOTPLUG_INFO hotplugInfo;
                if (DeviceIoControl(
                    hDevice,
                    IOCTL_STORAGE_GET_HOTPLUG_INFO,
                    NULL, 0,
                    &hotplugInfo, sizeof(hotplugInfo),
                    &bytesReturned,
                    NULL)) {
                    outstrs << "  Removable: " << (hotplugInfo.MediaRemovable ? "Yes" : "No") << "\n";
                    outstrs << "  Hotpluggable: " << (hotplugInfo.MediaHotplug ? "Yes" : "No") << "\n";
                }

                bool gotSize = false;

                GET_LENGTH_INFORMATION lengthInfo;
                if (DeviceIoControl(
                    hDevice,
                    IOCTL_DISK_GET_LENGTH_INFO,
                    NULL, 0,
                    &lengthInfo, sizeof(lengthInfo),
                    &bytesReturned,
                    NULL)) {
                    ULONGLONG diskSize = lengthInfo.Length.QuadPart;
                    outstrs << "  Size: " << std::fixed << std::setprecision(2) 
                           << (double)diskSize / (1024 * 1024 * 1024)
                           << " GB (" << diskSize << " bytes)\n";
                    gotSize = true;
                }

                if (!gotSize) {
                    DISK_GEOMETRY_EX diskGeometry;
                    if (DeviceIoControl(
                        hDevice,
                        IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,
                        NULL, 0,
                        &diskGeometry, sizeof(diskGeometry),
                        &bytesReturned,
                        NULL)) {
                        ULONGLONG diskSize = diskGeometry.DiskSize.QuadPart;
                        outstrs << "  Size: " << std::fixed << std::setprecision(2) 
                               << (double)diskSize / (1024 * 1024 * 1024)
                               << " GB (" << diskSize << " bytes)\n";
                        gotSize = true;
                    }
                }

                if (!gotSize) {
                    outstrs << "  Size: Could not determine size (Error: " << GetLastError() << ")\n";
                    if (GetLastError() == ERROR_ACCESS_DENIED) {
                        outstrs << "       Administrator privileges required for this operation\n";
                    }
                }

                outstrs << "\n";
            }
        } else {
            outstrs << "Could not query properties for \\\\.\\PhysicalDrive" << i 
                   << " (Error: " << GetLastError() << ")\n";
        }
        
        CloseHandle(hDevice);
    }

    if (foundDrives == 0) {
        outstrs << "No removable physical drives found.\n";
    } else {
        outstrs << "Total removable drives found: " << foundDrives << "\n";
    }
    out = outstrs.str();
}
#endif