#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Platform* platform = NULL;
//Freeing all replies in the reply linked list
void freeReplies(Reply* head) {
    Reply* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->username);
        free(tmp->content);
        free(tmp);
    }
}
//Freeing all comments in the comment linked list
void freeComments(Comment* head) {
    Comment* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        freeReplies(tmp->replies);
        free(tmp->username);
        free(tmp->content);
        free(tmp);
    }
}
//Freeing the view history linked list
void freeHistory(History* head) {
    History* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
//Function to add post to view history when post is created or viewed
void add_to_view_history(Post* post) {
    if (platform == NULL || post == NULL) {
        return;
    }

    if (platform->lastViewedPost != NULL && platform->lastViewedPost->post == post) {
        return;
    }

    History* prev = platform->lastViewedPost;
    History* curr = (platform->lastViewedPost != NULL) ? platform->lastViewedPost->next : NULL;

    while (curr != NULL) {
        if (curr->post == post) {
            prev->next = curr->next;

            curr->next = platform->lastViewedPost;
            platform->lastViewedPost = curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    History* newNode = (History*)malloc(sizeof(History));
    if (newNode == NULL) {
        perror("Failed to create view history node");
        return;
    }
    
    newNode->post = post;
    newNode->next = platform->lastViewedPost;
    platform->lastViewedPost = newNode;
}

//Creation of platform
Platform* createPlatform() {
    if (platform != NULL) {
        return platform;
    }

    platform = (Platform*)malloc(sizeof(Platform));
    if (platform == NULL) {
        perror("Failed to create platform");
        return NULL;
    }

    platform->posts = NULL;
    platform->lastViewedPost = NULL;
    return platform;
}

bool addPost(char* username, char* caption) {
    Post* newPost = createPost(username, caption);
    if (newPost == NULL) {
        return false;
    }

    if (platform->posts == NULL) {
        platform->posts = newPost;
    } else {
        newPost->next = platform->posts;
        platform->posts->prev = newPost;
        platform->posts = newPost;
    }
       

    return true;
}

bool deletePost(int n) {
    if (n < 1 || platform->posts == NULL) {
        return false;
    }

    Post* target = platform->posts;
    for (int i = 1; i < n && target != NULL; i++) {
        target = target->next;
    }

    if (target == NULL) {
        return false;
    }

    History* curr = platform->lastViewedPost;
    History* prev = NULL;
    while (curr != NULL) {
        if (curr->post == target) {
            History* to_delete = curr;
            if (prev == NULL) {
                platform->lastViewedPost = curr->next;
                curr = platform->lastViewedPost;
            } else {
                prev->next = curr->next;
                curr = curr->next;
            }
            free(to_delete);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (target->prev != NULL) {
        target->prev->next = target->next;
    } else {
        platform->posts = target->next;
    }

    if (target->next != NULL) {
        target->next->prev = target->prev;
    }

    if (platform->lastViewedPost == NULL && platform->posts != NULL) {
        add_to_view_history(platform->posts);
    }

    freeComments(target->comments);
    free(target->username);
    free(target->caption);
    free(target);

    return true;
}

Post* viewPost(int n) {
    if (n < 1 || platform->posts == NULL) {
        return NULL;
    }

    Post* target = platform->posts;
    for (int i = 1; i < n && target != NULL; i++) {
        target = target->next;
    }

    if (target != NULL) {
        add_to_view_history(target);
    }

    return target;
}

Post* currPost() {
    if (platform->lastViewedPost == NULL) {
        if (platform->posts != NULL) {
            add_to_view_history(platform->posts);
        } else {
            return NULL;
        }
    }

    return platform->lastViewedPost->post;
}

Post* nextPost() {
    Post* current = currPost();
    if (current == NULL) {
        return NULL;
    }

    Post* next = current->next;
    
    if (next != NULL) {
        add_to_view_history(next);
        return next;
    }
    
    add_to_view_history(current);
    return current;
}

Post* previousPost() {
    Post* current = currPost();
    if (current == NULL) {
        return NULL;
    }

    Post* previous = current->prev;

    if (previous != NULL) {
        add_to_view_history(previous);
        return previous;
    }
    
    add_to_view_history(current);
    return current;
}

bool addComment(char* username, char* content) {
    Post* current = currPost();
    if (current == NULL) {
        return false;
    }

    Comment* newComm = createComment(username, content);
    if (newComm == NULL) {
        return false;
    }

    newComm->next = current->comments;
    current->comments = newComm;
    
    return true;
}

bool deleteComment(int n) {
    Post* current = currPost();
    if (n < 1 || current == NULL || current->comments == NULL) {
        return false;
    }

    Comment* target = current->comments;
    Comment* prev = NULL;

    for (int i = 1; i < n && target != NULL; i++) {
        prev = target;
        target = target->next;
    }

    if (target == NULL) {
        return false;
    }

    if (prev == NULL) {
        current->comments = target->next;
    } else {
        prev->next = target->next;
    }

    freeReplies(target->replies);
    free(target->username);
    free(target->content);
    free(target);

    return true;
}

Comment* viewComments() {
    Post* current = currPost();
    if (current == NULL) {
        return NULL;
    }
    return current->comments;
}

bool addReply(char* username, char* content, int n) {
    Post* current = currPost();
    if (n < 1 || current == NULL || current->comments == NULL) {
        return false;
    }

    Comment* target = current->comments;
    for (int i = 1; i < n && target != NULL; i++) {
        target = target->next;
    }

    if (target == NULL) {
        return false;
    }

    Reply* newReply = createReply(username, content);
    if (newReply == NULL) {
        return false;
    }

    newReply->next = target->replies;
    target->replies = newReply;

    return true;
}

bool deleteReply(int n, int m) {
    Post* current = currPost();
    if (n < 1 || m < 1 || current == NULL || current->comments == NULL) {
        return false;
    }

    Comment* target = current->comments;
    for (int i = 1; i < n && target != NULL; i++) {
        target = target->next;
    }

    if (target == NULL || target->replies == NULL) {
        return false;
    }

    Reply* target1 = target->replies;
    Reply* prev = NULL;
    for (int j = 1; j < m && target1 != NULL; j++) {
        prev = target1;
        target1 = target1->next;
    }

    if (target1 == NULL) {
        return false;
    }

    if (prev == NULL) {
        target->replies = target1->next;
    } else {
        prev->next = target1->next;
    }

    free(target1->username);
    free(target1->content);
    free(target1);

    return true;
}

void freePlatform(Platform* platform) {
    if (platform == NULL) {
        return;
    }

    Post* currentPost = platform->posts;
    while (currentPost != NULL) {
        Post* nextPost = currentPost->next;
        freeComments(currentPost->comments);
        free(currentPost->username);
        free(currentPost->caption);
        free(currentPost);
        currentPost = nextPost;
    }

    freeHistory(platform->lastViewedPost);
    free(platform);
    platform = NULL;
}