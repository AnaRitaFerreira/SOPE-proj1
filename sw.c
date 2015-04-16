#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

int reverseOutput(){
	int pos=0, i ,index,size=0;
	char a;
	FILE * t;
	FILE * temp;
	
	temp=fopen("temp.txt","w");
	if (temp == NULL){
          perror("Erro");
          fclose(temp);
          return 3;
	}
	
	t=fopen("test.txt","r");
	if (t == NULL){
          perror("Erro");
          fclose(t);
          return 4;
	}

	do{ 
		char buf[100];
		char noLine[50];
		char word[50];
		a=fscanf(t,"%s",buf);
		size=strlen(buf);
		for(i=0; i<size;i++){
			 if(buf[i] != ':') 
			 noLine[i] = buf[i] ;
			 else pos = i+1; 
			 break; 
			 }
			 
		for(i=pos, index=0;i<size;i++, index++) {
			 word[index] = buf[i]; 
			 }
		strcat(word," : 1-");
		strcat(word,noLine);
		strcat(word,"\n");
		fputs(word,temp); 
	}while(a!=EOF);
	fclose(t);
	fclose(temp);
	return 0;
}

int main(int argc, char *argv[]){
	int fd=0;
	FILE * f1;
	char word[100];
	char c;
	
    pid_t pid;

	//unsigned char buf[BUFFER_SIZE]=0;
	
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
	
	do {
      c = fscanf(f1,"%s",word);									//got one word from the file 
      if((pid=fork())==-1){
			perror("fork error");
		}
		else if(pid==0){
		execlp("grep","grep","-o", "-n", word, "1.txt", NULL);
		}
   } while (c != EOF);          								  //repeat until EOF 
	
	fclose(f1);
	
	reverseOutput();
	return 0;
}


