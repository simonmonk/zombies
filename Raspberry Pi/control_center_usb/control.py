from Tkinter import *
import serial
import time

BAUD = 9600
PORT = "/dev/ttyACM0"

MIN_VOLTS = 11.0
TEMP_MIN = -10.0
TEMP_MAX = 45.0

class App:
    
    def __init__(self, master):
        self.frame = Frame(master)
        self.frame.pack()
        
        Label(self.frame, text='Volts').grid(row=0, column=0, sticky=E)
        self.volts_var = StringVar()
        self.volts_label = Label(self.frame, textvariable=self.volts_var)
        self.volts_label.grid(row=0, column=1)
        
        Label(self.frame, text='Temperature').grid(row=1, column=0, sticky=E)
        self.temp_var = StringVar()
        self.temp_label = Label(self.frame, textvariable=self.temp_var)
        self.temp_label.grid(row=1, column=1)
        
        Label(self.frame, text='Door').grid(row=2, column=0, sticky=E)
        self.door_var = StringVar()
        self.door_label = Label(self.frame, textvariable=self.door_var)
        self.door_label.grid(row=2, column=1)
        
        Label(self.frame, text='PIR').grid(row=3, column=0, sticky=E)
        self.pir_var = StringVar()
        self.pir_label = Label(self.frame, textvariable=self.pir_var)
        self.pir_label.grid(row=3, column=1)
        
        Label(self.frame, text='Fire').grid(row=4, column=0, sticky=E)
        self.fire_var = StringVar()
        self.fire_label = Label(self.frame, textvariable=self.fire_var)
        self.fire_label.grid(row=4, column=1)
        
        self.ser = serial.Serial(PORT, BAUD, timeout=1)
        time.sleep(2)
        


    def read_arduino(self):
        self.ser.write('?')
        volts, temp, door, pir, fire = self.ser.readline().split()
        self.volts_var.set(volts)
        self.temp_var.set(temp)
        self.door_var.set(door)
        self.pir_var.set(pir)
        self.fire_var.set(fire)
        if float(volts) < MIN_VOLTS:
            self.volts_label.configure(bg = "red")
        else:
            self.volts_label.configure(bg = "green")
            
        if float(temp) < TEMP_MIN or float(temp) > TEMP_MAX:
            self.temp_label.configure(bg = "red")
        else:
            self.temp_label.configure(bg = "green")
            
        if door == "1":
            self.door_label.configure(bg = "red")
        else:
            self.door_label.configure(bg = "green")
        
        if pir == "1":
            self.pir_label.configure(bg = "red")
        else:
            self.pir_label.configure(bg = "green")
        
        if fire == "1":
            self.fire_label.configure(bg = "red")
        else:
            self.fire_label.configure(bg = "green")        


root = Tk()
root.wm_title('Control')
app = App(root)

def update():
    app.read_arduino()
    root.after(500, update) 

root.after(100, update)


root.mainloop()