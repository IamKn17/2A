#ifndef POST_H
#define POST_H

#include "comment.h"
//A DOUBLE LINKED LIST FOR ACCESSING PREVIOUS AND NEXT POSTS EASILY
typedef struct Post {
    char* username;
    char* caption;
    Comment* comments;
    struct Post* next;
    struct Post* prev;
} Post;

Post* createPost(char* username, char* caption);

void freePost(Post* post);
#endif

