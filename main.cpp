#include <stdio.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

bool port_is_open(char const *TARGET, int PORT){
	int sock = 0, valread; 
    struct sockaddr_in serv_addr;  
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, TARGET, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        //printf("\nConnection Failed \n"); 
        return -1; 
    }
    else
    {
    	return 0;
    }
}
//nmap <ip>
void check_from_1_to_1000(char const *TARGET){
	for(int port=1 ; port < 1000 ; port++)
		if(port_is_open(TARGET, port) == 0)
			printf("Port %d: Open\n", port);
}
//nmap -p- <ip> 
void check_from_1_to_65535(char const *TARGET){
	for(int port=1 ; port < 65535 ; port++)
		if(port_is_open(TARGET, port) == 0)
			printf("Port %d: Open\n", port);
}

int main()
{
  	printf("NJuan!\n");
	
	//List ports from localhost
	check_from_1_to_1000("127.0.0.1"); 
  	//check_from_1_to_65535("127.0.0.1"); 

  	return 0;
}