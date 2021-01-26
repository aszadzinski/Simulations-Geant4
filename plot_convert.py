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
filename2 = sys.argv[2]
filename3 = sys.argv[3]

with open(filename3, 'r') as file:
    data = file.readlines()
    dataset3 = []
    for line in data:
        tmp = [ float(i) for i in line.split() ]
        dataset3.append(tmp)

dataset3 = np.array(dataset3)
tmp1hw,tmp1zw,tmp1dw = [],[],[]
tmp2hw,tmp2zw,tmp2dw = [],[],[]
tmp3hw,tmp3zw,tmp3dw = [],[],[]

s1w,s2w,s3w = [],[],[]

ghw,gzw=[],[]

for i in dataset3:
    if i[2] == 1:
        tmp1hw.append(i[4])
        tmp1zw.append(i[5])
        tmp1dw.append(i[6])
        s1w.append(i)
    if i[3] == 1:
        tmp2hw.append(i[4])
        tmp2zw.append(i[5])
        tmp2dw.append(i[6])
        s2w.append(i)

    if i[2] == 1 and i[3] == 1:
        tmp3hw.append(i[4])
        tmp3zw.append(i[5])
        tmp3dw.append(i[6])
        ghw.append(i[4])
        gzw.append(i[5])
        s3w.append(i)
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


with open(filename2, 'r') as file:
    data = file.readlines()
    dataset2 = []
    for line in data:
        tmp = [ float(i) for i in line.split() ]
        dataset2.append(tmp)

dataset2 = np.array(dataset2)
tmp1hq,tmp1zq,tmp1dq = [],[],[]
tmp2hq,tmp2zq,tmp2dq = [],[],[]
tmp3hq,tmp3zq,tmp3dq = [],[],[]

s1q,s2q,s3q = [],[],[]

ghq,gzq=[],[]

for i in dataset2:
    if i[2] == 1:
        tmp1hq.append(i[4])
        tmp1zq.append(i[5])
        tmp1dq.append(i[6])
        s1q.append(i)
    if i[3] == 1:
        tmp2hq.append(i[4])
        tmp2zq.append(i[5])
        tmp2dq.append(i[6])
        s2q.append(i)

    if i[2] == 1 and i[3] == 1:
        tmp3hq.append(i[4])
        tmp3zq.append(i[5])
        tmp3dq.append(i[6])
        ghq.append(i[4])
        gzq.append(i[5])
        s3q.append(i)


tmp1z = list(np.array(tmp1z) + 140.0)
detA = {i:tmp1z.count(i) for i in tmp1z}
detA = dict(sorted(detA.items(), key=lambda item: item[1] ))
tmp2z = list(np.array(tmp2z) + 140.0)
detB = {i:tmp2z.count(i) for i in tmp2z}
detB = dict(sorted(detB.items(), key=lambda item: item[1] ))
tmp3zq = list(np.array(tmp3zq) + 140.0)
detC = {i:tmp3zq.count(i) for i in tmp3zq}
detC = dict(sorted(detC.items(), key=lambda item: item[1] ))
tmp3hw = list(np.array(tmp3hw) + 0)
detH = {i:tmp3hw.count(i) for i in tmp3hw}
detH = dict(sorted(detH.items(), key=lambda item: item[1] ))

with open("{}_H.dat".format(sys.argv[4]),'w') as file:
    a = ["Height [mm] Counts\n"]
    for i,j in detH.items():
        a.append("{} {}\n".format(i,j))
    file.writelines(a)
with open("{}_D1.dat".format(sys.argv[4]),'w') as file:
    a = []
    for i,j in detA.items():
        a.append("{} {}\n".format(i,j))
    file.writelines(a)
with open("{}_D2.dat".format(sys.argv[4]),'w') as file:
    a = []
    for i,j in detB.items():
        a.append("{} {}\n".format(i,j))
    file.writelines(a)
with open("{}_D3.dat".format(sys.argv[4]),'w') as file:
    a = []
    for i,j in detC.items():
        a.append("{} {}\n".format(i,j))
    file.writelines(a)




nd1, yd1, _x1 = plt.hist(tmp1z,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k",label='detector A')
nd2, yd2, _x2 = plt.hist(tmp2z,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k",label='detector B')


plt.clf()


nh, yh,_h = plt.hist(tmp3h,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k")

plt.clf()

nc, yc, _c = plt.hist(tmp3z,histtype='stepfilled', alpha=0.3, density=False, bins=100, ec="k")

plt.clf()


