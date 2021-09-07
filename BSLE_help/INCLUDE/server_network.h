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
#include <poll.h>

#include "../INCLUDE/threadpool.h"

#define PORT_NUM 2000
#define MAX_CLIENTS 20
#define SERVER_FAILED -1
#define CHUNK_SIZE 1024
#define RECV_TIMEOUT 10000

static volatile int running = 1;

typedef struct _connection
{
    int client_socket;
    struct sockaddr_in client_address;
}connection;

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
void signal_handler(int sig);

/**
 * @brief Recieve Messages from the client and ensure the entire message is recieved
 *
 * @param socket is the accepted socket
 * @param messsage_size is the size of the expected message
 *
 * REF: https://www.binarytides.com/receive-full-data-with-recv-socket-function-in-c/
 * REF: https://stackoverflow.com/questions/2876024/linux-is-there-a-read-or-recv-from-socket-with-timeout
 * 
 * @return: 0 is a Sucessful connections, -1 is Failed connection
*/
char * get_message(int socket, int message_size);

/**
 * @brief Sends the entiriy of the buffer to the socket. 
 * Tracks the number of bytes sent to ensure the entire message was sent.
 * 
 * @param fd socket to send the message to
 * @param message_to_send message the server wants to send
 * @param message_size size of the message that the server wants to send 
 * @return 0 on sucess
 * @return -1 on failue
 */
static int send_message(int fd, char * message_to_send, size_t *message_size);

/**
 * @brief Checks teh function sent and exits if something fails.
 * This provides clarity with the code and being able to test functions that return errors.
 * 
 * @param check_this the function or value to complete due to critical operations
 * @param error_msg message to display before returning value
 * @param value is the value to test for
 *
 *
 * @return: function return operation on sucess, -1 on failue
*/
int check_functionality_server(int check_this, char * error_msg, int value);

/**
 * @brief Sets up the server Socket with all the correct values
 *
 * @param None
 *
 * REF: https://jameshfisher.com/2017/04/05/set_socket_nonblocking/
 *
 * @return: Int value with the socket connection, or -1 on failue
*/
int set_up_server_socket(void);

/**
 * @brief Handles the connection of the TCP server. Processes the messages to send back.
 *
 * @param thread_client_socket contains the socket FD to be able to use the connections
 *
 * @return 1 if fail and 0 on sucess
*/
void handle_connection(void * thread_client_socket);

/**
 * @brief Sets up the entire TCP Socket Connections. Allows Clients to connect to the server
 * @return: 0 is a Sucessful connections, 1 is Failed connection
*/
int main();