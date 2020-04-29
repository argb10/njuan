#include <stdio.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
int create_socket_tcp(){
	int sock = 0;
    //Socket Creation: AF_INET=IPV4, SOCK_STREAM=safe two way comunication, 0=standard protocol to the sock_stream specified
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Njuan: Socket creation error \n"); 
        return -1; 
    }
    else 
    	return sock;
}
bool port_is_open(char const *TARGET, int PORT, int sock){
	struct sockaddr_in serv_addr;
   	//Specifies protocol to try the connection
    serv_addr.sin_family = AF_INET; 

    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, TARGET, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    serv_addr.sin_port = htons(PORT); 
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

	int sock = create_socket_tcp();
	for(int port=1 ; port < 1000 ; port++)
		if(port_is_open(TARGET, port, sock) == 0)
			printf("Port %d: Open\n", port);
}
//nmap -p- <ip> 
void check_from_1_to_65535(char const *TARGET){

	int sock = create_socket_tcp();	
	for(int port=1 ; port < 65535 ; port++){
        //printf("Scaning %d\n",port);
		if(port_is_open(TARGET, port, sock) == 0)
			printf("Port %d: Open\n", port);
        sleep(0.5);
    }
}

int main()
{
  	printf("NJuan!\n");
	
    /*Check my postgres at 5432
    int sock = create_socket_tcp();
    if(port_is_open("127.0.0.1", 5432, sock) == 0)
        printf("Port %d: Open\n", 5432);
    */
	//List ports from localhost
	//check_from_1_to_1000("127.0.0.1"); 
    printf("--------------------------------\n");
  	check_from_1_to_65535("127.0.0.1"); 

  	return 0;
}