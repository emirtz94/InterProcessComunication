There are two types of sockets: Unix Domain sockets (IPC between proccesses runing on the SAME SYSTEM ) & Network sockets (Comunication between processes runing on different physical machines over the network).
Socket programing steps:

*Remove the socket if allready exists
*Create unix socket using socket();
*Specify the socket name
*Bind the socket using bind();
*listen();
*accept();
*Read the data recvd on socket using recvfrom();
*Send back the result using sendto();
*close the data socket
*close the connection socket
*Remove the socket
*exit


