# Wavelet Tree - C implementation

For more information see root folder.

This project includes following implementations:

 - WaveletTree
 - rank function
 - select function
 - access function
 - basic unit tests

For code documentation please see all header (.h) files.

### How to compile
In order to compile and run the program, you must have cmake and make commands available on your system.
If you are using a linux distribution, you most likely already have both installed.
Otherwise please install first.

Prepare for compilation by typing:

    $ cmake CMakeLists.txt
then comile with following command:

    $ make

Now you should see an executable file named 'c-wavelet-tree'.
To run the file type:

    $ ./c-wavelet-tree <arguments>

Following arguments are supported:

- `test`
- `<input-file-path> access <index>`
- `<input-file-path> rank <character> <index>`
- `<input-file-path> select <character> <index>`
- `batchtest <input-file-path> <output-file> <num-of-runs>`

### Authors

- dsisejkovic, 2016

