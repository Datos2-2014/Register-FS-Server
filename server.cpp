///* 
// * File:   ANB.cpp
// * Author: Rodrigo
// * 
// * Created on 21 de mayo de 2014, 04:23 AM
// */
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <errno.h>
//#include <string.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <sys/wait.h>
//#include <signal.h>
//#include <ctype.h>
//#include <string>
//
//#define MYPORT 3490    // Puerto al que conectarán los usuarios
//#define MAXBUFLEN 200  // Maximo de caracteres para el buffer
//#define BACKLOG 10     // Conexiones pendientes en cola
//
//
//#define MAX 100
//
//using namespace std;
//
//int longitud;//LONGITUD DE LA CADENA ENTRADA
//char salida[MAX];//SALIDA YA CONVERTIDA A LETRAS
//char actual[MAX];//VALOR DEL NUMERO ACTUAL
//char actualposterior[MAX];//VALOR DEL NUMERO POSTERIOR
//char revisada[MAX]; //LA ENTRADA UNA VEZ REVISADA PARA Q EL USUARIO NO ENTRE LETRAS
//
//void num_letra(char revisada[]); //FUNCION Q "TRADUCE" AL CASTELLANO
//
//
//int sockfd; // El servidor escuchara por sockfd
//int newfd; // las transferencias de datos se realizar mediante newfd
//char buf[MAXBUFLEN];// buffer para recivir o enviar datos
//struct sockaddr_in my_addr; // contendra la direccion IP y el numero de puerto local
//struct sockaddr_in their_addr;//Contendra la direccion IP y numero de puerto del cliente
//socklen_t sin_size;//Contendra el tamaño de la escructura sockaddr_in
//
//char *token = NULL;
//char vector [MAX];
//int cont,loop,a;
//
//void crear_socket();
//void atributos();
//void socket_name();
//void escuchar();
//void aceptar();
//void recibir();
//void enviar(char cadena[]);
//
//void crear_socket()//se crea el medio por el cual se va a realizar la comunicación:
//{
//  //AF_INET = Dominio donde se realiza la conexión.( unidos mediante una red TCP/IP).
//  //SOCK_STREAM = Uso del protocolo TCP
//  //0 = selecciona el protocolo más apropiado
//
//  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)//Crea el socket y verifica si hubo algun error
//  {
//    perror("socket");
//    exit(1);
//  }
//}
//
//void atributos() // Asignamos valores a la estructura my_addr para luego poder llamar a la funcion bind()
//{
//  my_addr.sin_family = AF_INET; //Se sa un servidor Stream (Protocolo TCP)
//
//  my_addr.sin_port = htons(MYPORT); //se asigna el puerto por el que se va a escuchar (3490)
//
//  my_addr.sin_addr.s_addr = INADDR_ANY; // se usa la IP local
//
//  bzero(&(my_addr.sin_zero), 8); // rellena con ceros el resto de la estructura 
//}
//
//void socket_name()//Le asignamos un nombre al socket, para recivir conexiones
//{
//  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
//  {
//    perror("bind");
//    exit(1);
//  }
//}
//
//void escuchar()// Habilitamos el socket para recibir conexiones, con una cola de 10 conexiones en espera como maximo (BACKLOG)
//{
//  if (listen(sockfd, BACKLOG) == -1)
//  {
//    perror("listen");
//    exit(1);
//  }  
//}
//
//void aceptar()//accept = Se utiliza en el servidor, con un socket habilitado para recibir conexiones
//{
//  sin_size = sizeof(struct sockaddr_in);
//    
//  //Se espera por conexiones
//    
//  if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr,&sin_size)) == -1)
//  {
//    perror("accept");
//    exit(1); // Si se produce un error se finaliza el programa
//  }
//  printf("server: conexion desde: %s\n", inet_ntoa(their_addr.sin_addr));  
//}
//
//void recibir()
//{
//  if ((recv(newfd, buf, MAXBUFLEN, 0)) == -1)// buf = tipo de funcion a realizar
//  {
//    perror("recv");
//    exit(1);
//  }
//}
//
//void enviar(char cadena[])
//{
//  if (send(newfd, cadena, MAXBUFLEN, 0) == -1)//envia el resultado de la conversion de numero a letras
//  perror("send");
//  exit(1);
//}
//
//int main()//metodo principal
//{ 
//  crear_socket();
//  
//  atributos();
//  
//  socket_name();
//
//  escuchar();
// 
//  while(1) // ciclo para llamar accept
//  {
//    cont=0;
//    // Llamamos a fork() para crear un proceso hijo que atendera a la conexion recien establecida
//    aceptar();
//    if (!fork())
//    { 
//      //comienza el proceso hijo y enviamos los datos mediante newfd
//      
//      recibir();//el servidor recive que tipo de funcion tiene que realizar, las opciones son:
//      // 1 = InitCap ... 2 = UpCap ... 3 = LowCap ... 4 = Numero -> Letras
//      if (strcmp (buf,"4") == 0)//4 = Numero -> Letras
//      {
//	if (send(newfd, "", 1, 0) == -1)// hago esto pq cuando hacia 2 send en el cliente me los recivia 1 recv, y necesitaba que estuvieran separados
//	perror("send");
//	
//	recibir();//recibo el numero del cliente
//	
//	num_letra(buf);//combierto el numero del cliente en letras
//
//	enviar(salida);//envia el resultado de la conversion del numero a letras
//      }
//      //close(newfd); //kdfdfdfdfdfdfdffddfdf
//      //exit(0);
//    }
//    //close(newfd); //fgggggggggggggggggggggggfgffg
//  }
//}
//
//void num_letra(char revisada[])
//{
//    
//    
//    strcat(salida,revisada);
//	
//
//} //fin de funcion
