/**
 * Wavelet tree node implementation.
 * 
 * @author ICapalija
 * 
 */
public class WaveletNode {

	/**
	 * Bit storage.
	 */
	private BitArray data;
	/**
	 * Start index in sequence alphabet.
	 */
	private byte alphStart;
	/**
	 * End index in sequence alphabet.
	 */
	private byte alphEnd;
	/**
	 * Parent node.
	 */
	private WaveletNode parent;
	/**
	 * Left child.
	 */
	private WaveletNode leftChild;
	/**
	 * Right child.
	 */
	private WaveletNode rightChild;

	/**
	 * Wavelet node constructor.
	 * 
	 * @param dataLen
	 *            number of bits.
	 * @param alphStart
	 *            start index in sequence alphabet.
	 * @param alphEnd
	 *            end index in sequence alphabet.
	 */
	public WaveletNode(int dataLen, byte alphStart, byte alphEnd) {
		this.data = new BitArray(dataLen);
		this.alphStart = alphStart;
		this.alphEnd = alphEnd;
	}

	/**
	 * Wavelet node constructor.
	 * 
	 * @param dataLen
	 *            number of bits.
	 * @param alphStart
	 *            start index in sequence alphabet.
	 * @param alphEnd
	 *            end index in sequence alphabet.
	 * @param parent
	 *            parent node.
	 */
	public WaveletNode(int dataLen, byte alphStart, byte alphEnd,
			WaveletNode parent) {
		this(dataLen, alphStart, alphEnd);
		this.parent = parent;
	}

	/**
	 * Wavelet node constructor.
	 * 
	 * @param data
	 *            array of data.
	 * @param alphStart
	 *            start index in sequence alphabet.
	 * @param alphEnd
	 *            end index in sequence alphabet.
	 */
	public WaveletNode(BitArray data, byte alphStart, byte alphEnd) {
		this.data = data;
		this.alphStart = alphStart;
		this.alphEnd = alphEnd;
	}

	/**
	 * Get start index of node alphabet in main alphabet.
	 * 
	 * @return
	 */
	public byte getStartAlphabetIndex() {
		return this.alphStart;
	}

	/**
	 * Get end index of node alphabet in main alphabet.
	 * 
	 * @return
	 */
	public byte getEndAlphabetIndex() {
		return this.alphEnd;
	}

	/**
	 * Get data length.
	 * 
	 * @return data length.
	 */
	public int getDataLength() {
		return this.data.length();
	}

	/**
	 * Set parent node.
	 * 
	 * @param parent
	 *            parent node.
	 */
	public void setParent(WaveletNode parent) {
		this.parent = parent;
	}

	/**
	 * Get parent node.
	 * 
	 * @return parent node.
	 */
	public WaveletNode getParent() {
		return this.parent;
	}

	/**
	 * Get left node.
	 * 
	 * @return left node.
	 */
	public WaveletNode getLeftChild() {
		return leftChild;
	}

	/**
	 * Set left child.
	 * 
	 * @param leftChild
	 *            left child.
	 */
	public void setLeftChild(WaveletNode leftChild) {
		this.leftChild = leftChild;
	}

	/**
	 * Get right node.
	 * 
	 * @return right node.
	 */
	public WaveletNode getRightChild() {
		return rightChild;
	}

	/**
	 * Set right child.
	 * 
	 * @param rightChild
	 *            right child.
	 */
	public void setRightChild(WaveletNode rightChild) {
		this.rightChild = rightChild;
	}

	/**
	 * Set bit.
	 * 
	 * @param index
	 *            index.
	 * @param value
	 *            bit value.
	 */
	public void setBit(int index, boolean value) {
		this.data.set(index, value);
	}

	/**
	 * Get bit.
	 * 
	 * @param index
	 *            index.
	 * @return bit value.
	 */
	public boolean getBit(int index) {
		return data.get(index);
	}

	/**
	 * Count number of occurrences of bit of given type in prefix with given end
	 * index.
	 * 
	 * @param type
	 *            bit type.
	 * @param index
	 *            index.
	 * @return number of occurrences.
	 */
	public int countOccurrence(boolean type, int index) {
		return this.data.countOccurrence(type, index);
	}

	/**
	 * Finds index of <code>occurrenceNum</code>-th occurrence of given bit.
	 * 
	 * @param type
	 *            bit type.
	 * @param occurrenceNum
	 *            number of occurrences.
	 * @return end index of prefix.
	 */
	public int calcOccurrenceArrayLength(boolean type, int occurrenceNum) {
		return this.data.calcOccurrenceArrayLength(type, occurrenceNum);
	}

	/**
	 * String representation of node.
	 * 
	 * @return string representation.
	 */
	public String toString() {
		return this.data.toString();
	}

	/**
	 * Calculates memory usage.
	 * 
	 * @return memory usage.
	 */
	public int getMemoryUsage() {
		int memory = this.data.length() / 8;
		// add alphStart, alphEnd
		memory += 2;
		// pointer to parent, left, right node
		memory += 3 * 4;
		// ask left child
		if (this.leftChild != null) {
			memory += this.leftChild.getMemoryUsage();
		}
		// ask right child
		if (this.rightChild != null) {
			memory += this.rightChild.getMemoryUsage();
		}

		return memory;
	}
}
