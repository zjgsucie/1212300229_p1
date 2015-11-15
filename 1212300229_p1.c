#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

//yong yu fenli shuru de canshu 
int split(char* cmd, char output[5][256]){
	int count = 0; //yongyu jisuan canshu 
	int length = strlen(cmd);
	int i,j=0,flag=0;
	for(i=0; i<length; i++){
		if(cmd[i] == ' '){
			if(count >0 && j!=0){
				output[count-1][j] = '\0';			
			}
			flag = 0;
		}else{
			if(flag == 0){
				count++;
				j = 0;
				flag = 1;			
			}
			output[count -1][j] = cmd[i];
			j++;		
		}
			
	}
	return count;
}
char cmd[256];
char params[5][256];
int counter=0;
void main(){
	int ret;
	printf("Hello World, this is Linux!");
	while(1){
		printf(">");
		fgets(cmd,256,stdin);
		if (cmd[strlen(cmd) - 1] == '\n')
		{  
                    cmd[strlen(cmd) - 1] = '\0';  
            	} 
		if(fork() == 0)  
        {    
            counter = split(cmd, params);  
                    if(counter != 0)  
                {   
                switch(counter)  
                {  
                    case 0: break;  
                    case 1:   
                    {  
                        execlp(params[0], params[0], NULL);  
                    }      
                    break;  
                    case 2:  
                    {  
                        //printf("%s %s\n" ,params[0] ,params[1] );  
                        execlp(params[0], params[0] , params[1], NULL);  
                    }  
                    break;  
                    case 3:  
                    {  
			printf("%s %s %s\n" ,params[0] ,params[1], params[2]);
                        execlp(params[0], params[0], params[1], params[2],  
                            (char*)0);  
                    }  
                    break;  
		     default:  
                    {  
                        printf("Illegal Input!\n");  
                    }  
                	} // end switch 
		}
		perror(cmd);
		exit(errno);
	   }else{  
		    wait(&ret);  
		    printf("child process return %d\n",ret);  
		}   
	    } // end while  
	    return 0; 
}
