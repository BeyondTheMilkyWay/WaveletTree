<?php

class WaveletTree
{

    /** Node $root */
    private $root;
    /** array $alphabet  */
    private $alphabet;

    public function __construct($string)
    {
        list($this->root, $this->alphabet) = $this->createNode($string);
        $this->root->setParent(null);
        $this->createChildNodes($this->root, $string);
    }

    public function createChildNodes($parent, $string)
    {
        $binary = $parent->getBinary();
        $left   = '';
        $right  = '';
        for ($i = 0; $i < strlen($string); $i++) {
            if ($binary[$i] == 0) {
                $left .= $string[$i];
            } elseif ($binary[$i] == 1) {
                $right .= $string[$i];
            }
        }

        $leftNode = $this->createNode($left)[0];
        $leftNode->setParent($parent);
        $parent->setLeftChild($leftNode);
        if (!$leftNode->isLeaf()) {
            $this->createChildNodes($leftNode, $left);
        }
        $rightNode = $this->createNode($right)[0];
        $parent->setRightChild($rightNode);
        $rightNode->setParent($parent);
        if (!$rightNode->isLeaf()) {
            $this->createChildNodes($rightNode, $right);
        }

    }

    public function createNode($string)
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
        return [new Node($result, $isLeaf, $dictionary), $dictionary];
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

    public function rank($index, $letter)
    {
        if (!isset($this->alphabet[$letter])) {
            return 0;
        }

        return $this->rankRecursive($this->root, $index + 1, $letter, $this->alphabet);
    }

    /**
     * @param $index
     *
     * @return string
     */
    public function access($index)
    {
        //TODO: check if index starts from zero or?
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
    private function rankRecursive($node, $index, $letter, $alphabet)
    {
        $letterCoded = $alphabet[$letter];

        //check letter coding
        if ($letterCoded == 1) {
            $trueCount = $node->countOccurrence(1, $index);

            if ($node->isLeaf() || $node->getRightChild() == null) {// if node is leaf
                return $trueCount;
            } else {// if node is not leaf
                return $this->rankRecursive($node->getRightChild(), $trueCount, $letter, $node->getRightChild()->getDictionary());
            }
        } else {
            $falseCount = $node->countOccurrence(0, $index);

            if ($node->isLeaf() || $node->getLeftChild() == null) {// if node is leaf
                return $falseCount;
            } else {// if node is not leaf
                return $this->rankRecursive($node->getLeftChild(), $falseCount, $letter, $node->getLeftChild()->getDictionary());
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
                return array_search(1, $node->getDictionary()); //get where coded as 1
            } else {
                $trueCount = $node->countOccurrence(1, $index);

                return $this->accessRecursive($node->getRightChild(), $trueCount, $alphabet);
            }
        } else {
            if ($node->isLeaf() || $node->getLeftChild() == null) {
                return array_search(0, $node->getDictionary()); //get where coded as 1
            } else {
                $falseCount = $node->countOccurrence(0, $index);

                return $this->accessRecursive($node->getLeftChild(), $falseCount, $alphabet);
            }
        }
    }

    public function select($occurenceNum, $letter) {

        $letterIndex = $this->alphabet[$letter];
        $currentNode = $this->root;

        return $this->selectRecursive($currentNode,$letter,$occurenceNum,$this->alphabet);
    }

    private function selectRecursive($currentNode,$letter,$occurenceNum,$alphabet) {
            return -1;
    }
}

class Node
{
    private $binary;
    private $isLeaf;
    /** Node[] $children */
    private $children;
    /** @var  Node $parent */
    private $parent;

    /** @var  array */
    private $dictionary;

    public function __construct($binary, $isLeaf, $dictionary)
    {
        $this->binary     = $binary;
        $this->isLeaf     = $isLeaf;
        $this->dictionary = $dictionary;
    }

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

    public function getDictionary()
    {
        return $this->dictionary;
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

//get memory usage 
$memUsageStart = memory_get_usage(false);
//Main program
$startTime = round(microtime(true) * 1000);

if (!isset($argv[1])) {
    print "Usage: php WaveletTree.php input.fas";

    return;
}
$file        = fopen($argv[1], 'r');
$inputString = '';
while (($line = fgets($file)) !== false) {
    $line = trim($line);
    if (strrpos($line, '>') === 0) {
        continue;
    }

    $inputString .= $line;
}
fclose($file);


$waveletTree = new WaveletTree($inputString);
$endTime     = round(microtime(true) * 1000);
$timeElapsed = ($endTime - $startTime);


print 'Time elapsed: ' . ($timeElapsed) . " ms\n"; //MS
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

for($i=0;$i<45;$i++){
    print "Access ($i) :" . $waveletTree->access($i) . "\n";
}
for($j=0;$j<strlen($inputString);$j++) {
    for($i=0;$i<45;$i++){
        $a = $inputString[$j];
        print "Rank ($i,$a) :" . $waveletTree->rank($i,$a) . "\n";
    }
}

//print $waveletTree->select(0,"$");
//print $waveletTree->select(1,"$");


?>
