// Taylor Morgan - tm2045
// Khalil Markham - km1783

// sources
// lecture notes and recordings, code from previous programming assignment

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
#include "packet.cpp"
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){

  struct sockaddr_in server;
  struct sockaddr_in client;
  int mysocket = 0;
  socklen_t clen = sizeof(client);
  char payload[512];
  char s_ack[512];
  int port = atoi(argv[1]);
  int seqnum;

  // create socker
  if ((mysocket=socket(AF_INET, SOCK_DGRAM, 0))==-1)
    cout << "Error in socket creation.\n";

  memset((char *) &server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  // bind socket
  if (bind(mysocket, (struct sockaddr *)&server, sizeof(server)) == -1)
    cout << "Error in binding.\n";

  // create output files
  fstream arrival("arrival.log");
  fstream output("fileName");

  if (recvfrom(mysocket, payload, 512, 0, (struct sockaddr *)&client, &clen)==-1)
    cout << "Failed to receive.\n";
  cout << "got payload" << endl;
  // TODO: deserialize payload and write to fileName
  // TODO: write seqnum to arrival.log + newline

  // create ack packet
  packet ack(0, seqnum, 0, NULL);
  ack.serialize(s_ack);

  if (sendto(mysocket, s_ack, 30, 0, (struct sockaddr *)&client, clen)==-1)
    cout << "Error in sendto function.\n";
  cout << "sent ack" << endl;

  // TODO: deal with EOT packet so you know when to close

  // close output files and socket
  arrival.close();
  output.close();
  close(mysocket);

  return 0;

}
