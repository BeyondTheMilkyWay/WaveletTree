import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

/**
 * Run rank method.
 * 
 * @author ICapalija
 * 
 */
public class RunRank {

	public static String usageInfo = "usage: java RunRank <filepath> <character> <index>";

	public static void main(String[] args) {
		if (args.length != 3) {
			System.out.println("Number of arguments is not valid.\n"
					+ usageInfo);
			System.exit(1);
		}

		if (args[1].length() != 1) {
			System.out.println("Second argument must be character.\n"
					+ usageInfo);
			System.exit(1);
		}
		byte character = (byte) args[1].charAt(0);

		int index = 0;
		try {
			index = Integer.parseInt(args[2]);
		} catch (Exception e) {
			System.out.println("Third argument must be integer.\n" + usageInfo);
			System.exit(1);
		}
		
		PrintWriter writer = null;
		try {
			writer = new PrintWriter("rank_result.txt", "UTF-8");
		} catch (FileNotFoundException e) {
			System.out.println("Result filepath is not valid.");
			System.exit(1);
		} catch (UnsupportedEncodingException e) {
			System.out.println("Result file encoding is unsupported.");
			System.exit(1);
		}

		String filepath = args[0];

		// parse FASTA file
		String fileData = Parser.parseFASTA(filepath);
		
		long buildElapsedTime = System.currentTimeMillis();
		// build tree
		WaveletTree wt = new WaveletTree(fileData.getBytes());
		buildElapsedTime = System.currentTimeMillis() - buildElapsedTime;
		
		long rankElapsedTime = System.currentTimeMillis();
		//calculate rank
		int rank = wt.rank(character, index);
		rankElapsedTime = System.currentTimeMillis() - rankElapsedTime;

		StringBuilder builder = new StringBuilder();
		builder.append("Rank result: ");
		builder.append(rank);
		builder.append('\n');
		builder.append('\n');
		builder.append("Rank time: ");
		builder.append(rankElapsedTime);
		builder.append(" ms\n");
		builder.append("Building tree time: ");
		builder.append(buildElapsedTime);
		builder.append(" ms\n");
		builder.append("Tree memory: ");
		builder.append(wt.getMemoryUsage());
		builder.append(" bytes\n");
		
		//write to result file
		writer.print(builder.toString());
		writer.close();
		
		//write to console
		System.out.print(builder.toString());
	}

}
