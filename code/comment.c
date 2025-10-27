#include "comment.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//creating comment node
Comment* createComment(char* username, char* content) {
    Comment* newComment = (Comment*)malloc(sizeof(Comment));
    if (newComment == NULL) {
        perror("Failed to allocate memory for comment");
        return NULL;
    }

    newComment->username = strdup(username);
    if (newComment->username == NULL) {
        perror("Failed to allocate memory for comment username");
        free(newComment);
        return NULL;
    }

    newComment->content = strdup(content);
    if (newComment->content == NULL) {
        perror("Failed to allocate memory for comment content");
        free(newComment->username);
        free(newComment);
        return NULL;
    }

    newComment->replies = NULL;
    newComment->next = NULL;
    return newComment;
}
//freeing the comment node
void freeComment(Comment* comment) {
    if (comment == NULL) {
        return;
    }

    free(comment->username);
    free(comment->content);
    Reply* currentReply = comment->replies;
    while (currentReply) {
        Reply* nextReply = currentReply->next;
        freeReply(currentReply);
        currentReply = nextReply;
    }

    free(comment);
}