# Basic Mechanism of Client-Server Setup
	The basic mechanisms of client-server setup are:
	•	A client app send a request to a server app.
	•	The server app returns a reply.
	•	Some of the basic data communications between client and server are:
		Echo - sends a message and gets it back.
		File transfer - sends name and gets a file.
		Web page - sends url and gets a page.
		
In this Project we are going tp focus on sending message from client and get it back from server

# Client Socket Setup
	•	create a socket.
	•	connect to a server.
	•	send/recv - repeat until we have or receive data
	•	shutdown to end read/write.
	•	close to releases data.
	
# Server Socket Setup
	•	create a socket - Get the file descriptor!
	•	bind to an address -What port am I on?
	•	listen on a port, and wait for a connection to be established.
	•	accept the connection from a client.
	•	send/recv - the same way we read and write for a file.
	•	shutdown to end read/write.
	•	close to releases data.

 # Execution Steps
	•	Build TCPMsgTransfer Solution in Visual Studio
	•	Open two Command Prompts
	•	In One Command Prompt, execute Server.exe present in Debug folder
	•	In another Command Prompt, execute Client.exe present in Debug folder
 
 # Reference
 For Detail Understanding refer **TCPMsgTransfer\Documents\SocketProgramming.docx**
