#include "../INCLUDE/server_network.h"

void signal_handler(int sig)
{
    if(sig == SIGINT)
    {
        running = 0;
    }
}

/*
static int get_message(int fd, char *buffer, size_t *buffer_size)
{
    char * message = buffer;
    size_t count = 0;
    while(count < *buffer_size && recv(fd, message, 1, 0) == 1)
    {
        count++;
        if ('\0' == *message)
        {
            *buffer_size = count;
            return 0;
        }
        message++;
    }
    
    printf("MESSAGE: %s \n", buffer);
    printf("SIZE: %ln \n", buffer_size);

    return -1;
}
*/

static int get_message(int fd, char * message_recv, size_t *message_size)
{
    int total_bytes_recv = 0;
    int bytes_recv = 0;
    int message_packet_size = 512;

    //Change to timeout after 10 secconds
    while(1)
    {
        bytes_recv = recv(fd, message_recv, 512, 0);
        if(bytes_recv < 0)
        {
            break;
        }
        else
        {
            total_bytes_recv += bytes_recv;
            printf("%s \n", message_recv);
        }
    }

    return total_bytes_recv;
}


static int send_message(int fd, char * message_to_send, size_t *message_size)
{
    int total_bytes = 0;
    int bytes_left = *message_size;
    int bytes_sent = 0;

    while(total_bytes < *message_size)
    {
        bytes_sent = send(fd, message_to_send + total_bytes, bytes_left, 0);

        if(bytes_sent == -1)
        {
            break;
        }

        total_bytes += bytes_sent;
        bytes_left -= bytes_sent;
    }

    *message_size = total_bytes;

    if(bytes_sent == -1)
    {
        return -1;
    }

    return 0;
}

int check_functionality_server(int check_this, char * error_msg, int value)
{
    if(check_this == value)
    {
        perror(error_msg);
        return SERVER_FAILED;
    }
    return check_this;
}

int set_up_server_socket(void)
{
    //Socket Varaibles
    int server_socket = 0;
    int flags = 0;
    int opt_val = 1;

    int return_check = 0;

    //Creating the TCP Socket to Connect to the Server
    server_socket = check_functionality_server(socket(AF_INET, SOCK_STREAM, 0),
        "In server_network.c Failed to set the Network Socket ", SERVER_FAILED);

    //Set Server to Non-Blocking
    flags = check_functionality_server(fcntl(server_socket, F_GETFL, 0),
        "In server_network.c Failed to get the flags on Socket", SERVER_FAILED);
    
    //Sets Up Non Blocking
    check_functionality_server(fcntl(server_socket, F_SETFL, flags | O_NONBLOCK),
        "In server_network.c Failed to set socket as Non-Blocking", SERVER_FAILED);

    //Setting the Server Socket family to IPv4 and Setting specified Port for server to be 2000
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_NUM);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //Setting the Socket OPTs to the apporpriate setting to reuse the Network
    return_check = check_functionality_server(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)),
        "In server_network.c Failed to set socket opt", SERVER_FAILED);
    
    if(SERVER_FAILED == return_check)
    {
        return SERVER_FAILED;
    }

    //Bind the specified socket to the created Scoket Addr
    return_check = check_functionality_server(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)),
        "In server_network.c Failed to Bind the Network", SERVER_FAILED);

    if(SERVER_FAILED == return_check)
    {
        return SERVER_FAILED;
    }

    //Beginning to Listen for Pythonic TCP Connections
    return_check = check_functionality_server(listen(server_socket, MAX_CLIENTS),
        "In server_network.c  Failed to Listen to Any Connections", SERVER_FAILED);
    
    if(SERVER_FAILED == return_check)
    {
        return SERVER_FAILED;
    }


    puts("Server Established");

    return server_socket;
}

void handle_connection(void * args)
{
    connection * thread_connection = (connection *)args;
    struct sockaddr_in client_address = thread_connection->client_address;
    int client_socket = thread_connection->client_socket;
    char client_ip[INET_ADDRSTRLEN];

    printf("Thread {%ld} Running Connection \n", pthread_self());
    printf("Accepted {%s} Adding Work to Thread\n", inet_ntop(AF_INET, &client_address.sin_addr.s_addr,
                client_ip, INET_ADDRSTRLEN));
    printf("SOCK: %d \n", client_socket);

    //Send Message to Client Stating the Connection has been established
    char * connected_message = "Connection Established! Welcome!";
    size_t message_size = strlen(connected_message);
    if(-1 == send_message(client_socket, connected_message, &message_size))
    {
        printf("In server_network.c Failed Send entire message to Client, Sent %ld \n" ,
            message_size);
        close(client_socket);
    }

    /***************** CHANGE CLIENT MESSAGE SIZE BASED ON PROJECT ****************/
    // Curently get_messages checks if the last value is a null byte
    size_t client_response_size = 65535;
    char client_response[65535] = {0};

    /*Calls the get message Function to read in bit by bit
    if(-1 == get_message(client_socket, client_response, &client_response_size))
    {
        puts("In server_network.c Failed to Recv the Entire Message from the Client");
        close(client_socket);
    }
    */

    recv(client_socket, client_response, client_response_size, 0);
    
    printf("Messaged Size from Client %ld \n", client_response_size);
    printf("Messaged Recieved from Client %s \n", client_response);

    close(client_socket);
}


int main()
{
    int client_connection = 0;
    //int * acceped_connection = NULL;
    connection accepted_connection = {0};

    struct sockaddr_in client_addr = {0};
    socklen_t client_len = 0;
    threadpool_t * server_threadpool;

    int server_socket = check_functionality_server(set_up_server_socket(),
        "In server_network.c Failed to Set Up Server", SERVER_FAILED);
    
    if(SERVER_FAILED == server_socket)
    {
        perror("Failed to Set up Server");
        exit(EXIT_FAILURE);
    }
    

    server_threadpool = tpool_create(MAX_CLIENTS);

    if(NULL == server_threadpool)
    {
        perror("Failed to Create the Threadpool Goodbye!");
        exit(EXIT_FAILURE);
    }

    //Signal handler
    if(SIG_ERR == signal(SIGINT, signal_handler))
    {
        puts("In server_network.c Signal handler did not work");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    puts("Listening for Connections");

    //Keeps the Server Open to accept connections
    while(running)
    {
        //Accepts Connections that are incomming, Prints IP with valid connection
        char client_ip[INET_ADDRSTRLEN];
        
        client_connection = accept(server_socket, (struct sockaddr *) &client_addr, &client_len);
        if(-1 == client_connection)
        {
            //Checks if the socket is just being blocked
            if(errno != EWOULDBLOCK || errno != EAGAIN)
            {
                puts("In server_network.c  Failed to Accept Connections from Clients");
                close(client_connection);
            }
            continue;
        }
        else
        {
            //acceped_connection = malloc(sizeof(int *));
            printf("Accepted {%s} Adding Work to Thread\n", inet_ntop(AF_INET, &client_addr.sin_addr.s_addr,
                client_ip, INET_ADDRSTRLEN));
            printf("SOCK: %d \n", client_connection);

            //acceped_connection = &client_connection;
            accepted_connection.client_socket = client_connection;
            accepted_connection.client_address = client_addr;

            if(false == tpool_add_work(server_threadpool, handle_connection, (void *) &accepted_connection))
            {
                puts("In server_network.c  Failed to Add work to threadpool");
                close(client_connection);
            }
        }
    }

    puts("Closing Connection");
    tpool_destroy(server_threadpool);
    close(client_connection);
    close(server_socket);
    exit(EXIT_SUCCESS);
}