<?php

class WaveletTree {
	/** Node $root */
	private $root;

	public function __construct($string) {
		$this->root = $this->createNode($string);
		$this->createChildNodes($this->root, $string);
	}

	public function createChildNodes($parent, $string) {
		$binary = $parent->getBinary();
		$left = '';
		$right = '';
		for ($i = 0; $i < strlen($string); $i++) {
			if($binary[$i] == 0) {
				$left .= $string[$i];
			}elseif($binary[$i] == 1) {
				$right .= $string[$i];
			}
		}

		$leftNode = $this->createNode($left);
		$parent->setLeftChild($leftNode);
		if(!$leftNode->isLeaf()) {
			$this->createChildNodes($leftNode, $left);
		}
		$rightNode = $this->createNode($right);
		$parent->setRightChild($rightNode);	
		if(!$rightNode->isLeaf()) {
			$this->createChildNodes($rightNode, $right);
		}

	}

	public function createNode($string) {
		if($string == null || $string == '') {
			return null;
		}
		$alphabet = WaveletTree::getAlphabet($string);
		$isLeaf = false;
		if(count($alphabet) == 1 || count($alphabet) == 2) {
			$isLeaf = true;
		}	
		$letters = array_keys($alphabet);
		usort($letters, "WaveletTree::sortLetters");
		//set half of letters to 0 half to 1
		$dictionary = [];
		for($i=0; $i < count($letters) /2; $i++) {
		  	$dictionary[$letters[$i]] = 0;
		}
		for($i=count($letters) /2; $i < count($letters); $i++) {
		  	$dictionary[$letters[$i]] = 1;
		}

		$result = [];
		for($i=0; $i < strlen($string); $i++) {
		  	$result[$i] = $dictionary[$string[$i]];
		}
		//translate dictionary to node strings
		return new Node($result, $isLeaf);
	}

	/**
	* Sort letters first is $, then _, then alphabet
	*/
	function sortLetters($a, $b) {
		if($a == '$') {
			return -1;
		}elseif($b == '$') {
			return 1;
		}
		return strcmp($a, $b);
	}

	public static function getAlphabet($string) {
		$dictionary = [];
		for($i=0;$i<strlen($string);$i++) {
		    $char = $string[$i];
		    if(!isset($dictionary[$char])) {
		        $dictionary[$char] = 1;
		    } else {
		    	$dictionary[$char]++;
		    }
		}
		return $dictionary;
	}
	public function getRoot() {
		return $this->root;
	}
}

class Node {
	private $binary;
	private $isLeaf;
	/** Node[] $children */
	private $children;

	public function __construct($binary, $isLeaf) {
		$this->binary = $binary; 
		$this->isLeaf = $isLeaf; 
	}

	public function getString() {
		return $this->string;
	}
	public function getBinary() {
		return $this->binary;
	}
	public function setLeftChild($child) {
		$this->children['left'] = $child;
	}
	public function setRightChild($child) {
		$this->children['right'] = $child;
	}
	public function getLeftChild($child) {
		return $this->children['left'];
	}
	public function getRightChild($child) {
		return $this->children['right'];
	}
	public function isLeaf() {
		return $this->isLeaf;
	}
}

//get memory usage 
$memUsageStart = memory_get_usage(false); 
//Main program
$startTime = round(microtime(true) * 1000);

print "Constructing WaveletTree\n";
$vaveletTree = new WaveletTree('Peter Piper picked a peck of pickled peppers$');
$endTime = round(microtime(true) * 1000);
$timeElapsed = ($endTime - $startTime);


print 'Time elapsed: ' . ($timeElapsed) . " ms\n"; //MS
$root = $vaveletTree->getRoot();
$memUsageEnd = memory_get_usage(false); 
$totalMemoryUsage = $memUsageEnd - $memUsageStart;

if ($totalMemoryUsage < 1024) 
    print $totalMemoryUsage." B\n"; 
elseif ($totalMemoryUsage < 1048576) 
    print round($totalMemoryUsage/1024,2)." KB\n"; 
else 
    print round($totalMemoryUsage/1048576,2)." MB\n";

?>
