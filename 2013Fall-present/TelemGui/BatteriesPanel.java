import java.awt.GridLayout;

public class BatteriesPanel extends WiFiPanel {

	public BatteriesPanel() {
		setLayout(new GridLayout(3, 1));
		add(new DynamicCharts(Device.BMS, "Temperatures", "Degrees Celsius", "Voltages", "mV"));
		add(new DynamicCharts(Device.BMS, "Temperatures", "Degrees Celsius", "Voltages", "mV"));
		add(new DynamicCharts(Device.BMS, "Temperatures", "Degrees Celsius", "Voltages", "mV"));
	}

}