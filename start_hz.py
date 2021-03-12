#!/usr/bin/env python3

import random
from itertools import count
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os
import subprocess
import sys
import time
import numpy as np

#plt.style.use('ggplot')

x_values = []
y_values = []

nlines = 0



filename = sys.argv[1]






def animate(i):
    global nlines
    global fig
    global plt1
    with open(filename, 'r') as file:
        data = file.readlines()
        dataset = []
        for line in data:
            tmp = [ float(i) for i in line.split() ]
            dataset.append(tmp)

    dataset = np.array(dataset)
    tmp1h,tmp1z,tmp1d = [],[],[]
    tmp2h,tmp2z,tmp2d = [],[],[]
    tmp3h,tmp3z,tmp3d = [],[],[]

    s1,s2,s3 = [],[],[]

    gh,gz=[],[]

    for i in dataset:
        if i[2] == 1:
            tmp1h.append(i[4])
            tmp1z.append(i[5])
            tmp1d.append(i[6])
            s1.append(i)
        if i[3] == 1:
            tmp2h.append(i[4])
            tmp2z.append(i[5])
            tmp2d.append(i[6])
            s2.append(i)

        if i[2] == 1 and i[3] == 1:
            tmp3h.append(i[4])
            tmp3z.append(i[5])
            tmp3d.append(i[6])
            gh.append(i[4])
            gz.append(i[5])
            s3.append(i)
    plt.cla()
    #N,U,c = plt.hist( x_values,histtype="step", bins=np.linspace(0,200,100),label="$N(E)$")

    if sys.argv[2] == '1':

        plt.hist(tmp3z, bins=100,histtype='stepfilled',ec='k', alpha=0.3, density=False)
        plt.xlabel("Distance [mm]")
        plt.title("Entries: {}".format(len(tmp3z)))
        plt.ylabel("counts")

    elif sys.argv[2] == '2':
        plt.hist(tmp1z,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k",label='detector A')
        plt.hist(tmp2z,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k",label='detector B')
        plt.title("Entries: {}".format(len(tmp1z)))
        plt.xlabel("Distance from the center [mm]")
        plt.ylabel("counts")
        plt.legend()
    #mean = (N*U[:-1]).sum()/N.sum()
    #plt.title("$E_m$= {} MeV".format(round(mean,4)))
    #plt.xlabel("$E [MeV]$")
    #plt.ylabel("$Counts$")
    #plt.legend()



if __name__ == "__main__":
    #os.system("./muon_run run.mac")
    subprocess.Popen(["./pet_run","run.mac"])
    time.sleep(1)
    ani = FuncAnimation(plt.gcf(), animate)
    plt.tight_layout()
    plt.show()
