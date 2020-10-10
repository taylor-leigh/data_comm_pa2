// Taylor Morgan - tm2045
// Khalil Markham - km1783

// sources
// lecture notes and recordings, code from previous programming assignment
// http://stackoverflow.com/questions/29395081/break-a-file-into-chunks-and-send-it-as-binary-from-client-to-server-in-c-using

#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fstream>
#include <arpa/inet.h>
#include "packet.h"
//#include "client.h"
#include <math.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){

  struct hostent *s;
  s = gethostbyname(argv[1]);

  struct sockaddr_in server;
  int mysocket = 0;
  socklen_t slen = sizeof(server);
  char payload[512];
  char ack[512];
  int port = atoi(argv[2]);

  cout << "using port " << port << endl;

  if ((mysocket=socket (AF_INET, SOCK_DGRAM, 0))==-1)
    cout << "Error in creating socket.\n";

  // get name of file to transfer
  char* filename;
  filename = argv[3];

  // open file
  ifstream file_to_send;
  file_to_send.open(filename);
  //cout << "opened file " << filename << endl;

  memset((char *) &server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  bcopy((char *)s->h_addr,
        (char *)&server.sin_addr.s_addr,
	s->h_length);

  // split the file into packets and serialize

  if (sendto(mysocket, payload, 30, 0, (struct sockaddr *)&server, slen)==-1)
    cout << "Error in sendto function.\n";
  cout << "sent payload " << payload << endl;

  if (recvfrom(mysocket, ack, 512, 0, (struct sockaddr *)&server, &slen)==-1)
    cout << "Error getting ack" << endl;
  cout << "got ack " << ack << endl;

  close(mysocket);
  return 0;

}
