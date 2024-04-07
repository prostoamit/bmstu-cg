import matplotlib.pyplot as plt

methods = [
    "ЦДА",
    "Брезенхэм\nвещественный",
    "Брезенхэм\nцелочисленный",
    "Брезенхэм\nс устранением\nступенчатости.",
    "Ву",
]


def main():

    plt.rcParams['figure.figsize'] = [25, 15]

    data = [[0 for _ in range(19)] for _ in range(5)]

    with open("steps_research.txt", "r") as file:
        for line_i in range(19 * 5):
            data[line_i // 19][line_i % 19] = int(file.readline()[:-1])

    fig, plots = plt.subplots(2, 3)


    fig.suptitle("Исследование ступенчатости алгоритмов.")

    plots[0, 0].set_title(methods[0])
    plots[0, 0].scatter([i for i in range(0, 91, 5)], data[0])
    plots[0, 0].plot([i for i in range(0, 91, 5)], data[0])


    plots[0, 1].set_title(methods[1])
    plots[0, 1].scatter([i for i in range(0, 91, 5)], data[1])
    plots[0, 1].plot([i for i in range(0, 91, 5)], data[1])

    plots[0, 2].set_title(methods[2])
    plots[0, 2].scatter([i for i in range(0, 91, 5)], data[2])
    plots[0, 2].plot([i for i in range(0, 91, 5)], data[2])

    plots[1, 0].set_title(methods[3])
    plots[1, 0].scatter([i for i in range(0, 91, 5)], data[3])
    plots[1, 0].plot([i for i in range(0, 91, 5)], data[3])

    plots[1, 1].axis("off")

    plots[1, 2].set_title(methods[4])
    plots[1, 2].scatter([i for i in range(0, 91, 5)], data[4])
    plots[1, 2].plot([i for i in range(0, 91, 5)], data[4])

    plt.savefig("steps_graph.png", dpi=200)

    pass


if __name__ == "__main__":
    main()
