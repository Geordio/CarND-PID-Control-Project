import sys
import numpy as np
import matplotlib
import matplotlib.pyplot as plt


plt.gcf().subplots_adjust(bottom=0.15)
index = np.loadtxt(open("debug.csv", "rb"), usecols=[0], delimiter=",", skiprows=1)
cte = np.loadtxt(open("debug.csv", "rb"), usecols=[1],delimiter=",", skiprows=1)
p_error = np.loadtxt(open("debug.csv", "rb"), usecols=[2],delimiter=",", skiprows=1)
d_error = np.loadtxt(open("debug.csv", "rb"), usecols=[3],delimiter=",", skiprows=1)
i_error = np.loadtxt(open("debug.csv", "rb"), usecols=[4],delimiter=",", skiprows=1)
steering_output = np.loadtxt(open("debug.csv", "rb"), usecols=[5],delimiter=",", skiprows=1)

matplotlib.rcParams.update({'font.size': 80})

plt.figure(figsize=(128, 128), dpi=80)
plt.subplot(1, 1, 1)
axes = plt.gca()
axes.set_xlim([0,200])
axes.set_ylim([-1.5,1.5])
plt.plot(index, cte, color="k", linewidth=15.0, linestyle="-")
plt.plot(index, p_error, color="g", linewidth=5.0, linestyle="-")
plt.plot(index, d_error, color="b", linewidth=5.0, linestyle="-")
plt.plot(index, i_error, color="c", linewidth=5.0, linestyle="-")
plt.plot(index, steering_output, color="r", linewidth=15.0, linestyle="-")
plt.axhline( y=0, color='m', linestyle=':', linewidth=10.0,label='zero' )
plt.title('PID debug')


plt.savefig( "debug_initial.png", bbox_inches = 'tight', dpi = 80)
plt.show()



plt.figure(figsize=(128, 128), dpi=80)
plt.subplot(1, 1, 1)
axes = plt.gca()
axes.set_xlim([550,700])
axes.set_ylim([-1.5,1.5])
plt.plot(index, cte, color="k", linewidth=15.0, linestyle="-")
plt.plot(index, p_error, color="g", linewidth=5.0, linestyle="-")
plt.plot(index, d_error, color="b", linewidth=5.0, linestyle="-")
plt.plot(index, i_error, color="c", linewidth=5.0, linestyle="-")
plt.plot(index, steering_output, color="r", linewidth=15.0, linestyle="-")
plt.axhline( y=0, color='m', linestyle=':', linewidth=10.0,label='zero' )
plt.title('PID debug')


plt.savefig( "debug_bend.png", bbox_inches = 'tight', dpi = 80)
plt.show()

