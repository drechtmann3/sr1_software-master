import java.awt.Toolkit;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;

/**
 * 
 * @author Pavel Komarov pkomarov@gatech.edu pvlkmrv@gmail.com 941-545-7573
 * @author Andrey Kurenkov
 */

public class Main {

	private static JFrame frame;

	public static void main(String... args) {
		frame = new JFrame("Marathon Mobile 1.0");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
		Toolkit tk = Toolkit.getDefaultToolkit();
		int xSize = ((int) tk.getScreenSize().getWidth());
		int ySize = ((int) tk.getScreenSize().getHeight());
		frame.setSize(xSize, ySize);
		frame.setContentPane(makeTabs());
		frame.setJMenuBar(new WiFiMenu());
		frame.setVisible(true);
		frame.pack();
		// /WiFiSerial.init();
		Timer timer = new Timer(true);
		TimerTask task = new TimerTask() {// set to read every second
			@Override
			public void run() { /* ///WiFiSerial.read(); */
			}
		};
		timer.schedule(task, 100, 1000);
	}

	private static JTabbedPane makeTabs() {
		JTabbedPane tabs = new JTabbedPane();
		tabs.addTab("Overview", new JScrollPane(new OverviewPanel()));
		tabs.addTab("Batteries", new JScrollPane(new BatteriesPanel()));
		tabs.addTab("Motor", new JScrollPane(new MotorPanel()));
		tabs.addTab("Solar", new JScrollPane(new SolarPanel()));
		tabs.addTab("Telemetry", new JScrollPane(new TelemetryPanel()));
		tabs.addTab("Earth", new Earth());
		tabs.addTab("Log", new JScrollPane(new LogPanel()));
		return tabs;
	}

}