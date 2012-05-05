#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sock.h"
#include "err.h"
#include "link.h"
#include "pic_link.h"
#include "renew.h"
#include "trans.h"
#include "do.h"

#define BUF_SIZE 1024
#define QLEN 20
#define SEC 5
#define TH_NUM 3 
#define ROOT_PATH "../jpg"

#define TCP_PORT 8000
#define UDP_PORT 8080
#define RENEW_PORT 8060
#define SERV_IP "192.168.0.26"

#define RENEW_MSG "need renew"
#define FIRST_MSG "first renew"

#ifdef DEBUG
#define DEBUG_PRINT0(arg0) printf(arg0)
#define DEBUG_PRINT1(arg0, arg1) printf(arg0, arg1)
#else
#define DEBUG_PRINT0(arg0) 
#define DEBUG_PRINT1(arg1) 
#endif

extern node_t *client;

#endif 
