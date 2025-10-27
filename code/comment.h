#ifndef COMMENT_H
#define COMMENT_H

#include "reply.h"
//SINGLE LINKED LIST WHICH CONTAINS REPLIES AS ANOTHER SINGLE LINKED LIST
typedef struct Comment {
    char* username;
    char* content;
    Reply* replies;
    struct Comment* next;
} Comment;

Comment* createComment(char* username, char* content);

void freeComment(Comment* comment);
#endif

