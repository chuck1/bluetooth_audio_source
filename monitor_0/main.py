import time
import struct
import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import scipy.signal

arduino_size_int = 2
sample_size = 64
channels = 3
packet_size = sample_size * arduino_size_int * channels

plot_width = sample_size * 20



class Foo:
    def __init__(self):
        self.t = 0
        self.t_offset = 0

        self.T = []
        self.V_0 = []
        self.V_1 = []
        self.V_2 = []

        self.fmt = f"{sample_size * channels}h"

        try:
            self.ser = serial.Serial('COM3', 9600)
        except Exception as ex:
            print(ex)
            

    def construct(self):

        time.sleep(0.5)

        def f_V_ip(t):
            y = 0.1 * t

        def f(V_ip):
            G = 2
            return max(min(V_ip * G, 820), 720)

        T = np.arange(sample_size) + self.t

        V_non_inv_input = scipy.signal.sawtooth(T * 0.005, width=0.5) * 500 + 500
        
        #V_non_inv_input = np.linspace(0, 1024, sample_size)

        
        V_output = np.vectorize(f)(V_non_inv_input)
        V_inv_input = V_output / 2
        
        a = np.concatenate((
            np.reshape(V_inv_input,(-1,1)),
            np.reshape(V_non_inv_input,(-1,1)),
            np.reshape(V_output,(-1,1)),
            ),axis=1)

        b = np.reshape(a, (-1,))
        
        #print(np.shape(a))
        #print(np.shape(b))

        #print(V_non_inv_input)

        return struct.pack(self.fmt, *[int(_) for _ in b.tolist()])
    
    def read(self):

        #b = self.ser.read(packet_size)
        b = self.construct()

        a = np.array(struct.unpack(self.fmt, b))

        
        
        #print(np.shape(a))

        T = np.arange(sample_size) + self.t - self.t_offset
        
        self.t += sample_size
        
        V_inv_input = a[0::3]
        V_non_inv_input = a[1::3]
        V_output = a[2::3]
        
        #print(np.shape(T))
        #print(np.shape(V_inv_input))
        #print(np.shape(V_non_inv_input))

        

        return T, V_inv_input, V_non_inv_input, V_output        

foo = Foo()

fig, ax = plt.subplots()

ax.set_xlim(0, plot_width)
ax.set_ylim(0, 1024)

fig_1, ax_1 = plt.subplots()

ax_1.set_xlim(0, 1024)
ax_1.set_ylim(0, 1024)


V_0 = []

line_0, = ax.plot([], [], 'ro')
line_1, = ax.plot([], [], 'go')
line_2, = ax.plot([], [], 'bo')

lines_b = [
    ax_1.plot([], [], 'ro')[0],
    ax_1.plot([], [], 'go')[0],
    ax_1.plot([], [], 'bo')[0],
    ]
    

def update():

    T_temp, d_0, d_1, d_2 = foo.read()
    
    foo.T = np.concatenate((foo.T, T_temp))
    foo.V_0 = np.concatenate((foo.V_0, d_0))
    foo.V_1 = np.concatenate((foo.V_1, d_1))
    foo.V_2 = np.concatenate((foo.V_2, d_2))

    w = np.shape(foo.T)[0]

    
    
    if w > plot_width:
        foo.T = foo.T[plot_width:]
        foo.V_0 = foo.V_0[plot_width:]
        foo.V_1 = foo.V_1[plot_width:]
        foo.V_2 = foo.V_2[plot_width:]
        
        foo.T -= plot_width
        foo.t_offset += plot_width
    
    #print(np.shape(foo.T))
    #print(np.shape(foo.V_0))

    #print(foo.T)
    
    line_0.set_data(foo.T, foo.V_0)
    line_1.set_data(foo.T, foo.V_1)
    line_2.set_data(foo.T, foo.V_2)

    lines_b[0].set_data(foo.V_1, foo.V_1)
    lines_b[1].set_data(foo.V_1, foo.V_0)
    lines_b[2].set_data(foo.V_1, foo.V_2)
    
    
    fig.canvas.draw()
    fig.canvas.flush_events()
    fig_1.canvas.draw()
    fig_1.canvas.flush_events()

    return line_0, line_1, line_2,

##################

#plt.ion()

plt.show(block=False)

while True:
    update()







