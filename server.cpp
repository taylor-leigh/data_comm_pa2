// Taylor Morgan - tm2045
// Khalil Markham - km1783

#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <fstream>
#include <arpa/inet.h>
#include <netdb.h>
#include "packet.h"
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){

  struct sockaddr_in server;
  struct sockaddr_in client;
  int mysocket = 0;
  socklen_t clen = sizeof(client);
  char payload[512];
  char ack[512];
  int port = atoi(argv[1]);

  if ((mysocket=socket(AF_INET, SOCK_DGRAM, 0))==-1)
    cout << "Error in socket creation.\n";

  memset((char *) &server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(mysocket, (struct sockaddr *)&server, sizeof(server)) == -1)
    cout << "Error in binding.\n";

  if (recvfrom(mysocket, payload, 512, 0, (struct sockaddr *)&client, &clen)==-1)
    cout << "Failed to receive.\n";

  if (sendto(mysocket, ack, 512, 0, (struct sockaddr *)&client, clen)==-1)
    cout << "Error in sendto function.\n";

  close(mysocket);
  return 0;

}
