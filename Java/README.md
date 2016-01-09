#WaveletTree


###Contents

######Included in this release are the following:

Files | Description
---------------- | ----------------------------
README.txt | This file
LICENSE.txt | Software license
Escherichia_coli.fa | Example of FASTA file with E. coli genome
src/WaveletTree.java | Implementation of Wavelet tree
src/WaveletNode.java | Implementation of Wavelet tree node
src/BitArray.java | Implementation of bit array
src/Parser.java | Implementation of parser for reading FASTA file
src/RunRank.java | Class that runs rank method 
src/RunSelect.java | Class that runs select method
src/RunAccess.java | Class that runs access method 


###JDK Version notes

* JDK 1.7

###Run instructions

* Compile files: 			**javac *.java**
* Run rank operation: 		**java RunRank \<filepath\> \<character\> \<index\>**
	* result stored in **rank_result.txt** file
* Run select operation: 	**java RunSelect \<filepath\> \<character\> \<index\>**
	* result stored in **select_result.txt** file
* Run access operation: 	**java RunAccess \<filepath\> \<index\>**
	* result stored in **access_result.txt** file
	
###Example

* **javac *.java**
* **java RunRank ../Escherichia_coli.fa T 45000**
	* result: 11160
* **java RunSelect ../Escherichia_coli.fa T 45000**
	* result: 175227
* **java RunRank ../Escherichia_coli.fa 45000**
	* result: T

	
	
	