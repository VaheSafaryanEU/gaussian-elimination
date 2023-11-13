#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <vector>

std::vector<float> ge(std::vector<std::vector<float>> a, std::vector<float> b) {
        int n = b.size();
        for (int i = 0; i < n; i++) {
                std::cout << "Step " << i + 1 << ":" << std::endl;
                int max_row = i;
                for (int k = i + 1; k < n; k++) {
                        if (std::abs(a[k][i]) > std::abs(a[max_row][i])) {
                                max_row = k;
                        }
                }
                std::swap(a[i], a[max_row]);
                std::swap(b[i], b[max_row]);
                float diag = a[i][i];
                if (diag == 0) {
                        throw std::runtime_error("Division by zero encountered. The system may have no solution or infinitely many solutions.");
                }
                for (int j = i; j < n; j++) {
                        a[i][j] /= diag;
                }
                b[i] /= diag;
                for (int j = 0; j < n; j++) {
                        std::cout << "[";
                        for (int k = 0; k < n; k++) {
                                std::cout << a[j][k] << " ";
                        }
                        std::cout << "| " << b[j] << " ]"<< std::endl;
                }
                std::cout << std::endl;
                for (int k = i + 1; k < n; k++) {
                        float factor = a[k][i];
                        for (int j = i; j < n; j++) {
                                a[k][j] -= factor * a[i][j];
                        }
                        b[k] -= factor * b[i];
                }
        }
        std::vector<float> x(n);
        for (int i = n - 1; i >= 0; i--) {
                x[i] = (b[i] - std::inner_product(a[i].begin() + i + 1, a[i].end(), x.begin() + i + 1, 0.0)) / a[i][i];
        }
        return x;
}

int main() {
        std::ifstream file("matrix.txt");
        std::vector<std::vector<float>> a;
        std::vector<float> b;
        std::string line;
        while (std::getline(file, line)) {
                std::vector<float> row;
                std::istringstream iss(line);
                float num;
                while (iss >> num) {
                        row.push_back(num);
                }
                a.push_back(row);
                b.push_back(row.back());
                row.pop_back();
        }
        file.close();
        int n = a.size();
        std::cout << "Matrix:" << std::endl;
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        std::cout << a[i][j] << " ";
                }
                std::cout << "\n";
        }
        try {
                std::vector<float> x = ge(a, b);
                int check = 0;
                for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                                check += a[i][j] * x[j];
                        }
                        if (b[i] != check && b[i] != check + 1) {
                                std::cout << b[i] << " " << check << std::endl;
                                std::cout << "It is impossible to solve the problem" << std::endl;;
                                return 1;
                        }
                        check =0;
                }
                std::cout << "The solution is:" << std::endl;
                for (int i = 0; i < n; i++) {
                        std::cout << "x" << i << " = " << x[i] << std::endl;
                }
        } catch (const std::runtime_error& e) {
                std::cout << e.what() << std::endl;
        }
        return 0;
}
