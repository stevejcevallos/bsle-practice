import socket
import argparse
import struct

def client_network_connection(ip_address, port):

    address = (ip_address, port)

    # Sets up the TCP Socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:

        #Connects the socket with the adderss
        client_socket.connect(address)

        #Receives Information from the Client
        server_response = client_socket.recv(1024)
        print(server_response.decode())

        #Add Functions to Deserialize and Process the Message for the Client
        client_message = input("\t Enter a Message: ")
        client_message_bytes = client_message.encode("utf-8")

        client_message_length = len(client_message_bytes)
        client_message_length_bytes = struct.pack("H", client_message_length)

        print(client_message_length_bytes)
        print(client_message_bytes)

        client_response = b"".join([client_message_length_bytes, client_message_bytes])
        
        print(client_response)

        client_socket.send(client_response)

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
