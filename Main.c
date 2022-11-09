#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_CARACTER 20
#define MAX_FILES 50

typedef struct{
    char name[MAX_CARACTER];
} File;


int main(int argc, char *argv[]){

    int id, i = 0;
    int fd[2];              //fd[0] -> read;  fd[1] -> write
    DIR *dir;               //Pointer on directory
    struct dirent *file;
    File f[MAX_FILES];
    struct stat statbuf;  

    if(pipe(fd) == -1){
        exit(1);
    }

    if((id=fork()) < 0){
        exit(2);
    }

    //Child:
    if(id == 0){
        if((dir = opendir(argv[1])) == NULL){
            exit(3);
        }
        close(fd[0]);

        file = readdir(dir);

        while(file != NULL){
            strcpy(f[i++].name, file->d_name);

            file = readdir(dir);
        }

        write(fd[1], &i, sizeof(int)); //write in pipe
        write(fd[1], f, sizeof(f) * i); //write in pipe

        close(fd[1]);
    }else{
        //Perent:
        wait(NULL);

        close(fd[1]);

        read(fd[0], &i, sizeof(int));
        read(fd[0], f, sizeof(f) * i);

        for(int j = 0; j < i; j++){
            stat(f[j].name, &statbuf);  

            printf("Name: %s\tSize= %ld bytes\tOwner identifier: %d\n",f[j].name, statbuf.st_size, statbuf.st_uid);
        }
        close(fd[0]);
    }

    closedir(dir);

    return 0;
}
