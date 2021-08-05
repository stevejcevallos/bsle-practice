#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>


#define PORT_NUM 2000
#define MAX_CLIENTS 20


/**
 * @brief Recieve Messages byte by byte from any connections
 *
 * @param fd is the accepted socket
 * @param buffer is the caracter * with the message being recieved
 * @param buffer_size is the isze of the expected message
 *
 * @return: 0 is a Sucessful connections, -1 is Failed connection
*/
static bool get_message(int fd, char *buffer, size_t *buffer_size){

    char *spot = buffer;
    size_t count = 0;
    while(count < *buffer_size && recv(fd, spot, 1, 0) == 1)
    {
        count++;
        if ('\0' == *spot)
        {
            *buffer_size = count;
            return true;
        }
        spot++;
    }

    return false;
}

int set_up_server_socket(void)
{
    //Socket Varaibles
    int server_socket;
    int opt_val = 1;

    //Structure for the sending and recving address
    struct sockaddr_in server_addr = {0};

    //Creating the TCP Socket to Connect to the Server
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        puts("In server_network.c Failed to set the Network Socket ");
    }

    //Setting the Socket family to IPv4 and Setting specified Port for server to be 2000
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_NUM);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //Setting the Socket OPTs to the apporpriate setting to reuse the Network
    if((setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val))) < 0)
    {
        puts("In server_network.c Failed to set socket opt");
        close(server_socket);
        return -1;
    }

    //Bind the specified socket to the created Scoket Addr
    if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        puts("In server_network.c  Failed to Bind the Network");
        close(server_socket);
        return -1;
    }

    //Beginning to Listen for Pythonic TCP Connections
    if(listen(server_socket, MAX_CLIENTS) == -1)
    {
        puts("In server_network.c  Failed to Listen to Any Connections");
        close(server_socket);
        return -1;
    }

    puts("Server Established");

    return server_socket;
}

/**
 * @brief Sets up the entire TCP Socket Connections. Allows Clients to connect to the server
 * @return: 0 is a Sucessful connections, -1 is Failed connection
*/
int main()
{
    int client_socket;
    struct sockaddr_in client_addr = {0};
    socklen_t client_len = 0;
    int server_socket = set_up_server_socket();
    if(server_socket == -1)
    {
        puts("In server_network.c Failed to Set Up Server");
        close(server_socket);
        return -1;
    }

    //Keeps the Server Open to accept connections
    //***********CHANGE TO CLOSE EVERYTHING AT A SIGINT *******
    while(1)
    {
        puts("Listening for New Connections");
        char client_ip[INET_ADDRSTRLEN];

        //Accepts Connections that are incomming, Prints IP with valid connection
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);
        if(client_socket < 0)
        {
            puts("In server_network.c  Failed to Accept Connections from Clients");
            close(server_socket);
            return -1;
        }
        else
        {
            printf("Connected to {%s} \n", inet_ntop(AF_INET, &client_addr.sin_addr.s_addr,
                client_ip, INET_ADDRSTRLEN));
        }

        //Send Message to Client Stating the Connection has been established
        char * connected_message = "Connection Established! Welcome!";
        int message_size = strlen(connected_message);
        if(send(client_socket, connected_message, message_size, 0) < 0)
        {
            puts("In server_network.c Failed to Send Connection to Clients");
            close(server_socket);
            return -1;
        }

        /***************** CHANGE CLIENT MESSAGE SIZE BASED ON PROJECT ****************
        size_t client_response_size = 256;
        char client_response[256] = {0};

        //Calls the get message Function to read in bit by bit
        if(get_message(client_socket, client_response, &client_response_size) == false)
        {
            puts("In server_network.c Failed to Recv the Entire Message from the Client");
            close(server_socket);
            return -1;
        }

        printf("MESSAGE: \t %s", client_response);
        */
    }

}