import socket 

PORT = 50505 #must use above 1024 
HEADER = 64 #fixed first message must be. May need to revisit this for longer messages. 
#grab the ip address from server.
SERVER = "192.168.1.23"
#to bind socket, address needs to be tuple
FORMAT = 'utf-8'
#message to start disconnection
DISCONNECT_MESSAGE = "!DISCONNECT"
ADDR = (SERVER, PORT)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(ADDR)

def send(msg):
    message = msg.encode(FORMAT)
    msg_length = len(message)
    send_length= str(msg_length).encode(FORMAT)
    send_length += b' '*(HEADER-len(send_length))
    client.send(send_length)
    client.send(message)
    print(client.recv(2048).decode(FORMAT))

send("Hello World")
input()
send("I see you")
input()
send(DISCONNECT_MESSAGE)