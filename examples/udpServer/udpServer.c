// Server side implementation of UDP client-server model
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <klee/klee.h>

#define PORT 55555
#define MAXLINE 1024



// len = sizeof(cliaddr); // len is value/resuslt

int evalBuffer(char *buffer, int sockfd, struct sockaddr_in servaddr, struct sockaddr_in cliaddr)
{
    char *replyA;
    char *replyB;
    char *replyC;
    int len, n;
    len = sizeof(cliaddr);
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) <
        0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                 (struct sockaddr *)&cliaddr, &len);

    if (strcmp(buffer, "x") == 0)
    {
        sendto(sockfd, (const char *)replyA, 1, MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        printf("executed replyA\n");
        return 1;
    }
    if (strcmp(buffer, "y") == 0)
    {
        sendto(sockfd, (const char *)replyB, 1, MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        printf("execcuted replyB\n");
        return -1;
    }
    if (strcmp(buffer, "z") == 0)
    {
        sendto(sockfd, (const char *)replyC, 1, MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        printf("executed replyC\n");
        return 0;
    }

    buffer[n] = '\0';
    printf("Client : %s\n", buffer);

    printf("Hello message sent.\n");
    return 0;
}

// Driver code
int main()
{
    char buffer[MAXLINE];
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    klee_make_symbolic(&buffer, sizeof(buffer), "buffer");
    klee_make_symbolic(&sockfd, sizeof(sockfd), "sockfd");
    evalBuffer(*buffer, sockfd, servaddr, cliaddr);

    return 0;
}
