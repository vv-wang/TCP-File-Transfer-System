#include "tftsc.h"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <server_ip> <server_port> <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *ip = argv[1];
  const char *port = argv[2];
  const char *filename = argv[3];

  int sockfd = tftsc_connect(ip, port);
  tftsc_send(sockfd, filename);
  close(sockfd);

  printf("[INFO] File '%s' sent successfully.\n", filename);
  return EXIT_SUCCESS;
}
