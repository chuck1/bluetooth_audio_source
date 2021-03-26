import time
import struct
import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import scipy.signal

arduino_size_int = 2



class Foo:
    def __init__(self, channels, samples, plot_width):
        
        self.channels = channels
        self.samples = samples

        self.packet_size = samples * arduino_size_int * channels
        
        self.plot_width = plot_width #samples * 60

        
        self.t = 0
        self.t_offset = 0

        self.T = []
        self.V = [[],[],[]]
        
        self.fmt = f"{samples * channels}h"
        
        self.ser = None
        try:
            self.ser = serial.Serial('COM3', 19200)
        except Exception as ex:
            print(ex)
        

    def construct(self):

        time.sleep(0.5)

        def f_V_ip(t):
            y = 0.1 * t

        def f(V_ip):
            G = 2
            return max(min(V_ip * G, 820), 720)

        T = np.arange(self.samples) + self.t

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
        if self.ser is not None:
            b = self.ser.read(self.packet_size)
        else:
            b = self.construct()
        
        a = np.array(struct.unpack(self.fmt, b))
        
        #print(np.shape(a))
        
        T = np.arange(self.samples) + self.t - self.t_offset
        
        self.t += self.samples
        
        V_inv_input = a[0::3]
        V_non_inv_input = a[1::3]
        V_output = a[2::3]
        
        #print(np.shape(T))
        #print(np.shape(V_inv_input))
        #print(np.shape(V_non_inv_input))

        return T, [V_inv_input, V_non_inv_input, V_output]

        

    def update(self):

        T_temp, V = self.read()
        
        self.T = np.concatenate((self.T, T_temp))

        for i in range(3):
            self.V[i] = np.concatenate((self.V[i], V[i]))
        
        w = np.shape(self.T)[0]
        
        if w > self.plot_width:
            self.T = self.T[self.plot_width:]
            for i in range(len(self.V)):
                self.V[i] = self.V[i][self.plot_width:]
            
            self.T -= self.plot_width
            self.t_offset += self.plot_width
        
        #print(np.shape(foo.T))
        #print(np.shape(foo.V_0))

        #print(foo.T)

        for i in range(len(self.V)):
            self.lines_a[i].set_data(self.T, self.V[i])
            self.lines_b[i].set_data(self.V[1], self.V[i])
        
        
        self.fig.canvas.draw()
        self.fig.canvas.flush_events()
        

        

    def setup_plots(self, xlim_1):

        
        self.fig, (ax_0, ax_1) = plt.subplots(1, 2)

        ax_0.set_xlim(0, self.plot_width)
        ax_0.set_ylim(0, 1024)

        ax_1.set_xlim(xlim_1)
        ax_1.set_ylim(0, 1024)

        V_0 = []

        self.lines_a = [
            ax_0.plot([], [], 'ro', markersize=2)[0],
            ax_0.plot([], [], 'go', markersize=2)[0],
            ax_0.plot([], [], 'bo', markersize=2)[0],
            ]

        self.lines_b = [
            ax_1.plot([], [], 'ro', markersize=2, label="A4 (non-inv input)")[0],
            ax_1.plot([], [], 'go', markersize=2, label="A5 (inv input)")[0],
            ax_1.plot([], [], 'bo', markersize=2, label="A3 (output)")[0],
            ]

        ax_1.set_xlabel("A4")
        ax_1.set_ylabel("A3, A5")
        
        plt.legend()        

#########################

def main(xlim_1=[0, 1024]):

    foo = Foo(3, 32, 2000)

    foo.setup_plots(xlim_1)
    
    plt.show(block=False)

    while True:
        foo.update()

########################

main()






