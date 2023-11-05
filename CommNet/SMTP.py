from socket import *

msg = "\r\n I love computer communication networks!"

endmsg = "\r\n.\r\n"

# Choose a mail server (e.g. Google mail server) and call it mailserver
mailserver = "localhost"

# Create socket called clientSocket and establish a TCP connection with mailserver
#Fill in start
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((mailserver, 25))

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '220':
    print('220 reply not received from server.')
#Fill in end

# Send HELO command and print server response.
heloCommand = 'HELO Alice\r\n'
clientSocket.send(heloCommand.encode())
recv1 = clientSocket.recv(1024).decode()
print(recv1)
if recv1[:3] != '250':
    print('250 reply not received from server.')

# Send MAIL FROM command and print server response.
# Fill in start
mailFrom = "MAIL FROM: <random_email@gmail.com>\r\n"
clientSocket.send(mailFrom.encode())
recvMF = clientSocket.recv(1024).decode()
print(recvMF)
if recvMF[:3] != '250':
    print('250 reply not received from server')
# Fill in end

# Send RCPT TO command and print server response.
# Fill in start
rcptTo = "RCPT TO: <sopatz@kent.edu>\r\n"
clientSocket.send(rcptTo.encode())
recvRT = clientSocket.recv(1024).decode()
print(recvRT)
if recvRT[:3] != '250':
    print('250 reply not received from server')
# Fill in end

# Send DATA command and print server response.
# Fill in start
data = "DATA\r\n"
clientSocket.send(data.encode())
recvData = clientSocket.recv(1024).decode()
print(recvData)
if recvData[:3] != '354':
    print('354 reply not received from server')
# Fill in end

# Send message data.
# Fill in start
subject = "SUBJECT: Testing SMTP\r\n"
clientSocket.send(subject.encode())
clientSocket.send(msg.encode())
# Fill in end

# Message ends with a single period.
# Fill in start
clientSocket.send(endmsg.encode())
recvMessage = clientSocket.recv(1024).decode()
print(recvMessage)
if recvMessage[:3] != '250':
    print('250 reply not received from server')
# Fill in end

# Send QUIT command and get server response.
# Fill in start
quit = "QUIT\r\n"
clientSocket.send(quit.encode())
recvQuit = clientSocket.recv(1024).decode()
print(recvQuit)
if recvQuit[:3] != '221':
    print('221 reply not received from server')
# Fill in end
