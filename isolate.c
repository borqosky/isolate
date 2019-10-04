#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

struct params
{
    int fd[2];
    char **argv;
};

static void parse_args(int argc, char **argv, struct params *params)
{
# define NEXT_ARG() do { argc--; argv++; } while (0)
    // Skip binary path
    NEXT_ARG();
    if (argc < 1) {
        printf("Nothing to do!\n");
        exit(0);
    }
    params->argv = argv;
#undef NEXT_ARG
}

#define STACKSIZE (1024*1024)
static char cmd_stack[STACKSIZE];

static void die(const char *fmt, ...)
{
    va_list params;

    va_start(params, fmt);
    vfprintf(stderr, fmt, params);
    va_end(params);
    exit(1);
}

int main(int argc, char const *argv[])
{
    struct params params;
    memset(&params, 0, sizeof(struct params));
    parse_args(argc, argv, &params);

    // Create pipe to communicate between main and command process.
    if (pipe(params.fd) < 0)
        die("Failed to create pipe: %m");

    return 0;
}
