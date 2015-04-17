#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

int reverseOutput(){
	sleep(1);
	int pos=0, i ,index,size=0;
	char a;
	FILE * t;
	FILE * temp;
	
	temp=fopen("temp.txt","w"); // escreve
	if (temp == NULL){
          perror("Erro");
          fclose(temp);
          return 3;
	}
	t=fopen("test.txt","r"); // lê
	if (t == NULL){
          perror("Erro");
          fclose(t);
          return 4;
	}
	do{ 
		char buf[BUFFER_SIZE]="";
		char noLine[BUFFER_SIZE]="";
		char word[BUFFER_SIZE]="";
		char str[BUFFER_SIZE]="";
		a=fscanf(t,"%s",buf); // lê linha 
		size=strlen(buf);
		for(i=0; i<size;i++){
			 if(buf[i] != ':') 
				noLine[i] = buf[i] ;
			 else {
				pos = i+1; 
				break; 
			 }
		}		 
		for(i=pos, index=0; i<size; i++, index++) {
			 word[index] = buf[i]; 
		}
		sprintf(str, "%s : 1-%s\n", word, noLine);
		int strSize=strlen(word);
		if(strSize!=0)
			fputs(str,temp);
	}while(a!=EOF);
	fclose(t);
	fclose(temp);
	return 0;
}

int main(int argc, char *argv[]){
	int f2=0;
	FILE * f1;
	char word[BUFFER_SIZE];
	char c;
    pid_t pid;
	
	f1=fopen("words.txt","r");
	if (f1 == NULL){
          perror("Erro");
          fclose(f1);
          return 2;
	   }
	f2=open("test.txt", O_WRONLY | O_CREAT, 0644);
	if(f2==-1){
		perror("Erro");
		close(f2);
		return 1;
	}
	dup2(f2,STDOUT_FILENO);
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
	close(f2);
	reverseOutput();
	return 0;
}


