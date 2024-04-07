import matplotlib.pyplot as plt

methods = [
    "ЦДА",
    "Брезенхэм\nвещественный",
    "Брезенхэм\nцелочисленный",
    "Брезенхэм\nс устранением\nступенчатости.",
    "Ву",
]


def main():
    plt.rcParams['figure.figsize'] = [16, 9]

    fig, ax = plt.subplots()

    numbers = []
    # plt.rcParams.update({'font.size': 10})

    with open("time_research.txt", "r") as file:
        for line in file.readlines():
            line = line[:-1]
            numbers.append(int(float(line)))

    bar_container = ax.bar(methods, numbers)

    ax.set_ylabel("Среднее время отрисовки отрезка (мс)")
    ax.bar_label(bar_container)
    plt.savefig("time_graph.png", dpi=200)
    # plt.show()


if __name__ == "__main__":
    main()
