#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
 #include <stdlib.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
	int fd=0;
	FILE * f1;
	//FILE * fd;
	char word[100];
	char c;
	//char  line[100];
   // size_t len = 0;
    //ssize_t rd;
    pid_t pid;

	//unsigned char buf[BUFFER_SIZE]=0;
	//fd=fopen("test.txt","w");
	fd=open("test.txt", O_WRONLY | O_CREAT, 0644);
	if(fd==-1){
		perror("Erro");
		close(fd);
		return 1;
	}
	//fd2=open("words.txt",O_RDONLY);
	/*if(fd2==-1){
		perror("Erro");
		close(fd2);
		return 2;
	}*/
	f1=fopen("words.txt","r");
	if (f1 == NULL){
          perror("Erro");
          fclose(f1);
          return 2;
         
	   }
	dup2(fd,STDOUT_FILENO);
	/*while ((rd = getline(&line, &len, f1)) != -1) {
		if((pid=fork())==-1){
			perror("fork error");
		}
		else if(pid==0){
		execlp("grep","grep","-o", "-n", line, "1.txt", NULL);
		}
       }*/
	do {
      c = fscanf(f1,"%s",word);									//got one word from the file 
      if((pid=fork())==-1){
			perror("fork error");
		}
		else if(pid==0){
		execlp("grep","grep","-o", "-n", word, "1.txt", NULL);
		}
   } while (c != EOF);           								  //repeat until EOF 
	
	fclose(f1);
	 
	return 0;
}
