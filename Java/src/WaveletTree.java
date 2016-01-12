import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;

/**
 * Wavelet tree implementation.
 * 
 * @author ICapalija
 * 
 */
public class WaveletTree {

	/**
	 * Root node of the tree.
	 */
	private WaveletNode rootNode;
	/**
	 * Sequence alphabet.
	 */
	private byte[] alphabet;

	/**
	 * Wavelet tree constructor.
	 * 
	 * @param sequence
	 *            character sequence.
	 */
	public WaveletTree(byte[] sequence) {
		// convert sequence to list
		List<Byte> seq = new ArrayList<>();
		for (byte l : sequence) {
			seq.add(l);
		}
		
		this.alphabet = getDistinct(seq);
		System.out.println(Arrays.toString(this.alphabet));
		this.rootNode = new WaveletNode(seq.size(), (byte) 0,
				(byte) (this.alphabet.length - 1));

		// build tree
		this.buildTree(this.rootNode, seq, 0, this.alphabet);
	}

	/**
	 * Build tree.
	 * 
	 * @param node
	 *            current node.
	 * @param sequence
	 *            char sequence.
	 * @param currDepth
	 *            tree depth.
	 * @param alphabet
	 *            sequence alphabet.
	 */
	private void buildTree(WaveletNode node, List<Byte> sequence,
			int currDepth, byte[] alphabet) {
		// current node alphabet size
		byte alphSize = (byte) (node.getEndAlphabetIndex()
				- node.getStartAlphabetIndex() + 1);
		// current node alphabet split
		byte alphHalf = (byte) (node.getStartAlphabetIndex() + alphSize / 2);

		List<Byte> leftSeq = new ArrayList<>();
		List<Byte> rightSeq = new ArrayList<>();

		// encode letters into bits
		for (int i = 0; i < sequence.size(); i++) {
			byte letter = sequence.get(i);

			if (letter < alphabet[alphHalf]) {// if the letter is on the left
												// side of the alphabet
				leftSeq.add(letter);
				node.setBit(i, false);
			} else {// if the letter is on the right side of the alphabet
				rightSeq.add(letter);
				node.setBit(i, true);
			}
		}

		// if left child's alphabet is greater than 0
		if ((alphHalf - node.getStartAlphabetIndex() - 1) > 0) {
			node.setLeftChild(new WaveletNode(leftSeq.size(), node
					.getStartAlphabetIndex(), (byte) (alphHalf - 1), node));
			buildTree(node.getLeftChild(), leftSeq, currDepth + 1, alphabet);
		}

		// if right child's alphabet is greater than 0
		if ((node.getEndAlphabetIndex() - alphHalf) > 0) {
			node.setRightChild(new WaveletNode(rightSeq.size(), alphHalf, node
					.getEndAlphabetIndex(), node));
			buildTree(node.getRightChild(), rightSeq, currDepth + 1, alphabet);
		}
	}

	/**
	 * Rank method. 
	 * Rank is number of occurrences of given letter
	 * in prefix S[0..index].
	 * 
	 * @param letter
	 *            letter whose rank is calculated.
	 * @param index
	 *            end index of prefix.
	 * @return letter rank in prefix.
	 */
	public int rank(byte letter, int index) {
		return rank(this.rootNode, index + 1, letter);
	}

	/**
	 * Recursive method that calculates rank. Rank is number of 
	 * occurrences of given letter in prefix S[0..index].
	 * 
	 * @param node
	 *            current node.
	 * @param index
	 *            end index of prefix.
	 * @param letter
	 *            letter whose rank is calculated.
	 * @return letter rank in prefix.
	 */
	private int rank(WaveletNode node, int index, byte letter) {
		byte alphSize = (byte) (node.getEndAlphabetIndex()
				- node.getStartAlphabetIndex() + 1);
		byte alphHalf = (byte) (node.getStartAlphabetIndex() + alphSize / 2);

		if (letter < this.alphabet[alphHalf]) {// if letter is 0 encoded
			// count number of occurrences of 0 in bit array
			int falseCount = node.countOccurrence(false, index);

			if (node.getLeftChild() == null) {// if node is leaf
				return falseCount;
			} else {// if node is not leaf
				return rank(node.getLeftChild(), falseCount, letter);
			}
		} else {// if letter is 1 encoded
			// count number of occurrences of 1 in bit array
			int trueCount = node.countOccurrence(true, index);

			if (node.getRightChild() == null) {// if node is leaf
				return trueCount;
			} else {// if node is not leaf
				return rank(node.getRightChild(), trueCount, letter);
			}
		}
	}

	/**
	 * Select method.
	 * Result of a select method is smallest prefix with 
	 * <code>occurrenceNum + 1</code> occurrences of given letter.
	 * 
	 * @param letter
	 *            letter.
	 * @param occurrenceNum
	 *            number of occurrences in prefix.
	 * @return end index of result prefix.
	 */
	public int select(byte letter, int occurrenceNum) {
		// calculate index of the letter in alphabet, which is starting point of
		// select method
		int letterIndex = Arrays.binarySearch(this.alphabet, letter);
		WaveletNode currNode = this.rootNode;

		// find starting point node
		while (true) {
			byte alphSize = (byte) (currNode.getEndAlphabetIndex()
					- currNode.getStartAlphabetIndex() + 1);
			byte alphHalf = (byte) (currNode.getStartAlphabetIndex() + alphSize / 2);

			if (alphHalf > letterIndex) {
				if (currNode.getLeftChild() == null) break;
				currNode = currNode.getLeftChild();
			} else {
				if (currNode.getRightChild() == null) break;
				currNode = currNode.getRightChild();
			}
		}
		

		// call recursive method
		return select(currNode, letter, occurrenceNum, alphabet);
	}

	/**
	 * Recursive calculation of select method.
	 * 
	 * @param node
	 *            current node.
	 * @param letter
	 *            letter.
	 * @param occurrenceNum
	 *            number of occurrences in prefix.
	 * @param alphabet
	 *            alphabet.
	 * @return end index of result prefix.
	 */
	private int select(WaveletNode node, byte letter, int occurrenceNum,
			byte[] alphabet) {
		byte alphSize = (byte) (node.getEndAlphabetIndex()
				- node.getStartAlphabetIndex() + 1);
		byte alphHalf = (byte) (node.getStartAlphabetIndex() + alphSize / 2);

		// is letter 0 or 1 encoded
		boolean bitType = letter >= alphabet[alphHalf];

		// calculate length of prefix of an array which contains
		// <code>occurranceNum</code> bits of type <code>bitType</code>
		int index = node.calcOccurrenceArrayLength(bitType, occurrenceNum + 1);

		if (node.getParent() == null) {// if root return result
			return index;
		} else {// else ask parent
			return select(node.getParent(), letter, index, alphabet);
		}
	}

	/**
	 * Access method.
	 * Get character on given index in sequence.
	 * 
	 * @param index
	 *            index of character.
	 * @return character on given index.
	 */
	public byte access(int index) {
		return access(this.rootNode, index, this.alphabet);
	}

	/**
	 * Get character on given index in sequence.
	 * 
	 * @param node
	 *            current node.
	 * @param index
	 *            index of character.
	 * @param alphabet
	 *            alphabet.
	 * @return character on given index.
	 */
	public byte access(WaveletNode node, int index, byte[] alphabet) {

		if (!node.getBit(index)) {// if letter is 0 encoded

			if (node.getLeftChild() == null) {// if node is leaf
				return alphabet[node.getStartAlphabetIndex()];
			} else {// if node is not leaf
				// count number of occurrences of 0 in bit array
				int falseCount = node.countOccurrence(false, index);
				return access(node.getLeftChild(), falseCount, alphabet);
			}

		} else {// if letter is 1 encoded

			if (node.getRightChild() == null) {// if node is leaf
				return alphabet[node.getEndAlphabetIndex()];
			} else {// if node is not leaf
				// count number of occurrences of 1 in bit array
				int trueCount = node.countOccurrence(true, index);
				return access(node.getRightChild(), trueCount, alphabet);

			}

		}
	}

	/**
	 * Convert tree to string.
	 * 
	 * @return string representation of tree.
	 */
	public String toString() {
		Queue<WaveletNode> queue = new LinkedList<>();
		WaveletNode temp;
		StringBuilder builder = new StringBuilder();

		queue.add(this.rootNode);
		int counter = 1;
		while (!queue.isEmpty()) {
			counter++;

			// remove the node from the queue
			temp = queue.poll();

			// process current node
			builder.append(temp.toString());
			builder.append(' ');
			double pom = Math.log(counter) / Math.log(2);
			if (pom == (int) pom) {
				builder.append('\n');
			}

			// process the left child first if not null
			if (temp.getLeftChild() != null) {
				queue.add(temp.getLeftChild());
			}
			// process the right child after the left if not null
			if (temp.getRightChild() != null) {
				queue.add(temp.getRightChild());
			}
		}

		return builder.toString();
	}

	/**
	 * Get distinct values from array.
	 * 
	 * @param sequence
	 *            sequence.
	 * @return byte of sorted distinct values.
	 */
	private byte[] getDistinct(List<Byte> sequence) {
		// get distinct values
		Set<Byte> set = new TreeSet<Byte>(sequence);

		// convert to byte array
		byte[] distinct = new byte[set.size()];
		int index = 0;
		for (byte letter : set) {
			distinct[index] = letter;
			index++;
		}

		return distinct;
	}

	/**
	 * Calculate memory usage.
	 * 
	 * @return memory usage.
	 */
	public int getMemoryUsage() {
		return 4 + this.alphabet.length + this.rootNode.getMemoryUsage();
	}

}
