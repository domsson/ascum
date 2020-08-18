# ascum

*ASC*II s*um*

Sums up the ASCII values of all characters in the given string and prints the result to `stdout`. Optionally, a factor can be given via `-f`, which will be added to each character's ASCII value before adding it to the result.

## Usage

    ascum [-f] 'string to sum'

Examples:

    ascum 'hello world'
    1116

    ascum -f-64 'hello world'
    412

