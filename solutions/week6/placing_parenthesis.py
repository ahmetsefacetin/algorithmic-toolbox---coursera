def operation(a, b, c):
    if c == '+':
        return a + b
    if c == '-':
        return a - b
    if c == '*':
        return a * b

def minandmax(i, j, m, M, op):
    minimum = float('inf')
    maximum = float('-inf')
    for k in range(i,j):
        a = operation(m[i][k], m[k+1][j], op[k])
        b = operation(m[i][k], M[k+1][j], op[k])
        c = operation(M[i][k], m[k+1][j], op[k])
        d = operation(M[i][k], M[k+1][j], op[k])
        minimum = min(minimum, a, b, c, d)
        maximum = max(maximum, a, b, c, d)
    return minimum, maximum

def parenthesis(expression):
    numbers = expression[0:len(expression)+1:2]
    op = expression[1:len(expression):2]

    n = len(numbers)
    m = [[0 for i in range(n)] for j in range(n)]
    M = [[0 for i in range(n)] for j in range(n)]

    for i in range(n):
        m[i][i] = int(numbers[i])
        M[i][i] = int(numbers[i])
    for s in range(1,n):
        for i in range(n-s):
            j = i + s
            m[i][j], M[i][j] = minandmax(i, j, m, M, op)
    return M[0][n-1]

expression = input()
print(parenthesis(expression))