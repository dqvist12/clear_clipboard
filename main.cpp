#include <windows.h>





void ClearClipBoard() {

    if (OpenClipboard(NULL)) {
        // Will clear the current text

        EmptyClipboard();
        CloseClipboard();
    }

    // Will clear the clipboard history

    const auto hScm = OpenSCManager(nullptr, nullptr, NULL);
    const auto hSc = OpenService(hScm, "cbdhsvc_625cd", SERVICE_QUERY_STATUS);
                                       // ^ The clipboard service

    SERVICE_STATUS_PROCESS ssp = {};

    DWORD bytesNeeded = 0;
    QueryServiceStatusEx(hSc, SC_STATUS_PROCESS_INFO, reinterpret_cast <LPBYTE> (&ssp), sizeof(ssp), &bytesNeeded);

    CloseServiceHandle(hSc);
    CloseServiceHandle(hScm);

    HANDLE ProcPidHANDLE;
    ProcPidHANDLE = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, TRUE, ssp.dwProcessId);
    TerminateProcess(ProcPidHANDLE, 0);
}



    //use ClearClipBoard();
