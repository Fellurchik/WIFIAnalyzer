#define _CRT_SECURE_NO_WARNINGS

#include "Analyzer.h"
#include <stdio.h>
#include <string.h>

int SSIDnum = 0;
int counter = 0;
char globalstr[100];

void wlan_analyse(FILE* fp)
{
	struct ssid s;
	char arr[150];

	s.num_ap = wlan_count(fp);
	//printf("Num Ap %d", s.num_ap);																					//printf
	
	while (NULL != fgets(arr, 100, fp))
		{ if (strlen(arr) > 2) { what_line(arr); }; };

	full_out(s.num_ap);
}

int wlan_count(FILE* fp)
{
	char arr[150];

	fgets(arr, 50, fp);
	fgets(arr, 100, fp);

	fscanf(fp, "%s", arr);
	fscanf(fp, "%s", arr);
	fscanf(fp, "%s", arr);

	int num = num_from_ch(arr);

	fgets(arr, 100, fp);
	fgets(arr, 100, fp);

	return num;
}

void what_line(char arr[150])
{
	char buff[30];
	counter = 0;
	int i1 = 0;

	while (arr[counter] == ' ')
		{ counter++; };

	while (arr[counter] != ' ')
	{
		buff[i1] = arr[counter];
		counter++;
		i1++;
	};

	if ((buff[0] == 'S') && (buff[1] == 'S'))
	{
		read_value(arr);

		strcpy(ssid_list[SSIDnum].ssid_name, globalstr);

		//printf("\n\nSSID %d : %s", SSIDnum + 1, ssid_list[SSIDnum].ssid_name);											//printf

		SSIDnum++;
		ssid_list[SSIDnum-1].num_ap = 0;

	}
	else if ((buff[0] == 'B') && (buff[1] == 'S'))
	{
		read_value(arr);
		
		ssid_list[SSIDnum-1].num_ap++;
		int BSSIDnum = ssid_list[SSIDnum-1].num_ap;

		strcpy(ssid_list[SSIDnum-1].aplist[BSSIDnum-1].apmac, globalstr);
		//printf("\n  BSSID %d : %s", ssid_list[SSIDnum-1].num_ap, ssid_list[SSIDnum-1].aplist[BSSIDnum-1].apmac);			//printf
	}
	else if ((buff[0] == 'S') && (buff[1] == 'i'))
	{
		read_value(arr);

		int BSSIDnum = ssid_list[SSIDnum-1].num_ap;

		ssid_list[SSIDnum-1].aplist[BSSIDnum-1].signal_strength = num_from_ch(globalstr);

		//printf("\n    Signal: %d", ssid_list[SSIDnum-1].aplist[BSSIDnum-1].signal_strength);								//printf
	}
	else if ((buff[0] == 'C') && (buff[1] == 'h'))
	{
		read_value(arr);

		int BSSIDnum = ssid_list[SSIDnum-1].num_ap;

		ssid_list[SSIDnum-1].aplist[BSSIDnum-1].channel = num_from_ch(globalstr);

		//printf("\n    Channel: %d", ssid_list[SSIDnum-1].aplist[BSSIDnum-1].channel);										//printf
	}
	else if ((buff[0] == 'E') && (buff[1] == 'n'))
	{
		read_value(arr);

		strcpy(ssid_list[SSIDnum-1].encryption, globalstr);

		//printf("\n  Encryption: %s", ssid_list[SSIDnum - 1].encryption);													//printf
	}
	else if ((buff[0] == 'A') && (buff[1] == 'u'))
	{
		read_value(arr);

		strcpy(ssid_list[SSIDnum - 1].authentication, globalstr);

		//printf("\n  Authentication: %s", ssid_list[SSIDnum - 1].authentication);											//printf
	}
}

void read_value(char arr[150])
{
	char buff[30];
	int i1 = 0;
	counter++;

	while (arr[counter] != ' ') { counter++; };
	while (arr[counter] == ' ') { counter++; };
	while (arr[counter] != ' ') { counter++; };
	while (arr[counter] == ' ') { counter++; };

	i1 = 0;
	while (arr[counter] != '\n')
	{
		buff[i1] = arr[counter];
		counter++;
		i1++;
	};
	buff[i1] = '\0';

	strcpy(globalstr, buff);
}

int num_from_ch(char arr[100])
{
	int i = 1;
	int num1 = 1;
	int num2 = 0;
	num1 = arr[0] - '0';
	num2 = arr[1] - '0';

	while ((arr[i] != '\0') && (arr[i] != ' ') && (arr[i] != '%'))
	{
		num1 = num1 * 10 + num2;
		i++;
		num2 = arr[i] - '0';
	};

	return num1;
}