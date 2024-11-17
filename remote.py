import serial
import time
import tkinter as tk

# Set the serial port and baud rate
port = 'COM7'  # Change this to your Bluetooth module's COM port
baud = 9600

# Connect to the serial port
ser = serial.Serial(port, baud)

def send_command(command):
    ser.write(command.encode())

def forward():
    send_command('F')

def back():
    send_command('B')

def left():
    send_command('L')

def right():
    send_command('R')

def stop():
    send_command('S')

# Set up the GUI
root = tk.Tk()
root.title("Bluetooth Car Controller")

frame = tk.Frame(root)
frame.pack()

forward_button = tk.Button(frame, text="Forward", command=forward)
forward_button.grid(row=0, column=1)

left_button = tk.Button(frame, text="Left", command=left)
left_button.grid(row=1, column=0)

stop_button = tk.Button(frame, text="Stop", command=stop)
stop_button.grid(row=1, column=1)

right_button = tk.Button(frame, text="Right", command=right)
right_button.grid(row=1, column=2)

back_button = tk.Button(frame, text="Back", command=back)
back_button.grid(row=2, column=1)

root.mainloop()

# Close the serial port when the GUI is closed
ser.close()
