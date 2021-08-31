import socket
import argparse

def client_network_connection(ip_address, port):

    address = (ip_address, port)

    # Sets up the TCP Socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:

        #Connects the socket with the adderss
        client_socket.connect(address)

        #Receives Information from the Client
        server_response = client_socket.recv(1024)
        print(server_response.decode())

        server_connected_messgage = "Thank you!\0"

        client_socket.send(server_connected_messgage.encode())

def main():
    #Proppts User to Enter the Public IP of the Server
    #Ask user for the specified port to enter the server

    #Is their a way to improve the the argparse?
    connection_info_parse = argparse.ArgumentParser()
    connection_info_parse.add_argument("ip", type=str,
        help="IP Address of the Server to Connect")
    connection_info_parse.add_argument("port", type=int,
        help="Port to connect to")

    arguments = connection_info_parse.parse_args()

    client_network_connection(arguments.ip, arguments.port)

if __name__ == "__main__":
    main()
