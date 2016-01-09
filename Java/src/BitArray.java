import java.io.ByteArrayOutputStream;
import java.util.Arrays;

/**
 * A packed array of booleans.
 * 
 * @author Joshua Bloch
 * @author Douglas Hoover
 * @author ICapalija (modified 08.01.2016)
 */
public class BitArray {

	/**
	 * Bit storage.
	 */
	private byte[] repn;
	/**
	 * Number of 1 bits in blocks.
	 */
	private byte[] positiveNum;
	/**
	 * Size of bit storage.
	 */
	private int length;

	/**
	 * Bits per unit.
	 */
	private static final int BITS_PER_UNIT = 8;

	/**
	 * Number of units in given length.
	 * 
	 * @param idx
	 *            length.
	 * @return number of units.
	 */
	private static int subscript(int idx) {
		return idx / BITS_PER_UNIT;
	}

	/**
	 * Position in storage array.
	 * 
	 * @param idx
	 *            index.
	 * @return position in storage array.
	 */
	private static int position(int idx) { // bits big-endian in each unit
		return 1 << (BITS_PER_UNIT - 1 - (idx % BITS_PER_UNIT));
	}

	/**
	 * Creates a BitArray of the specified size, initialized to zeros.
	 * 
	 * @param length
	 *            size of storage.
	 */
	public BitArray(int length) throws IllegalArgumentException {
		if (length < 0) {
			throw new IllegalArgumentException("Negative length for BitArray");
		}

		this.length = length;
		repn = new byte[(length + BITS_PER_UNIT - 1) / BITS_PER_UNIT];
		int blockSize = (int) Math.ceil(Math.log(this.length) / Math.log(2));
		this.positiveNum = new byte[this.length / blockSize + 1];
	}

	/**
	 * Creates a BitArray of the specified size, initialized from the specified
	 * byte array. The most significant bit of a[0] gets index zero in the
	 * BitArray. The array a must be large enough to specify a value for every
	 * bit in the BitArray. In other words, 8*a.length <= length.
	 * 
	 * @param length
	 *            number of bits to store.
	 * @param data
	 *            bits to store.
	 */
	public BitArray(int length, byte[] data) throws IllegalArgumentException {

		if (length < 0) {
			throw new IllegalArgumentException("Negative length for BitArray");
		}
		if (data.length * BITS_PER_UNIT < length) {
			throw new IllegalArgumentException(
					"Byte array too short to represent "
							+ "bit array of given length");
		}

		this.length = length;

		int repLength = ((length + BITS_PER_UNIT - 1) / BITS_PER_UNIT);
		int unusedBits = repLength * BITS_PER_UNIT - length;
		byte bitMask = (byte) (0xFF << unusedBits);

		/*
		 * normalize the representation: 1. discard extra bytes 2. zero out
		 * extra bits in the last byte
		 */
		repn = new byte[repLength];
		int blockSize = (int) Math.ceil(Math.log(this.length) / Math.log(2));
		this.positiveNum = new byte[blockSize];
		System.arraycopy(data, 0, repn, 0, repLength);
		if (repLength > 0) {
			repn[repLength - 1] &= bitMask;
		}
	}

	/**
	 * Create a BitArray whose bits are those of the given array of Booleans.
	 * 
	 * @param bits
	 *            bits to store.
	 */
	public BitArray(boolean[] bits) {
		length = bits.length;
		repn = new byte[(length + 7) / 8];
		int blockSize = (int) Math.ceil(Math.log(this.length) / Math.log(2));
		this.positiveNum = new byte[blockSize];

		for (int i = 0; i < length; i++) {
			set(i, bits[i]);
		}
	}

	/**
	 * Copy constructor (for cloning).
	 * 
	 * @param bitArray
	 *            clone.
	 */
	private BitArray(BitArray bitArray) {
		length = bitArray.length;
		repn = bitArray.repn.clone();
		int blockSize = (int) Math.ceil(Math.log(this.length) / Math.log(2));
		this.positiveNum = new byte[blockSize];
	}

	/**
	 * Returns the indexed bit in this BitArray.
	 * 
	 * @param index
	 *            index.
	 * @return bit.
	 */
	public boolean get(int index) throws ArrayIndexOutOfBoundsException {
		if (index < 0 || index >= length) {
			throw new ArrayIndexOutOfBoundsException(Integer.toString(index));
		}

		return (repn[subscript(index)] & position(index)) != 0;
	}

	/**
	 * Sets the indexed bit in this BitArray.
	 * 
	 * @param index
	 *            index.
	 * @param value
	 *            value.
	 */
	public void set(int index, boolean value)
			throws ArrayIndexOutOfBoundsException {
		if (index < 0 || index >= length) {
			throw new ArrayIndexOutOfBoundsException(Integer.toString(index));
		}
		int idx = subscript(index);
		int bit = position(index);

		if (value) {
			repn[idx] |= bit;
			int blockSize = (int) Math
					.ceil(Math.log(this.length) / Math.log(2));
			this.positiveNum[index / blockSize] += 1;
		} else {
			repn[idx] &= ~bit;
		}
	}

	/**
	 * Returns the length of this BitArray.
	 * 
	 * @return length;
	 */
	public int length() {
		return length;
	}

	/**
	 * Returns a Byte array containing the contents of this BitArray. The bit
	 * stored at index zero in this BitArray will be copied into the most
	 * significant bit of the zeroth element of the returned byte array. The
	 * last byte of the returned byte array will be contain zeros in any bits
	 * that do not have corresponding bits in the BitArray. (This matters only
	 * if the BitArray's size is not a multiple of 8.)
	 * 
	 * @return byte array.
	 */
	public byte[] toByteArray() {
		return repn.clone();
	}

	/**
	 * Compares two objects.
	 * 
	 * @return <code>true</code> if equals, else <code>false</code>.
	 */
	public boolean equals(Object obj) {
		if (obj == this)
			return true;
		if (obj == null || !(obj instanceof BitArray))
			return false;

		BitArray ba = (BitArray) obj;

		if (ba.length != length)
			return false;

		for (int i = 0; i < repn.length; i += 1) {
			if (repn[i] != ba.repn[i])
				return false;
		}
		return true;
	}

	/**
	 * Return a boolean array with the same bit values a this BitArray.
	 * 
	 * @return array.
	 */
	public boolean[] toBooleanArray() {
		boolean[] bits = new boolean[length];

		for (int i = 0; i < length; i++) {
			bits[i] = get(i);
		}
		return bits;
	}

	/**
	 * Returns a hash code value for this bit array.
	 * 
	 * @return a hash code value for this bit array.
	 */
	public int hashCode() {
		int hashCode = 0;

		for (int i = 0; i < repn.length; i++)
			hashCode = 31 * hashCode + repn[i];

		return hashCode ^ length;
	}

	/**
	 * Clone object.
	 * 
	 * @return clone.
	 */
	public Object clone() {
		return new BitArray(this);
	}

	/**
	 * Count number of occurrences of bit in prefix with given end index.
	 * 
	 * @param type
	 *            bit type.
	 * @param index
	 *            index.
	 * @return number of occurrences.
	 */
	public int countOccurrence(boolean type, int index) {
		int blockSize = (int) Math.ceil(Math.log(this.length) / Math.log(2));
		int blockNum = index / blockSize;
		int counter = 0;

		// count occurrences with precomputed blocks
		for (int i = 0; i < blockNum; i++) {
			if (type) {
				counter += this.positiveNum[i];
			} else {
				counter += blockSize - this.positiveNum[i];
			}
		}

		// count occurrences in last block
		int endBits = index % blockSize;
		for (int i = 0; i < endBits; i++) {
			if (type == this.get(blockNum * blockSize + i)) {
				counter++;
			}
		}

		return counter;
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
	public int calcOccurrenceArrayLength(boolean type, int occurranceNum) {
		int blockSize = (int) Math.ceil(Math.log(this.length) / Math.log(2));
		int occurrances = 0;
		int counter = 0;

		// count occurrences with precomputed blocks
		for (int i = 0; i < this.positiveNum.length; i++) {
			int update = 0;
			if (type) {
				update = this.positiveNum[i];
			} else {
				update = blockSize - this.positiveNum[i];
			}

			if (occurrances + update >= occurranceNum
					|| i == this.positiveNum.length - 1) {// if last block
				break;
			} else {
				occurrances += update;
				counter += blockSize;
			}
		}

		// count occurrences in last block
		for (int i = counter; i < this.length; i++) {
			if (occurrances >= occurranceNum) {
				break;
			}
			if (type == this.get(i)) {
				occurrances++;
			}
			counter++;
		}
		return counter - 1;
	}

	private static final byte[][] NYBBLE = {
			{ (byte) '0', (byte) '0', (byte) '0', (byte) '0' },
			{ (byte) '0', (byte) '0', (byte) '0', (byte) '1' },
			{ (byte) '0', (byte) '0', (byte) '1', (byte) '0' },
			{ (byte) '0', (byte) '0', (byte) '1', (byte) '1' },
			{ (byte) '0', (byte) '1', (byte) '0', (byte) '0' },
			{ (byte) '0', (byte) '1', (byte) '0', (byte) '1' },
			{ (byte) '0', (byte) '1', (byte) '1', (byte) '0' },
			{ (byte) '0', (byte) '1', (byte) '1', (byte) '1' },
			{ (byte) '1', (byte) '0', (byte) '0', (byte) '0' },
			{ (byte) '1', (byte) '0', (byte) '0', (byte) '1' },
			{ (byte) '1', (byte) '0', (byte) '1', (byte) '0' },
			{ (byte) '1', (byte) '0', (byte) '1', (byte) '1' },
			{ (byte) '1', (byte) '1', (byte) '0', (byte) '0' },
			{ (byte) '1', (byte) '1', (byte) '0', (byte) '1' },
			{ (byte) '1', (byte) '1', (byte) '1', (byte) '0' },
			{ (byte) '1', (byte) '1', (byte) '1', (byte) '1' } };

	private static final int BYTES_PER_LINE = 8;

	/**
	 * Returns a string representation of this BitArray.
	 * 
	 * @return string representation.
	 */
	public String toString() {
		ByteArrayOutputStream out = new ByteArrayOutputStream();

		for (int i = 0; i < repn.length - 1; i++) {
			out.write(NYBBLE[(repn[i] >> 4) & 0x0F], 0, 4);
			out.write(NYBBLE[repn[i] & 0x0F], 0, 4);

			if (i % BYTES_PER_LINE == BYTES_PER_LINE - 1) {
				out.write('\n');
			}
		}

		// in last byte of repn, use only the valid bits
		for (int i = BITS_PER_UNIT * (repn.length - 1); i < length; i++) {
			out.write(get(i) ? '1' : '0');
		}

		String bits = new String(out.toByteArray());
		StringBuilder builder = new StringBuilder();
		for (int i = 0; i < this.length; i++) {
			builder.append(bits.charAt(i));
		}
		return builder.toString();
	}

	/**
	 * Truncates array on multiplier of <code>BITS_PER_UNIT</code>.
	 * 
	 * @return truncated array.
	 */
	public BitArray truncate() {
		for (int i = length - 1; i >= 0; i--) {
			if (get(i)) {
				return new BitArray(i + 1, Arrays.copyOf(repn,
						(i + BITS_PER_UNIT) / BITS_PER_UNIT));
			}
		}
		return new BitArray(1);
	}

}
