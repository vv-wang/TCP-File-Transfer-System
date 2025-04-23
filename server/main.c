#include "tftss.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <listen_ip> <listen_port>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *ip = argv[1];
  const char *port = argv[2];

  int connfd = tftss_start(ip, port);
  tftss_recv(connfd);
  close(connfd);

  printf("[INFO] File received successfully.\n");
  return EXIT_SUCCESS;
}
