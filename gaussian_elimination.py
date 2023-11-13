import numpy as np

def gaussian_elimination(A, b):
    n = len(b)

    for i in range(n):
        print(f"Step {i + 1}:")

        max_row = i
        for k in range(i+1, n):
            if abs(A[k, i]) > abs(A[max_row, i]):
                max_row = k
        A[[i, max_row]] = A[[max_row, i]]
        b[i], b[max_row] = b[max_row], b[i]

        diag_elem = A[i, i]
        if diag_elem == 0:
            raise ValueError("The system may have no solution or infinitely many solutions.")
        A[i, :] /= diag_elem
        b[i] /= diag_elem

        print("Matrix")
        print(np.concatenate((A, b[:, None]), axis=1))
        print()

        for k in range(i+1, n):
            factor = A[k, i]
            A[k, i:] -= factor * A[i, i:]
            b[k] -= factor * b[i]

    x = np.zeros(n)
    for i in range(n-1, -1, -1):
        x[i] = round((b[i] - np.dot(A[i, i+1:], x[i+1:])) / A[i, i])

    return x

if __name__ == '__main__':
    with open('matrix.txt', 'r') as file:
        lines = file.readlines()

    n = len(lines)
    A = np.zeros((n, n))
    b = np.zeros(n)

    for i, line in enumerate(lines):
        row = list(map(float, line.strip().split()))
        A[i, :] = row[:-1]
        b[i] = row[-1]
    print(A)

    try:
        x = gaussian_elimination(A, b)
        print("The solution is:")
        for i in range(n):
            print(f"x{i+1} = {x[i]}")

    except ValueError as e:
        print(e)
