# Wavelet Tree - C++ implementation

This project implements WaveletTree data structure.
It includes the following query methods on data structure:
- `rank` - Counts number of times some 'character' appeares in string up to 'position'
- `access` - Returns character at 'index' position in string
- `select` - Returns position in string at which 'character' occurs for the 'nth_occurrence' time

### Requirements
Make sure you have `cmake` installed

### How to compile
    $ cmake CMakeLists.txt
    $ make

After this step, an executable file should appear together with several cmake files.

### How to run
    $ ./WaveletTree <in_file> <out_file> <task> <task_args...>

#### Program arguments:
- `<in_file>` - path to FASTA file which is used to build Wavelet tree
- `<out_file>` - path to where to write result
- `<task>` - name of the task to run
  - `build` - just builds the tree
  - `rank <position> <character>` - builds the tree and executes rank query with `position` and `character` arguments
  - `access <index>` - builds the tree and executes access query with `index` argument
  - `select <nth_occurence> <character>` - builds the tree and executes select query with `nth_occurence` and `character` arguments

### Licence MIT
See root directory for details
