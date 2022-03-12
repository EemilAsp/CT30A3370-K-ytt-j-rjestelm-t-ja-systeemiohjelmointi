import random
from bokeh.plotting import figure, output_file, show
import matplotlib.pyplot as plt
import numpy as np

asize = 1024
psize = 16 * 1024
uList = [0] * psize
zlist = []

for i in range(300):
    random.seed(i)
    for j in range(psize):
        limit = j
        vaddr = int(asize * random.random())
        if (vaddr < limit):
            uList[j] += psize

fig = plt.figure()
x = np.linspace(1, psize, psize) 
plt.plot(x, [u/300 for u in uList], color='green')
plt.ylim(0, psize)
plt.margins(0)
plt.ylabel('Avergae valid fraction')
plt.savefig('valid_fraction.png', dpi=227)
plt.show()
