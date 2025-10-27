#include "post.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//creation of post node
Post* createPost(char* username, char* caption) {
    Post* newPost = (Post*)malloc(sizeof(Post));
    if (newPost == NULL) {
        perror("Failed to allocate memory for post");
        return NULL;
    }

    newPost->username = strdup(username);
    if (newPost->username == NULL) {
        perror("Failed to allocate memory for post username");
        free(newPost);
        return NULL;
    }

    newPost->caption = strdup(caption);
    if (newPost->caption == NULL) {
        perror("Failed to allocate memory for post caption");
        free(newPost->username);
        free(newPost);
        return NULL;
    }

    newPost->comments = NULL;
    newPost->next = NULL;
    newPost->prev = NULL;
    return newPost;
}
//freeing the post node
void freePost(Post* post) {
    if (post == NULL) {
        return;
    }

    free(post->username);
    free(post->caption);
    Comment* currentComment = post->comments;
    while (currentComment) {
        Comment* nextComment = currentComment->next;
        freeComment(currentComment);
        currentComment = nextComment;
    }

    free(post);
}