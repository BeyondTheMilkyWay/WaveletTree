# Wavelet Tree - C implementation

For more information see root folder.

This project includes following implementations:

 - WaveletTree
 - rank function
 - select function
 - access function
 - basic unit tests


### How to compile
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

### Authors

- dsisejkovic, 2016

