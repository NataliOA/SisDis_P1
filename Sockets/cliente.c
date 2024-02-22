// Ficheros de cabecera
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
 
int main(int argc, char *argv[])
{
if(argc > 2){
 //Definir variables
 char *ip;
 int fd, numbytes,puerto;
 char buf[100];
 puerto=atoi(argv[2]);
 ip=argv[1];

struct hostent *he; //nodo remoto
struct sockaddr_in server; //direccion del servidor

if((he=gethostbyname(ip))==NULL){
printf("gethostbyname() error\n");
exit(-1);
}
 
 //Socket
 if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
 printf("socket() error\n");
 exit(-1);
 }
 
 //Datos del servidor
 server.sin_family = AF_INET;
 server.sin_port = htons(puerto);
 server.sin_addr = *((struct in_addr *)he->h_addr); //he->h_addr pasa la información de ''*he'' a "h_addr"
 bzero(&(server.sin_zero),8);
 
//Conectarse al servidor
 if(connect(fd, (struct sockaddr *)&server,
 sizeof(struct sockaddr))==-1){
 printf("connect() error\n");
 exit(-1);
 }


 //Recibir mensaje de bienvenida
 if ((numbytes=recv(fd,buf,100,0)) == -1){
 printf("Error en recv() \n");
 exit(-1);
 }

 buf[numbytes]='\0';

 //imprime respuesta del servidor
 printf("Servidor: %s\n",buf);

 close(fd);
}
else{
 printf("No se ingresó el ip y puerto por parametro\n");
}
 return 0;
}
