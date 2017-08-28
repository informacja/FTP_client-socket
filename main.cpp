#include <stdio.h>        /* for printf() and fprintf() */
#include <stdlib.h>       /* for atoi() */
#include <string.h>       /* for memset() */
#include <unistd.h>       /* for close() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ftp.h"
#include <libssh/libssh.h>


#define RCVBUFSIZE 32     /* Size of receive buffer */

// ----------------------------------------------------------------------------

using namespace std;

// ----------------------------------------------------------------------------

int ftpSendFile(char * buf, char * host, int port);
int ftpRecvResponse(int sock, char * buf);

int main(int argc, char *argv[])
{
//test
ssh_session my_ssh_session;
  int rc;
  my_ssh_session = ssh_new();
  if (my_ssh_session == NULL)
    exit(-1);
  ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "localhost");
  rc = ssh_connect(my_ssh_session);
  if (rc != SSH_OK)
  {
    fprintf(stderr, "Error connecting to localhost: %s\n",
            ssh_get_error(my_ssh_session));
    exit(-1);
  }
  //...
  ssh_disconnect(my_ssh_session);
  ssh_free(my_ssh_session);





    int sock;                          /*  Socket descriptor */
    int dataSock;              /* Data sockeet Descriptor*/
    int numberOfConn;
    struct sockaddr_in ftpServAddr;   /*  server address */
    struct sockaddr_in dataServAddr;  /* data address*/
    struct hostent *pt_clientAddress;
    unsigned short ftpServPort;       /*  server port */
    unsigned short dataServPort;
    unsigned int PORTBUFFER = 256;
    char *servlP     = new char[256];                      /*  Server IP address (dotted quad) */
    char *host_name  = new char[256];
    char *echoString = new char[256];                 /*  String to send to echo server */
    char *command    = new char[256];
    char *p          = new char[256];
    char echoBuffer[RCVBUFSIZE];       /* Buffer for echo string */
    unsigned int echoStringLen;        /* Length of string to echo */
    int bytesRcvd, totalBytesRcvd;     /* Bytes read in single recv()
                                           and total bytes read */
host_name = "";
                                 /* First arg' server IP address (dotted quad) */
/*servlP = argv[0] ;*/
 servlP = "217.117.129.205";                                /* Second arg' string to echo */
// servlP = "127.0.0.1";                                /* Second arg' string to echo */
 host_name = "test";
 const char *pass = "test"; // password

 ftpServPort = 21;
ftpServPort = 2731;

 /*echoString = argv[2] ;*/
 char buf[1024];

 show_IPs( servlP );

    WSADATA Data;
    WSAStartup(MAKEWORD(2, 2), &Data); // 2.2 version

    //    printf("\nCreating Socket\n");
    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
         printf(" \nsocket () failed %d\n", sock) ;

    /*Create a data socket for ftp file transfer */
//    if ((dataSock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
//         printf(" \ndata socket () failed\n") ;


    /* Construct the server address structure */
    memset(&ftpServAddr, 0, sizeof(ftpServAddr));         /* Zero out structure */
    ftpServAddr.sin_family         = AF_INET;              /* Internet address family */
    ftpServAddr.sin_addr.s_addr     = inet_addr(servlP);       /* Server IP address */
    ftpServAddr.sin_port           = htons(ftpServPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &ftpServAddr, sizeof(ftpServAddr)) < 0)
         printf("\nconnect () failed\n") ;
    else
        printf("\nConnection Successful\n");

    if ( host_name == "")
    {
        gethostname(host_name, PORTBUFFER);

        cout << "hostname (" << host_name << "): ";
        string buff = "";
        getline(std::cin, buff);
        if ( buff != "" )
            strcpy( host_name, (const char*) &buff);
    }

    login( sock, host_name, pass );

    p = strcpy(command, "public_html/index.php");                    /// wybieramy co pobieramy
    get_file( sock, servlP, command );


//dataServPort = 20;
///* Construct the server address structure */
//memset(&dataServAddr, 0, sizeof(dataServAddr));         /* Zero out structure */
//dataServAddr.sin_family         = AF_INET;              /* Internet address family */
//dataServAddr.sin_addr.s_addr    = htonl(INADDR_ANY);       /* Server IP address */
//dataServAddr.sin_port           = htons(dataServPort); /* Server port */
//
///* BIND socket to (sockaddr_in) clientAddr */
//bind(dataSock,(struct sockaddr *) &dataServAddr, sizeof(dataServAddr));
//
///* LISTEN on data_socket */
//listen(dataSock, numberOfConn);


//printf("*******PORT********\n");
//printf(host_name);
//printf("\n*******\n");
/* Determine input length */
//echoStringLen = strlen(echoString) ;
//printf("Sending HTTP Request\n");
//printf(echoString);




//system("pause");
//buff = string ( "USER " + string(*host_name)+ "\r\n");
//p = strcpy(command, "USER test\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);
//
//p = strcpy(command, "PASS test\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);
//
//p = strcpy(command, "CWD /\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);
//

//
//p = strcpy(command, "size 1.txt\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);

//p = strcpy(command, "CWD /\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);

//
//p = strcpy(command, "TYPE I\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);

//p= strcpy(command, "PASV\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);


//p=strcpy(command, "RETR 1.txt\r\n");
//send(sock, command, strlen(command), 0);
//char *host;
//int tmpPort;
//host = "test";
//tmpPort = 20;

//ftpRecvResponse(sock, buf);

//
//p = strcpy(command, "PASV \r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);
//
//p = strcpy(command, "RETR SAM_7383.JPG\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);

//string  buff;

//cout << "\nType \"exit\" to end";
////
////while ( buff != "exit" )
////{
//    buff = "";
//    cout << "\nPolecenie: ";
//    cin >> buff;
////    p = strcpy(command, (const char*) &buff);
////    *command = buff.c_str();
//    std::copy(buff.begin(), buff.end(), command);
//    command[buff.size()] = '\0';
//
////    p = strcpy(command, buff.c_str());
//    send(sock, command, strlen(command), 0);
//    ftpRecvResponse(sock, buf);
//system("pause");

//// Get a file from server
//	strcpy(command, "Get ");
//	strcat(command, FILENAME);
//	p = strcpy(command, "RECV 1.txt");
//    send(dataSock, command, strlen(command), 0);
////	write(dataSock, command, strlen(command) );
////ftpRecvResponse(dataSock, buf);
//	recv(dataSock, buf, 2, 0);
////	// Variables for the file being received
//
//	int	file_size = 0,
//		file_desc = 0;
//	char	*data;
//
//	// Start receiving file
//	if (strcmp(buf, "OK") != 0) {
//
//		recv(dataSock, (char*)&file_size, sizeof(int), 0);
//		file_size = 2131291;
//		data = (char*)malloc(file_size);
////		file_desc = open(FILENAME, O_CREAT  | O_WRONLY | O_APPEND, 0666);
//		file_desc = open(FILENAME, O_CREAT  | O_WRONLY , 0666);
//		recv(dataSock, data, file_size, 0);
//		write(file_desc, data, file_size);
//		close(file_desc);
//	}
//	else {
//
//		fprintf(stderr, "Bad request\n");
//	}
//cout << "\nLast Err: " << WSAGetLastError();
//system("pause");
//p = strcpy(command,"MODE S\r\n");
//send(sock,command, strlen(command), 0);
//ftpRecvResponse(sock, buf);
//p = strcpy(command,"TYPE A\r\n");
//send(sock,command, strlen(command), 0);
//ftpRecvResponse(sock, buf);
//p= strcpy(command, "STRU F\r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);
//p = strcpy(command,"LIST \r\n");
//send(sock,command, strlen(command), 0);
//ftpRecvResponse(sock, buf);
//p= strcpy(command, "PASV \r\n");
//send(sock, command, strlen(command), 0);
//ftpRecvResponse(sock, buf);

//if (connect(dataSock, (struct sockaddr *) &dataServAddr, sizeof(dataServAddr)) < 0)
//     printf(" connect () failed\n") ;
//else
//    printf("Connection Successful\n");


//p=strcpy(command, "RETR 1.txt\r\n");
//send(sock, command, strlen(command), 0);
//char *host;
//int tmpPort;
//host = "test";
//tmpPort = 20;
//
//ftpRecvResponse(sock, buf);
//*buf= 'T';
//ftpSendFile(buf,host_name,20);

printf("\n");     /* Print a final linefeed */

delete servlP;
delete host_name;
delete echoString;
delete command;
delete p;

  close(sock);
  WSACleanup();
  return 0;
//  exit(0);

}


int ftpSendFile(char * buf, char * host, int port) {
   int sd;
   struct sockaddr_in pin;
   struct hostent *hp;

   if ((hp = gethostbyname(host)) == 0) {
      perror("gethostbyname");
      return -1;
   }
   memset(&pin, 0, sizeof(pin));
   pin.sin_family = AF_INET;
   pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
   pin.sin_port = htons(port);
   if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("socket");
      return -1;
   }
   if (connect(sd,(struct sockaddr *)  &pin, sizeof(pin)) == -1) {
      perror("connect");
      return -1;
   }
   if(send(sd, buf, strlen(buf), 0) == -1) {
      perror("send");
      return -1;
   }
   /*closesocket(sd); //close the socket*/
   return 0;
}
int ftpRecvResponse(int sock, char * buf) {
   int i;

   if (recv(sock, buf, 5120, 0) == -1) {//receive the data
      perror("recv");
      return 0;;
   }

//   for(i=(strlen(buf) - 1);i>0;i--) {
//      if(buf[i]=='.' || buf[i]=='\r') {
//         buf[i+1]='\0';
//         break;
//      }
//   }

//// Fixed version by Puler
//    for( i = 0; i < strlen(buf)-1; i++ )
//    {
//        if( buf[i]=='.' || buf[i]=='\r' ) {
//            buf[i+1]='\0';
//            break;
//        }
//    }


    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 0x08);
//   printf("\033[32;1m %s \033[0m", buf); //print response to the screen
    cout << buf;
//   printf("%s", buf); //print response to the screen
    SetConsoleTextAttribute(hConsole, 0x07);

// Beter Fixed version by Puler
   unsigned length = strlen(buf);
    for( i = 0; i < length; i++ )
    {
        buf[i]='\0';
    }

   return 0;
}
/*
 *  client.c
 *
 *  Simple FTP Client
 *  ====================
 *  Connects the server, and sends a command "Get FILENAME" to retrieve
 *  the file. If the file exists on the server, client retrieves it.
 *
 *  Compile & link  :   gcc client.c -o client
 *  Execute         :   ./client
 *
 *  Ozcan Ovunc <ozcan_ovunc@hotmail.com>
 */
//
//#include <stdio.h>
////#include <socsys/socket.h>
////#include <arpa/inet.h>
////#include <sys/stat.h>
////#include <sys/sendfile.h>
//#include <winsock2.h>
//#include <WS2tcpip.h>
//#include <fcntl.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define FILENAME 	"a.txt"
//#define SERVER_IP 	"127.0.0.1"
//#define SERVER_PORT 	21
//
//int main(int argc , char **argv)
//{
//    WSADATA Data;
////   int socket; // or you can use SOCKET socket
//   WSAStartup(MAKEWORD(2, 2), &Data); // 2.2 version
//   int  socket1; socket1 = socket(AF_INET, SOCK_DGRAM, 0);
//   if(socket1<0){
//        printf("Error Creating Socket");
//   }else{
//        printf("Successfully Created Socket");
//   }
//   system("pause");
//
//
//	int 	socket_desc;
//	struct 	sockaddr_in server;
//	char 	request_msg[BUFSIZ],
//		reply_msg[BUFSIZ];
//
//	// Variables for the file being received
//	int	file_size,
//		file_desc;
//	char	*data;
//
//	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
//	if (socket_desc == -1)
//	{
//		perror("Could not create socket");
//		return 1;
//	}
//
//	server.sin_addr.s_addr = inet_addr(SERVER_IP);
//	server.sin_family = AF_INET;
//	server.sin_port = htons(SERVER_PORT);
//
//	// Connect to server
//	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
//	{
//		perror("Connection failed");
//		return 1;
//	}
//
//	// Get a file from server
//	strcpy(request_msg, "Get ");
//	strcat(request_msg, FILENAME);
//	write(socket_desc, request_msg, strlen(request_msg));
//	recv(socket_desc, reply_msg, 2, 0);
//
//	// Start receiving file
//	if (strcmp(reply_msg, "OK") == 0) {
//
//		recv(socket_desc, (char*)&file_size, sizeof(int), 0);
//		data = (char*)malloc(file_size);
//		file_desc = open(FILENAME, O_CREAT | O_EXCL | O_WRONLY, 0666);
//		recv(socket_desc, data, file_size, 0);
//		write(file_desc, data, file_size);
//		close(file_desc);
//	}
//	else {
//
//		fprintf(stderr, "Bad request\n");
//	}
//
//	return 0;
//}
