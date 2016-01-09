import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

/**
 * Run access method.
 * 
 * @author ICapalija
 * 
 */
public class RunAccess {

	public static String usageInfo = "usage: java RunAccess <filepath> <index>";

	public static void main(String[] args) {
		if (args.length != 2) {
			System.out.println("Number of arguments is not valid.\n" + usageInfo);
			System.exit(1);
		}
		
		int index = 0;
		try {
			index = Integer.parseInt(args[1]);
		} catch (Exception e) {
			System.out.println("Second argument must be integer.\n" + usageInfo);
			System.exit(1);
		}
		
		PrintWriter writer = null;
		try {
			writer = new PrintWriter("access_result.txt", "UTF-8");
		} catch (FileNotFoundException e) {
			System.out.println("Result filepath is not valid.");
			System.exit(1);
		} catch (UnsupportedEncodingException e) {
			System.out.println("Result file encoding is unsupported.");
			System.exit(1);
		}
		
		String filepath = args[0];
		
		//parse FASTA file
		String fileData = Parser.parseFASTA(filepath);
		
		

		long buildElapsedTime = System.currentTimeMillis();
		// build tree
		WaveletTree wt = new WaveletTree(fileData.getBytes());
		buildElapsedTime = System.currentTimeMillis() - buildElapsedTime;
		
		long accessElapsedTime = System.currentTimeMillis();
		//get letter on index
		char letter = (char) wt.access(index);
		accessElapsedTime = System.currentTimeMillis() - accessElapsedTime;
		
		StringBuilder builder = new StringBuilder();
		builder.append("Access result: ");
		builder.append(letter);
		builder.append('\n');
		builder.append('\n');
		builder.append("Access time: ");
		builder.append(accessElapsedTime);
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
