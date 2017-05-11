package com.example.kristof.project2_android;

public class Timer {

    private final long length;
	private final long start;
	private long end;
	
	public Timer(long arg0) {
		this.length = arg0;
		this.start = System.currentTimeMillis();
		this.end = this.start + this.length;
	}
	
	public Timer() {
		this(0);
	}
	
	public static String format(final long time) {
		final int sec = (int) (time / 1000), h = sec / 3600, m = sec / 60 % 60, s = sec % 60;
		return (h < 10 ? "0" + h : h) + ":" + (m < 10 ? "0" + m : m) + ":" + (s < 10 ? "0" + s : s);
    }

	public long getElapsed() {
		return System.currentTimeMillis() - start;
	}

	public long getRemaining() {
		return isRunning() ? end - System.currentTimeMillis() : 0;
	}

	public boolean isRunning() {
		return System.currentTimeMillis() < end;
	}

	public void reset() {
		end = System.currentTimeMillis() + length;
	}

	public long setEndIn(long arg0) {
		end = System.currentTimeMillis() + arg0;
		return end;
	}

	public String toElapsedString() {
		return format(getElapsed());
	}

    public String toRemainingString() {
		return format(getRemaining());
	}
	
}