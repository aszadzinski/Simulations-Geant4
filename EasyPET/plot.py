#!/usr/bin/env python3

import random
from itertools import count
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os, sys
import subprocess
import time
import numpy as np

#plt.style.use('ggplot')

filename = sys.argv[1]

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

plt.hist(tmp1z,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k",label='detector A')
plt.hist(tmp2z,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k",label='detector B')
plt.xlabel("Distance from the center [mm]")
plt.ylabel("counts")
plt.legend()
plt.savefig("distance.pdf")

plt.clf()

plt.hist(tmp1h,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k",label='detector A')
plt.xlabel("Height above axis of the detectors [mm]")
plt.ylabel("counts")
plt.legend()
plt.savefig("A_height.pdf")

plt.clf()

plt.hist(tmp2h,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k",label='detector B')
plt.xlabel("Height above axis of the detectors [mm]")
plt.ylabel("counts")
plt.legend()
plt.savefig("B_height.pdf")
plt.clf()

plt.hist(tmp3h,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k")
plt.xlabel("Height [mm]")
plt.ylabel("counts")
plt.title("Photon coincidence")
plt.savefig("Coi_height.pdf")

plt.clf()

plt.hist(tmp3z,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k")
plt.xlabel("Distance [mm]")
plt.ylabel("counts")
plt.title("Photon coincidence")
plt.savefig("Coi_distance.pdf")

plt.clf()

plt.hist2d(gh,gz,[40,40],[[-20,20],[-20,20]])
plt.xlabel("x [mm]")
plt.ylabel("y [mm]")
plt.title("Object reconstruct")
plt.savefig("reconstruct.pdf")


