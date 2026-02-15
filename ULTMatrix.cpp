#include <iostream>
#include <vector>

using namespace std;

class matrix
{
    int columns;
    int rows;
public:
	vector<vector<float>> Entry;

    void set_columns(int column) { columns = column; }
    void set_rows(int row) { rows = row; }
    int get_columns() const { return columns; }
    int get_rows() const { return rows; }
};

void print_matrix(matrix A)
{
    for (int i = 0; i < A.get_rows(); i++) {
		cout << "| ";
        for (int j = 0; j < A.get_columns(); j++) {
            cout << A.Entry[i][j] << " ";
        }
        cout << "|" << endl;
    }
}

matrix plus_matrix(matrix A, matrix B)
{
    for (int i = 0; i < A.get_rows(); i++) {
        for (int j = 0; j < A.get_columns(); j++) {
            A.Entry[i][j] = A.Entry[i][j] + B.Entry[i][j];
        }
    }
    return A;
}
matrix subtract_matrix(matrix A, matrix B)
{
    for (int i = 0; i < A.get_rows(); i++) {
        for (int j = 0; j < A.get_columns(); j++) {
            A.Entry[i][j] = A.Entry[i][j] - B.Entry[i][j];
        }
    }
	return A;
}
matrix multiply_matrix(matrix A, matrix B)
{
    matrix C;
	C.set_rows(A.get_rows());
	C.set_columns(B.get_columns());
    C.Entry = vector<vector<float>>(C.get_rows(), vector<float>(C.get_columns(), 0));
    int temp = 0;
    for (int i = 0; i < A.get_rows(); i++) {
        for (int j = 0; j < B.get_columns(); j++) {
            for(int k = 0; k < A.get_columns(); k++) {
				temp = temp + (A.Entry[i][k] * B.Entry[k][j]);
			}
			C.Entry[i][j] = temp;
            temp = 0;
        }
    }
    return C;
}

matrix multiply_by_number(matrix A, float n) {
    for(int i = 0; i < A.get_rows(); i++) {
        for(int j = 0; j < A.get_columns(); j++) {
            A.Entry[i][j] *= n;
        }
	}
    return A;
}

matrix divide_by_number(matrix A, float n) {
    matrix C;
    C.set_rows(A.get_rows());
    C.set_columns(A.get_columns());
    C.Entry = vector<vector<float>>(C.get_rows(), vector<float>(C.get_columns(), 0));

    for(int i = 0; i < A.get_rows(); i++) {
        for (int j = 0; j < A.get_columns(); j++) {
            if (n != 0) {
                C.Entry[i][j] = A.Entry[i][j] / n;
            }
            else {
                cout << "Division by zero is not allowed." << endl;
                return A;
            }
        }
    }
	return C;
}

float calculate_determination(matrix A)
{
    int swap_count = 0;

    int n = A.get_rows();
    for (int k = 0; k < n; k++) {
        if (A.Entry[k][k] == 0) {
            for (int i = k + 1; i < n; i++) {
                if (A.Entry[i][k] != 0) {
                    swap(A.Entry[k], A.Entry[i]);
                    swap_count++;
                    break;
                }
            }
        }

        for (int i = k + 1; i < n; i++) {

            float factor = A.Entry[i][k] / A.Entry[k][k];

            for (int j = k; j < n; j++) {
				A.Entry[i][j] = A.Entry[i][j] - factor * A.Entry[k][j];
            }
        }
    }
	print_matrix(A);

    float det = 1;

    for (int i = 0; i < n; i++) {
        det *= A.Entry[i][i];
    }
    
    if ((swap_count % 2) == 0) {
        return det;
    }
    else {
		return -det;
    }
}

matrix inverse_matrix(matrix A)
{
    int n = A.get_rows();

    matrix I;
    I.set_rows(n);
	I.set_columns(n);
    I.Entry = vector<vector<float>>(I.get_rows(), vector<float>(I.get_columns(), 0));

    for (int i = 0; i < n; i++)
        I.Entry[i][i] = 1;

    for (int k = 0; k < n; k++)
    {
        float pivot = A.Entry[k][k];

        if (pivot == 0)
        {
            for (int r = k + 1; r < n; r++)
            {
                if (A.Entry[r][k] != 0)
                {
                    swap(A.Entry[k], A.Entry[r]);
                    swap(I.Entry[k], I.Entry[r]);
                    pivot = A.Entry[k][k];
                    break;
                }
            }
        }

        if (pivot == 0)
        {
            cout << "Matrix is not invertible\n";
            return I;
        }

        for (int j = 0; j < n; j++)
        {
            A.Entry[k][j] /= pivot;
            I.Entry[k][j] /= pivot;
        }
        for (int i = 0; i < n; i++)
        {
            if (i == k) continue;

            float factor = A.Entry[i][k];

            for (int j = 0; j < n; j++)
            {
                A.Entry[i][j] -= factor * A.Entry[k][j];
                I.Entry[i][j] -= factor * I.Entry[k][j];
            }
        }
    }

    return I;
}

int main()
{
    matrix A, B;

    A.set_columns(2);
    A.set_rows(2);
    A.Entry = vector<vector<float>>(A.get_rows(), vector<float>(A.get_columns(), 0));

    B.set_columns(2);
    B.set_rows(2);
    B.Entry = vector<vector<float>>(B.get_rows(), vector<float>(B.get_columns(), 0));

    for (int i = 0; i < A.get_rows(); i++) {
        A.Entry[i][i] = 1;
    }
    
    A.Entry = {
        {1, 2},
        {0, 0}
    };
    matrix A_inv = inverse_matrix(A);
    cout << "Inverse Matrix:" << endl;
    print_matrix(A_inv);
	return 0;
}


