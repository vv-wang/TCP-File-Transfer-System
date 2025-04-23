#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define DEBUG
#ifdef DEBUG
#define DEBUG_INFO(fmt, ...)\
  fprintf(stderr, "[DEBUG]%s:%d:%s(): " fmt "\n", \
      __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
#define DEBUG_INFO(fmt, ...)
#endif

#define SZ_FILENAME 256
#define SZ_BUFFER   1024

typedef struct {
  size_t filesize;
  char filename[SZ_FILENAME];
} file_header_t;

#endif
