#pragma once

#define CMD "netsh wlan show networks mode=bssid > wlan.txt"

#define WINDOWS

struct ap
{
	char apmac[20];
	int signal_strength;
	int channel;
};

struct ssid
{
	char ssid_name[30];
	int num_ap;
	char encryption[30];
	char authentication[30];
	struct ap aplist[20];
};

struct ssid ssid_list[20];

void wlan_analyse(fp);
int wlan_count(fp);
void what_line(char*);
void read_value(char*);

void full_out();