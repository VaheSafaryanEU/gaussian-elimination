const fs = require('fs');

function gaussian_elimination(A, b) {
    const n = b.length;
    for (let i = 0; i < n; i++) {
        console.log(`Step ${i + 1}:`);
        let max_row = i;
        for (let k = i + 1; k < n; k++) {
            if (Math.abs(A[k][i]) > Math.abs(A[max_row][i])) {
                max_row = k;
            }
        }
        [A[i], A[max_row]] = [A[max_row], A[i]];
        [b[i], b[max_row]] = [b[max_row], b[i]];
        const diag_elem = A[i][i];
        if (diag_elem === 0) {
            throw new Error("Division by zero encountered. The system may have no solution or infinitely many solutions.");
        }
        for (let j = i; j < n; j++) {
            A[i][j] /= diag_elem;
        }
        b[i] /= diag_elem;
        console.log("Matrix");
        for (let j = 0; j < n; j++) {
            for (let k = 0; k < n; k++) {
                process.stdout.write(A[j][k] + " ");
            }
            console.log(b[j]);
        }
        console.log();
        for (let k = i + 1; k < n; k++) {
            const factor = A[k][i];
            for (let j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }
    const x = new Array(n);
    for (let i = n - 1; i >= 0; i--) {
            x[i] = Math.round((b[i] - A[i].slice(i + 1).reduce((acc, val, idx) => acc + val * x[i + 1 + idx], 0)) / A[i][i]);
    }
    return x;
}

fs.readFile('matrix.txt', 'utf8', (err, data) => {
    if (err) {
        console.error(err);
        return;
    }
    const lines = data.trim().split('\n');
    const A = [];
    const b = [];
    for (const line of lines) {
        const row = line.trim().split(' ').map(Number);
        A.push(row.slice(0, -1));
        b.push(row[row.length - 1]);
    }
    const n = A.length;
    console.log("A:");
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            process.stdout.write(A[i][j] + " ");
        }
        console.log();
    }
    try {
        const x = gaussian_elimination(A, b);
        console.log("The solution is:");
        for (let i = 0; i < n; i++) {
            console.log(`x${i + 1} = ${x[i]}`);
        }
    } catch (e) {
        console.error(e.message);
    }
});
