import subprocess


file_names = [f"{x}_10.xml" for x in [100, 1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000]]
folder = "../tests/root_point/"

for i in range(1, 4):
    for name in file_names:
        path = folder + name
        command = ["../build/IO", "--file", path, "--temp", str(i), "--proc", "1"]
        print(" ".join(command))
        subprocess.run(command);
