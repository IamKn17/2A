#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"


#define MAX_LENGTH 256
#define MAX_CMD 50
void print_replies_reverse(Reply* head) {
    if (head == NULL) {
        return;
    }
    print_replies_reverse(head->next);
    printf("\t\t%s: %s\n", head->username, head->content);
}

void print_comments_reverse(Comment* head) {
    if (head == NULL) {
        return;
    }
    print_comments_reverse(head->next);
    printf("\t%s: %s\n", head->username, head->content);
    print_replies_reverse(head->replies);
}

int main() {
    char command[MAX_CMD];
    char input1[MAX_LENGTH];
    char input2[MAX_LENGTH];
    int n, m;

    while (1) {
        printf("> ");
        if (scanf("%s", command) == EOF) {
            break;
        }

        if (strcmp(command, "create_platform") == 0) {
            if (createPlatform() != NULL) {
                printf("Platform created.\n");
            } else {
                printf("Error: Failed to create platform.\n");
            }
        } else if (strcmp(command, "add_post") == 0) {
            scanf("%s", input1);
            scanf(" %[^\n]", input2);
            if (addPost(input1, input2)) {
                printf("Post added.\n");
            } else {
                printf("Error: Failed to add post.\n");
            }
        } else if (strcmp(command, "delete_post") == 0) {
            scanf("%d", &n);
            if (deletePost(n)) {
                printf("Post %d deleted.\n", n);
            } else {
                printf("Error: Post does not exist.\n");
            }
        } else if (strcmp(command, "view_post") == 0) {
            scanf("%d", &n);
            Post* post = viewPost(n);
            if (post != NULL) {
                printf("%s: %s\n", post->username, post->caption);
            } else {
                printf("Error: Post does not exist.\n");
            }
        } else if (strcmp(command, "current_post") == 0) {
            Post* post = currPost();
            if (post != NULL) {
                printf("%s: %s\n", post->username, post->caption);
            } else {
                printf("Error: No post to show.\n");
            }
        } else if (strcmp(command, "next_post") == 0) {
            Post* post = nextPost();
            if (post != NULL) {
                printf("%s: %s\n", post->username, post->caption);
            } else {
                printf("Error: Next post does not exist.\n");
            }
        } else if (strcmp(command, "previous_post") == 0) {
            Post* post = previousPost();
            if (post != NULL) {
                printf("%s: %s\n", post->username, post->caption);
            } else {
                printf("Error: Previous post does not exist.\n");
            }
        } else if (strcmp(command, "add_comment") == 0) {
            scanf("%s", input1);
            scanf(" %[^\n]", input2);
            if (addComment(input1, input2)) {
                printf("Comment added.\n");
            } else {
                printf("Error: Failed to add comment.\n");
            }
        } else if (strcmp(command, "delete_comment") == 0) {
            scanf("%d", &n);
            if (deleteComment(n)) {
                printf("Comment %d deleted.\n", n);
            } else {
                printf("Error: Comment does not exist.\n");
            }
        } else if (strcmp(command, "view_comments") == 0||strcmp(command, "view_all_comments") == 0) {
            Comment* comments = viewComments();
            if (comments != NULL) {
                print_comments_reverse(comments);
            } else {
                printf("Error: No comments to show.\n");
            }
        } else if (strcmp(command, "add_reply") == 0) {
            scanf("%s", input1);
            scanf(" %[^\n]", input2);
            scanf("%d", &n);
            if (addReply(input1, input2, n)) {
                printf("Reply added.\n");
            } else {
                printf("Error: Failed to add reply.\n");
            }
        } else if (strcmp(command, "delete_reply") == 0) {
            scanf("%d", &n);
            scanf("%d", &m);
            if (deleteReply(n, m)) {
                printf("Reply %d from comment %d deleted.\n", m, n);
            } else {
                printf("Error: Reply does not exist.\n");
            }
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting.\n");
            break;
        } else {
            printf("Error: Unknown command.\n");
            while (getchar() != '\n');
        }
    }

    return 0;
}

