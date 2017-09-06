const char * usage =
"                                                               \n"
"IRCServer:                                                   \n"
"                                                               \n"
"Simple server program used to communicate multiple users       \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   IRCServer <port>                                          \n"
"                                                               \n"
"Where 1024 < port < 65536.                                     \n"
"                                                               \n"
"In another window type:                                        \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where talk-server      \n"
"is running. <port> is the port number you used when you run    \n"
"daytime-server.                                                \n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
//#include "LinkedList.h"
#include "IRCServer.h"
#include "LinkedList.c"

int QueueLength = 5;


int
IRCServer::open_server_socket(int port) {

	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress; 
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);
  
	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1; 
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
			     (char *) &optval, sizeof( int ) );
	
	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
			  (struct sockaddr *)&serverIPAddress,
			  sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}
	
	// Put socket in listening mode and set the 
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	return masterSocket;
}

void
IRCServer::runServer(int port)
{
	int masterSocket = open_server_socket(port);

	initialize();
	
	while ( 1 ) {
		
		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
					  (struct sockaddr *)&clientIPAddress,
					  (socklen_t*)&alen);
		
		if ( slaveSocket < 0 ) {
			perror( "accept" );
			exit( -1 );
		}
		
		// Process request.
		processRequest( slaveSocket );		
	}
}

int
main( int argc, char ** argv )
{
	// Print usage if not enough arguments
	if ( argc < 2 ) {
		fprintf( stderr, "%s", usage );
		exit( -1 );
	}
	
	// Get the port from the arguments
	int port = atoi( argv[1] );

	IRCServer ircServer;

	// It will never return
	ircServer.runServer(port);
	
}

//
// Commands:
//   Commands are started y the client.
//
//   Request: ADD-USER <USER> <PASSWD>\r\n
//   Answer: OK\r\n or DENIED\r\n
//
//   REQUEST: GET-ALL-USERS <USER> <PASSWD>\r\n
//   Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
//   REQUEST: CREATE-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LIST-ROOMS <USER> <PASSWD>\r\n
//   Answer: room1\r\n
//           room2\r\n
//           ...
//           \r\n
//
//   Request: ENTER-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LEAVE-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE> <ROOM>\n
//   Answer: OK\n or DENIED\n
//
//   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-NUM> <ROOM>\r\n
//   Answer: MSGNUM1 USER1 MESSAGE1\r\n
//           MSGNUM2 USER2 MESSAGE2\r\n
//           MSGNUM3 USER2 MESSAGE2\r\n
//           ...\r\n
//           \r\n
//
//    REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD> <ROOM>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//

void
IRCServer::processRequest( int fd )
{
	// Buffer used to store the comand received from the client
	const int MaxCommandLine = 1024;
	char commandLine[ MaxCommandLine + 1 ];
	int commandLineLength = 0;
	int n;
	
	// Currently character read
	unsigned char prevChar = 0;
	unsigned char newChar = 0;
	
	//
	// The client should send COMMAND-LINE\n
	// Read the name of the client character by character until a
	// \n is found.
	//

	// Read character by character until a \n is found or the command string is full.
	while ( commandLineLength < MaxCommandLine &&
		read( fd, &newChar, 1) > 0 ) {

		if (newChar == '\n' && prevChar == '\r') {
			break;
		}
		
		commandLine[ commandLineLength ] = newChar;
		commandLineLength++;

		prevChar = newChar;
	}
	
	// Add null character at the end of the string
	// Eliminate last \r
	commandLineLength--;
        commandLine[ commandLineLength ] = 0;

	printf("RECEIVED: %s\n", commandLine);

	char * command = (char *) malloc(100 * sizeof(char));
	char * user = (char *) malloc(100 * sizeof(char));
	char * password = (char *) malloc(100 * sizeof(char));
	char * args = (char *) malloc(100 * sizeof(char));
	char * message = (char *)malloc(150 * sizeof(char));

	int argc = 0;
	int i = 0;   //character in commandLine
	int j = 0;   //character in each array

	for (i = 0; i < 100; i++) {
		if (commandLine[i] == ' ' && argc != 4) {
			argc++;
			j = 0;
		}
		else if (argc == 0)   //command
			command[j++] = commandLine[i];
		else if (argc == 1)   //user name
			user[j++] = commandLine[i];
		else if (argc == 2)   //password
			password[j++] = commandLine[i];
		else if (argc == 3)   //argument
			args[j++] = commandLine[i];
		else if (argc == 4)
			message[j++] = commandLine[i];
		else
			break;
	}

	if (args[0] == '\0')
		args = strdup("NULL");
	if (message[0] == '\0')
		message = strdup("NULL");


	// printf("The commandLine has the following format:\n");
	// printf("COMMAND <user> <password> <arguments>. See below.\n");
	// printf("You need to separate the commandLine into those components\n");
	// printf("For now, command, user, and password are hardwired.\n");


	printf("command=%s\n", command);
	printf("user=%s\n", user);
	printf( "password=%s\n", password );
	printf("args=%s\n", args);

	if (!strcmp(command, "ADD-USER")) {
		addUser(fd, user, password, args);
	}
	else if (!strcmp(command, "CREATE-ROOM")) {
		createRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LIST-ROOMS")) {
		listRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "ENTER-ROOM")) {
		enterRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LEAVE-ROOM")) {
		leaveRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "SEND-MESSAGE")) {
		sendMessage(fd, user, password, args, message);
	}
	else if (!strcmp(command, "GET-MESSAGES")) {
		getMessages(fd, user, password, args, message);
	}
	else if (!strcmp(command, "GET-USERS-IN-ROOM")) {
		getUsersInRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-ALL-USERS")) {
		getAllUsers(fd, user, password, args);
	}
	else {
		const char * msg =  "UNKNOWN COMMAND\r\n";
		write(fd, msg, strlen(msg));
	}

	// Send OK answer
	//const char * msg =  "OK\n";
	//write(fd, msg, strlen(msg));

	close(fd);	
}

typedef struct MESSAGE
{
        const char * userName;
        const char * messageContent;
}
MESSAGE;

typedef struct ROOM
{
        const char * roomName;
        int userCount;
        int messageCount;
        LinkedList * usersInRoom;
        MESSAGE * messageList;
}
ROOM;


#define MAX_MESSAGE_COUNT 100
#define MAX_ROOM_COUNT 50   
#define ROOM_NAME_FILE "roomName.txt"

LinkedList * usersTotal= (LinkedList*) malloc((50*6) * sizeof(ListNode));

LinkedList * roomNameExisted = (LinkedList*) malloc(50 * sizeof(ListNode));

ROOM roomList[MAX_ROOM_COUNT];

int roomNumber = 0;

int messageNumber = 0;

void
IRCServer::initialize()
{
        FILE * fd = fopen(PASSWORD_FILE,"w+");
        FILE * file = fopen(ROOM_NAME_FILE,"w+");

        llist_init(usersTotal);
        llist_init(roomNameExisted);

        int a;
        int b;

        for (a = 0;(MAX_ROOM_COUNT) > a; a = (a + (10/10)))
        {
                roomList[a].roomName =(char*)malloc(100 * sizeof(char));
                roomList[a].userCount =0;
                roomList[a].messageCount= 0;

                roomList[a].usersInRoom=(LinkedList *)malloc((5*10) * sizeof(ListNode));
                roomList[a].messageList=(MESSAGE*)malloc(100 * sizeof(MESSAGE));

                for (b = 0; (MAX_MESSAGE_COUNT) > b; b = b+1)
                {
                        roomList[a].messageList[b].userName = (char *)malloc(50 * sizeof(char));
                        roomList[a].messageList[b].messageContent = (char *)malloc(250 * sizeof(char));
                }
        }

}

bool
IRCServer::checkPassword(int fd, const char * user, const char * password) {
        if(llist_exists_name(usersTotal,user)==0)
        {
        return false;
        }
        else if(strcmp(llist_password(usersTotal,user),password)==0)
        {
        return true;
        }
        else
                return false;;
}

void
IRCServer::addUser(int fd, const char * user, const char * password, const char * args)
{
        if (llist_exists_name(usersTotal,user)==0)
        {
                llist_add(usersTotal,user,password);
                llist_save(usersTotal,(char*)PASSWORD_FILE);

                const char * message;
                message ="OK\r\n";
                write(fd, message, strlen(message));
        }
        else {
                const char * message;
                message ="DENIED\r\n";

                write(fd,message,strlen(message));
        }

        return;
}
void
IRCServer::createRoom(int fd, const char * user, const char * password, const char * args)
{       
        if (checkPassword(fd,user,password))
        {       
                if (llist_exists_name(roomNameExisted,args)==0)
                {       
                        roomList[roomNumber].roomName=strdup(args);    
                        llist_add_room(roomNameExisted,roomList[roomNumber].roomName,roomNumber);
                        
                        llist_save(roomNameExisted,(char*)ROOM_NAME_FILE);
                        roomNumber =(roomNumber+1);
                        
                        const char * message;
                        message ="OK\r\n";
                        
                        write(fd, message, strlen(message));
                }
                else
                {       
                        const char * message;
                        message="DENIED\r\n";
                        
                        write(fd, message, strlen(message));
                }
        }
        else
        {       
                const char * message;
                message ="ERROR (Wrong password)\r\n";
                
                write(fd,message,strlen(message));
        }
        
        return;
}

void
IRCServer::listRoom(int fd, const char * user, const char * password, const char * args)
{
        if (checkPassword(fd, user, password))
        {
                if (roomNumber!= 0)
                {
                        llist_sort_room(roomNameExisted);
                        ListNode * a= roomNameExisted->head;

                        while (a != NULL)
                        {
                                write(fd, a->userName, strlen(a->userName));
                                write(fd,"\r\n",2);

                                a =(a->next);
                        }

                        write(fd,"\r\n",2);
                        close(fd);
                }
                else {
                        const char *message;
                        message ="No Room Existed\r\n";

                        write(fd,message,strlen(message));
                }
        }
        else {
                const char *message;
                message= "ERROR (Wrong password)\r\n";

                write(fd,message,strlen(message));
        }
}

void
IRCServer::enterRoom(int fd, const char * user, const char * password, const char * args)
{
        int room_number;

        if (checkPassword(fd,user,password))
        {
                if (llist_exists_name(roomNameExisted, args) == 0)
                {
                        const char * message;
                        message ="ERROR (No room)\r\n";

                        write(fd,message,strlen(message));
                }

                else
                {
                        room_number =llist_roomNumber(roomNameExisted,args);

                        if (50 > roomList[room_number].userCount)
                        {
                                if(llist_exists_name(roomList[room_number].usersInRoom,user)==0)
                                {
                                        roomList[room_number].userCount++;
                                        llist_add(roomList[room_number].usersInRoom, user, password);
                                }

                                const char * message;
                                message=  "OK\r\n";

                                write(fd, message, strlen(message));
                        }

                        else
                        {
                                const char * message;
                                message ="DENIED\r\n";

                                write(fd,message,strlen(message));
                        }
                }
        }
        else
        {
                const char * message;
                message= "ERROR (Wrong password)\r\n";

                write(fd,message,strlen(message));
        }
}

void
IRCServer::leaveRoom(int fd, const char * user, const char * password, const char * args)
{
        int a;
        int room_number;

        if (checkPassword(fd,user,password))
        {
                if(llist_exists_name(roomNameExisted,args)==0)
                {
                        const char *message;
                        message= "DENIED\r\n";

                        write(fd,message,strlen(message));

                }

                else

                {
                        room_number= llist_roomNumber(roomNameExisted,args);

                        if (llist_exists_name(roomList[room_number].usersInRoom,user)==1)
                        {
                                llist_remove(roomList[room_number].usersInRoom, user);
                                roomList[room_number].userCount = roomList[room_number].userCount - 1;

                                const char * message;
                                message=  "OK\r\n";

                                write(fd, message, strlen(message)); }

                        else
                        {
                                const char *message;
                                message = "ERROR (No user in room)\r\n";

                                write(fd,message,strlen(message));
                        }
                }
        }
        else {
                const char * message;
                message= "ERROR (Wrong password)\r\n";

                write(fd,message,strlen(message));
        }
}

void
IRCServer::sendMessage(int fd, const char * user, const char * password, const char * args, char * message)
{
        int room_number;

        strcat(message,"\r\n");

        if (checkPassword(fd,user,password))
        {
                room_number=llist_roomNumber(roomNameExisted,args);

                if (llist_exists_name(roomList[room_number].usersInRoom,user)==1)
                {
                        roomList[room_number].messageList[roomList[room_number].messageCount].userName= strdup(user);
                        roomList[room_number].messageList[roomList[room_number].messageCount].messageContent =strdup(message);

                        roomList[room_number].messageCount = (roomList[room_number].messageCount + 1);

                        if(roomList[room_number].messageCount== 100)
                        {       roomList[room_number].messageCount = 0; }

                        const char * message;
                        message= "OK\r\n";

                        write(fd, message,strlen(message));
                }

                else
                {
                        const char * message;
                        message ="ERROR (user not in room)\r\n";

                        write(fd,message,strlen(message));
                }
        }

        else
        {
                const char *message;
                message= "ERROR (Wrong password)\r\n";

                write(fd,message,strlen(message));
        }
}

void
IRCServer::getMessages(int fd, const char * user, const char * password, char * args, const char * roomName)
{
        int room_number;
        int message_number;
        message_number= atoi(args);

        if (checkPassword(fd,user,password))
        {
          if (llist_exists_name(roomNameExisted,roomName)==1)
           {
                room_number=llist_roomNumber(roomNameExisted,roomName);

            if (llist_exists_name(roomList[room_number].usersInRoom,user)== 1)
             {
                if ( roomList[room_number].messageCount > message_number)
                {
                                        int message;

                                        for (message = (message_number + 1);roomList[room_number].messageCount > message; message = (message + 1))
                                        {
                                                char num[10];
                                                snprintf(num, sizeof(num), "%i", message);

                                                if (10 > message)
                                                {       write(fd,num, 1); }

                                                else{
                                                        write(fd,num, 2);
                                                        }

                                                write(fd," ", 1);
                                                write(fd, roomList[room_number].messageList[message].userName,
                                                        strlen(roomList[room_number].messageList[message].userName));

                                                write(fd," ", 1);
                                                write(fd, roomList[room_number].messageList[message].messageContent,
                                                        strlen(roomList[room_number].messageList[message].messageContent));
                                        }
                                        write(fd,"\r\n", sizeof("\r\n"));
                                }
                                else
                                {
                                        const char * message;
                                        message = "NO-NEW-MESSAGES\r\n";

                                        write(fd,message,strlen(message));
                                }
                        }
 else

                        {
                                const char * message;
                                message = "ERROR (User not in room)\r\n";

                                write(fd, message, strlen(message));   }
                }
        }
        else
        {
                const char * message;
                message = "ERROR (Wrong password)\r\n";

                write(fd, message,strlen(message));
        }
}

void
IRCServer::getUsersInRoom(int fd, const char * user, const char * password, const char * args)
{
        int room_number;

        if (checkPassword(fd,user,password))
        {
                if (llist_exists_name(roomNameExisted,args)== 0)
                {
                        const char *message;
                        message= "DENIED\r\n";

                        write(fd, message, strlen(message));
                }

                else
                {
                        room_number= llist_roomNumber(roomNameExisted,args);

                        if (roomList[room_number].userCount != 0)
                        {
                                llist_sort(roomList[room_number].usersInRoom);

                                ListNode * x = roomList[room_number].usersInRoom->head;

                                while (x != NULL)
                                {
                                        write(fd, x->userName, strlen(x->userName));
                                        write(fd,"\r\n",2);

                                        x = x->next;
                                }
                        }
 write(fd,"\r\n",2);
                        close(fd);
                }
        }
        else {
                const char * message;
                message = "ERROR (Wrong password)\r\n";

                write(fd,message,strlen(message));
        }
}

void
IRCServer::getAllUsers(int fd, const char * user, const char * password,const  char * args)
{
        if (checkPassword(fd,user,password))
        {
                llist_sort(usersTotal);

                ListNode * a = usersTotal->head;

                while (a != NULL)
                {
                        write(fd, a->userName,strlen(a->userName));
                        write(fd,"\r\n",2);

                        a = a->next;
                }

                write(fd,"\r\n",2);
                close(fd);
        }

        else
        {
                const char *message;
                message = "ERROR (Wrong password)\r\n";

                write(fd,message,strlen(message));
        }
}

