#include "tftss.h"

int tftss_start(const char *ip, const char *port) {
  int sockfd, connfd;
  struct sockaddr_in to, from;
  socklen_t from_len;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  } 

  memset(&to, 0, sizeof(to));
  to.sin_family = AF_INET;
  to.sin_addr.s_addr = inet_addr(ip);
  to.sin_port = htons(atoi(port));

  if(bind(sockfd, (struct sockaddr *)&to, sizeof(to)) < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  if(listen(sockfd, 1) < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  from_len = sizeof(from);
  connfd = accept(sockfd, (struct sockaddr *)&from, &from_len);
  if(connfd < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return connfd;
}

void tftss_recv(int connfd) {
  file_header_t head;
  char *p, buf[SZ_BUFFER];
  int filefd;
  size_t filesize, rem;
  ssize_t rbytes, total;
  
  total = 0, p = (char *)&head;
  while(total < sizeof(head)) {
    rbytes = recv(connfd, p+total, sizeof(head)-total, 0);
    if(rbytes <= 0) {
      DEBUG_INFO("[ERROR] %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
    total += rbytes;
  }

  total = 0;
  filefd = open(head.filename, O_WRONLY|O_CREAT|O_TRUNC, 0666);
  if(filefd < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  rem = head.filesize;
  while(rem > 0) {
    size_t to_read = rem < sizeof(buf) ? rem : sizeof(buf);
    rbytes = recv(connfd, buf, to_read, 0);
    if(rbytes <= 0) {
      DEBUG_INFO("[ERROR] %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
    if(write(filefd, buf, rbytes) < 0) {
      DEBUG_INFO("[ERROR] %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
    rem -= rbytes;
  }
}
