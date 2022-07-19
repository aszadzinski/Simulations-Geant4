#!/usr/bin/env python3

import random
from itertools import count
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os
import subprocess
import time
import numpy as np

from sys import argv
#plt.style.use('ggplot')

x_values = []
y_values = []

nlines = 0

print("\nUSAGE: python3 start_new.py <data file>\n")
with open(argv[1],"r") as file:
    x = file.readlines()
    x_values = [ var.split() for var in x]
    X = np.array(x_values, dtype=float).T
    E = X[0] + X[1] #All events form left and right det.
    Tdet = X[2]; Tdet = Tdet[Tdet != 0] #only top det.
    Bdet = X[3]; Bdet = Bdet[Bdet != 0] #only bottom det.
    coiT = []# coincidences with L R and T det.
    coiB = []# coincidences with L R and B det.
    coiTB = []# coincidences with L R T and B det.
    for event in X.T:
        if (event[0] or event[1]) and event[2]: coiT.append(event[0]+event[1])
        if (event[0] or event[1]) and event[3]: coiB.append(event[0]+event[1])
        if (event[0] or event[1]) and event[2] and event[3]: coiTB.append(event[0]+event[1])
plt.cla()
bins=200
fig, ax = plt.subplots(2,2,figsize=(16,9))

ax[0,0].hist( E,histtype="step", bins=bins,label="CH0+CH1")

ax[0,1].hist(Tdet,histtype="step", bins=bins,label="Top det.")
ax[0,1].hist(Bdet,histtype="step", bins=bins,label="Bottom det")

ax[1,0].hist(coiT,histtype="step", bins=bins,label="Coi. CH1&CH2&CH3")
ax[1,0].hist(coiB,histtype="step", bins=bins,label="Coi. CH1&CH2&CH3")
ax[1,1].hist(coiTB,histtype="step", bins=bins,label="Coi. CH1&CH2&CH3&CH4")



ax[0,0].set_xlabel("$E [MeV]$")
ax[0,0].set_ylabel("$Counts$")
ax[0,1].set_xlabel("$E [MeV]$")
ax[0,1].set_ylabel("$Counts$")
ax[1,0].set_xlabel("$E [MeV]$")
ax[1,0].set_ylabel("$Counts$")
ax[1,1].set_xlabel("$E [MeV]$")
ax[1,1].set_ylabel("$Counts$")
ax[0,0].legend()
ax[0,1].legend()
ax[1,0].legend()
ax[1,1].legend()

ax[0,0].set_title("CH0/CH1")
ax[0,1].set_title("CH2/CH3")
ax[1,0].set_title("CH0/CH1")
ax[1,1].set_title("CH0/CH1")


print(f"Histogram saved to output.pdf")
fig.savefig("output.pdf")
