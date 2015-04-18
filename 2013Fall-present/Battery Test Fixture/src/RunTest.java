import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

import jssc.SerialPort;
import jssc.SerialPortException;

public class RunTest {

	final static String OPEN_RELAY = "0";
	final static String CLOSE_RELAY = "1";
	final static String MEASURE_VOLTAGE = "MEAS:VOLT:DC? 10,0.003";
	final static String SEND_MEASUREMENT = "bus enter statement";
	final static double RELAY_OPEN_TIME = 5;
	final static double MULTIMETER_WAIT_TIME = 0.1;

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter multimeter port number: ");
		String multPortName = "COM" + scan.nextLine();
		System.out.println("Enter arduino port (COM<#>): ");
		String arduinoPortName = "COM" + scan.nextLine();
		SerialPort multimeterPort = new SerialPort(multPortName);
		SerialPort arduinoPort = new SerialPort(arduinoPortName);
		int count = 0;
		try {
			System.out.println("Multimeter port opened: " + multimeterPort.openPort());
			System.out.println("Arduino port opened: " + arduinoPort.openPort());
			System.out.println("Multimeter params set: " + multimeterPort.setParams(115000, 8, 1, 0));
			System.out.println("Arduino params set: " + arduinoPort.setParams(115000, 8, 1, 0));

			System.out.println("Enter file name to save values to. Q to quit.");
			String name = scan.nextLine();
			if (!name.equals("Q")) {
				PrintWriter writer = new PrintWriter(name);
				while (true) {
					System.out.println("Press enter to read next voltage. Q to quit.");
					String input = scan.nextLine();
					if (input.equals("Q"))
						break;
					arduinoPort.writeString(OPEN_RELAY);
					System.out.println("Relay open command sent.");
					long startTime = System.nanoTime();
					long time = System.nanoTime();
					while ((time - startTime) / Math.pow(10, 9) < RELAY_OPEN_TIME) {
						time = System.nanoTime();
					}
					multimeterPort.writeString(MEASURE_VOLTAGE);
					multimeterPort.writeString(SEND_MEASUREMENT);
					System.out.println("Measurement command sent.");
					startTime = System.nanoTime();
					time = System.nanoTime();
					while ((time - startTime) / Math.pow(10, 9) < MULTIMETER_WAIT_TIME) {
						time = System.nanoTime();
					}
					String measurement = multimeterPort.readString();
					System.out.println("Read in voltage value " + measurement + ".\n");
					writer.write(count + " " + measurement + "\n");
					System.out.println("Press enter to close relay. Q to quit.");
					input = scan.nextLine();
					if (input.equals("Q"))
						break;
					arduinoPort.writeString(OPEN_RELAY);
					System.out.println("Relay close command sent.");
				}
				writer.close();
			}
			System.out.println("\nExiting program");
			System.out.println("Port closed: " + multimeterPort.closePort());
			System.out.println("Port closed: " + arduinoPort.closePort());
		} catch (SerialPortException ex) {
			System.out.println(ex);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}
