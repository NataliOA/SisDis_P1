// Ficheros de cabecera
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
 
//Funcion principal
int main(int argc, char **argv)
{

if(argc>1){

//Primer paso, definir variables
int fd,fd2,longitud_cliente,numbytes,puerto;
puerto=atoi(argv[1]);

//Se necesitan dos estructuras del tipo sockaddr
//La primera guarda info del server
//La segunda del cliente
struct sockaddr_in server;
struct sockaddr_in client;

//Configuración del servidor
 server.sin_family= AF_INET; //TCPIP
 server.sin_port = htons(puerto); //PUERTO
 server.sin_addr.s_addr = INADDR_ANY; //CUALQUIER CLIENTE
 bzero(&(server.sin_zero),8); //RELLENA CON 0
 
 //Definicion de socket
 if (( fd=socket(AF_INET,SOCK_STREAM,0) )<0){
 perror("Error de apertura de socket");
 exit(-1);
 }
 
 //Avisar al sistema que se creo un socket
 if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
 printf("error en bind() \n");
 exit(-1);
 }
 
 //Establecer el socket en modo escucha
 if(listen(fd,5) == -1) {
 printf("error en listen()\n");
 exit(-1);
 }

//Aceptar conexiones
while(1){
longitud_cliente= sizeof(struct sockaddr_in);
if((fd2 = accept(fd,(struct sockaddr *)&client,&longitud_cliente))==-1){
printf("Error en accept()\n");
exit(-1);
}
 
 printf("SERVIDOR EN ESPERA...\n");
 
 //El cliente recibe el mensaje del servidor
 send(fd2,"Bienvenido a mi servidor.\n",26,0);

close(fd2);
}
 close(fd);
}
else{
printf("No se ingresó el puerto por parametro\n");
}

return 0;
}
