#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include "Analyzer.h"

int main(void)
{
	system(CMD);
	FILE* fp = fopen("wlan.txt", "r");

	if (fp != NULL)
	{
		wlan_analyse(fp);
		fclose(fp);
	}
	else printf("Error: wlan.txt file doesn't exist!\n");

	return 1;
}