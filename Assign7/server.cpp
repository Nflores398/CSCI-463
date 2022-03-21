//***************************************************************************
//
//  Noah Flores
//  z1861588
//  CSCI-463-1
//
//  I certify that this is my own work and where appropriate an extension
//  of the starter code provided for the assignment.
//
//***************************************************************************

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sstream>

#include <iostream>
/**
 * @brief Writes back to client
 *
 * Loop through buffer and write to client
 *
 * @param fd file descriptor
 *
 * @param buf buffer of data to write server
 *
 * @param len the length of the buffer
 *
 * @return how many bytes written to server
 *
 ********************************************************************************/
static ssize_t safe_write(int fd, const char *buf, size_t len)
{
   // loop through length of string
   while (len > 0)
   {
      // write to client
      ssize_t wlen = write(fd, buf, len);
      if (wlen == -1)
         return -1;

      len -= wlen;
      buf += wlen;
   }
   return len;
}
/**
 * @brief Server that takes data and processes data
 *
 * Server will calc sum and get length and return it back to client
 *
 * @param argc	used to get option types
 *
 * @param argv  used to get option types
 *
 * @return 0
 ********************************************************************************/
int main(int argc, char **argv)
{
   int sock;
   socklen_t length;
   struct sockaddr_in server; //server
   struct sockaddr_in from; //client
   int msgsock;
   char buf[2048];
   int rval;
   int opt;
   int listener_port = 0;
   uint16_t sum;  // store sum
   uint32_t len;  // store len
   uint8_t inbit; // store read in bytes

   // set op listening port
   while ((opt = getopt(argc, argv, "l:")) != -1)
   {
      switch (opt)
      {
      case 'l':
      {
         std::istringstream iss(optarg);
         iss >> listener_port;
         server.sin_port = htons(listener_port);
      }
      break;

      default:
         server.sin_port = 0;
         break;
      }
   }

   signal(SIGPIPE, SIG_IGN);
   // create socket
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock < 0)
   {
      perror("opening stream socket");
      exit(1);
   }

   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   if (bind(sock, (sockaddr *)&server, sizeof(server)))
   {
      perror("binding stream socket");
      exit(1);
   }
   // get the assigned port
   length = sizeof(server);
   if (getsockname(sock, (sockaddr *)&server, &length))
   {
      perror("getting socket name");
      exit(1);
   }
   std::cout << "Socket has port " << ntohs(server.sin_port) << "\n";

   // start listen to accept connections
   listen(sock, 5);
   while (true)
   {
      socklen_t from_len = sizeof(from);
      msgsock = accept(sock, (struct sockaddr *)&from, &from_len);
      if (msgsock == -1)
         perror("accept");
      else
      {
         // get ip address and port of client
         inet_ntop(from.sin_family, &from.sin_addr, buf, sizeof(buf));
         std::cout << "Accepted connection from '" << buf << "' port " << ntohs(from.sin_port);
         while (rval != 0)
         {
            // loop and read in buffer and calc sum and get lens
            if ((rval = read(msgsock, buf, sizeof(buf))) < 0)
               perror("reading stream message");
            if (rval == 0)
               std::cout << "\nEnding connection\n";
            else
            {

               for (int i = 0; i < rval; i++)
               {
                  inbit = buf[i]; //move 1 byte of buf into a uint8
                  sum += inbit;   //add it to a sum
               }

               len += rval; //add to bytes read
            }
         }
         //sleep for 1 second
         sleep(1);
         // create outstream to send back to client
         std::ostringstream os;
         os << "SUM: " << sum << " Len: " << len << "\n";
         std::string str = os.str();
         const char *ch = str.c_str();
         // write data back to client
         rval = safe_write(msgsock, ch, strlen(ch));
         if (rval < 0)
         {
            perror("writen failed");
         }

         close(msgsock);
      }
      rval = 1; // reset rval
      sum = 0;  // reset sum
      len = 0;  // reset len
   }
}
