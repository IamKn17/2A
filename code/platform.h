#ifndef PLATFORM_H
#define PLATFORM_H

#include "post.h"
#include <stdbool.h>
//instead of using stack for view history I am using linked list to store the view history of posts instead of lastViewedPost
typedef struct History {
    Post* post;
    struct History* next;
} History;

typedef struct Platform {
    Post* posts;
    History* lastViewedPost;
} Platform;

extern Platform* platform;

Platform* createPlatform();

bool addPost(char* username, char* caption);

bool deletePost(int n);

Post* viewPost(int n);

Post* currPost();

Post* nextPost();

Post* previousPost();

bool addComment(char* username, char* content);

bool deleteComment(int n);

Comment* viewComments();

bool addReply(char* username, char* content, int n);

bool deleteReply(int n, int m);

void freePlatform(Platform* platform);
#endif

