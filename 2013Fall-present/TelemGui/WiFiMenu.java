import javax.swing.*;
import java.awt.event.*;

/**
 * WiFiMenu allows the user quick access to additional options.
 * @author Pavel Komarov
 */
public class WiFiMenu extends JMenuBar {
	
	private JMenu menu;
	private JMenuItem saveData,saveLog,menuItem3;
	private int count=0;
	
	/**
	 * Creates the menu items and places them in a menu
	 */
	public WiFiMenu(){
		menu  = new JMenu("Options");
		this.add(menu);

		saveData = new JMenuItem("Save Telemetry Data");
		saveData.setAccelerator(KeyStroke.getKeyStroke(
			java.awt.event.KeyEvent.VK_S,java.awt.Event.CTRL_MASK));
		saveData.addActionListener(new MenuListener());
		menu.add(saveData);

		saveLog = new JMenuItem("Save Log");
		saveLog.setAccelerator(KeyStroke.getKeyStroke(
			java.awt.event.KeyEvent.VK_L,java.awt.Event.CTRL_MASK));
		saveLog.addActionListener(new MenuListener());
		menu.add(saveLog);
	}

	private class MenuListener implements ActionListener{
		public void actionPerformed(ActionEvent event){
			if (event.getSource()==saveData) {
				LogPanel.println("Saving data to ./data.txt");
				//MAKE CALL TO SOMEONE TO SAVE ALL THE DATA
			} else if (event.getSource()==saveLog) {
				LogPanel.saveLog();
			}
		} 
	}
	
}