#include "helpers.h"
#include "parson.h"
#include "requests.h"
#include <arpa/inet.h>
#include <netdb.h> /* struct hostent, gethostbyname */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <unistd.h> /* read, write, close */

int main(int argc, char* argv[])
{
    char* message;
    char* response;
    int sockfd;
    char command[100];
    char cookie_login[400] = { 0 };
    char jwt_token[400] = { 0 };

    while (1) {
        sockfd = open_connection("3.8.116.10", 8080, AF_INET, SOCK_STREAM, 0);

        printf("Command:\n");
        scanf("%s", command);
        if (!strcmp(command, "register")) {
            char username[20], password[20];
            printf("username=");
            scanf("%s", username);
            printf("password=");
            scanf("%s", password);

            JSON_Value* root_value = json_value_init_object();
            JSON_Object* root_object = json_value_get_object(root_value);
            json_object_set_string(root_object, "username", username);
            json_object_set_string(root_object, "password", password);
            char* data = json_serialize_to_string(root_value);

            message = compute_post_request("3.8.116.10", "/api/v1/tema/auth/register", data, jwt_token);
            send_to_server(sockfd, message);
            json_free_serialized_string(data);
            json_value_free(root_value);

            response = receive_from_server(sockfd);

            char* tmp = strstr(response, "error");
            if (tmp) {
                puts("Username already taken!");
            } else {
                puts("Registered succesfully!");
            }

            free(message);
            free(response);
        } else if (!strcmp(command, "login")) {
            char username[20], password[20];
            printf("username=");
            scanf("%s", username);
            printf("password=");
            scanf("%s", password);
            puts("");

            JSON_Value* root_value = json_value_init_object();
            JSON_Object* root_object = json_value_get_object(root_value);
            json_object_set_string(root_object, "username", username);
            json_object_set_string(root_object, "password", password);
            char* data = json_serialize_to_string(root_value);

            message = compute_post_request("3.8.116.10", "/api/v1/tema/auth/login", data, jwt_token);
            send_to_server(sockfd, message);
            json_free_serialized_string(data);
            json_value_free(root_value);

            response = receive_from_server(sockfd);
            puts("");
            puts(response);
            puts("");

            memset(cookie_login, 0, 200);
            char* tmp = strstr(response, "connect.sid");
            if (tmp) {
                char* tmp_end = strstr(tmp, ";");
                memcpy(cookie_login, tmp, tmp_end - tmp);
            }
            free(message);
            free(response);
        } else if (!strcmp(command, "enter_library")) {
            message = compute_get_request("3.8.116.10", "/api/v1/tema/library/access", cookie_login, jwt_token);
            send_to_server(sockfd, message);

            response = receive_from_server(sockfd);
            puts("");
            puts(response);
            puts("");

            memset(jwt_token, 0, 200);
            char* tmp = strstr(response, "token\":");
            if (tmp) {
                tmp = tmp + 8;
                char* tmp_end = strstr(tmp, "\"}");
                memcpy(jwt_token, tmp, tmp_end - tmp);
            }

            free(message);
            free(response);
        } else if (!strcmp(command, "add_book")) {
            char title[20], author[20], publisher[20], genre[20];
            int page_count;
            printf("title=");
            scanf("%s", title);
            printf("author=");
            scanf("%s", author);
            printf("genre=");
            scanf("%s", genre);
            printf("publisher=");
            scanf("%s", publisher);
            printf("page_count=");
            scanf("%d", &page_count);
            puts("");

            JSON_Value* root_value = json_value_init_object();
            JSON_Object* root_object = json_value_get_object(root_value);
            json_object_set_string(root_object, "title", title);
            json_object_set_string(root_object, "author", author);
            json_object_set_string(root_object, "genre", genre);
            json_object_set_number(root_object, "page_count", page_count);
            json_object_set_string(root_object, "publisher", publisher);
            char* data = json_serialize_to_string(root_value);

            message = compute_post_request("3.8.116.10", "/api/v1/tema/library/books", data, jwt_token);
            send_to_server(sockfd, message);
            json_free_serialized_string(data);
            json_value_free(root_value);

            response = receive_from_server(sockfd);
            puts("");
            puts(response);
            puts("");

            free(message);
            free(response);
        } else if (!strcmp(command, "get_books")) {
            message = compute_get_request("3.8.116.10", "/api/v1/tema/library/books", cookie_login, jwt_token);
            send_to_server(sockfd, message);

            response = receive_from_server(sockfd);
            puts("");
            puts(response);
            puts("");

            free(message);
            free(response);
        } else if (!strcmp(command, "get_book")) {
            char id[20], url[50] = "/api/v1/tema/library/books/";
            printf("id=");
            scanf("%s", id);
            strcat(url, id);

            message = compute_get_request("3.8.116.10", url, cookie_login, jwt_token);
            send_to_server(sockfd, message);

            response = receive_from_server(sockfd);
            puts("");
            puts(response);
            puts("");

            free(message);
            free(response);
        } else if (!strcmp(command, "delete_book")) {
            char id[20], url[50] = "/api/v1/tema/library/books/";
            printf("id=");
            scanf("%s", id);
            strcat(url, id);

            message = compute_delete_request("3.8.116.10", url, cookie_login, jwt_token);
            send_to_server(sockfd, message);

            response = receive_from_server(sockfd);
            puts("");
            puts(response);
            puts("");

            free(message);
            free(response);
        } else if (!strcmp(command, "logout")) {
            message = compute_get_request("3.8.116.10", "/api/v1/tema/auth/logout", cookie_login, jwt_token);
            send_to_server(sockfd, message);

            response = receive_from_server(sockfd);
            puts("");
            puts(response);
            puts("");

            free(message);
            free(response);
        } else if (!strcmp(command, "exit")) {
            close_connection(sockfd);
            break;
        } else {
            puts("Unknown command");
        }
        close_connection(sockfd);
    }
    return 0;
}
