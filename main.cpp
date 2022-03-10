#include <windows.h>




LPCSTR GetClipBoardService() {

	SC_HANDLE manager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (manager == INVALID_HANDLE_VALUE) {
		std::cout << "Invalid Handle Value." << std::endl;
	}

	PROCESSESMAP* processesMap = new PROCESSESMAP;

	GetProcessNameAndId(processesMap);

	DWORD bytesNeeded;
	DWORD servicesNum;

	BOOL status = EnumServicesStatusEx(
		manager,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		NULL,
		0,
		&bytesNeeded,
		&servicesNum,
		NULL,
		NULL
	);

	PBYTE lpBytes = (PBYTE)malloc(bytesNeeded);

	status = EnumServicesStatusEx(
		manager,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,
		lpBytes,
		bytesNeeded,
		&bytesNeeded,
		&servicesNum,
		NULL,
		NULL
	);

	ENUM_SERVICE_STATUS_PROCESS* lpServiceStatus = (ENUM_SERVICE_STATUS_PROCESS*)lpBytes;

	for (DWORD i = 0; i < servicesNum; i++) {

		const char* cstr = lpServiceStatus[i].lpServiceName;

		//WpnUserService_38a78
		std::string s = cstr;


		string AllServices = cstr;
		string serviceNameToFind = "cbdhsvc_";

		if (strstr(AllServices.c_str(), serviceNameToFind.c_str()))
		{
			return cstr;

			std::cout << cstr << std::endl;
		}
	}

	delete processesMap;
	free(lpBytes);

}

void ClearClipBoard() {

	// Will clear the clipboard history

	const auto hScm = OpenSCManager(nullptr, nullptr, NULL);
	const auto hSc = OpenService(hScm, GetClipBoardService(), SERVICE_QUERY_STATUS);
										// ^ The clipboard service

	SERVICE_STATUS_PROCESS ssp = {};

	DWORD bytesNeeded = 0;
	QueryServiceStatusEx(hSc, SC_STATUS_PROCESS_INFO, reinterpret_cast <LPBYTE> (&ssp), sizeof(ssp), &bytesNeeded);

	CloseServiceHandle(hSc);
	CloseServiceHandle(hScm);

	HANDLE ProcPidHANDLE;
	ProcPidHANDLE = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, TRUE, ssp.dwProcessId);
	TerminateProcess(ProcPidHANDLE, 0);

	if (OpenClipboard(NULL)) {
		// Will clear the current text

		EmptyClipboard();
		CloseClipboard();
	}
}


    //use ClearClipBoard();
