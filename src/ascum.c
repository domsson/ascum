#include <stdio.h>      // NULL, fprintf(), stdout 
#include <stdlib.h>     // NULL, EXIT_FAILURE, EXIT_SUCCESS
#include <unistd.h>     // getopt(), fstat()
#include <sys/types.h>  // fstat()
#include <sys/stat.h>   // fstat()
#include <ctype.h>      // isprint()

typedef unsigned char byte;

struct options
{
	byte  help : 1;        // Print help and exit
	byte  printable : 1;   // count only printable characters
	byte  nonl : 1;        // do not output a trailing newline
	int   factor;          // add this factor to every char value
	char *string;          // the string to process
};

typedef struct options opts_s;

/*
 * Prints usage information.
 */
static void
help(char *invocation, FILE *stream)
{
	fprintf(stream, "Usage:\n");
	fprintf(stream, "\t%s [OPTIONS...] [INPUT]\n", invocation);
	fprintf(stream, "\n");
	fprintf(stream, "Options:\n");
	fprintf(stream, "\t-f INT\tAdd this number to ever character's ASCII value.\n");
	fprintf(stream, "\t-h\tPrint this help text and exit.\n");
	fprintf(stream, "\t-n\tDo not print a trailing newline.\n");
	fprintf(stream, "\t-p\tOnly sum up ASCII values for printable characters.\n");
}

static void
fetch_opts(opts_s *opts, int argc, char **argv)
{
	// Process command line options
	opterr = 0;
	int o;
	while ((o = getopt(argc, argv, "f:hnp")) != -1)
	{
		switch(o)
		{
			case 'f':
				opts->factor = atoi(optarg);
				break;
			case 'h':
				opts->help = 1;
				break;
			case 'n':
				opts->nonl = 1;
				break;
			case 'p':
				opts->printable = 1;
				break;
		}
	}

	if (optind < argc)
	{
		opts->string = argv[optind];
	}
}

size_t sum_string(char *str, int printable, int factor)
{
	size_t sum = 0;
	int add = 0;
	for (; *str; str++)
	{
		add = (!printable || isprint(*str)) * (*str + factor);
		sum += add > 0 ? add : 0;
	}
	return sum;
}

size_t sum_stream(FILE *stream, int printable, int factor)
{
	size_t sum = 0;
	int add = 0;
	char c = 0;
	while ((c = fgetc(stream)) != EOF)
	{
		add = (!printable || isprint(c)) * (c + factor);
		sum += add > 0 ? add : 0;
	}
	return sum;
}

int
is_pipe(int fd)
{
	struct stat st_info;
	if (fstat(fd, &st_info) != 0)
	{
		return 0;
	}
	return (S_ISFIFO(st_info.st_mode));
}

/*
 * Here be tofu wraps!
 */
int
main(int argc, char **argv)
{
	// parse command line arguments
	opts_s opts = { 0 };
	fetch_opts(&opts, argc, argv);
	
	// print help and exit
	if (opts.help)
	{
		help(argv[0], stdout);
		return EXIT_SUCCESS;
	}

	size_t sum = 0;

	// input via command line arg
	if (opts.string)
	{
		sum = sum_string(opts.string, opts.printable, opts.factor);
	}

	// input via stdin pipe
	else if (is_pipe(STDIN_FILENO))
	{
		sum = sum_stream(stdin, opts.printable, opts.factor);
	}
	
	fprintf(stdout, "%zu%c", sum, opts.nonl ? '\0' : '\n');
	return EXIT_SUCCESS;
}

