import socket
import threading 

#sending an object back to server, need pickle?
#https://www.youtube.com/watch?v=3QiPPX-KeSc explanation of code
PORT = 5050 #must use above 1024 
HEADER = 64 #fixed first message must be. May need to revisit this for longer messages. 
#grabs your own computer's ip address
SERVER = socket.gethostbyname(socket.gethostname())
#to bind socket, address needs to be tuple
ADDR = (SERVER, PORT)
FORMAT = 'utf-8'
#message to start disconnection
DISCONNECT_MESSAGE = "!DISCONNECT"

#type of ip address we want to look at and streaming data. 
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind(ADDR)

def handle_client(conn, addr):
    print("{New connection! ", addr, " connected.")
    connected = True 
    while connected: 
        #number of bytes to recieve? header.
        msg_length = conn.recv(HEADER).decode(FORMAT) #always need to decode a message 
        if msg_length:
            msg_length = int(msg_length)
            msg = conn.recv(msg_length).decode(FORMAT)
            if msg == DISCONNECT_MESSAGE: 
                connected = False
            print(addr,": ", msg) #show the message.
            conn.send("Msg recieved".encode(FORMAT))

    conn.close() 


def start():
    server.listen()
    print("[Listening] Server is listening on ", SERVER)
    while True:
        #waiting for connection and then store info in an object
        conn, addr = server.accept()
        #pass connection to handle client by creating a new thread. 
        thread = threading.Thread(target = handle_client, args = (conn, addr))
        thread.start()
        print("[Active connections] ", threading.active_count()-1)

print("Server is starting...")
start()
