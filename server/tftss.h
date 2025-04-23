#ifndef __TFTSS_H__
#define __TFTSS_H__

#include "../include/protocol.h"

extern int tftss_start(const char *ip, const char *port);
extern void tftss_recv(int connfd);

#endif
