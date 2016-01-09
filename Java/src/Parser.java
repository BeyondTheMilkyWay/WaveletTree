import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 * File parsers.
 * 
 * @author ICapalija
 * 
 */
public class Parser {

	/**
	 * Parser for FASTA file.
	 * @param filepath filepath.
	 * @return concatenated file lines.
	 */
	public static String parseFASTA(String filepath) {

		StringBuilder builder = new StringBuilder();

		try (BufferedReader br = new BufferedReader(new FileReader(filepath))) {
			String line;
			while ((line = br.readLine()) != null) {
				if (line.startsWith(">")) {
					continue;
				}
				builder.append(line);
			}
		} catch (FileNotFoundException e) {
			System.out.println("Filepath is not valid.");
			System.exit(1);
		} catch (IOException e) {
			System.out.println("File is not in valid format.");
			System.exit(1);
		}

		return builder.toString();
	}

}
