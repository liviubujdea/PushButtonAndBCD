import serial
import numpy as np 
import time
import tkinter as tk 
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

data = np.array([])
cond = True
def plot():
    low_value = False
    medium_value = False
    big_value = False
    global cond, data
    if(cond == True):
        a = s.read()
        a.decode()
        string = a.rstrip()
        if(len(data) < 100):
            try:
                data = np.append(data, int(string))
                
                segment=int(string)
                s.reset_input_buffer()
                if(segment >= 1 and segment < 3):
                    lines.set_color(color= 'green')
                if(segment >= 3 and segment < 5):
                    lines.set_color(color= 'yellow')
                if(segment >= 5 and segment < 8):
                    lines.set_color(color= 'red')
            except:
                pass
        lines.set_xdata(np.arange(0, len(data)))
        lines.set_ydata(data) 
        
        canvas.draw()
    root.after(1500,plot)


root = tk.Tk()
root.title('Real Time plot')
root.configure(background= 'powderblue')
root.geometry("700x500")

fig = Figure()
ax = fig.add_subplot(111)

ax.set_title('Baleaj BCD')
ax.set_xlabel('Time')
ax.set_ylabel('Segment BCD')
ax.set_xlim(0, 70)
ax.set_ylim(1, 7)
lines = ax.plot([], [])[0]

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().place(x = 10, y = 10, width=600, height=400)
canvas.draw()

s = serial.Serial('COM9', 115200)
s.reset_input_buffer()

root.after(1500,plot)

root.mainloop()
