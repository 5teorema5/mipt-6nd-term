import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter
import glob
import os

CFL = ['0.60', '1.00', '1.01']

for cfl in CFL:
    # путь к папке с файлами
    data_folder_kurant = f'data-kurant-isakson-ris-CFL={cfl}'
    file_pattern_kurant = os.path.join(data_folder_kurant, 'time_*.csv')

    data_folder_laks = f'data-laks-vendroff-CFL={cfl}'
    file_pattern_laks = os.path.join(data_folder_laks, 'time_*.csv')

    # ищем все подходящие файлы
    files_kurant = sorted(glob.glob(file_pattern_kurant), key=lambda x: int(x.split('_')[-1].split('.')[0]))

    files_laks = sorted(glob.glob(file_pattern_laks), key=lambda x: int(x.split('_')[-1].split('.')[0]))

    # первый кадр
    first_data = np.genfromtxt(files_kurant[0], delimiter=',', skip_header=2)
    x = first_data[:, 0]

    # создаём фигуру
    fig, ax = plt.subplots(figsize=(10, 6))
    line_kurant, = ax.plot(x, np.zeros_like(x), 'b-', linewidth=2, label='Схема Куранта-Изаксона-Риса')
    line_laks, = ax.plot(x, np.zeros_like(x), 'r-', linewidth=2, label='Схема Лакса-Вендроффа')
    time_text = ax.text(0.02, 0.95, '', transform=ax.transAxes, fontsize=12)

    ax.set_xlabel('x', fontsize=12)
    ax.set_ylabel('u(x, t)', fontsize=12)
    ax.set_title(f'Решение уравнения переноса во времени CFL={cfl}', fontsize=14)
    ax.legend(loc='upper right')
    ax.grid(True, alpha=0.3)

    # определим границы по y
    all_values = []
    for file in files_kurant:
        data = np.genfromtxt(file, delimiter=',', skip_header=2)
        all_values.extend(data[:, 1])
    for file in files_laks:
        data = np.genfromtxt(file, delimiter=',', skip_header=2)
        all_values.extend(data[:, 1])
    ax.set_ylim(min(all_values), max(all_values))

    def update(frame):
        data_kurant = np.genfromtxt(files_kurant[frame], delimiter=',', skip_header=2)
        y_kurant = data_kurant[:, 1]

        data_laks = np.genfromtxt(files_laks[frame], delimiter=',', skip_header=2)
        y_laks = data_laks[:, 1]

        with open(files_kurant[frame], 'r') as f:
            header = f.readline().strip()
            time = float(header.split('=')[1].strip())

        ax.set_title(f'Решение уравнения переноса во времени CFL={cfl} (шаг {frame+1}/{len(files_kurant)})')
        line_kurant.set_ydata(y_kurant)
        line_laks.set_ydata(y_laks)
        time_text.set_text(f't = {time:.3f}')

        return line_kurant, line_laks, time_text

    anim = FuncAnimation(fig, update, frames=min(len(files_kurant), len(files_laks)), interval=200, repeat=True, blit=True)
    plt.tight_layout()
    # plt.show()

    anim.save(f'animation-CFL={cfl}.gif', writer=PillowWriter(fps=10))

    print(f"Finish CFL={cfl}")