import sys
import numpy as np
import matplotlib.pyplot as plt
plt.rcParams.update({'text.usetex': False, 'mathtext.fontset': 'cm'})

def read_out_file(filename):
    file = None
    try:
        file = open(filename, 'r')
    except FileNotFoundError:
        print('File \'' + filename +'\' not found')
        return

    lines = file.readlines()

    data = []
    for line in lines:
        data.append(line)

    save_plot(data, 'algorithm')

def save_plot(str_list, name, dpi=400):
    data = []

    #figure = plt.figure()
    #plt.title('Zależności błędów przybliżeń różnicowych\n'
    #          'dla wartości typu 'r'$\mathit{' + name + r'}$')
    #plt.ylabel(r'$\log_{10} (\mathrm{|błąd|})$')
    #plt.xlabel(r'$\log_{10} (\mathrm{h})$')
    counter = 0
    for line in str_list:
        line = np.array(line.split(' '))
        data.append((counter, float(line[0]), float(line[1]), float(line[2])))
        counter += 1

    #legend = plt.legend(bbox_to_anchor=(0, -0.125, 1, 0), loc='upper left', ncol=3,
    #                    mode='expand', borderaxespad=0., fontsize='x-small')
    #figure.savefig(name + ".png", dpi=dpi,
    #               bbox_extra_artists=(legend,), bbox_inches='tight')

    x = [i[0] for i in data]
    bestAll = [i[1] for i in data]
    bestGeneration = [i[2] for i in data]
    average = [i[3] for i in data]
    plt.plot(x, average, label="Average for generation")
    plt.plot(x, bestGeneration, label="Best for generation")
    plt.plot(x, bestAll, label="Best overall")
    plt.legend(loc='lower right')
    plt.show()

def is_number(obj):
    try:
        float(obj)
        return True
    except ValueError:
        return False


read_out_file('out' if len(sys.argv) != 2 else sys.argv[1])
