import javax.swing.JTextArea;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Color;
import java.io.PrintWriter;
import java.io.FileNotFoundException;

public class LogPanel extends WiFiPanel{

	private static JTextArea text;//I do not like having this static, but it works

	public LogPanel() {
		text = new JTextArea();
		text.setColumns(100);
		text.setRows(500);
		text.setFont(new Font("Monospaced",Font.BOLD,14));
		text.setLineWrap(true);
		this.add(text);
	}
	
	/**
	 * Based on System.out.print
	 */
	public static void print(String str) {
		text.append(str);
	}

	/**
	 * Based on System.out.println
	 */
	public static void println(String str) {
		text.append(str + "\n");
	}
	
	/**
	 * Save the session log text to a file
	 */
	public static void saveLog() {
		try {
			PrintWriter pw = new PrintWriter("log.txt");
			pw.print(text.getText());
			pw.close();
		} catch (FileNotFoundException ex) {}
	}
}