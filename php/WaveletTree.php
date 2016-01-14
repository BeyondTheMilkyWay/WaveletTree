<?php

/**
 * Class WaveletTree represents wavelet tree
 */
class WaveletTree
{

    /** Node $root */
    private $root;
    /** array $alphabet  */
    private $alphabet;

    public function __construct($string)
    {
        list($this->root, $this->alphabet) = $this->createNode($string, 0);
        $this->root->setParent(null);
        $this->createChildNodes($this->root, $string, 0);
    }

    /**
     * Method creates child nodes from root node
     * @param $parent
     * @param $string
     * @param $left
     */
    public function createChildNodes($parent, $string, $left)
    {
        $binary = $parent->getBinary();
        $leftString   = '';
        $rightString  = '';
        for ($i = 0; $i < strlen($string); $i++) {
            if ($binary[$i] == 0) {
                $leftString .= $string[$i];
            } elseif ($binary[$i] == 1) {
                $rightString .= $string[$i];
            }
        }

        list($leftNode, $dict) = $this->createNode($leftString, $left);
        $leftNode->setParent($parent);
        $parent->setLeftChild($leftNode);
        if (!$leftNode->isLeaf()) {
            $this->createChildNodes($leftNode, $leftString, $left);
        }
        $rightNode = $this->createNode($rightString, $left + count($dict))[0];
        $parent->setRightChild($rightNode);
        $rightNode->setParent($parent);
        if (!$rightNode->isLeaf()) {
            $this->createChildNodes($rightNode, $rightString, $left + count($dict));
        }

    }

    /**
     * Method creates node
     * @param $string
     * @param $left
     *
     * @return array|null
     */
    public function createNode($string, $left)
    {
        if ($string == null || $string == '') {
            return null;
        }
        $alphabet = WaveletTree::getAlphabet($string);
        $isLeaf   = false;
        if (count($alphabet) == 1 || count($alphabet) == 2) {
            $isLeaf = true;
        }
        $letters = array_keys($alphabet);
        usort($letters, "WaveletTree::sortLetters");
        //set half of letters to 0 half to 1
        $dictionary = [];
        for ($i = 0; $i < count($letters) / 2; $i++) {
            $dictionary[$letters[$i]] = 0;
        }
        for ($i = count($letters) / 2; $i < count($letters); $i++) {
            $dictionary[$letters[$i]] = 1;
        }

        $result = [];
        for ($i = 0; $i < strlen($string); $i++) {
            $result[$i] = $dictionary[$string[$i]];
        }

        //translate dictionary to node strings
        return [new Node($result, $isLeaf, $left, $left + count($dictionary) - 1 ), $dictionary];
    }

    /**
     * Sort letters first is $, then _, then alphabet
     */
    function sortLetters($a, $b)
    {
        if ($a == '$') {
            return -1;
        } elseif ($b == '$') {
            return 1;
        }
        return strcmp($a, $b);
    }

    public function getFinalAlphabet() {
        return $this->alphabet;
    }

    public static function getAlphabet($string)
    {
        $dictionary = [];
        for ($i = 0; $i < strlen($string); $i++) {
            $char = $string[$i];
            if (!isset($dictionary[$char])) {
                $dictionary[$char] = 1;
            } else {
                $dictionary[$char]++;
            }
        }

        return $dictionary;
    }

    public function getRoot()
    {
        return $this->root;
    }

    /**
     * Rank method in wavelet tree
     * @param $index
     * @param $letter
     *
     * @return int|mixed
     */
    public function rank($index, $letter)
    {
        if (!isset($this->alphabet[$letter])) {
            return 0;
        }

        return $this->rankRecursive($this->root, $index + 1, $letter);
    }

    /**
     * Access method in wavelet tree
     * @param $index
     *
     * @return string
     */
    public function access($index)
    {
        return $this->accessRecursive($this->root, $index, $this->alphabet);
    }

    /**
     * @param $node Node
     * @param $index
     * @param $letter
     *
     * @param $alphabet
     *
     * @return mixed
     */
    private function rankRecursive($node, $index, $letter)
    {
        $letterCoded = $node->getLetterCoded($this->alphabet, $letter);

        //check letter coding
        if ($letterCoded == 1) {
            $trueCount = $node->countOccurrence(1, $index);

            if ($node->isLeaf() || $node->getRightChild() == null) {// if node is leaf
                return $trueCount;
            } else {// if node is not leaf
                return $this->rankRecursive($node->getRightChild(), $trueCount, $letter);
            }
        } else {
            $falseCount = $node->countOccurrence(0, $index);

            if ($node->isLeaf() || $node->getLeftChild() == null) {// if node is leaf
                return $falseCount;
            } else {// if node is not leaf
                return $this->rankRecursive($node->getLeftChild(), $falseCount, $letter);
            }
        }
    }

    /**
     * @param $node Node
     * @param $index
     * @param $alphabet
     *
     * @return string
     */
    private function accessRecursive($node, $index, $alphabet)
    {
        if ($node->getBinary()[$index] == 1) {
            if ($node->isLeaf() || $node->getRightChild() == null) {
                return $node->getLastCharacter($alphabet); //get where coded as 1
            } else {
                $trueCount = $node->countOccurrence(1, $index);

                return $this->accessRecursive($node->getRightChild(), $trueCount, $alphabet);
            }
        } else {
            if ($node->isLeaf() || $node->getLeftChild() == null) {
                return $node->getFirstCharacter($alphabet); //coded as 0
            } else {
                $falseCount = $node->countOccurrence(0, $index);

                return $this->accessRecursive($node->getLeftChild(), $falseCount, $alphabet);
            }
        }
    }

    /**
     * Select method in wavelet tree
     * @param $occurrenceNum
     * @param $letter
     *
     * @return int
     */
    public function select($occurrenceNum, $letter)
    {
        if($occurrenceNum < 0) {
            return -1;
        }
        $letterIndex = 0;
        foreach ($this->alphabet as $key => $value) {
            if ($key == $letter) {
                break;
            }
            $letterIndex++;
        }
        $currentNode = $this->root;
        while (!$currentNode->isLeaf()) {
            if ($currentNode->getLeftChild()->characterInNode($this->alphabet, $letter)) {
                $currentNode = $currentNode->getLeftChild();
            } else {
                $currentNode = $currentNode->getRightChild();
            }
        }

        return $this->selectRecursive($currentNode, $letter, $occurrenceNum, $this->alphabet);
    }

    private function selectRecursive($currentNode, $letter, $occurrenceNum, $alphabet)
    {
        $letterCoded = $currentNode->getLetterCoded($this->alphabet, $letter);
        $index       = $currentNode->calculateOccurrence($letterCoded, $occurrenceNum + 1);
        if ($currentNode->getParent() == null) {
            return $index;
        } else {
            return $this->selectRecursive($currentNode->getParent(), $letter, $index, $alphabet);
        }
    }
}

/**
 * Class Node represents Node in Wawelet tree
 */
class Node
{
    private $binary;
    private $isLeaf;
    /** Node[] $children */
    private $children;
    /** @var  Node $parent */
    private $parent;

    /** @var  integer */
    private $leftCharacter;
    /** @var  integer */
    private $rightCharacter;


    public function __construct($binary, $isLeaf, $leftCharacter, $rightCharacter)
    {
        $this->binary     = $binary;
        $this->isLeaf     = $isLeaf;
        $this->leftCharacter = $leftCharacter;
        $this->rightCharacter = $rightCharacter;
    }

    /**
     * Return bits of node
     * @return mixed
     */
    public function getBinary()
    {
        return $this->binary;
    }

    public function setLeftChild($child)
    {
        $this->children['left'] = $child;
    }

    public function setRightChild($child)
    {
        $this->children['right'] = $child;
    }

    /**
     * @return Node
     */
    public function getLeftChild()
    {
        return isset($this->children['left']) ? $this->children['left'] : null;
    }

    /**
     * @return Node
     */
    public function getRightChild()
    {
        return isset($this->children['right']) ? $this->children['right'] : null;
    }

    public function isLeaf()
    {
        return $this->isLeaf;
    }

    public function characterInNode($dictionary, $character)
    {
        $i=0;
        foreach($dictionary as $key => $value) {
            if($key == $character) {
                if($this->leftCharacter <= $i && $this->rightCharacter >= $i) {
                    return true;
                }else {
                    return false;
                }
            }
            $i++;
        }
        return false;
    }

    public function getLetterCoded($dictionary, $character) {
        $i=0;
        foreach($dictionary as $key => $value) {
            if($key == $character) {
                break;
            }
            $i++;
        }
        $half = round(($this->rightCharacter - $this->leftCharacter - 1) / 2);
        if($this->leftCharacter + $half >= $i) {
            return 0;
        }
        return 1;
    }

    public function countOccurrence($bit, $index)
    {
        $counter = 0;
        for ($i = 0; $i < count($this->binary); $i++) {
            if ($i >= $index) {
                break;
            }
            if ($this->binary[$i] == $bit) {
                $counter++;
            }
        }

        return $counter;
    }

    public function calculateOccurrence($bit, $occurrences)
    {
        if($occurrences == 0) {
            return -1;
        }
        $counter = 0;
        for ($i = 0; $i < count($this->binary); $i++) {
            if ($this->binary[$i] == $bit) {
                $counter++;
            }
            if ($counter == $occurrences) {
                return $i;
            }
        }
        return -1;
    }

    public function getFirstCharacter($alphabet) {
        $i=0;
        foreach($alphabet as $key => $value) {
            if($i == $this->leftCharacter) {
                return $key;
            }
            $i++;
        }
        return null;
    }

    public function getLastCharacter($alphabet) {
        $i=0;
        foreach($alphabet as $key => $value) {
            if($i == $this->rightCharacter) {
                return $key;
            }
            $i++;
        }
        return null;
    }

    /**
     * @return Node
     */
    public function getParent()
    {
        return $this->parent;
    }

    /**
     * @param Node $parent
     */
    public function setParent($parent)
    {
        $this->parent = $parent;
    }

}

function readFasFile($name) {
    $file        = fopen($name, 'r');
    $inputString = '';
    while (($line = fgets($file)) !== false) {
        $line = trim($line);
        if (strrpos($line, '>') === 0) {
            continue;
        }

        $inputString .= $line;
    }
    fclose($file);
    return $inputString;
}

ini_set("memory_limit","2000M");

//get memory usage 
$memUsageStart = memory_get_usage(false);


if (!isset($argv[1])) {
    print "Usage: php WaveletTree.php input.fas output operation params\n";
    print "access num\n";
    print "rank index letter \n";
    print "select occurrenceNumber letter \n";
    print "test \n";
    return;
}


//Main program
$readStartTime   = round(microtime(true) * 1000);
$inputString     = readFasFile($argv[1]);
$readEndTime     = round(microtime(true) * 1000);
$readTimeElapsed = ($readEndTime - $readStartTime);


$buildStartTime   = round(microtime(true) * 1000);
$waveletTree = new WaveletTree($inputString);
$buildEndTime     = round(microtime(true) * 1000);
$buildTimeElapsed = ($buildEndTime - $buildStartTime);



print 'Time elapsed: ' . ($readTimeElapsed + $buildTimeElapsed) . " ms\n"; //MS
$root             = $waveletTree->getRoot();
$memUsageEnd      = memory_get_usage(false);
$totalMemoryUsage = $memUsageEnd - $memUsageStart;

if ($totalMemoryUsage < 1024) {
    print $totalMemoryUsage . " B\n";
} elseif ($totalMemoryUsage < 1048576) {
    print round($totalMemoryUsage / 1024, 2) . " KB\n";
} else {
    print round($totalMemoryUsage / 1048576, 2) . " MB\n";
}


if($argv[2] == "test") {

    $output   = fopen('read.out', 'w+');
    $buildOut = fopen('build.out', 'w+');
    fwrite($output, $readTimeElapsed);
    fwrite($buildOut, $buildTimeElapsed);
    fflush($output);
    fflush($buildOut);
    fclose($output);
    fclose($buildOut);
    return;
}

if($argv[2] == "query") {
    $testLetter = $inputString[0];
    $rankIndex = count($inputString) / 2;
    $selectIndex = sqrt(count($inputString) / 2);

    $output = fopen('rank.out', 'w+');

    $readStartTime   = round(microtime(true) * 1000);

    for($i = 0; $i < 1000; $i++) {
        $waveletTree->rank($rankIndex, $testLetter);
    }

    $readEndTime     = round(microtime(true) * 1000);
    $readTimeElapsed = ($readEndTime - $readStartTime);

    fwrite($output, $readTimeElapsed/1000);
    fflush($output);
    fclose($output);

    $output = fopen('rank.out', 'w+');
    $readStartTime   = round(microtime(true) * 1000);

    for($i = 0; $i < 1000; $i++) {
        $waveletTree->access($rankIndex);
    }

    $readEndTime     = round(microtime(true) * 1000);
    $readTimeElapsed = ($readEndTime - $readStartTime);

    fwrite($output, $readTimeElapsed/1000);
    fflush($output);
    fclose($output);

    $output = fopen('index.out', 'w+');
    $readStartTime   = round(microtime(true) * 1000);

    for($i = 0; $i < 1000; $i++) {
        $waveletTree->select($selectIndex,$testLetter );
    }

    $readEndTime     = round(microtime(true) * 1000);
    $readTimeElapsed = ($readEndTime - $readStartTime);

    fwrite($output, $readTimeElapsed/1000);
    fflush($output);
    fclose($output);
    return;
}

$operation = $argv[3];

if($operation == "access") {
    $result = $waveletTree->access($argv[4]);
} elseif($operation == "rank") {
    $result = $waveletTree->rank($argv[4], $argv[5]);
} elseif($operation == "select") {
    $result = $waveletTree->select($argv[4]-1, $argv[5]);
} else {
    print "Invalid operation";
    return;
}

//write to output file
$outputFile = fopen($argv[2], 'w');
fwrite($outputFile, $result);
fwrite($outputFile, "\r\n");
fflush($outputFile);
fclose($outputFile);

?>
