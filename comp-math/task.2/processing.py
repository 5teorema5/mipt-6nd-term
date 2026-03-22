import numpy as np
import matplotlib.pyplot as plt
import os


def plot_at_time(variable_name, target_time, L=10.0, save_fig=True):
    data_file = f'data/{variable_name}.csv'
    if not os.path.exists(data_file):
        print(f"File {data_file} not found!")
        return None, None

    data = np.genfromtxt(data_file, delimiter=',', skip_header=1)

    times = data[:, 0]
    values = data[:, 1:]

    with open(data_file, 'r') as f:
        header = f.readline().strip()

    x_coords = []
    parts = header.split(',')
    for part in parts[1:]:
        if part.startswith('x='):
            x_coords.append(float(part.split('=')[1]))

    x_center = np.array(x_coords) - L / 2

    idx = np.argmin(np.abs(times - target_time))
    actual_time = times[idx]

    fig, ax = plt.subplots(figsize=(12, 6))

    titles = {
        'rho': (r'Плотность $\rho$', r'(кг/м³)', 'density'),
        'u': (r'Скорость $u$', r'(м/с)', 'velocity'),
        'p': (r'Давление $p$', r'(Па)', 'pressure'),
        'e': (r'Внутренняя энергия $e$', r'(Дж/кг)', 'energy')
    }

    title_ru, units, title_en = titles.get(variable_name, ('Value', '', 'value'))

    ax.plot(x_center, values[idx], 'b-', linewidth=2, label=f'{title_ru}')
    ax.set_xlabel('x (м)', fontsize=12)
    ax.set_ylabel(f'{title_ru} {units}', fontsize=12)
    ax.set_title(f'{title_ru} в момент времени t = {actual_time:.6f} с', fontsize=14)
    ax.grid(True, alpha=0.3)
    ax.axvline(x=0, color='gray', linestyle='--', alpha=0.5, label='x = 0')
    ax.legend()

    ax.set_xlim(x_center.min(), x_center.max())

    y_min, y_max = values[idx].min(), values[idx].max()
    margin = (y_max - y_min) * 0.05
    ax.set_ylim(y_min - margin, y_max + margin)

    plt.tight_layout()

    if save_fig:
        output_file = f'results/plot_{variable_name}_t={actual_time:.3f}.png'
        plt.savefig(output_file, dpi=150, bbox_inches='tight')


if __name__ == "__main__":
    target_time = 0.001

    plot_at_time('rho', target_time)
    plot_at_time('u', target_time)
    plot_at_time('p', target_time)
    plot_at_time('e', target_time)
