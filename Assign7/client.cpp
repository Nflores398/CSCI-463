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
#include <assert.h>
#include <sstream>

#include <iostream>


/**
 * @brief Writes to server that client is connected to
 *
 * Loop through buffer and write to server
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
   //amount written
   ssize_t writen = 0;
   //loop through length of buffer
   while (len > 0)
   {
      ssize_t wlen = write(fd, buf, len);
      if (wlen == -1)
         return -1;

      len -= wlen; //decrease length of buffer
      buf += wlen; //move through buffer to next
      writen += wlen; //keep track of times written
   }
   return writen;
}
/**
 * @brief prints response from server
 *
 * Loop through and print results from server
 *
 * @param fd file descriptor 
 * 
 * @return status 0 success and -1 fail
 *
 ********************************************************************************/
static int print_response(int fd)
{
   //buffer from server
   char buf[2024];
   int rval = 1;
   //loop though data sent by server
   while (rval > 0)
   {
      if ((rval = read(fd, buf, sizeof(buf) - 1)) == -1)
      {
         perror("reading scream message");
         return -1;
      }
      else if (rval > 0)
      {
         //print data
         buf[rval] = '\0';
         write(fileno(stdout), buf, rval);
      }
   }
   return 0;
}
/**
 * @brief Client server that reads data from file and passes to server
 *
 * Server will return length and calc sum
 *
 * @param argc	used to get option types
 *
 * @param argv  used to get option types
 *
 * @return 0
 ********************************************************************************/
int main(int argc, char *argv[])
{
   int sock;
   struct sockaddr_in server;
   int opt; //op code
   bool temp = false; 
   char buf[2024];
   int writer = 0;
   int reader = 999;

   while ((opt = getopt(argc, argv, "s:")) != -1)
   {
      switch (opt)
      {
      case 's':
      {
         //if ip is given to program
         if (inet_pton(AF_INET, argv[2], &server.sin_addr) <= 0)
         {
            perror("connecting stream socket");
            exit(-1);
         }
         server.sin_family = AF_INET;
         //set port
         if(optind >= argc)
         {
           perror("connecting stream socket");
           exit(-1);
         }
         server.sin_port = htons(atoi(argv[3]));
         temp = true;
      }
      break;

      default:
         break;
      }
   }
   //if no ip was given defualt 
   if (!temp)
   {
      //set ip
      inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
      server.sin_family = AF_INET;
      //set port
      server.sin_port = htons(atoi(argv[1]));
   }
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock < 0)
   {
      perror("opening stream socket");
      exit(1);
   }

   //connect to socket
   server.sin_family = AF_INET;

   if (connect(sock, (sockaddr *)&server, sizeof(server)) < 0)
   {
      perror("connecting stream socket");
      exit(1);
   }
   //until file is at end
   reader = read(fileno(stdin), buf, sizeof(buf));
   writer += safe_write(sock, buf, reader);
   while (reader != 0)
   {
      
      reader = read(fileno(stdin), buf, sizeof(buf));
      if(reader !=0)
      {
         writer += safe_write(sock, buf, reader);
      }

      if (writer < 0)
         perror("writing on stream socket");

   }

   //stop writing of socket
   shutdown(sock, SHUT_WR);
   //print info returned from server
   print_response(sock);
   //close socket
   close(sock);
}
