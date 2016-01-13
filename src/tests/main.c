#include "threads.c"
#include "posts.c"

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    run_thread_tests();
    test_posts();
    return 1;
}

