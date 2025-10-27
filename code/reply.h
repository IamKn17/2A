#ifndef REPLY_H
#define REPLY_H
//A SINGLE LINKED LIST FOR REPLIES
typedef struct Reply {
    char* username;
    char* content;
    struct Reply* next;
} Reply;

Reply* createReply(char* username, char* content);

void freeReply(Reply* reply);
#endif
