import subprocess
from tqdm import tqdm

path = "../tests/procs/40000_10.xml"
evaluation = [0.0 for x in range(16)]
time = [0.0 for x in range(16)]
iterations = 10

procs = [1, 2, 4, 6, 8, 10, 12, 14, 16]

for i in tqdm(procs):
    for it in tqdm(range(iterations)):
        command = ["../build/IO", "--file", path, "--temp", "1", "--procs", str(i)]
        print(" ".join(command))
        proc = subprocess.Popen(command, stdout=subprocess.PIPE);
        while True:
            line = proc.stdout.readline()
            if not line:
                break
            line = line.decode("UTF_8")
            if "End" in line:
                evaluation[i - 1] += float(line.split()[2])
            if "time" in line:
                time[i - 1] += float(line.split()[2])
mid_evaluation =[]
mid_time = []

for i in range(16):
    mid_evaluation.append(evaluation[i] / iterations)
    mid_time.append(time[i] / iterations)

print("{", end="")
for index, now_time in enumerate(mid_time):
    secs = now_time / 1000
    print(f"({index+1}, {secs:.3f})", end="")
print("}")

print("{", end="")
for index, now_eval in enumerate(mid_evaluation):
    print(f"({index+1}, {now_eval:.3f})", end="")
print("}")
