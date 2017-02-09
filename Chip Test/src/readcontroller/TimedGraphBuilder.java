package readcontroller;

import java.awt.Color;
import java.awt.Window;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.swing.JPanel;

public class TimedGraphBuilder extends GraphBuilder {

	public Calendar timeStarted;

	//разница между мкс и мин значениями
	protected float xAxisRange;
	protected float yAxisRange;

	public void resetTimeStarted() {
		timeStarted.clear();
	}
	
	public void setMaxXAxisRange(float r) {
		xAxisRange = r;
	}

	public void setMaxYAxisRange(float r) {
		yAxisRange = r;
	}

	public TimedGraphBuilder(int x0, int y0, int width, int height,
			JPanel parent, Window window) {
		super(x0, y0, width, height, parent, window);

	}

	@Override
	public void init(boolean run) {

		if (run) {
			super.init(run);
			timeStarted = new GregorianCalendar();
		}

	}

	public void draw() {

		int from = 0;

		for (Point p : pointArray) {
			if (p.x > xMinRangeValue) {
				break;
			}

			from++;
		}

		drawFromTo(from, pointArray.size());

	}

	@Override
	public void drawFromTo(int from, int to) {

		bufferStrategy = window.getBufferStrategy();
		g = bufferStrategy.getDrawGraphics();

		g.setColor(Color.black);
		g.fillRect(x0, y0, width, height);
		drawYAxis();
		drawXAxis();

		for (int i = from; i < to - 1; i++) {

			int xOffset = 0;
			if (i != 0)
				xOffset = (int) (pointArray.get(from).x * width / xAxisRange);

			g.drawLine(
					x0 + (int) (pointArray.get(i).x * width / xAxisRange)
							- xOffset,
					(int) (y0 + (1 - yPaddingBottomInPrc) * height - (int) pointArray
							.get(i).y
							* height
							* (1 - yPaddingBottomInPrc - yPaddingTopInPrc)
							/ yAxisRange),
					x0 + (int) (pointArray.get(i + 1).x * width / xAxisRange)
							- xOffset,
					y0
							+ (int) ((1 - yPaddingBottomInPrc) * height - pointArray
									.get(i + 1).y * height * (1 - yPaddingBottomInPrc - yPaddingTopInPrc) / yAxisRange));
		}

		g.dispose();
		bufferStrategy.show();

	}

	@Override
	public void addPoint(float value) {

		Calendar now = Calendar.getInstance();
		
		float xSecondsValue = (float) (now.getTimeInMillis() - timeStarted
				.getTimeInMillis()) / 1000;

		pointArray.add(new Point(value, xSecondsValue));

		if (xSecondsValue > xAxisRange) {
			setXAxisRange(xSecondsValue - xAxisRange, xSecondsValue);
		} else
			setXAxisRange(0, xSecondsValue);
		
		// System.out.println(pointArray.get(pointArray.size() - 1).x);
	}

	public Calendar getTimeStarted() {
		return timeStarted;
	}

	public void setTimeStarted(Calendar timeStarted) {
		this.timeStarted = timeStarted;
	}
	
	

}
