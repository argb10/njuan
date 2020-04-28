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
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    else 
    	return sock;
}

sockaddr_in create_serv_addr(char const *TARGET){

	struct sockaddr_in serv_addr; 
   	//Specifies protocol and port to try the connection
    serv_addr.sin_family = AF_INET; 

    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, TARGET, &serv_addr.sin_addr)<=0)  
        printf("\nInvalid address/ Address not supported \n"); 

   	return serv_addr;
}

void check_open_ports(char const *TARGET, bool fullscan){
	
	int sock = create_socket_tcp();
	struct sockaddr_in serv_addr = create_serv_addr(TARGET);
	int limit = 1000;

	if(fullscan)
		limit = 65535;

	for(int PORT=1 ; PORT < limit ; PORT++){
	    serv_addr.sin_port = htons(PORT);
	    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0) 
			printf("Port %d: Open\n", PORT);
	}
}
/*
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
*/
int main()
{
  	printf("NJuan!\n");
	
	//List ports from localhost
	check_open_ports("127.0.0.1", true); 
  	//check_from_1_to_65535("127.0.0.1"); 

  	return 0;
}