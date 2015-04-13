#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
	int fd=0;
	//unsigned char buf[BUFFER_SIZE]=0;
	
	fd=open("test.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);
	if(fd==-1){
		perror("Erro");
		close(fd);
		return 1;
	}
	fd2=open("words.txt",O_RDONLY);
	if(fd2==-1){
		perror("Erro");
		close(fd2);
		return 2;
	}
	while(){
	execlp("grep","grep","-o -n", word, "test.txt", NULL);
	}
	return 0;
}
