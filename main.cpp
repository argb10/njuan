#include <stdio.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

int create_socket_tcp(){
	int sock = 0;
    //Socket Creation: AF_INET=IPV4, SOCK_STREAM=safe two way comunication(tcp), 0=standard protocol to the sock_stream specified
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n NjuanAlert: Socket creation error \n"); 
        return -1; 
    }
    else 
    	return sock;
}
bool port_is_open(char const *TARGET, int PORT){
	int sock = create_socket_tcp();
	struct sockaddr_in serv_addr;

   	//Set Ipv4
    serv_addr.sin_family = AF_INET; 

    //Set port
    serv_addr.sin_port = htons(PORT); 

    // Convert IPv4 addresses from text to binary
    if(inet_pton(AF_INET, TARGET, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nNjuanAlert: Invalid address / Address not supported \n"); 
        return -1; 
    }
   
    //Try connect
    int status = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    //Close socket so we can continue scanning
    close(sock);

    //Shoulf I do the sleep here?----------------
    //sleep(0.0001);

    if (status < 0)
        return -1; //Connection Failed
    else
    	return 0;
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

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        printf ("Please enter the server IP address and range of ports to be scanned\n");
        printf ("USAGE: %s <IP> (-p-)\n", argv[0]);
        return(1);
    }
    
    char IP[16] = {0};
    strcpy(IP, argv[1]); // Copy the IP

    char ports[3] = {0};
    if (argc == 3){
   		strcpy(ports, argv[2]); // Copy the parameter
	}
 	
  	printf("NJuan! :)\n");
	
	if( strcmp(ports, "-p-") == 0)
		check_from_1_to_65535("127.0.0.1");
	else
		check_from_1_to_1000("127.0.0.1");
  	return 0;
}