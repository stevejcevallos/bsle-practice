#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include "threadpool.h"


#define PORT_NUM 2000
#define MAX_CLIENTS 20

static volatile int running = 1;

/**
 * @brief Signal handler
 *
 * @param fd is the accepted socket
 * @param buffer is the caracter * with the message being recieved
 * @param buffer_size is the size of the expected message
 *
 * REF: https://stackoverflow.com/questions/4217037/catch-ctrl-c-in-c
 *
 * @return: None
*/
void signal_handler(int sig)
{
    if(sig == SIGINT)
    {
        running = 0;
    }
}

/**
 * @brief Recieve Messages byte by byte from any connections
 * and checks the last byte to see if it is a NULL BYTE
 *
 * @param fd is the accepted socket
 * @param buffer is the caracter * with the message being recieved
 * @param buffer_size is the size of the expected message
 *
 * @return: 0 is a Sucessful connections, -1 is Failed connection
*/
static bool get_message(int fd, char *buffer, size_t *buffer_size)
{
    char * message = buffer;
    size_t count = 0;
    while(count < *buffer_size && recv(fd, message, 1, 0) == 1)
    {
        count++;
        if ('\0' == *message)
        {
            *buffer_size = count;
            return true;
        }
        message++;
    }

    printf("buffer is |%s|\n", buffer);
    printf("message is |%s|\n", message);
    printf("MY SIZE: %ld \n", count);
    return false;

}

/**
 * @brief Test the given functions/value return values, prints error message on failue
 *
 * @param check_this the function or value to complete due to critical operations
 * @param error_msg message to display before returning value
 * @param value is the value to test for
 *
 *
 * @return: function return operation on sucess, -1 on failue
*/
int check_functionality_server(int check_this, char * error_msg, int value)
{
    if(check_this == value)
    {
        perror(error_msg);
        exit(EXIT_FAILURE);
    }
    return check_this;
}

/**
 * @brief Sets up the server Socket with all the correct values
 *
 * @param None
 *
 * REF: https://jameshfisher.com/2017/04/05/set_socket_nonblocking/
 *
 * @return: Int value with the socket connection, or -1 on failue
*/
int set_up_server_socket(void)
{
    //Socket Varaibles
    int server_socket = 0;
    int flags = 0;
    int opt_val = 1;

    //Creating the TCP Socket to Connect to the Server
    server_socket = check_functionality_server(socket(AF_INET, SOCK_STREAM, 0),
        "In server_network.c Failed to set the Network Socket ", -1);

    //Set Server to Non-Blocking
    flags = check_functionality_server(fcntl(server_socket, F_GETFL, 0),
        "In server_network.c Failed to get the flags on Socket", -1);

    check_functionality_server(fcntl(server_socket, F_SETFL, flags | O_NONBLOCK),
        "In server_network.c Failed to set socket as Non-Blocking", -1);


    //Setting the Server Socket family to IPv4 and Setting specified Port for server to be 2000
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_NUM);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //Setting the Socket OPTs to the apporpriate setting to reuse the Network
    check_functionality_server(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)),
        "In server_network.c Failed to set socket opt", -1);

    //Bind the specified socket to the created Scoket Addr
    check_functionality_server(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)),
        "In server_network.c  Failed to Bind the Network", -1);

    //Beginning to Listen for Pythonic TCP Connections
    check_functionality_server(listen(server_socket, MAX_CLIENTS),
        "In server_network.c  Failed to Listen to Any Connections", -1);

    puts("Server Established");

    return server_socket;
}

/**
 * @brief Handles the connection of the TCP server. Processes the messages to send back.
 *
 * @param thread_client_socket contains the socket FD to be able to use the connections
 *
 * @return 1 if fail and 0 on sucess
*/
void * handle_connection(void * thread_client_socket)
{
    int client_socket = *((int*) thread_client_socket);

    printf("Thread {%ld} Running Connection", pthread_self());

    //Send Message to Client Stating the Connection has been established
    char * connected_message = "Connection Established! Welcome!";
    int message_size = strlen(connected_message);
    if(send(client_socket, connected_message, message_size, 0) < 0)
    {
        puts("In server_network.c Failed to Send Connection to Clients");
        close(client_socket);
        return (void *)1;
    }

    /***************** CHANGE CLIENT MESSAGE SIZE BASED ON PROJECT ****************/
    // Curently get_messages checks if the last value is a null byte
    size_t client_response_size = 65535;
    char client_response[65535] = {0};

    //Calls the get message Function to read in bit by bit
    if(get_message(client_socket, client_response, &client_response_size) == false)
    {
        puts("In server_network.c Failed to Recv the Entire Message from the Client");
        close(client_socket);
        return (void *)1;
    }

    printf("MESSAGE: %s \n", client_response);
    printf("SIZE: %ld \n", client_response_size);

    close(client_socket);

    return (void *)0;
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
    threadpool_t * server_threadpool;

    int server_socket = check_functionality_server(set_up_server_socket(),
        "In server_network.c Failed to Set Up Server", -1);

    server_threadpool = tpool_create(MAX_CLIENTS);

    if(NULL == server_threadpool)
    {
        perror("Failed to Create the Threadpool Goodbye!");
        exit(EXIT_FAILURE);
    }

    //Signal handler
    if(signal(SIGINT, signal_handler) ==  SIG_ERR)
    {
        puts("In server_network.c Signal handler did not work");
        close(server_socket);
        return -1;
    }
    puts("Listening for New Connections");

    //Keeps the Server Open to accept connections
    while(running)
    {
        char client_ip[INET_ADDRSTRLEN];

        //Accepts Connections that are incomming, Prints IP with valid connection
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);
        if(client_socket < 0)
        {
            //Checks if the socket is just  being blocked
            if(errno != EWOULDBLOCK)
            {
                puts("In server_network.c  Failed to Accept Connections from Clients");
                close(server_socket);
                return -1;
            }
            continue;
        }
        else
        {
            printf("Accepted {%s} Adding Work to Thread\n", inet_ntop(AF_INET, &client_addr.sin_addr.s_addr,
                client_ip, INET_ADDRSTRLEN));
            tpool_add_work(server_threadpool, &handle_connection, &client_socket);
        }
    }
    puts("Closing Connection");
    tpool_destroy(server_threadpool);
    close(server_socket);
    exit(EXIT_SUCCESS);
}