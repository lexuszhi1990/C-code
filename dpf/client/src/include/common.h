#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <semaphore.h>

#include <linux/fb.h>

#include <jpeglib.h>
#include <jerror.h>

#include "types.h"
#include "err.h"
#include "fb.h"
#include "jpeg.h"
#include "effect.h"
#include "mouse.h"
#include "pic_link.h"
#include "do.h"
#include "sock.h"
#include "renew.h"

#endif 
