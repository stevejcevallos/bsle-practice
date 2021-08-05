import socket

def client_network_connection(ip_address, port):

    address = (ip_address, port)

    # Sets up the TCP Socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:

        #Connects the socket with the adderss
        client_socket.connect(address)

        #Receives Information from the Client
        server_response = client_socket.recv(1024)
        print(server_response.decode())

        #server_connected_messgage = "Thank you! Looking Forward to more communications"

        #client_socket.send(server_connected_messgage.encode())

def main():
    #Proppts User to Enter the Public IP of the Server
    #Ask user for the specified port to enter the server
    ip = input("IP: ")
    port = input("PORT: ")
    client_network_connection(ip, int(port))

if __name__ == "__main__":
    main()
