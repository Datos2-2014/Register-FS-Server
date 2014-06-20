 #include <string.h>
#include <iostream>
#include "Disk_File.h"
#include <list>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "Jzon.h"
#include "ANB.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <sstream>


#define MYPORT 3490    // Puerto al que conectarán los usuarios
#define MAXBUFLEN 200  // Maximo de caracteres para el buffer
#define BACKLOG 10     // Conexiones pendientes en cola
#define MAX 100

using namespace std;

//main prueba server//


ANB* File_System = new ANB();
int longitud;//LONGITUD DE LA CADENA ENTRADA
char salida[MAX];//SALIDA YA CONVERTIDA A LETRAS
char actual[MAX];//VALOR DEL NUMERO ACTUAL
char actualposterior[MAX];//VALOR DEL NUMERO POSTERIOR
char revisada[MAX]; //LA ENTRADA UNA VEZ REVISADA PARA Q EL USUARIO NO ENTRE LETRAS

void comandExecute(char comandoClient[]); //FUNCION Q "TRADUCE" AL CASTELLANO


int sockfd; // El servidor escuchara por sockfd
int newfd; // las transferencias de datos se realizar mediante newfd
char buf[MAXBUFLEN];// buffer para recivir o enviar datos
struct sockaddr_in my_addr; // contendra la direccion IP y el numero de puerto local
struct sockaddr_in their_addr;//Contendra la direccion IP y numero de puerto del cliente
socklen_t sin_size;//Contendra el tamaño de la escructura sockaddr_in

char *token = NULL;
char vector [MAX];
int cont,loop,a;

void crear_socket();
void atributos();
void socket_name();
void escuchar();
void aceptar();
void recibir();
void enviar(char cadena[]);

void crear_socket()//se crea el medio por el cual se va a realizar la comunicación:
{
  //AF_INET = Dominio donde se realiza la conexión.( unidos mediante una red TCP/IP).
  //SOCK_STREAM = Uso del protocolo TCP
  //0 = selecciona el protocolo más apropiado

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)//Crea el socket y verifica si hubo algun error
  {
    perror("socket");
    exit(1);
  }
}

void atributos() // Asignamos valores a la estructura my_addr para luego poder llamar a la funcion bind()
{
  my_addr.sin_family = AF_INET; //Se sa un servidor Stream (Protocolo TCP)

  my_addr.sin_port = htons(MYPORT); //se asigna el puerto por el que se va a escuchar (3490)

  my_addr.sin_addr.s_addr = INADDR_ANY; // se usa la IP local

  bzero(&(my_addr.sin_zero), 8); // rellena con ceros el resto de la estructura 
}

void socket_name()//Le asignamos un nombre al socket, para recivir conexiones
{
  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
  {
    perror("bind");
    exit(1);
  }
}

void escuchar()// Habilitamos el socket para recibir conexiones, con una cola de 10 conexiones en espera como maximo (BACKLOG)
{
  if (listen(sockfd, BACKLOG) == -1)
  {
    perror("listen");
    exit(1);
  }  
}

void aceptar()//accept = Se utiliza en el servidor, con un socket habilitado para recibir conexiones
{
  sin_size = sizeof(struct sockaddr_in);
    
  //Se espera por conexiones
    
  if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr,&sin_size)) == -1)
  {
    perror("accept");
    exit(1); // Si se produce un error se finaliza el programa
  }
  printf("server: conexion desde: %s\n", inet_ntoa(their_addr.sin_addr));  
}

void recibir()
{
  if ((recv(newfd, buf, MAXBUFLEN, 0)) == -1)// buf = tipo de funcion a realizar
  {
    perror("recv");
    exit(1);
  }
}

void enviar(char cadena[])
{
  if (send(newfd, cadena, MAXBUFLEN, 0) == -1)//envia el resultado de la conversion de numero a letras
  perror("send");
  exit(1);
}

int main()//metodo principal
{
  cout<<"SERvidor"<<endl;  
  crear_socket();
  
  atributos();
  
  socket_name();
 
  escuchar();
 
 
  while(1) // ciclo para llamar accept
  {
    cont=0;
    // Llamamos a fork() para crear un proceso hijo que atendera a la conexion recien establecida
    aceptar();
    if (!fork())
    { 
      //comienza el proceso hijo y enviamos los datos mediante newfd
      
      recibir();//el servidor recive que tipo de funcion tiene que realizar, las opciones son:
      // 1 = InitCap ... 2 = UpCap ... 3 = LowCap ... 4 = Numero -> Letras
      if (strcmp (buf,"4") == 0)//4 = Numero -> Letras
      {
	if (send(newfd, "", 1, 0) == -1)// hago esto pq cuando hacia 2 send en el cliente me los recivia 1 recv, y necesitaba que estuvieran separados
	perror("send");
	
	recibir();//recibo el numero del cliente
	
	comandExecute(buf);//combierto el numero del cliente en letras
           
        printf("Salida  :%s\n",salida);
        
	enviar(salida);//envia el resultado de la conversion del numero a letras
      }
      //close(newfd); //kdfdfdfdfdfdfdffddfdf
      //exit(0);
    }
    //close(newfd); //fgggggggggggggggggggggggfgffg
  }
//    std::cout << " Creando archivos" << std::endl;
//    Disk_File* file1 = new Disk_File("AAAUsers", "users");
//    Disk_File* file2 = new Disk_File("AAAUsers", "users2");
//    std::cout << " creando schemas " << std::endl;
//    file1->setSchema("{{<username>,<Char-array>,<64>},{<password>,<Char-array>,<64>},{<id>,<Int>,<4>},{<admin>,<Byte>,<1>}}");
//    file2->setSchema("{{<pathFile>,<Char-array>,<512>},{<userId>,<Int>,<4>},{<owner>,<Byte>,<1>}}");
//    std::cout << " escribiendo registros  " << std::endl;
//    file1->addReg("{{<username>,<Gonzo>},{<password>,<heloo132*>},{<id>,<1>},{<admin>,<1>}}");
//    file1->addReg("{{<username>,<Yoda>},{<password>,<y0ur3Next@>},{<id>,<2>},{<admin>,<1>}}");
//    file1->addReg("{{<username>,<DarthRevan>},{<password>,<th3f0rc3~!>},{<id>,<3>},{<admin>,<1>}}");
//    file1->flush();
//    std::cout << "Termino" << endl;
}

void comandExecute(char comandoClient[])
{
    strcat(salida,comandoClient);
    stringstream ss;
    string comando;
    ss << comandoClient;
    ss >> comando;
    int j=0;
    
    
    while (comando[j]!= '<'){
        j++;
    }
    string dato=comando.substr(0,j);
    //cout <<dato;
    if(dato=="touch"){
        cout<<"ingreso";
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<< "Filename: "<<param1<<endl;
        if(param1.size()>64) {
            cout << "Numero de caracteres excedido en file name" << endl; //Añadir error
        }
        else {;
            int punt2 = punt1+2;
            int aux2=0;
            while (comando[punt2] != '>'){
                punt2++;
                aux2++;
            }
            string param2 = comando.substr(punt1+2,aux2);
            cout<< "client descriptor: "<<param2<<endl;
            if(param2.size()>64) {
                cout << "Numero de caracteres excedido en client descriptor" << endl; //Añadir error
            }
            else {
                int punt3 = punt2+2;
                int aux3=0;
                while (comando[punt3] != '>'){
                    punt3++;
                    aux3++;
                }
                string param3 = comando.substr(punt2+2,aux3);
                cout<< "Path: "<<param3<<endl;
                /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
                
                //Extraccion de los parametros de usuario y password.
                int punt4 = punt3+2;
                int aux4=0;
                while (comando[punt4] != '>'){
                    punt4++;
                    aux4++;
                }
                string param4 = comando.substr(punt3+2,aux4);
                int punt5 = punt4+2;
                int aux5=0;
                while (comando[punt5] != '>'){
                    punt5++;
                    aux5++;
                }
                string param5 = comando.substr(punt4+2,aux5);
                //Extraccion de los parametros de usuario y password.
                
                string ret = File_System->newFile(param2, param1, param3);
                if(ret=="") {
                    cout << "Ubicacion incorrecta" << endl; //Añadir error
                }
                else {
                    /*Parse y envío en formato json */
                    Jzon::Object root;                              //Creación del objeto para parsear el contenido
                    root.Add("Peer descriptor", ret);               //Añade una etiqueta con el valor correspondiente

                    Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
                    writer.Write();                                 //Escribe el nodo
                    std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
                    cout << result << endl;

                    //Enviar "result" al cliente
                }
            }
        }

        cout << "touch Finalizado" << endl;
    }

    else if(dato=="mkcont"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<< "Container name: "<<param1<<endl;
        
        if(param1.size()>64) {
                cout << "Numero de caracteres excedido en container name" << endl; //Añadir error
        }
        else {
            int punt2 = punt1+2;
            int aux2=0;
            while (comando[punt2] != '>'){
                punt2++;
                aux2++;
            }
            string param2 = comando.substr(punt1+2,aux2);
            cout<< "path: "<<param2<<endl;
             //Extraccion de los parametros de usuario y password.
            int punt3 = punt2+2;
            int aux3=0;
            while (comando[punt3] != '>'){
                punt3++;
                aux3++;
            }
            string param3 = comando.substr(punt2+2,aux3);
            int punt4 = punt3+2;
            int aux4=0;
            while (comando[punt4] != '>'){
                punt4++;
                aux4++;
            }
            string param4 = comando.substr(punt3+2,aux4);
             //Extraccion de los parametros de usuario y password.

            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
            int ret =0;
            ret=File_System->newFolder(param1, param2);
            cout<<"NUMERO"<<endl;
            cout<<ret<<endl;

            /*Parse y envío en formato json */
            Jzon::Object root;                              //Creación del objeto para parsear el contenido
            root.Add("Operacion No Exitosa", ret);          //Añade una etiqueta con el valor correspondiente

            Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
            writer.Write();                                 //Escribe el nodo
            std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado

            //Enviar "result" al cliente

            cout << result << endl;

        }
        cout << "mkcont Finalizado" << endl;
    }

    else if(dato=="mkschema"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"file descriptor: "<<param1<<endl;

        int punt2 = punt1+1;
        int aux2=0;
        bool flag = false;
        while(!flag) {
            if((comando[punt2]=='}') && (comando[punt2+1]=='}')) {
                flag = true;
                aux2+=2;
            }
            else {
                punt2++;
                aux2++;
            }
        }
        string param2 = comando.substr(punt1+1,aux2);
        cout<<"Nombres columnas: "<<param2<<endl;
         //Extraccion de los parametros de usuario y password.
        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
        int punt4 = punt3+2;
        int aux4=0;
        while (comando[punt4] != '>'){
            punt4++;
            aux4++;
        }
        string param4 = comando.substr(punt3+2,aux4);
         //Extraccion de los parametros de usuario y password.

        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        int ret = File_System->createSchema(param1, param2);

        /*Parse y envío en formato json */
        Jzon::Object root;                              //Creación del objeto para parsear el contenido
        root.Add("Operacion No Exitosa", ret);          //Añade una etiqueta con el valor correspondiente

        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
        writer.Write();                                 //Escribe el nodo
        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado

        //Enviar "result" al cliente

        cout << result << endl;
        cout << "mkschema Finalizado" << endl;
    }

    else if(dato=="add-reg"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"file descriptor: "<<param1<<endl;

        int punt2 = punt1+1;
        int aux2=0;
        bool flag = false;
        while(!flag) {
            if(comando[punt2]=='}' && comando[punt2+1]=='}') {
                flag = true;
                aux2+=2;
            }
            else {
                punt2++;
                aux2++;
            }
        }
        string param2 = comando.substr(punt1+1,aux2);
        cout<<"Columnas: "<<param2<<endl;
         //Extraccion de los parametros de usuario y password.
        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
        int punt4 = punt3+2;
        int aux4=0;
        while (comando[punt4] != '>'){
            punt4++;
            aux4++;
        }
        string param4 = comando.substr(punt3+2,aux4);
         //Extraccion de los parametros de usuario y password.

        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        string ret =std::to_string( File_System->addRegister(param1, param2));
        if(ret=="") {
            cout << "Archivo no encontrado" << endl; //Añadir error
        }
        else {
            /*Parse y envío en formato json */
            Jzon::Object root;                              //Creación del objeto para parsear el contenido
            root.Add("Número de registro", ret);            //Añade una etiqueta con el valor correspondiente

            Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
            writer.Write();                                 //Escribe el nodo
            std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado

            //Enviar "result" al cliente

            cout << result << endl;
        }
        cout << "add-reg Finalizado" << endl;
    }

    else if(dato=="get-reg"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"file descriptor: "<<param1<<endl;

        int punt2 = punt1+2;
        int aux2=0;
        while (comando[punt2] != '>'){
            punt2++;
            aux2++;
        }
        string param2 = comando.substr(punt1+2,aux2);
        cout<<"Entero 1 o 0: "<<param2<<endl;
        int param2_int = atoi(param2.c_str());

        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
        cout<<"offset or reg num: "<<param3<<endl;
        int param3_int = atoi(param3.c_str());

        int punt4 = punt3+2;
        int aux4=0;
        while (comando[punt4] != '>'){
            punt4++;
            aux4++;
        }
        string param4 = comando.substr(punt3+2,aux4);
        cout<<"todo o columnas: "<<param4<<endl;
         //Extraccion de los parametros de usuario y password.
        int punt5 = punt4+2;
        int aux5=0;
        while (comando[punt5] != '>'){
            punt5++;
            aux5++;
        }
        string param5 = comando.substr(punt4+2,aux5);
        int punt6 = punt5+2;
        int aux6=0;
        while (comando[punt6] != '>'){
            punt6++;
            aux6++;
        }
        string param6 = comando.substr(punt5+2,aux6);
         //Extraccion de los parametros de usuario y password.

        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        string ret = File_System->getRegister(param1, param2_int, param3_int, param4);

        /*Parse y envío en formato json */
        Jzon::Object root;                              //Creación del objeto para parsear el contenido

        int pos = 1;
        while(pos < ret.size()-1) {
            int i = pos;
            int j = pos;

            while(ret[j]!=':') {
                j++;
            }
            string nodNomb = ret.substr(i,j);
            j += 1;
            int k = j;
            while(ret[k]!='>') {
                k++;
            }
            string nodVal = ret.substr(j,k);

            root.Add(nodNomb, nodVal);                  //Añade una etiqueta con el valor correspondiente

            pos = k+2;
        }

        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
        writer.Write();                                 //Escribe el nodo
        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
        cout << result << endl;

        //Enviar "result" al cliente

        cout << "get-reg Finalizado";
    }

    else if(dato=="del-reg"){
         /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"file descriptor: "<<param1<<endl;
        
        int punt2 = punt1+2;
        int aux2=0;
        while (comando[punt2] != '>'){
            punt2++;
            aux2++;
        }
        string param2 = comando.substr(punt1+2,aux2);
        cout<<"1 o 0: "<<param2<<endl;
        int param2_int = atoi(param2.c_str());
        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
         cout<<"offset o reg num: "<<param3<<endl;
        int param3_int = atoi(param3.c_str());
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
         //Extraccion de los parametros de usuario y password.
        int punt4 = punt3+2;
        int aux4=0;
        while (comando[punt4] != '>'){
            punt4++;
            aux4++;
        }
        string param4 = comando.substr(punt3+2,aux4);
        int punt5 = punt4+2;
        int aux5=0;
        while (comando[punt5] != '>'){
            punt5++;
            aux5++;
        }
        string param5 = comando.substr(punt4+2,aux5);
         //Extraccion de los parametros de usuario y password.
        File_System->deleteRegister(param1, param2_int, param3_int);

        cout << "del-reg Finalizado";
    }

    else if(dato=="mod-reg"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"file descriptor: "<<param1<<endl;

        int punt2 = punt1+2;
        int aux2=0;
        while (comando[punt2] != '>'){
            punt2++;
            aux2++;
        }
        string param2 = comando.substr(punt1+2,aux2);
        cout<<"1 o 0: "<<param2<<endl;
        int param2_int = atoi(param2.c_str());

        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
        cout<<"offset o regnum: "<<param3<<endl;
        int param3_int = atoi(param3.c_str());


        //
        int punt4 = punt3+1;
        int aux4=0;
        bool flag = false;
        while(!flag) {
            if(comando[punt4]=='}' && comando[punt4+1]=='}') {
                flag = true;
                aux4+=2;
            }
            else {
                punt4++;
                aux4++;
            }
        }
        string param4 = comando.substr(punt3+1,aux4);
        cout<<"Columnas: "<<param4<<endl;
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
         //Extraccion de los parametros de usuario y password.
        int punt5 = punt4+2;
        int aux5=0;
        while (comando[punt5] != '>'){
            punt5++;
            aux5++;
        }
        string param5 = comando.substr(punt4+2,aux5);
        int punt6 = punt5+2;
        int aux6=0;
        while (comando[punt6] != '>'){
            punt6++;
            aux6++;
        }
        string param6 = comando.substr(punt5+2,aux6);
         //Extraccion de los parametros de usuario y password.
        File_System->modifyReg(param1, param2_int, param3_int, param4);

        cout << "mod-reg Finalizado";
    }

    else if(dato=="del-file"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"file descriptor: "<<param1<<endl;
         //Extraccion de los parametros de usuario y password.
        int punt2 = punt1+2;
        int aux2=0;
        while (comando[punt2] != '>'){
            punt2++;
            aux2++;
        }
        string param2 = comando.substr(punt1+2,aux2);
        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
         //Extraccion de los parametros de usuario y password.

        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        File_System->deleteFile(param1);

        cout << "del-file Finalizado" << endl;
    }

    else if(dato=="del-cont"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"path: "<<param1<<endl;
         //Extraccion de los parametros de usuario y password.
        int punt2 = punt1+2;
        int aux2=0;
        while (comando[punt2] != '>'){
            punt2++;
            aux2++;
        }
        string param2 = comando.substr(punt1+2,aux2);
        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
         //Extraccion de los parametros de usuario y password.
        

        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        File_System->deleteFolder(param1);

        cout << "del-cont Finalizado" << endl;
    }

    else if(dato=="get-schema"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"file descriptor: "<<param1<<endl;
        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
         //Extraccion de los parametros de usuario y password.
        int punt2 = punt1+2;
        int aux2=0;
        while (comando[punt2] != '>'){
            punt2++;
            aux2++;
        }
        string param2 = comando.substr(punt1+2,aux2);
        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3= comando.substr(punt2+2,aux3);
         //Extraccion de los parametros de usuario y password.
        string ret = File_System->getSchema(param1);

        //Enviar result al cliente

        cout << ret << endl;
        cout << "get-schema Finalizado" << endl;
    }

    else if(dato=="ls-cont"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"path: "<<param1<<endl;
         //Extraccion de los parametros de usuario y password.
        int punt2 = punt1+2;
        int aux2=0;
        while (comando[punt2] != '>'){
            punt2++;
            aux2++;
        }
        string param2 = comando.substr(punt1+2,aux2);
        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
        //Extraccion de los parametros de usuario y password.

        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        File_System->queryFolder(param1);

        cout << "ls-cont Finalizado" << endl;
    }

    else if(dato=="cat-file"){
        /*Separación de los parámetros del comando*/
        int punt1 = j+1;
        int aux1=0;
        while (comando[punt1] != '>'){
            punt1++;
            aux1++;
        }
        string param1 = comando.substr(j+1,aux1);
        cout<<"file descriptor: "<<param1<<endl;
         //Extraccion de los parametros de usuario y password.
        int punt2 = punt1+2;
        int aux2=0;
        while (comando[punt2] != '>'){
            punt2++;
            aux2++;
        }
        string param2 = comando.substr(punt1+2,aux2);
        int punt3 = punt2+2;
        int aux3=0;
        while (comando[punt3] != '>'){
            punt3++;
            aux3++;
        }
        string param3 = comando.substr(punt2+2,aux3);
         //Extraccion de los parametros de usuario y password.

        /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
        File_System->checkFile(param1);

        cout << "cat-file Finalizado";
    }

    else{
        cout <<"se ha digitado un comando invalido";     //Añadir error  
    }
}//fin de funcion

    
//fin de funcion
  
//    ANB* File_System = new ANB();
//    int tmp = 1;
//    while(tmp==1){
//        string pru;
//        getline(cin,pru);
//        int j=0;
//        while (pru[j]!= '<'){
//            j++;
//        }
//        string dato=pru.substr(0,j);
//        cout <<dato;
//        if(dato=="touch"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//            if(param1.size()>64) {
//                cout << "Numero de caracteres excedido en file name" << endl; //Añadir error
//            }
//            else {
//                int punt2 = punt1+2;
//                while (pru[punt2] != '>'){
//                    punt2++;
//                }
//                string param2 = pru.substr(punt1+2,punt2);
//                if(param2.size()>64) {
//                    cout << "Numero de caracteres excedido en client descriptor" << endl; //Añadir error
//                }
//                else {
//                    int punt3 = punt2+2;
//                    while (pru[punt3] != '>'){
//                        punt3++;
//                    }
//                    string param3 = pru.substr(punt2+2,punt3);
//
//                    /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//                    string ret = File_System->newFile(param2, param1, param3);
//                    if(ret=="") {
//                        cout << "Ubicacion incorrecta" << endl; //Añadir error
//                    }
//                    else {
//                        /*Parse y envío en formato json */
//                        Jzon::Object root;                              //Creación del objeto para parsear el contenido
//                        root.Add("Peer descriptor", ret);               //Añade una etiqueta con el valor correspondiente
//
//                        Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//                        writer.Write();                                 //Escribe el nodo
//                        std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//                        cout << result << endl;
//
//                        //Enviar "result" al cliente
//                    }
//                }
//            }
//
//            cout << "touch Finalizado" << endl;
//        }
//
//        else if(dato=="mkcont"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//            if(param1.size()>64) {
//                    cout << "Numero de caracteres excedido en container name" << endl; //Añadir error
//            }
//            else {
//                int punt2 = punt1+2;
//                while (pru[punt2] != '>'){
//                    punt2++;
//                }
//                string param2 = pru.substr(punt1+2,punt2);
//
//                /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//                int ret = File_System->newFolder(param2, param1);
//
//                /*Parse y envío en formato json */
//                Jzon::Object root;                              //Creación del objeto para parsear el contenido
//                root.Add("Operacion No Exitosa", ret);          //Añade una etiqueta con el valor correspondiente
//
//                Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//                writer.Write();                                 //Escribe el nodo
//                std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//
//                //Enviar "result" al cliente
//
//                cout << result << endl;
//
//            }
//            cout << "mkcont Finalizado" << endl;
//        }
//
//        else if(dato=="mkschema"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            int punt2 = punt1+1;
//            bool flag = false;
//            while(!flag) {
//                if((pru[punt2]=='}') && (pru[punt2+1]=='}')) {
//                    flag = true;
//                }
//                else {
//                    punt2++;
//                }
//            }
//            string param2 = pru.substr(punt1+1,punt2+2);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            int ret = File_System->createSchema(param1, param2);
//
//            /*Parse y envío en formato json */
//            Jzon::Object root;                              //Creación del objeto para parsear el contenido
//            root.Add("Operacion No Exitosa", ret);          //Añade una etiqueta con el valor correspondiente
//
//            Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//            writer.Write();                                 //Escribe el nodo
//            std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//
//            //Enviar "result" al cliente
//
//            cout << result << endl;
//            cout << "mkschema Finalizado" << endl;
//        }
//
//        else if(dato=="add-reg"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            int punt2 = punt1+1;
//            bool flag = false;
//            while(!flag) {
//                if(pru[punt2]=='}' && pru[punt2+1]=='}') {
//                    flag = true;
//                }
//                else {
//                    punt2++;
//                }
//            }
//            string param2 = pru.substr(punt1+1,punt2+2);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            string ret = File_System->addRegister(param1, param2);
//            if(ret=="") {
//                cout << "Archivo no encontrado" << endl; //Añadir error
//            }
//            else {
//                /*Parse y envío en formato json */
//                Jzon::Object root;                              //Creación del objeto para parsear el contenido
//                root.Add("Número de registro", ret);            //Añade una etiqueta con el valor correspondiente
//
//                Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//                writer.Write();                                 //Escribe el nodo
//                std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//
//                //Enviar "result" al cliente
//
//                cout << result << endl;
//            }
//            cout << "add-reg Finalizado" << endl;
//        }
//
//        else if(dato=="get-reg"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            int punt2 = punt1+2;
//            while (pru[punt2] != '>'){
//                punt2++;
//            }
//            string param2 = pru.substr(punt1+2,punt2);
//            int param2_int = atoi(param2.c_str());
//
//            int punt3 = punt2+2;
//            while (pru[punt3] != '>'){
//                punt3++;
//            }
//            string param3 = pru.substr(punt2+2,punt3);
//            int param3_int = atoi(param3.c_str());
//
//            int punt4 = punt3+2;
//            while (pru[punt4] != '>'){
//                punt4++;
//            }
//            string param4 = pru.substr(punt2+2,punt3);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            string ret = File_System->getRegister(param1, param2_int, param3_int, param4);
//
//            /*Parse y envío en formato json */
//            Jzon::Object root;                              //Creación del objeto para parsear el contenido
//
//            int pos = 1;
//            while(pos < ret.size()-1) {
//                int i = pos;
//                int j = pos;
//
//                while(ret[j]!=':') {
//                    j++;
//                }
//                string nodNomb = ret.substr(i,j);
//                j += 1;
//                int k = j;
//                while(ret[k]!='>') {
//                    k++;
//                }
//                string nodVal = ret.substr(j,k);
//
//                root.Add(nodNomb, nodVal);                  //Añade una etiqueta con el valor correspondiente
//
//                pos = k+2;
//            }
//
//            Jzon::Writer writer(root, Jzon::StandardFormat);//Escribe la etiqueta en el formato estándar
//            writer.Write();                                 //Escribe el nodo
//            std::string result = writer.GetResult();        //Almacena en una variable string el formato json creado
//            cout << result << endl;
//
//            //Enviar "result" al cliente
//
//            cout << "get-reg Finalizado";
//        }
//
//        else if(dato=="del-reg"){
//             /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//            int punt2 = punt1+2;
//            while (pru[punt2] != '>'){
//                punt2++;
//            }
//            string param2 = pru.substr(punt1+2,punt2);
//            int param2_int = atoi(param2.c_str());
//            int punt3 = punt2+2;
//            while (pru[punt3] != '>'){
//                punt3++;
//            }
//            string param3 = pru.substr(punt2+2,punt3);
//            int param3_int = atoi(param3.c_str());
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            File_System->deleteRegister(param1, param2_int, param3_int);
//
//            cout << "del-reg Finalizado";
//        }
//
//        else if(dato=="mod-reg"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            int punt2 = punt1+2;
//            while (pru[punt2] != '>'){
//                punt2++;
//            }
//            string param2 = pru.substr(punt1+2,punt2);
//            int param2_int = atoi(param2.c_str());
//
//            int punt3 = punt2+2;
//            while (pru[punt3] != '>'){
//                punt3++;
//            }
//            string param3 = pru.substr(punt2+2,punt3);
//            int param3_int = atoi(param3.c_str());
//
//            int punt4 = punt3+2;
//            while (pru[punt4] != '>'){
//                punt4++;
//            }
//            string param4 = pru.substr(punt2+2,punt3);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            File_System->modifyReg(param1, param2_int, param3_int, param4);
//
//            cout << "mod-reg Finalizado";
//        }
//
//        else if(dato=="del-file"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            File_System->deleteFile(param1);
//
//            cout << "del-file Finalizado" << endl;
//        }
//
//        else if(dato=="del-cont"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            File_System->deleteFolder(param1);
//
//            cout << "del-cont Finalizado" << endl;
//        }
//
//        else if(dato=="get-schema"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            string ret = File_System->getSchema(param1);
//
//            //Enviar result al cliente
//
//            cout << ret << endl;
//            cout << "get-schema Finalizado" << endl;
//        }
//
//        else if(dato=="ls-cont"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            File_System->queryFolder(param1);
//
//            cout << "ls-cont Finalizado" << endl;
//        }
//
//        else if(dato=="cat-file"){
//            /*Separación de los parámetros del comando*/
//            int punt1 = j+1;
//            while (pru[punt1] != '>'){
//                punt1++;
//            }
//            string param1 = pru.substr(j+1,punt1);
//
//            /*Llamada a la función correspondiente y almacenamiento de su valor de retorno */
//            File_System->checkFile(param1);
//
//            cout << "cat-file Finalizado";
//        }
//
//        else{
//            cout <<"se ha digitado un comando invalido";      //Añadir error  
//        }
//    }
//}
