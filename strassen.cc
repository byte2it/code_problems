// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<long long> > Matrix;

int rows(const Matrix& m) {
    return m.size();
}

int cols(const Matrix& m) {
    return m[0].size();
}

Matrix add(const Matrix& m, const Matrix& m2) {
    if (rows(m) != rows(m2) || cols(m) != cols(m2))
        throw exception("Matrices must have same dimensions");

    int rws = rows(m);
    int cls = cols(m);
    Matrix c(rws);
    for (int i = 0; i < rws; ++i) {
        c[i].resize(cls);
        for (int j = 0; j < cls; ++j) {
            c[i][j] = m[i][j] + m2[i][j];
        }
    }
    return c;
}

Matrix sub(const Matrix& m, const Matrix& m2) {
    if (rows(m) != rows(m2) || cols(m) != cols(m2))
        throw exception("Matrices must have same dimensions");

    int rws = rows(m);
    int cls = cols(m);
    Matrix c(rws);
    for (int i = 0; i < rws; ++i) {
        c[i].resize(cls);
        for (int j = 0; j < cls; ++j) {
            c[i][j] = m[i][j] - m2[i][j];
        }
    }
    return c;
}

Matrix mul(const Matrix& m, const Matrix& m2) {
    if (cols(m) != rows(m2))
        throw("Cannot multiply these matrices");

    int rws = rows(m);
    int cls2 = cols(m2);
    int rows2 = rows(m2);
    Matrix c(rws);
    for (int i = 0; i < rws; ++i) {
        c[i].resize(cls2);
        for (int j = 0; j < cls2; ++j) {
            for (int k = 0; k < rows2; ++k) {
                c[i][j] += m[i][k] * m2[k][j];
            }
        }
    }
    return c;
}

vector<vector<int>> params_(int r, int c) {
    return {
        {0, r, 0, c, 0, 0},
        {0, r, c, 2 * c, 0, c},
        {r, 2 * r, 0, c, r, 0},
        {r, 2 * r, c, 2 * c, r, c}

    };
}

vector<Matrix> toQuarters(const Matrix& m) {
    int r = rows(m) / 2;
    int c = cols(m) / 2;
    auto p = params_(r, c);
    vector<Matrix> quarters(4);

    for (int k = 0; k < 4; ++k) {
        Matrix q(r);
        for (int i = p[k][0]; i < p[k][1]; ++i) {
            q[i - p[k][4]].resize(c);
            for (int j = p[k][2]; j < p[k][3]; ++j) {
                q[i - p[k][4]][j - p[k][5]] = m[i][j];
            }
        }
        quarters[k] = q;
    }
    return quarters;

}

Matrix fromQuarters(vector<Matrix>& q) {
    int r = rows(q[0]);
    int c = cols(q[0]);
    auto p = params_(r, c);
    r *= 2;
    c *= 2;
    Matrix m(r);

    for (int i = 0; i < r; ++i) {
        m[i].resize(c);
    }

    for (int k = 0; k < 4; ++k) {
        for (int i = p[k][0]; i < p[k][1]; ++i) {
            for (int j = p[k][2]; j < p[k][3]; ++j) {
                //cout << "i = " << i << ", " << "j = " << j << ", " << "p[k][4] == " << p[k][4] << ", " << "p[k][5] == " << p[k][5] << endl;
                m[i][j] = q[k][i - p[k][4]][j - p[k][5]];
            }
        }
    }
    return m;
}

Matrix strassen(const Matrix& a, const Matrix& b) {
    int rows_a = rows(a);
    int rows_b = rows(b);
    int cols_a = cols(a);
    int cols_b = cols(b);

    if (rows_a != cols_a || rows_b != cols_b || rows_a != rows_b)
        throw exception("Matrices must be square and of equal size.");

    if (rows_a == 0 || (rows_a & (rows_b - 1)) != 0)
        throw exception("Size of matrices must be a power of two.");

    if (rows_a == 1)
        return mul(a, b);

    vector<Matrix> qa = toQuarters(a);
    vector<Matrix> qb = toQuarters(b);

    auto p1 = strassen(sub(qa[1], qa[3]), add(qb[2], qb[3]));
    auto p2 = strassen(add(qa[0], qa[3]), add(qb[0], qb[3]));
    auto p3 = strassen(sub(qa[0], qa[2]), add(qb[0], qb[1]));

    auto p4 = strassen(add(qa[0], qa[1]), qb[3]);
    auto p5 = strassen(qa[0], sub(qb[1], qb[3]));
    auto p6 = strassen(qa[3], sub(qb[2], qb[0]));
    auto p7 = strassen(add(qa[2], qa[3]), qb[0]);

    vector<Matrix> q(4);
    q[0] = add(sub(add(p1, p2), p4), p6);
    q[1] = add(p4, p5);
    q[2] = add(p6, p7);
    q[3] = sub(add(sub(p2, p3), p5), p7);
    return fromQuarters(q);
}

string printMatrix(const Matrix& m) {
    string s = "{";
    for (int i = 0; i < rows(m); ++i) {
        s.push_back('{');
        for (int j = 0; j < cols(m); ++j) {
            if (j > 0)
                s.push_back(',');
            char sz[10] = { 0 };
            sprintf_s(sz, "%lld", m[i][j]);
            s.append(sz);
        }
        s.push_back('}');
    }
    s.push_back('}');
    return s;
}

int main() {
    auto a = Matrix{ {1, 2}, {3, 4} };
    auto b = Matrix{ {5, 6}, {7, 8} };
    auto c = Matrix{ {1, 1, 1, 1}, {2, 4, 8, 16}, {3, 9, 27, 81}, {4, 16, 64, 256} };
    auto d = Matrix{ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
    auto e = Matrix{ {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} };
    cout << "\nUsing 'Strassen' matrix multiplication:" << endl;
    cout << "  a * b = " << printMatrix(strassen(a, b)) << endl;
    cout << "  c * d = " << printMatrix(strassen(c, d)) << endl;
    cout << "  e * f = " << printMatrix(strassen(d, e)) << endl;
}
