import os
import sys
import random
import shutil

shutil.rmtree("mybench")
os.makedirs("mybench", exist_ok=True)
file = open("mybench/bench", 'w', encoding="utf-8")

def gen_data():
    T = '{:.4e}'.format(random.uniform(0, 20000))
    sx = random.randint(0, 8)
    sy = random.randint(0, 8)
    dx = random.randint(0, 8)
    dy = random.randint(0, 8)
    while [dx, dy] == [sx, sy]:
        dx = random.randint(0, 8)
        dy = random.randint(0, 8)
    return [T, str(sx), str(sy), str(dx), str(dy), str(5)]
    # file.write(" ".join([T, str(sx), str(sy), str(dx), str(dy), str(5)]) + "\n")


def gen_bench(line):
    bench = []
    for i in range(line):
        bench.append(gen_data())
    bench.sort(key=lambda time: eval(time[0]))
    for temp in bench:
        bench_str = [str(j) for j in temp]
        x = bench_str[1]
        y = bench_str[2]
        subfile = open("mybench/bench." + x + "." + y, "a", encoding="utf-8")
        subfile.write(" ".join(bench_str) + "\n")
        file.write(" ".join(bench_str) + "\n")


def main(size):
    gen_bench(eval(size))


#main("100")
main(sys.argv[1])


# gen_bench(10000)
# file.seek(0)
# print(file.readlines())
# print(eval("2.5826e+01"))

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
