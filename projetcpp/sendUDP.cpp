#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

// Mise en place d'un client UDP qui envoie sur le port 9010

int main()
{
	// Cr�ation du socket
	SOCKET sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	fprintf(stderr, "socket() message: %s\n", strerror(errno));

	SOCKADDR_IN destAddrUdp;
	destAddrUdp.sin_addr.s_addr = inet_addr("192.168.65.44");
	destAddrUdp.sin_family = AF_INET;
	destAddrUdp.sin_port = htons(9012);
	// On d�clate le message que l'on veut envoy� au serveur, dans notre cas "bonjour"
	char buffer[8];
	buffer[0] = 'b';
	buffer[1] = 'o';
	buffer[2] = 'n';
	buffer[3] = 'j';
	buffer[4] = 'o';
	buffer[5] = 'u';
	buffer[6] = 'r';
	buffer[7] = '\0';
	socklen_t tailleudp = sizeof(destAddrUdp);
	int error_message;
	// Envoie du message au serveur
	error_message = sendto(sock, buffer, sizeof(buffer), 0,
		(SOCKADDR*)&destAddrUdp, sizeof(destAddrUdp));
	// Gestion d'erreur de la m�thode sendto
	if (error_message == 0) {
		fprintf(stderr, "sendto message erreur : %s\n", strerror(errno));
	}
	// Fermeture du socket
	close(sock);

}