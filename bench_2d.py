import os
import sys
import random
import shutil

if os.path.exists("mybench_2D"):
    shutil.rmtree("mybench_2D")
os.makedirs("mybench_2D", exist_ok=True)
file = open("mybench_2D/bench", 'w', encoding="utf-8")

def gen_data(m):
    T = '{:.4e}'.format(random.uniform(0, 20000))
    sx = random.randint(0, m-1)
    sy = random.randint(0, m-1)
    dx = random.randint(0, m-1)
    dy = random.randint(0, m-1)
    while [dx, dy] == [sx, sy]:
        dx = random.randint(0, m-1)
        dy = random.randint(0, m-1)
    return [T, str(sx), str(sy), str(dx), str(dy), str(5)]
    # file.write(" ".join([T, str(sx), str(sy), str(dx), str(dy), str(5)]) + "\n")


def gen_bench(line,matrix):
    bench = []
    for i in range(line):
        bench.append(gen_data(matrix))
    bench.sort(key=lambda time: eval(time[0]))
    for temp in bench:
        bench_str = [str(j) for j in temp]
        x = bench_str[1]
        y = bench_str[2]
        subfile = open("mybench_2D/bench." + x + "." + y, "a", encoding="utf-8")
        subfile.write(" ".join(bench_str) + "\n")
        file.write(" ".join(bench_str) + "\n")


def main(size,matrix):
    gen_bench(eval(size),eval(matrix))


#main("100")
main(sys.argv[1],sys.argv[2])


# gen_bench(10000)
# file.seek(0)
# print(file.readlines())
# print(eval("2.5826e+01"))

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
