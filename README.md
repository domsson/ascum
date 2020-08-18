# ascum

**ASC**II s**um**

Sums up the ASCII values of all characters in the given string and prints the result to `stdout`.
 
## Usage

    ascum [-f INT] [-h] [-n] [-p] [INPUT]

Options:

 - `-f INT` Add this number to every character's ASCII value
 - `-h` Print this help text and exit
 - `-n` Do not print a trailing newline character
 - `-p` Only sum up ASCII values for printable characters

## Example usages

    ascum "hello world"
    1116

    echo "hello world" | ascum
    1126

    echo -n "hello world" | ascum
    1116

    echo "hello world" | ascum -p
    1116

    ascum -f-96 "hello world"
    124


