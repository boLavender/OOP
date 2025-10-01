#include <iostream>
using namespace std;

class TwoD {
public:
    int **matrix; // Making matrix public
    int rows;
    int cols;

    // Parameterized constructor 
    TwoD(int Row, int Col) : rows(Row), cols(Col) {
        matrix = new int *[rows];          //***記憶體的設定可以直接在這裡寫，而不是先設matrix為nullptr
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
        }
    }

    // Copy constructor
    TwoD(const TwoD& other) : rows(other.rows), cols(other.cols) {  //*****
        matrix = new int *[rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {        //***注意 這裡是直接連在一起操作的
                matrix[i][j] = other.matrix[i][j];  //*先用new把二階陣列設定好，接著將other.matrix指派進matrix
            }
        }
    }

    // Destructor
    ~TwoD() {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Matrix addition
    TwoD operator+(const TwoD& other) {
        TwoD result(rows, cols);    //*

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    // Matrix multiplication
    TwoD operator*(const TwoD& other) {  //*****
        TwoD result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < cols; ++k) {   //***cols
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    // Matrix assignment
    TwoD& operator=(const TwoD& other) {  //****TwoD&
        if (this != &other) { //*****this 指針在 assignment operator 中，用來避免自我賦值
//虽然 const 确保了 other 不会被修改，但并不能防止由于自我赋值而导致的内存问题
            // Clean up existing memory
            for (int i = 0; i < rows; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;

            // Allocate new memory and copy data
            rows = other.rows;
            cols = other.cols;
            matrix = new int *[rows];
            for (int i = 0; i < rows; ++i) {
                matrix[i] = new int[cols];
                for (int j = 0; j < cols; ++j) {
                    matrix[i][j] = other.matrix[i][j];
                }
            }
        }
        return *this;  //*****
    }

    // Display matrix
    void display() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int row1, col1, row2, col2;

    // Input dimension of matrix1
    cout << "Enter the row and column dimension of matrix1:\n";
    cin >> row1 >> col1;

    // Create matrix1 object
    TwoD matrix1(row1, col1);
    cout << "Enter " << row1 << " rows of " << col1 << " integers each:\n";
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1; ++j) {
            cin >> matrix1.matrix[i][j]; // Accessing matrix directly
        }
    }

    // Input dimension of matrix2
    cout << "Enter the row and column dimension of matrix2:\n";
    cin >> row2 >> col2;

    // Create matrix2 object
    TwoD matrix2(row2, col2);
    cout << "Enter " << row2 << " rows of " << col2 << " integers each:\n";
    for (int i = 0; i < row2; ++i) {
        for (int j = 0; j < col2; ++j) {
            cin >> matrix2.matrix[i][j]; // Accessing matrix directly
        }
    }

    // Perform matrix operations
    TwoD matrix3 = matrix1; // Copy matrix1 to matrix3  //這行程式碼是拷貝初始化，會調用 copy constructor。儘管看起來像賦值操作，但這是初始化新物件的特例。在這裡，matrix3 是新創建的物件，所以會調用 copy constructor，而不是 assignment operator  //使用 TwoD matrix3 = matrix1; 或 TwoD matrix3(matrix1); 初始化一個新的物件時，實際上是調用了 copy constructor
    TwoD matrix5 = matrix2 + matrix3; // Matrix addition
    TwoD matrix4 = matrix2 * matrix3; // Matrix multiplication
    

    // Display results
    
    cout << "matrix1=\n";
    matrix5.display();
    cout<<"matrix2=\n";
    matrix2.display();
    cout << "matrix3=\n";
    matrix3.display();
    cout << "matrix4=matrix2*matrix3:\n";
    matrix4.display();

    return 0;
}
