import gov.nasa.worldwind.*;
import gov.nasa.worldwind.avlist.AVKey;
import gov.nasa.worldwind.awt.*;
import gov.nasa.worldwind.event.*;
import gov.nasa.worldwind.exception.WWAbsentRequirementException;
import gov.nasa.worldwind.layers.*;
import gov.nasa.worldwind.layers.placename.PlaceNameLayer;
import gov.nasa.worldwind.util.*;
import gov.nasa.worldwindx.examples.util.*;
import gov.nasa.worldwindx.examples.LayerPanel;
import gov.nasa.worldwindx.examples.ClickAndGoSelectListener;

import javax.swing.*;
import java.awt.*;

public class Earth extends JPanel {

	protected WorldWindow wwd;
	protected StatusBar statusBar;
	protected ToolTipController toolTipController;
	protected HighlightController highlightController;
	protected LayerPanel layerPanel;

	public Earth() {
		super(new BorderLayout());

		this.wwd = new WorldWindowGLCanvas();
		//((Component) this.wwd).setPreferredSize(canvasSize);

		// Create the default model as described in the current worldwind properties.
		Model m = (Model) WorldWind.createConfigurationComponent(AVKey.MODEL_CLASS_NAME);
		this.wwd.setModel(m);

		// Setup a select listener for the worldmap click-and-go feature
		this.wwd.addSelectListener(new ClickAndGoSelectListener(this.getWwd(), WorldMapLayer.class));

		//add the worldwindow
		this.add((Component) this.wwd, BorderLayout.CENTER);
			
		//create and add the statusbar
		this.statusBar = new StatusBar();
		this.add(statusBar, BorderLayout.PAGE_END);
		this.statusBar.setEventSource(wwd);
			
		//create and add the layerpanel
		this.layerPanel = new LayerPanel(this.wwd, null);
		this.add(this.layerPanel, BorderLayout.WEST);

		// Create and install the view controls layer and register a controller for it with the World Window.
		ViewControlsLayer viewControlsLayer = new ViewControlsLayer();
		insertBeforeCompass(this.wwd, viewControlsLayer);
		this.wwd.addSelectListener(new ViewControlsSelectListener(this.wwd, viewControlsLayer));
			
		// Add controllers to manage highlighting and tool tips.
		this.toolTipController = new ToolTipController(this.getWwd(), AVKey.DISPLAY_NAME, null);
		this.highlightController = new HighlightController(this.getWwd(), SelectEvent.ROLLOVER);
	}
		
	public static void insertBeforeCompass(WorldWindow wwd, Layer layer) {
		// Insert the layer into the layer list just before the compass.
		int compassPosition = 0;
		LayerList layers = wwd.getModel().getLayers();
		for (Layer l : layers) {
			if (l instanceof CompassLayer) {
				compassPosition = layers.indexOf(l);
			}
		}
		layers.add(compassPosition, layer);
	}
	
	public WorldWindow getWwd() {
		return wwd;
	}

	public StatusBar getStatusBar() {
		return statusBar;
	}
		
	public LayerPanel getLayerPanel() {
		return layerPanel;
	}
	
}
