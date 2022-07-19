#!/usr/bin/env python3

import random
from itertools import count
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os
import subprocess
import time
import numpy as np

#plt.style.use('ggplot')

x_values = []
y_values = []

nlines = 0


def animate(i):
    global nlines
    with open("output.dat","r") as file:
        x = file.readlines()
        x_values = [ var.split() for var in x]
        X = np.array(x_values, dtype=float).T
        E = X[0] + X[1]
    plt.cla()
    N,U,c = plt.hist( E,histtype="step", bins=np.linspace(0,200,100),label="$N(E)$")
    mean = (N*U[:-1]).sum()/N.sum()
    plt.title("$E_m$= {} MeV".format(round(mean,4)))
    plt.xlabel("$E [MeV]$")
    plt.ylabel("$Counts$")
    plt.legend()


if __name__ == "__main__":
    #os.system("./muon_run run.mac")
    subprocess.Popen(["./muon_run","run.mac"])
    time.sleep(1)
    ani = FuncAnimation(plt.gcf(), animate)
    plt.tight_layout()
    plt.show()
