#!/usr/bin/python3

import serial
import datetime as dt
import matplotlib.pyplot as plt
import matplotlib.animation as animation

ser = serial.Serial("/dev/ttyUSB0", baudrate=115200) #, timeout=None)
#time.sleep(3)

# while 1:
#     serialData = ser.readline().decode('ascii')
#     print(serialData)

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []

# This function is called periodically from FuncAnimation
def animate(i, xs, ys):

    # Read temperature (Celsius) from TMP102
    serialData = ser.readline().decode('ascii')

    # Add x and y to lists
    xs.append(dt.datetime.now().strftime('%H:%M:%S.%f'))
    ys.append(serialData)

    # Limit x and y lists to 20 items
    xs = xs[-20:]
    ys = ys[-20:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, ys)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('ADC value over Time')
    plt.ylabel('Voltage (V)')

# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1000)
plt.show()
axes.set_xlim([-2.5, 7])
