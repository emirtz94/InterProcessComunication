There are two types of sockets: Unix Domain sockets (IPC between proccesses runing on the SAME SYSTEM ) & Network sockets (Comunication between processes runing on different physical machines over the network).
Socket programing steps:

* Remove the socket if allready exists
* Create unix socket using socket();
* Specify the socket name
* Bind the socket using bind();
* listen();
* accept();
* Read the data recvd on socket using recvfrom();
* Send back the result using sendto();
* close the data socket
* close the connection socket
* Remove the socket
* exit

# SOCKET MESSAGE TYPES

* Messages(or requests) exchanged between the client and the server process can be categorized in two types:
  * Connection initialization request messages(CIR)
    * This message is used by the client process to request the server process to establish a dedicated conection
    * Only after the connection has been established, then only client can send Service request message to the server
  * Service request messages(SRM)
    * Client can sent these messages to the server once the connection is fully established
    * Through these messages, Client requests server to provide a service
* Server identifies and process both the type of messages very differently
