import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
//import com.genlogic.*;

/**
 *This exists because DRY principle, but right now it is pretty empty and useless.
 *@author Pavel Komarov pkomarov@gatech.edu pvlkmrv@gmail.com 941-545-7573
 */
public abstract class WiFiPanel extends JPanel{

	public WiFiPanel() {
		addMouseListener(new WiFiPanelListener());
	}
	
	public void paintComponent(Graphics page){
		page.clearRect(0,0,getWidth(),getHeight());
	}
	
	private class WiFiPanelListener extends MouseAdapter {
		public void mouseClicked(MouseEvent event){
			int button = event.getButton();
			//event.getPoint() is a thing
			if (button==MouseEvent.BUTTON1){//left click
				
			}
			else if (button==MouseEvent.BUTTON3){//right click (button 2 is middle click)
				
			}
			repaint();
		}
	}



}