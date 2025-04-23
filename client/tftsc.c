#include "tftsc.h"

int tftsc_connect(const char *ip, const char *port) {
  int sockfd;
  struct sockaddr_in to;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  } 

  memset(&to, 0, sizeof(to)); 
  to.sin_family = AF_INET;
  to.sin_addr.s_addr = inet_addr(ip);
  to.sin_port = htons(atoi(port));

  if(connect(sockfd, (struct sockaddr *)&to, sizeof(to)) < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return sockfd;
}

void tftsc_send(int sockfd, const char *filename) {
  int filefd;
  size_t filesize;
  ssize_t total, rbytes, sbytes;
  file_header_t head;
  char *p, buf[SZ_BUFFER];

  filefd = open(filename, O_RDONLY);
  if(filefd < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  filesize = lseek(filefd, 0, SEEK_END);
  if(filesize < 0 || lseek(filefd, 0, SEEK_SET) < 0) {
    DEBUG_INFO("[ERROR] %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  head.filesize = filesize;
  strcpy(head.filename, filename);

  total = 0, p = (char *)&head;
  while(total < sizeof(head)) {
    sbytes = send(sockfd, p+total, sizeof(head)-total, 0);
    if(sbytes < 0) {
      DEBUG_INFO("[ERROR] %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
    total += sbytes;
  }

  while((rbytes = read(filefd, buf, sizeof(buf))) > 0) {
    total = 0;
    while(total < rbytes) {
      sbytes = send(sockfd, buf+total, rbytes-total, 0);
      if(sbytes < 0) {
        DEBUG_INFO("[ERROR] %s", strerror(errno));
        exit(EXIT_FAILURE);
      }
      total += sbytes;
    }
  }

  close(filefd);
}
