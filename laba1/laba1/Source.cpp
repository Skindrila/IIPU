#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <locale.h>
#include <SetupAPI.h>

#pragma comment( lib, "setupapi.lib" )

int main() {
	int deviceIndex = 0;

	DWORD propertyType = 0;
	DWORD requiredSize = 0;

	SP_DEVINFO_DATA sp_devinfo_data;

	char propertyBuffer[256];

	setlocale(LC_ALL, "Russian");

	HDEVINFO deviceInfo = SetupDiGetClassDevs(0, "PCI", NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if (deviceInfo == INVALID_HANDLE_VALUE) {
		printf("�� ������� �������� ������ ���������.\n");
		getchar();
		system("pause");
		return EXIT_FAILURE;
	}

	sp_devinfo_data.cbSize = sizeof(sp_devinfo_data);

	printf(" # | �������������\t\t\t    | ���\n\n");

	while (SetupDiEnumDeviceInfo(deviceInfo, deviceIndex, &sp_devinfo_data)) {
		SetupDiGetDeviceRegistryProperty(deviceInfo, &sp_devinfo_data, SPDRP_MFG, &propertyType, (BYTE*)propertyBuffer, 256, &requiredSize);
		printf("#%-2d| %-39s| ", deviceIndex + 1, propertyBuffer);

		SetupDiGetDeviceRegistryProperty(deviceInfo, &sp_devinfo_data, SPDRP_DEVICEDESC, &propertyType, (BYTE*)propertyBuffer, 256, &requiredSize);
		printf("%s\n", propertyBuffer);

		deviceIndex++;
	}

	getchar();
	system("pause");
	return EXIT_SUCCESS;
}