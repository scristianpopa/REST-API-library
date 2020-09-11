#ifndef _REQUESTS_
#define _REQUESTS_

char* compute_get_request(char* host, char* url, char* cookies, char* jwt_token);

char* compute_post_request(char* host, char* url, char* body_data, char* jwt_token);

char* compute_delete_request(char* host, char* url, char* cookies, char* jwt_token);
#endif
