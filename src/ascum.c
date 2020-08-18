#include <stdio.h>      // NULL, fprintf(), stdout 
#include <stdlib.h>     // NULL, EXIT_FAILURE, EXIT_SUCCESS
#include <unistd.h>     // getopt(), sleep()

typedef unsigned char byte;

struct options
{
	byte  help : 1;        // Print help and exit
	int   factor;
	char* string;
};

typedef struct options opts_s;

/*
 * Prints usage information.
 */
static void
help(char *invocation)
{
	fprintf(stdout, "Usage:\n");
	fprintf(stdout, "\t%s [OPTIONS...] server_ip\n", invocation);
	fprintf(stdout, "\n");
	fprintf(stdout, "Options:\n");
	fprintf(stdout, "\t-h\tPrint this help text and exit.\n");
}

static void
fetch_opts(opts_s *opts, int argc, char **argv)
{
	// Process command line options
	opterr = 0;
	int o;
	while ((o = getopt(argc, argv, "f:h")) != -1)
	{
		switch(o)
		{
			case 'h':
				opts->help = 1;
				break;
			case 'f':
				opts->factor = atoi(optarg);
				break;
		}
	}

	if (optind < argc)
	{
		opts->string = argv[optind];
	}
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
		help(argv[0]);
		return EXIT_SUCCESS;
	}

	if (opts.string == NULL)
	{
		return EXIT_SUCCESS;
	}

	int sum = 0;
	for (; *opts.string; opts.string++)
	{
		sum += *opts.string + opts.factor;
	}

	fprintf(stdout, "%d\n", sum);
	
	// done, bye
	return EXIT_SUCCESS;
}

