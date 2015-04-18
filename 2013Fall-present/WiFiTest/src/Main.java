import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortList;



public class Main {
	static SerialPort  serialPort;
	/**
	 * Setup serial port.
	 */
	public static void init() {
		//Initialize datastructure

		//Make sure only one serial device is connected
		SerialPortList spl = new SerialPortList();
		String[] portNames = spl.getPortNames();
		if (portNames.length==0) {
			LogPanel.println("Serial device not connected. Connect and wait five seconds to proceed.");
		} else if (portNames.length!=1) {
			LogPanel.println("Too many serial ports connected. Disconnect all not connected to the wireless module");
		}
		while (portNames.length!=1) {
			portNames = spl.getPortNames();
			try {
				Thread.sleep(5000);
			} catch (InterruptedException ex) { 
				LogPanel.println("Who hath disturbed my slumber?"); 
			}
		}

		//Setup the serial connection
		serialPort = new SerialPort(portNames[0]);
		try {
			LogPanel.println("Port opened: " + serialPort.openPort());
			LogPanel.println("Params set: " + serialPort.setParams(115000, 8, 1, 0));//setParams(int baudRate, int dataBits, int stopBits, int parity)
		}
		catch (SerialPortException ex) {
			LogPanel.println("SerialPortException");
		}
	}

	
	//Testing sequence
	public static void main(String[] args) throws SerialPortException {
		init();
		while(true){
			System.out.println(serialPort.readString());
		}
		
		
	}
	
}