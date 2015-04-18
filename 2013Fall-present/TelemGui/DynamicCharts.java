import info.monitorenter.gui.chart.Chart2D;
import info.monitorenter.gui.chart.ITrace2D;
import info.monitorenter.gui.chart.traces.Trace2DLtd;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JComboBox;
import javax.swing.JPanel;

/**
 * Create a set of dynamic charts to be filled with data at different time intervals
 * 
 * @author Pavel Komarov & Achim Westermann
 */
public class DynamicCharts extends Container {

	private int timeScale = 0, chart = 0, numtraces = 3;
	private Color[] graphColors = { Color.blue, Color.red, Color.green, Color.yellow, Color.cyan, Color.magenta,
			Color.orange, Color.pink, Color.black, Color.darkGray };
	Chart2D[][] charts;
	String[] titles, ylabels, timeScales = { "1 second", "5 seconds", "30 seconds", "5 minutes" };
	JComboBox<String> timeScaleCombo, chartCombo;
	JPanel chartPanel;

	/**
	 * Charts are layered.
	 */
	public DynamicCharts(Device toMonitor, String... titlesAndYLabels) {
		this.setLayout(new BorderLayout());

		// Determine what individual charts the user wants
		int numgraphs = titlesAndYLabels.length / 2;
		titles = new String[numgraphs];
		ylabels = new String[numgraphs];
		int a = 0, b = 0;
		for (int i = 0; i < titlesAndYLabels.length; i++) {
			if (i % 2 == 0) {
				titles[a++] = titlesAndYLabels[i];
			} else {
				ylabels[b++] = titlesAndYLabels[i];
			}
		}

		// Create a charts array, fill it with those charts, format those charts,
		// fill the charts with traces, and set a panel to display a chart
		charts = new Chart2D[numgraphs][4];
		for (int i = 0; i < charts.length; i++) {
			for (int j = 0; j < 4; j++) { // create 4 charts for each title/y-data pair,
				Chart2D newChart = new Chart2D(); // each with a different update interval
				newChart.setGridColor(Color.lightGray);
				newChart.getAxisX().setPaintGrid(true);
				newChart.getAxisY().setPaintGrid(true);
				newChart.getAxisX().getAxisTitle().setTitle(timeScales[j] + " increments");
				newChart.getAxisY().getAxisTitle().setTitle(ylabels[i]);
				charts[i][j] = newChart;
				for (int k = 0; k < numtraces; k++) {
					ITrace2D trace = new Trace2DLtd(120); // 120 datapoints to each trace
					trace.setColor(graphColors[k % graphColors.length]);
					trace.setVisible(true);
					charts[i][j].addTrace(trace);
				}
			}
		}
		// chartPanel = new JPanel();
		// chartPanel.add(charts[chart][timeScale]); // default to first chart
		this.add(charts[chart][timeScale], BorderLayout.CENTER);

		// Create a panel for user controls
		JPanel controlPanel = new JPanel();
		timeScaleCombo = new JComboBox<>();
		chartCombo = new JComboBox<>(); // These will allow the user to specify which
		for (String str : timeScales) { // chart they want to see and at which timescale
			timeScaleCombo.addItem(str);
		}
		for (int i = 0; i < titles.length; i++) {
			chartCombo.addItem(titles[i]);
		}
		controlPanel.add(timeScaleCombo);
		controlPanel.add(chartCombo);
		timeScaleCombo.addActionListener(new comboListener());
		chartCombo.addActionListener(new comboListener());
		this.add(controlPanel, BorderLayout.SOUTH);

		// Dynamically add new datapoints
		Timer timer = new Timer(true);
		TimerTask task = new TimerTask() {
			private long m_starttime = System.currentTimeMillis();
			private double[][][] m_y = new double[charts.length][4][numtraces];

			// ^i ^j ^k
			@Override
			public void run() {
				long elapsed = (System.currentTimeMillis() - (this.m_starttime + 500)) / 100;// in tenths of a second
				int toUpdate;
				if (elapsed % 3000 == 0) {
					toUpdate = 4;
				} else if (elapsed % 300 == 0) {
					toUpdate = 3;
				} else if (elapsed % 50 == 0) {
					toUpdate = 2;
				} else {
					toUpdate = 1;
				}
				// /byte[] deviceData = WiFiSerial.read(toMonitor);//get device data
				for (int i = 0; /* ///deviceData!=null && */i < charts.length; i++) {
					for (int j = 0; j < toUpdate; j++) {
						int k = 0;
						for (ITrace2D trace : charts[i][j].getTraces()) {
							boolean add = (Math.random() > 0.5) ? true : false;// random data
							m_y[i][j][k] = (add) ? m_y[i][j][k] + Math.random() : m_y[i][j][k] - Math.random();
							// /m_y[i][j][k] = deviceData[100*i + k];//SOMETHING TO PARSE DATA CORRECTLY
							trace.addPoint(((double) elapsed), m_y[i][j][k]);
							k++;
						}
					}
				}
			}// end run()
		};// end TimerTask
		timer.schedule(task, 500, 1000);// Start collecting at 500ms and add new every second.
	}// end constructor

	// ---------------------------------------------------------------private listener classes
	private class comboListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			chartPanel.removeAll();
			if (e.getSource() == timeScaleCombo) {
				Object cmd = timeScaleCombo.getSelectedItem();
				for (int i = 0; i < timeScales.length; i++) {
					if (cmd.equals(timeScales[i])) {
						timeScale = i;
					}
				}
			} else if (e.getSource() == chartCombo) {
				Object cmd = chartCombo.getSelectedItem();
				for (int i = 0; i < titles.length; i++) {
					if (cmd.equals(titles[i])) {
						chart = i;
					}
				}
			}
			chartPanel.add(charts[chart][timeScale], BorderLayout.CENTER);
			chartPanel.repaint(); // forces the panel to redraw so visual changes are fast
			DynamicCharts.this.validate(); // forces the container to redraw itself. Without
		} // this the changes made here are not displayed
	}

}