#include "requests.h"
#include "helpers.h"
#include <arpa/inet.h>
#include <netdb.h> /* struct hostent, gethostbyname */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h>
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <unistd.h> /* read, write, close */

char* compute_get_request(char* host, char* url, char* cookies, char* jwt_token)
{
    char* message = calloc(BUFLEN, sizeof(char));
    char* line = calloc(LINELEN, sizeof(char));

    memset(line, 0, LINELEN);
    sprintf(line, "GET %s HTTP/1.1", url);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (strlen(jwt_token)) {
        memset(line, 0, LINELEN);
        sprintf(line, "Authorization: Bearer %s", jwt_token);
        compute_message(message, line);
    }

    if (strlen(cookies)) {
        memset(line, 0, LINELEN);
        sprintf(line, "Cookie: %s;", cookies);
        compute_message(message, line);
    }

    compute_message(message, "");
    return message;
}

char* compute_delete_request(char* host, char* url, char* cookies, char* jwt_token)
{
    char* message = calloc(BUFLEN, sizeof(char));
    char* line = calloc(LINELEN, sizeof(char));

    memset(line, 0, LINELEN);
    sprintf(line, "DELETE %s HTTP/1.1", url);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (strlen(jwt_token)) {
        memset(line, 0, LINELEN);
        sprintf(line, "Authorization: Bearer %s", jwt_token);
        compute_message(message, line);
    }

    if (strlen(cookies)) {
        memset(line, 0, LINELEN);
        sprintf(line, "Cookie: %s;", cookies);
        compute_message(message, line);
    }
    compute_message(message, "");
    return message;
}

char* compute_post_request(char* host, char* url, char* body_data, char* jwt_token)
{
    char* message = calloc(BUFLEN, sizeof(char));
    char* line = calloc(LINELEN, sizeof(char));

    memset(line, 0, LINELEN);
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    if (strlen(jwt_token)) {
        memset(line, 0, LINELEN);
        sprintf(line, "Authorization: Bearer %s", jwt_token);
        compute_message(message, line);
    }

    memset(line, 0, LINELEN);
    sprintf(line, "Content-Type: application/json");
    compute_message(message, line);

    memset(line, 0, LINELEN);
    sprintf(line, "Content-Length: %ld", strlen(body_data));
    compute_message(message, line);

    compute_message(message, "");

    if (body_data != NULL) {
        compute_message(message, body_data);
    }

    free(line);
    return message;
}
