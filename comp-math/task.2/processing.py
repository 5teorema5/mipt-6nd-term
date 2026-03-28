import numpy as np
import matplotlib.pyplot as plt
import os


def plot_at_time(variable_name, target_time, L=10.0, save_fig=True):
    data_file = f'data/{variable_name}.csv'
    data = np.genfromtxt(data_file, delimiter=',', skip_header=0)

    y_coord = data[1:]
    x_coord = np.linspace(-L/2, L/2, y_coord.size)

    fig, ax = plt.subplots(figsize=(12, 6))

    titles = {
        'rho': (r'Плотность $\rho$', r'(кг/м³)', 'density'),
        'u': (r'Скорость $u$', r'(м/с)', 'velocity'),
        'p': (r'Давление $p$', r'(Па)', 'pressure'),
        'e': (r'Внутренняя энергия $e$', r'(Дж/кг)', 'energy')
    }

    title_ru, units, title_en = titles.get(variable_name, ('Value', '', 'value'))

    ax.plot(x_coord, y_coord, 'b-', linewidth=2, label=f'{title_ru}')
    ax.set_xlabel('x (м)', fontsize=12)
    ax.set_ylabel(f'{title_ru} {units}', fontsize=12)
    ax.set_title(f'{title_ru} в момент времени t = {target_time} с', fontsize=14)
    ax.grid(True, alpha=0.3)
    ax.axvline(x=0, color='gray', linestyle='--', alpha=0.5, label='x = 0')
    ax.legend()

    ax.set_xlim(x_coord.min(), x_coord.max())

    y_min, y_max = y_coord.min(), y_coord.max()
    margin = (y_max - y_min) * 0.05
    ax.set_ylim(y_min - margin, y_max + margin)

    plt.tight_layout()

    if save_fig:
        output_file = f'results/plot_{variable_name}_t={target_time}.png'
        plt.savefig(output_file, dpi=150, bbox_inches='tight')


if __name__ == "__main__":
    target_time = 0.015

    plot_at_time('rho', target_time)
    plot_at_time('u', target_time)
    plot_at_time('p', target_time)
    plot_at_time('e', target_time)
