# Wavelet Tree - C# implementation

For more information see root folder.

This project includes following implementations:

 - WaveletTree
 - rank function
 - select function
 - access function


### How to compile
 Prepare for compilation by typing:

    sudo apt-get install mono-mcs
then comile with following command:

    mcs Run.cs Tree.cs Node.cs Parser.cs

Now you should see an executable file named 'c-wavelet-tree'.
To run the file type:

    $ ./c-wavelet-tree <arguments>

Following arguments are supported:

- `test`
- `<input-file-path> access <index>`
- `<input-file-path> rank <index> <character>`
- `<input-file-path> select <index> <character>`

### Authors

- ddragicevic, 2016


