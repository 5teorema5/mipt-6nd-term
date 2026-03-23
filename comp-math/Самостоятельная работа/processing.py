import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.animation import FuncAnimation

f = "u"

data = pd.read_csv(f'data/f=1_g=0_{f}.csv')
x_coords = [float(col.split('=')[1]) for col in data.columns[1:]]
time = data['time'].values
u_all = data.iloc[:, 1:].values

fig, ax = plt.subplots(figsize=(10, 6))
line, = ax.plot(x_coords, u_all[0], 'b-', linewidth=2)
ax.set_xlim(0, max(x_coords))
ax.set_ylim(-1.5, 11.5)
# ax.set_ylim(-1.5, 1.5)
ax.set_xlabel('x')
ax.set_ylabel(f'{f}(x,t)')
ax.grid(True, alpha=0.3)
time_text = ax.text(0.02, 0.95, '', transform=ax.transAxes)


def update(frame):
    line.set_ydata(u_all[frame])
    time_text.set_text(f't = {time[frame]:.2f}')
    return line, time_text


anim = FuncAnimation(fig, update, frames=len(time), interval=50, blit=True)
anim.save(f'res/f=1_g=0_{f}.gif', writer='pillow', fps=20)
plt.show()
