import subprocess
from tqdm import tqdm

problems  = [100, 1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000]

file_names = [f"{x}_10.xml" for x in problems]
folder = "../tests/root_point/"
iteration = 10

evaluation = [[0.0 for x in range(len(file_names))] for y in range(3)]
time = [[0.0 for x in range(len(file_names))] for y in range(3)]

for it in tqdm(range(iteration)):
    for i in range(1, 4):
        for index, name in enumerate(file_names):
            path = folder + name
            command = ["../build/IO", "--file", path, "--temp", str(i), "--proc", "1"]
            print(" ".join(command))
            proc = subprocess.Popen(command, stdout=subprocess.PIPE);
            while True:
                line = proc.stdout.readline()
                if not line:
                    break
                line = line.decode("UTF_8")
                if "End" in line:
                    evaluation[i - 1][index] += float(line.split()[2])
                if "time" in line:
                    time[i - 1][index] += float(line.split()[2])
mid_evaluation =[]
mid_time = []

for i in range(3):
    mid_evaluation.append([])
    mid_time.append([])
    for index in range(len(file_names)):
        mid_evaluation[i].append(evaluation[i][index] / iteration)
        mid_time[i].append(time[i][index] / iteration)

for i in range(3):
    print("{", end="")
    for index, now_time in enumerate(mid_time[i]):
        secs = now_time / 1000
        print(f"({problems[index]}, {secs:.3f})", end="")
    print("}")

    print("{", end="")
    for index, now_eval in enumerate(mid_evaluation[i]):
        print(f"({problems[index]}, {now_eval:.3f})", end="")
    print("}")
    print()
