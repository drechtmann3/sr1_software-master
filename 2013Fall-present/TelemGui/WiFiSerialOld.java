import jssc.*;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Arrays;

/**
 *This class is designed to recieve data sent over WiFi and display it in a gui
 *
 *@author PK
 */
public class WiFiSerialOld {

	public static void main(String[] args) {
		
		byte[] message;
		//String message;
		
		SerialPortList spl = new SerialPortList();
		String[] portNames = spl.getPortNames();
		/*for (String portName : portNames) {
			System.out.println(portName);
		}*/
		if(portNames.length==0) {
			System.out.println("Serial device not connected");
			System.exit(0);
		}
		
		SerialPort serialPort = new SerialPort("COM11"/*portNames[0]*/);
		try {
			System.out.println("Port opened: " + serialPort.openPort());
			System.out.println("Params set: " + serialPort.setParams(115000, 8, 1, 0));//(int baudRate, int dataBits, int stopBits, int parity) 
			while(true) {
				message = serialPort.readBytes();
				if (message!=null) {
					//System.out.println(new String(message));
					System.out.println(Arrays.toString(message));
				} /*else {
					System.out.println("nothing");
				}*/
			}
			//System.out.println("Port closed: " + serialPort.closePort());
		}
		catch (SerialPortException ex){
			System.out.println(ex);
		}
		
		
	}
}