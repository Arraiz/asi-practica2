/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: osboxes
 *
 * Created on 21 February 2018, 07:24
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/msg.h>
//ruta de las pipes
#define FILENAME "/tmp/fifo_monitor_1"
#define FILENAME2 "/tmp/fifo_monitor_2"
#define CLAVE_COLA 0x78953960L
/*
 * 
 */
int pid_monitor;
char buffer1[255];
char buffer2[255];
int bytesLeidos;
int bytesEscritos;
int fifo1;
int fifo2;
int clave3;
char clave4[255];
int id_cola_msg_1;
int id_cola_msg_2;
int id_cola_msg_3;
int id_cola_msg_4;
int id_cola_msg_5;

char clave5[255];
int *p;

typedef struct Mensaje {
    long ID_mensaje;
    char mensaje[255];


} Mensaje;

Mensaje msg; //ejercicio3
Mensaje msg2; //ejericcio4
Mensaje msg3; //ejercico5
Mensaje msg4; //ejercico6

Mensaje msg5; //ejercico7

void ejercicio7() {

    //abrimo cola
    id_cola_msg_5 = msgget(CLAVE_COLA, 0666 | IPC_CREAT);
    //enviamos mensaje
    msg5.ID_mensaje = pid_monitor;
    msgsnd(id_cola_msg_5, &msg5, sizeof (Mensaje) - sizeof (long), 0);
    sleep(1);
    close(id_cola_msg_5);
    msgctl(id_cola_msg_5, IPC_RMID, (struct msqid_ds*) NULL);

}

void ejercicio6() {
    int error;
    Mensaje msg4; //ejercicio6
    //abrimos acceso a la cola
    int id_cola_msg_4 = msgget(CLAVE_COLA, 0666 | IPC_CREAT);
    if (id_cola_msg_4 == -1) {
        printf("error en cola");
    } else {
        //escribimos el mensaje
        sprintf(msg4.mensaje, "%s", clave5);
        msg4.ID_mensaje = pid_monitor;
        printf("enviando id: %ld y mensaje: %s\n", msg4.ID_mensaje, msg4.mensaje);
        error = msgsnd(id_cola_msg_4, &msg4, sizeof (Mensaje) - sizeof (long), 0);

        if (error == -1) {
            printf("error");

        } else {
            printf("mensaje enviado %s\n", msg4.mensaje);
        }
    }




}

void ejercicio5() {
    int error;
    //accedemos a la cola
    id_cola_msg_3 = msgget(CLAVE_COLA, 0666);
    if (id_cola_msg_3 == -1) {
        printf(":((((\n");
    } else {
        //leer de la cola pero un tipo especifico de mensaje el PID
        error = msgrcv(id_cola_msg_3, &msg3, sizeof (Mensaje) - sizeof (long), getpid(), 0);
        if (error == -1) {
            printf("error en leyendo msg");
        } else {
            printf("leido %s", msg3.mensaje);
            sprintf(clave5, msg3.mensaje);
        }
    }

}

void ejercicio4() {
    int error;
    //creamos la cola
    id_cola_msg_2 = msgget(CLAVE_COLA, 0666 | IPC_CREAT);
    if (id_cola_msg_2 == -1) {
        printf("error creando cola");

    } else {
        //escrimos en la cola!!!
        //1º volcamos el contenido al mesaje
        sprintf(msg2.mensaje, "<%d>%s", clave3, clave4);
        //2º escrimos el id del mensaje
        msg2.ID_mensaje = msg.ID_mensaje;
        error = msgsnd(id_cola_msg_2, &msg2, sizeof (Mensaje) - sizeof (long), 0);
        if (error == -1) {
            printf("mensaje enviado!!\n");
        }

    }

}

void ejercicio3() {

    int error;
    //obtenemos aceso a la cola de mensajes
    id_cola_msg_1 = msgget(CLAVE_COLA, 0666);
    //leemos de la cola
    error = msgrcv(id_cola_msg_1, &msg, sizeof (Mensaje) - sizeof (long), 0, 0);
    if (error == -1) {
        printf("error leyendo el mensaje");

    } else {
        printf("id mensaje: %ld  conexto del mensaje: %s\n", msg.ID_mensaje, msg.mensaje);
        clave3 = (int) msg.ID_mensaje;
        sprintf(clave4, "%s", msg.mensaje);

    }



}

void ejercicio2() {


    int error;
    int bytesEscritos;

    printf("ejercicio2\n");
    printf("creando FIFO2\n");
    mkfifo(FILENAME2, S_IRWXU);
    if (error) {
        puts("error\n");
        printf("error %d\n", error);
    } else {

        printf("error: %d\n", error);
        printf("fifo creada\n");

    }
    printf("abriendo fifo para escribir\n");
    fifo2 = open(FILENAME2, O_RDWR);
    if (fifo2 == -1) {
        puts("error abirndo fifo\n");

    } else {
        puts("fifo abierta para escribir\n");
        puts(buffer1);
        bytesEscritos = write(fifo2, buffer1, 6);
        printf("bytes escritos %d\n", bytesEscritos);

        printf("leyendo la respuesta del monitor en FIFO1\n");
        bytesLeidos = read(fifo1, buffer2, 255);
        printf("bytes leidos %d\n", bytesLeidos);
        printf("enviado respuesta al monitor\n");
        bytesEscritos = write(fifo2, buffer2, 6);
        printf("bytes escritos %d\n", bytesEscritos);





    }


}

void ejercicio1() {

    int bytesLeidos;
    printf("ejercicio1 \n");
    printf("abriendo fifo para leer\n");
    fifo1 = open(FILENAME, O_RDWR);
    //error handling
    if (fifo1 == -1) {
        printf("error\n");
    } else {
        printf("leyendo FIFO\n");
        bytesLeidos = read(fifo1, buffer1, 255);
        printf("bites leidos: %d\n", bytesLeidos);
        puts(buffer1);

    }

}


/*++++++++++Ejercicio 3 con punteros++++++++++++++*/
void ejercicio3p(){
    
    long ID;
    char buffer[255];
    printf("tam puntero: %lu\n",sizeof(p));
    
  
}





int main(int argc, char** argv) {

  

    pid_monitor = atoi(argv[1]);
/*
    printf("pid monitor es: %d\n ", pid_monitor);
    getchar();
    ejercicio1();
    getchar();
    ejercicio2();
    printf("pulsa para el ejercicio 3");
    getchar();
    ejercicio3();
    printf("pulsa para el ejercicio 4");
    getchar();
    ejercicio4();
    ejercicio5();
    getchar();
    ejercicio6();
 
    getchar();
 
    ejercicio7();
    getchar();
 */
    
    ejercicio3p();
    printf("tam: %d\n",sizeof(Mensaje));

    return (EXIT_SUCCESS);
}

