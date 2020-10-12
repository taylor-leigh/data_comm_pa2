// Taylor Morgan - tm2045
// Khalil Markham - km1783

// sources
// lecture notes and recordings, code from previous programming assignment
// http://stackoverflow.com/questions/29395081/break-a-file-into-chunks-and-send-it-as-binary-from-client-to-server-in-c-using
// https://mycodecamp.blogspot.com/2019/03/c-program-to-implement-go-back-n.html

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
#include "packet.cpp"
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
  char spayload[512];	// for the serialized payload
  char ack[512];
  int port = atoi(argv[2]);
  int N = 7;	// window size is 7
  int seqnum;

  // for debugging
  //cout << "using port " << port << endl;

  // create socket
  if ((mysocket=socket (AF_INET, SOCK_DGRAM, 0))==-1)
    cout << "Error in creating socket.\n";

  // TODO: create log files ! clientseqnum.log and clientack.log

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

  // split the file into packets, serialize, send, and wait for acks
  while (file_to_send.peek() != EOF) {

    // splits file into 30-char chunks
    for (int i = 0; i < 30; i++) {
      char nextchar;
      if (file_to_send.peek() != EOF) {
        nextchar = file_to_send.get();
      } else {
        nextchar = '\0';
      }
      payload[i] = nextchar;
    }

    // TODO: set seqnum

    // put 30-char chunks into packets & serialize
    packet pack(1, seqnum, 30, payload);
    pack.serialize(spayload);

    // send payload to server
    if (sendto(mysocket, spayload, 30, 0, (struct sockaddr *)&server, slen)==-1)
      cout << "Error in sendto function.\n";
    // TODO: put seqnum of sent packet into clientseqnum.log + newline
    cout << "sent payload " << payload << endl;

    // TODO: put timer and interrupt here
    if (recvfrom(mysocket, ack, 512, 0, (struct sockaddr *)&server, &slen)==-1)
      cout << "Error getting ack" << endl;
    // TODO: put seqnum of ack packet into clientack.log + newline
    cout << "got ack " << ack << endl;
  }

  // EOT packet
  packet EOT(3, seqnum, 0, NULL);
  EOT.serialize(spayload);
  // TODO: serialize this ? can't send the packet
  if (sendto(mysocket, spayload, 30, 0, (struct sockaddr *)&server, slen)==-1)
    cout << "Error sending EOT packet." << endl;
  cout << "sent EOT packet" << endl;

  close(mysocket);
  return 0;

}
