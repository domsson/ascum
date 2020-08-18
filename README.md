# ascum

**ASC**II s**um**

Sums up the ASCII values of all characters in the given string and prints the result to `stdout`. Optionally, a factor can be given via `-f`, which will be added to each character's ASCII value before adding it to the result. If the `-p` option is given, only printable characters will be summed up.

The input string can be provided as command line argument or by piping it into `ascum`. Note, however, that there might be an additional line break character if piping is used; the `-p` option can help if counting such character values is not desired.

By default, `ascum` adds a trailing newline to the result. This can be prevented by using the `-n` option.

## Usage

    ascum [-f] [-h] [-n] [-p] [INPUT]

Examples:

    ascum "hello world"
    1116

    echo "hello world" | ascum
    1126

    echo -n "hello world" | ascum
    1116

    echo "hello world" | ascum -p
    1116

    ascum -f-64 "hello world"
    412


