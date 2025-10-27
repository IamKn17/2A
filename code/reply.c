#include "reply.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//creation of reply node
Reply* createReply(char* username, char* content) {
    //allocation of memory
    Reply* newReply = (Reply*)malloc(sizeof(Reply));
    //if not allocated or no enough memory
    if (newReply == NULL) {
        perror("Failed to allocate memory for reply");
        return NULL;
    }
    //creating copy of username and content and checking for memory allocation
    newReply->username = strdup(username);
    if (newReply->username == NULL) {
        perror("Failed to allocate memory for reply username");
        free(newReply);
        return NULL;
    }

    newReply->content = strdup(content);
    if (newReply->content == NULL) {
        perror("Failed to allocate memory for reply content");
        free(newReply->username);
        free(newReply);
        return NULL;
    }

    newReply->next = NULL;
    return newReply;
}
//freeing the reply node
void freeReply(Reply* reply) {
    if (reply == NULL) {
        return;
    }
    free(reply->username);
    free(reply->content);
    free(reply);
}