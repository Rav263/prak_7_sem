import subprocess
import os
import time

def get_p_mut(ser):
    return 0.0004 * 1.5**ser


series_count = 10
exp_count = 10

stab = []
best = []
time_max = []

os.chdir("./exp_5/")
for series in range(series_count):
    times = []
    evaluates = []
    procs = []

    os.chdir(f"./series_{series}/")
    
    for exp in range(exp_count):
        command =["../../build/LG", "--series", str(series), "--exp", str(exp)]
        print(" ".join(command))
        procs.append(subprocess.Popen(command, stdout=subprocess.PIPE));
        time.sleep(3)

    for proc in procs:
        while True:
            line = proc.stdout.readline();
            if not line:
                break

            line = line.decode("UTF_8")
            times.append(float(line.split()[0]))
            evaluates.append(int(line.split()[1]))
    stab.append(max(evaluates) - min(evaluates))
    best.append(max(evaluates))
    time_max.append(max(times))
    os.chdir("../")

print("{", end="")
for index, now_stab in enumerate(stab):
    print(f"({index}, {now_stab})", end="")
print("}")

print("{", end="")
for index, now_best in enumerate(best):
    print(f"({index}, {now_best})", end="")
print("}")

print("{", end="")
for index, now_time in enumerate(time_max):
    secs = now_time / 1000
    print(f"({index}, {secs:.3f})", end="")
print("}")


