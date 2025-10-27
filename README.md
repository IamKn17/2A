Project 2A: Social Media Platform

This project is a command-line application that simulates a simple social media platform. It is built in C and uses a modular structure to manage posts, comments, and replies.

The core data structures are:

Posts: Managed as a doubly linked list, allowing for easy navigation between next and previous posts.

Comments: Managed as a singly linked list, attached to each post.

Replies: Managed as a singly linked list, attached to each comment.

View History: A singly linked list is used to track the post viewing history, enabling the current_post functionality.

Features & Commands

The platform supports the following commands:

create_platform: Initializes the platform.

add_post <username> <caption_content>: Adds a new post.

delete_post <post_number>: Deletes a post by its 1-based index.

view_post <post_number>: Views a specific post, setting it as the "current post".

current_post: Displays the last viewed post.

next_post: Moves to and displays the post immediately following the current one.

previous_post: Moves to and displays the post immediately preceding the current one.

add_comment <username> <comment_content>: Adds a comment to the current post.

delete_comment <comment_number>: Deletes a comment from the current post by its 1-based index.

view_comments / view_all_comments: Displays all comments and their replies for the current post (in reverse chronological order).

add_reply <username> <reply_content> <comment_number>: Adds a reply to a specific comment on the current post.

delete_reply <comment_number> <reply_number>: Deletes a specific reply from a specific comment.

exit: Exits the application and frees all allocated memory.

Building and Running

This project uses make to build the executable from the source files located in the code/ directory.

Prerequisites

gcc (C compiler)

make

Compilation

Navigate to the 106124072/2A/ directory in your terminal.

Run the make command:

make


This will compile all .c files from the code/ directory, link the object files, and create an executable named program in the 106124072/2A/ directory.

Running the Program

Execute the compiled program:

./program


You will see a > prompt, where you can enter any of the commands listed above.

Cleaning Up

To remove the compiled executable and all intermediate object files (.o), run:

make clean


File Structure

106124072/2A/
├── Makefile           # The build script
├── program            # The compiled executable (after running 'make')
└── code/
    ├── main.c         # Handles user input and the main application loop
    ├── platform.h     # Header for the main platform logic
    ├── platform.c     # Implementation of the platform logic
    ├── post.h         # Header for the Post data structure
    ├── post.c         # Implementation of Post functions
    ├── comment.h      # Header for the Comment data structure
    ├── comment.c      # Implementation of Comment functions
    ├── reply.h        # Header for the Reply data structure
    └── reply.c        # Implementation of Reply functions
