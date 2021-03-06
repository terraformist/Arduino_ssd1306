/* 
 * File:   main.c
 * Author: vadzim
 *
 * Created on December 9, 2016, 3:09 PM
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <linux/if_link.h>
#include <signal.h>

#include "ssd1306.h"


#define NI_MAXHOST 1025 
#define NI_MAXSERV 32

volatile sig_atomic_t done = 0;
struct sigaction action;

extern FONT_INFO    *_font; 
extern int bus; //i2c bus descriptor

/**
 * 
 * @return 
 */
float GetCPULoad() {
    int FileHandler;
    char FileBuffer[1024];
    float load;

    FileHandler = open("/proc/loadavg", O_RDONLY);
    if(FileHandler < 0) {
        return -1; }
    read(FileHandler, FileBuffer, sizeof(FileBuffer) - 1);
    sscanf(FileBuffer, "%f", &load);
    close(FileHandler);
    return load;
}

/**
 * 
 * @return 
 */
float GetMemUsage() {
    int FileHandler;
    char FileBuffer[1024];
    int memTotal, memFree, memAvail, memBuf,memCached;
    float result;
    FileHandler = open("/proc/meminfo", O_RDONLY);
    if(FileHandler < 0) {
        return -1; }
    read(FileHandler, FileBuffer, sizeof(FileBuffer) - 1);
    sscanf(FileBuffer, "MemTotal:         %d kB\n MemFree:          %d kB\n MemAvailable:          %d kB\n Buffers:           %d kB\n Cached:           %d kB",
     &memTotal, &memFree, &memAvail, &memBuf, &memCached);
    close(FileHandler);
    result = 1.0 - (float)(memFree + memCached) / memTotal;
    return result;
}
/**
 * 
 * @return 
 */
int GetCPUTemp() {
   int FileHandler;
   char FileBuffer[1024];
   int CPU_temp;
   FileHandler = open("/sys/devices/virtual/thermal/thermal_zone0/temp", O_RDONLY);
   if(FileHandler < 0) {
      return -1; }
   read(FileHandler, FileBuffer, sizeof(FileBuffer) - 1);
   sscanf(FileBuffer, "%d", &CPU_temp);
   close(FileHandler);
   return CPU_temp / 1000;
}

void sig_handler(int signo)
{
    done = 1;
    printf("received signo :%d \n", signo);
}


/*
 * 
 */
int main(int argc, char** argv) {
    time_t mytime;
    struct tm *tm;
    char time_buffer[80];
    char text_buffer[100];
    struct ifaddrs *ifaddr, *ifa;
    int family, s, n, row;
    char host[NI_MAXHOST];


    // Print pid, so that we can send signals from other shells
    printf("My pid is: %d\n", getpid());
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = sig_handler;
    // Intercept SIGHUP and SIGINT
    if (sigaction(SIGINT, &action, NULL) == -1) {
        perror("Error: cannot handle SIGINT"); // Should not happen
    }
    if (sigaction(SIGTERM, &action, NULL) == -1) {
        perror("Error: cannot handle SIGTERM"); // Should not happen
    }

    /* Init I2C bus  */
    bus = i2c_init((char*)&"/dev/i2c-0", 0x3c); //dev, slavei2caddr
    /* */
    ssd1306Init(SSD1306_SWITCHCAPVCC);
    while (done == 0) {
        _font = (FONT_INFO*) &ubuntuMono_8ptFontInfo;
	for (int i=0; i<32; i++) {
            ssd1306DrawPixel(i, i, WHITE, LAYER0);
//            ssd1306DrawPixel(i, i, WHITE, LAYER0);
	}
        /* Refresh screen */
        ssd1306Refresh();
        SSD1306MSDELAY(1000);
    }


    _font = (FONT_INFO*)&ubuntuMono_24ptFontInfo;
    ssd1306ClearScreen(LAYER0 | LAYER1) ;
    ssd1306Refresh();
    close(bus);
    printf("All done!\r\n");
    return (EXIT_SUCCESS);
}

