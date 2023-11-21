#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void handle_request(int client_socket);

int main(){

	//declarations
	int server_socket, client_socket;
	struct sockaddr_in server_address, client_address;
	socklen_t client_address_lenth = sizeof(client_address);

	//creating a stream socket
	if((server_socket = socket(AF_INET, SOCK_STREAM, 0))==-1){
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	//setting up the server address structure
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	//converting 16 bit integer byte order from host machine byte order
	//to network byte order. In my case, my machine has an intel CPU
	//its converting my host PC's little endian to the network's big endian
	server_address.sin_port = htons(PORT);
	//binding the server socket
	if(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
		perror("Error binding socket");
		close(server_socket);
		exit(EXIT_FAILURE);
	}

	//listening
	//backlog parameter of 10, this sets the maximum allowed pending connections
	if(listen(server_socket, 10) == -1) {
		perror("Error listening for connections");
		close(server_socket);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d...\n", PORT);
	
	//handling incoming connections
	while(1) 
	{
		if((client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_lenth))== -1){
			perror("Error accepting connection");
			continue;
		}

		//fork a new process to handle the request
		if(fork() == 0) {
			close(server_socket); //child process doesn't need this
			handle_request(client_socket);
			exit(EXIT_SUCCESS);
		} else {
			close(client_socket); //at this point, this is unneeded
		}
	}
}



void handle_request(int client_socket) { 

	char buffer[BUFFER_SIZE];
	ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

	if (bytes_received <= 0) {
		perror("Error receiving data..");
		close(client_socket);
		return;
	}

	buffer[bytes_received] = '\0';
	printf("Received request: \n%s\n", buffer);
	const char* response;
	if(strstr(buffer, "GET /hello") != NULL) {
		response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
	} else {
		response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found";
	}

	send(client_socket, response, strlen(response), 0);
	close(client_socket);
}
