#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

int sortLines(){
	execlp("sort","sort","-u","--output=final.txt","temp_1.txt",NULL);
	return 0;
}

int clean(){
	char a;
	FILE * read;
	FILE * write;
	char oldw[BUFFER_SIZE]="";
	char str[BUFFER_SIZE]="";
	int p=0;
	read=fopen("final.txt","r"); // lê
	if (read == NULL){
          perror("Erro");
          fclose(read);
          return 1;
	}
	
	write=fopen("index.txt","w"); // lê
	if (write == NULL){
          perror("Erro");
          fclose(write);
          return 1;
	}
	do{ 
		char fLine[BUFFER_SIZE]="";
		char word[BUFFER_SIZE]="";
		char token[BUFFER_SIZE]="";
		a=fscanf(read,"%s",word); // lê linha 
		a=fscanf(read,"%s",token); // lê linha 
		a=fscanf(read,"%s",fLine); // lê linha 
		if(strcmp(oldw,word)!=0){
			strcpy(oldw,word);
			printf("%s\n",str);
			strcat(str,"\n");
			if(p!=0)
				fputs(str,write);
			else
				p=1;
			sprintf(str, "%s : %s", word, fLine);
		}
		else{
			strcat(str,", ");
			strcat(str,fLine);
		}
	}while(a!=EOF);
	return 0;
}
	
int main(int argc, char *argv[]){
	//sortLines();
	clean();
	return 0;
}
