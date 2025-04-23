#ifndef __TFTSC_H__
#define __TFTSC_H__

#include "../include/protocol.h"

extern int tftsc_connect(const char *ip, const char *port);
extern void tftsc_send(int sockfd, const char *filename);

#endif
