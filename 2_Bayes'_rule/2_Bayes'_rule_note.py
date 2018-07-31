p = [0.2, 0.2, 0.2, 0.2, 0.2]
world = ['green', 'red', 'red', 'green', 'green']
measurements = ["red", "green"]
pHit = 0.6
pMiss = 0.2


def sense(p, Z):
    q = []
    for i in range(len(p)):
        hit = (Z == world[i])
        q.append(p[i] * (hit * pHit + (1 - hit) * pMiss))
    q_normalize = [each/sum(q) for each in q] # 正则化
    return q_normalize

# for k in range(len(measurements)):
    # p = sense(p, measurements[k])
    # print(p)

# 思路：列表中的元素移动，即它的索引值发生改变，
# 比如，原来索引值为0的元素，向右移动两格，变成了2.
# 反过来，移动后位于新的列表中第一位的元素，原来的索引值需要-2，
# 即0-2.考虑循环：(0-2)%len(p)。采用了倒推的方法。

# 机器人的移动并不准确。比如，U=2时，有0.8的概率前进2格，
# 0.1的概率前进1格，0.1的概率前进3格。更新move。

pExact = 0.8
pOvershoot = 0.1
pUndershoot = 0.1

def move(p, U):
    q = []
    n = len(p)
    for i in range(len(p)):
        # (i-U) % len(p)，取余数。当(i-U)在[0, 4]区间之外时，
        # 可以实现循环，比如(i-U) = -1，-1/5 = -1...4，
        # (i-U) = 5, 5/5 = 1...0
        q.append(p[(i-U) % n]*pExact
            + p[(i-U-1) % n]*pOvershoot
            + p[(i-U+1) % n]*pUndershoot) 
    return q

# 机器人移动两次
p = move(p, 1)
p = move(p, 1)

# 编写代码，输入为初始概率p，测量measurements = ['red', 'green']，
# 移动motions = [1,1]，输出更新后的概率。
measurements = ['red', 'green']
motions = [1,1]

for i in range(len(measurements)):
    p = sense(p, measurements[i])
    p = move(p, motions[i])

print(p)