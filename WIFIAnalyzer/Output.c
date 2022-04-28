#define _CRT_SECURE_NO_WARNINGS

#include "Analyzer.h"
#include <stdio.h>

void full_out(int NumAp)
{
	struct ssid s;
	printf("\nFound %d WLANs", NumAp);

	for (int i = 0; i < NumAp; i++)
	{
		printf("\n\nESSID:  %s\n", ssid_list[i].ssid_name);
		printf("    Authentication: %s\n", ssid_list[i].authentication);
		printf("    Encryption:     %s", ssid_list[i].encryption);
		for (int i1 = 0; i1 < ssid_list[i].num_ap; i1++)
		{
			printf("\n        AP %d MAC:  %s", i1+1, ssid_list[i].aplist[i1].apmac);
			printf("  Channel:%3d", ssid_list[i].aplist[i1].channel);
			int dBm = (ssid_list[i].aplist[i1].signal_strength / 2) - 100;
			printf(", Signal:%3d%% (%d dBm)", ssid_list[i].aplist[i1].signal_strength, dBm);
		};
		printf("\n\n------------------------------------------------------");
	};
	printf("\n");
	system("pause");
}