// Taylor Morgan - tm2045
// Khalil Markham - km1783

#include <iostream>
#include <sys/types.h>   // defines types (like size_t)
#include <sys/socket.h>  // defines socket class
#include <netinet/in.h>  // defines port numbers for (internet) sockets, some address structures, and constants
#include <netdb.h>
#include <iostream>
#include <fstream>
#include <arpa/inet.h>   // if you want to use inet_addr() function
#include <string.h>
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
  int port = argv[2];

  if ((mysocket=socket (AF_INET, SOCK_DGRAM, 0))==-1)
    cout << "Error in creating socket.\n";

  // get name of file to transfer
  char* filename;
  filename = argv[3];

  // open file
  ifstream file_to_send;
  file_to_send.open(filename);

  memset((char *) &server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  bcopy((char *)s->h_addr,
        (char *)&server.sin_addr.s_addr,
	s->h_length;

  if (sendto(mysocket, payload, 30, 0, (struct sockaddr *)&server, slen)==-1)
    cout << "Error in sendto function.\n";

  recvfrom(mysocket, ack, 512, 0, (struct sockaddr *)&server, &slen);

  close(mysocket);
  return 0;

}
