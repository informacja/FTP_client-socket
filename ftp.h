#ifndef FTP_H_INCLUDED
#define FTP_H_INCLUDED

#include <winsock2.h>   /* for sockaddr_in and inet_addr() */
#include <WS2tcpip.h>
#include <fstream>
#include <iostream>

/*
 *  Code below from
 *  https://github.com/pedro-vicente/lib_netsockets/blob/master/src/ftp.cc
 *  https://github.com/pedro-vicente/lib_netsockets/blob/master/examples/ftp_client.cc
 */


void send_all(int sock, const void *vbuf, size_t size_buf)
{
  const char *buf = (char*)vbuf;	// can't do pointer arithmetic on void*
  int send_size; // size in bytes sent or -1 on error
  size_t size_left; // size left to send
  const int flags = 0;

  size_left = size_buf;
  while (size_left > 0)
  {
    if ((send_size = send(sock, buf, size_left, flags)) == -1)
    {
      std::cout << "send error: " << std::endl;
    }
    size_left -= send_size;
    buf += send_size;
  }
  return;
}

// ----------------------------------------------------------------------------

void get_response(int sock, std::string &str_rep)
{
  int recv_size; // size in bytes received or -1 on error
  const int flags = 0;
  const int size_buf = 1024;
  char buf[size_buf];

  if ((recv_size = recv(sock, buf, size_buf, flags)) == -1)
  {
    std::cout << "recv error: " << strerror(errno) << std::endl;
  }

  std::string str(buf, recv_size);
  std::cout << "response: " << str;
  str_rep = str;
  return;
}

// ----------------------------------------------------------------------------

void send_request(int sock, const char* buf_request)
{
  std::cout << "request: " << buf_request;
//  std::cout << "request: " << buf_request << std::endl;

  //send
  send_all(sock, (void *)buf_request, strlen(buf_request));
  return;
}

// ----------------------------------------------------------------------------

int login( SOCKET sock, const char *user_name, const char *pass, int port = 21 )
{
  char buf_request[255];
  std::string str_server_ip;
  std::string str_rsp;

  //create the control socket
//  create_socket(sock, m_server_ip.c_str(), m_server_port);

  get_response(sock, str_rsp);

  //construct USER request message using command line parameters
  //Note: there is no space between the user name and CRLF; example of request is "USER me\r\n"
  sprintf(buf_request, "USER %s\r\n", user_name);

  //send USER request
  send_request(sock, buf_request);

  //receive response
  get_response(sock, str_rsp);

  //construct PASS request message using command line parameters
  sprintf(buf_request, "PASS %s\r\n", pass);

  //send PASS request
  send_request(sock, buf_request);

  //receive response
  get_response(sock, str_rsp);
}

// ----------------------------------------------------------------------------

void parse_PASV_response(const std::string &str_rsp, std::string &str_server_ip, unsigned short &server_port)
{
  unsigned int h[4];
  unsigned int p[2];
  char server_ip[100];

  size_t pos = str_rsp.find('(');
  std::string  str_ip = str_rsp.substr(pos + 1);
  sscanf(str_ip.c_str(), "%u,%u,%u,%u,%u,%u", &h[0], &h[1], &h[2], &h[3], &p[0], &p[1]);
  server_port = static_cast<unsigned short>(p[0] * 256 + p[1]);
  sprintf(server_ip, "%u.%u.%u.%u", h[0], h[1], h[2], h[3]);
  str_server_ip = server_ip;
}

// ----------------------------------------------------------------------------

void create_socket(int &sock, const char* server_ip, const unsigned short server_port)
{
  // server address
  struct sockaddr_in server_addr;

  // construct the server address structure
  memset(&server_addr, 0, sizeof(server_addr));// zero out structure
  server_addr.sin_family = AF_INET;// internet address family
  server_addr.sin_addr.s_addr = inet_addr(server_ip);// server IP address
  server_addr.sin_port = htons(server_port);// server port

  // create a stream socket using TCP
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  {
  }

  // establish the connection to the server
  if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
  {
    std::cout << "connect error: " << strerror(errno) << std::endl;
    exit(1);
  }
}

// ----------------------------------------------------------------------------

void receive_all(int sock, const char *file_name)
{
  int recv_size; // size in bytes received or -1 on error
  const int flags = 0;
  const int size_buf = 4096;
  char buf[size_buf];
  FILE *file;

    std::ofstream fout;
    sprintf(buf, "STREAM%s", file_name);
    fout.open( buf, std::ios::out);

  file = fopen( file_name, "wb");

  while (1)
  {
    if ((recv_size = recv(sock, buf, size_buf, flags)) == -1)
    {
      std::cout << "recv error: " << strerror(errno) << std::endl;
    }
    if (recv_size == 0)
    {
      std::cout << "all bytes received " << std::endl;
      break;
    }

    fwrite(buf, recv_size, 1, file);
    fout << buf;
    recv_size = 0;
  }
  fout.close();
  fclose(file);

  sprintf(buf, "STREAM%s", file_name);          // to FIX
  remove(buf);


/// przerobiæ na  fstream
    recv_size = 2191;
//
//    int file_desc = 0;
//
//    file_desc = open(file_name, O_CREAT  | O_WRONLY , 0666);
////    recv(sock, buf, file_size, 0);
//    write(file_desc, buf, recv_size);
//    close(file_desc);
//std::cout << buf;



  return;
}

// ----------------------------------------------------------------------------

void close_socket(int sock)
{
#if defined (_MSC_VER)
  closesocket(sock);
#else
  ::close(sock);
#endif
}

// ----------------------------------------------------------------------------

void get_file( SOCKET sock_ctrl, const char *file_name)
{
  char buf_request[255];
  std::string str_server_ip = "127.0.0.1";
  std::string str_rsp;
  unsigned short server_port = 21;

  //The FTP command, SIZE OF FILE (SIZE), is used to obtain the transfer
  //size of a file from the server-FTP process.This is the exact number
  //of octets(8 bit bytes) that would be transmitted over the data
  //connection should that file be transmitted.
  //syntax: "SIZE" SP pathname CRLF
  //get SIZE
  sprintf(buf_request, "SIZE %s\r\n", file_name);

  //send SIZE request
  send_request(sock_ctrl, buf_request);

  //get response on control socket
  get_response(sock_ctrl, str_rsp);

  //parse the file size
  std::string  str_code = str_rsp.substr(0, 3);
  unsigned long long size_file = 0;
  if ("213" == str_code)
  {
    std::string  str_size = str_rsp.substr(4, str_rsp.size() - 2 - 4); //subtract end CRLF plus start of "213 ", 213 SP
    size_file = atoi(str_size.c_str());

    std::cout << "FILE transfer is " << size_file << " bytes" << std::endl;
  }

  //enter passive mode: make PASV request
  sprintf(buf_request, "PASV\r\n");

  //send PASV request
  send_request(sock_ctrl, buf_request);

  //get response on control socket
  get_response(sock_ctrl, str_rsp);

  //parse the PASV response
  parse_PASV_response(str_rsp, str_server_ip, server_port);
    int sock_data;
  //create the data socket
  create_socket( sock_data, str_server_ip.c_str(), server_port);

  //construct RETR request message
  sprintf(buf_request, "RETR %s\r\n", file_name);

  //send RETR request on control socket
  send_request(sock_ctrl, buf_request);

  //get response on control socket
  get_response(sock_ctrl, str_rsp);

  //get the file (data socket), save to local file with same name
  receive_all(sock_data, file_name);

  //get response
  get_response(sock_ctrl, str_rsp);

  //close data socket
  close_socket(sock_data);
}


#endif // FTP_H_INCLUDED
