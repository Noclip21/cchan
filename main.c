#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main()
{
    /* Some variables */
    char error404[256] =
        "HTTP/1.1 404\r\n"
        "Connection: close\r\n\r\n"
        "<html><head><title>404 not found</title></head>"
        "<body><h1>404 not found</h1></body></html>\r\n\r\n";
    /* Reading buffer */
    char buf[2000] = {0};
    /* Create our socket */
    printf("Creating socket.\n");
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Error creating socket\n");
        return EXIT_FAILURE;
    }
    printf("Socket created.\nBinding socket.\n");
    /* Prepare sockaddr_in structure */
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(42069);
    /* Bind our socket */
    if (bind(socket_desc, (struct sockaddr *)& server, sizeof (server)) < 0) {
        printf("Couldn't bind socket\n");
        return EXIT_FAILURE;
    }
    printf("Done binding socket.\n");
    /* Start listening to socket */
    listen(socket_desc, 3);

    /* Accept connections */
    struct sockaddr_in client;
    int client_socket;
    int c = sizeof (struct sockaddr_in);
    client_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c);
    if (client_socket < 0) {
        printf("Failed to accept connection.\n");
        return EXIT_FAILURE;
    }
    /* Connection has been accepted */
    printf("Client connected\n");
    /* Read data from client */
    int rc;
    while ( (rc = read(client_socket, buf, 2000)) > 0) {
        printf("Got data...\n");
        printf("%s", buf);
        /* Write HTTP response */
        write(client_socket, error404, strlen(error404));
        printf("Response sent.\n");
        close(client_socket);
        close(socket_desc);
        return EXIT_SUCCESS;
    }
    if (rc == 0) {
        printf("Client closed connection\n");
        close(client_socket);
    } else if (rc == -1) {
        printf("Error reading data...\n");
        return EXIT_FAILURE;
    }
    close(socket_desc);
    return EXIT_SUCCESS;
}

