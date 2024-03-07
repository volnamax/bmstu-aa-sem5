#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

#include "mtr.h"
#include "alg.h"
#include "measure.h"

enum MenuOption {
    STANDARD_MULTIPLICATION = 1,
    WINOGRAD_MULTIPLICATION,
    WINOGRAD_OPTIMIZED_MULTIPLICATION,
    STRASSEN_MULTIPLICATION,
    TIME_MEASURE,
    EDIT_MATRICES,
    EXIT_PROGRAM
};

static constexpr const char *kFirstMatrixPath = "/home/max/c/bmstu_aa/lab_02/vm21u004/src/data/mtrx.txt";
static constexpr const char *kSecondMatrixPath = "/home/max/c/bmstu_aa/lab_02/vm21u004/src/data/mtry.txt";

bool IsPowerOfTwo(int val) {
    while ((val & 1) != 1)
        val >>= 1;
    return val == 1;
}

bool isValidMatrix(const Matrix &matrix, int option) {
    if (matrix.rows() == 0) {
        std::cout << "Matrix " << option << " has an invalid size\n";
        return false;
    }
    // Add other validation checks as needed
    return true;
}

int menu() {
    std::cout << "\n\t\tMenu\n"
                 "1. Standard matrix multiplication.\n"
                 "2. Winograd algorithm multiplication.\n"
                 "3. Optimized winograd algorithm multiplication.\n"
                 "4. Strassen algorithm multiplication.\n"
                 "5. Measure time for implemented algorithms.\n"
                 "6. Edit matrices\n"
                 "0. Exit.\n\n"
                 "Choose an option (0-6): ";

    int choice;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1; // Invalid input
    }

    return choice;
}

void performStandardMultiplication(const Matrix &matrix1, const Matrix &matrix2) {
    if (!isValidMatrix(matrix1, 1) || !isValidMatrix(matrix2, 2)) {
        return;
    }

    std::cout << Multiply::classicAlg(matrix1, matrix2);
}

void performWinogradMultiplication(const Matrix &matrix1, const Matrix &matrix2,
                                   Matrix (*winograd)(const Matrix &matrix1, const Matrix &matrix2)) {
    if (!isValidMatrix(matrix1, 1) || !isValidMatrix(matrix2, 2)) {
        return;
    }

    if (matrix1.rows() != matrix1.columns() || matrix2.rows() != matrix2.columns()) {
        std::cout << "Matrices must be square\n";
        return;
    }

    if (matrix1.rows() != matrix2.rows()) {
        std::cout << "Size of the first matrix (" << matrix1.rows() << "x" << matrix1.rows() <<
                  ") does not match the size of the second matrix (" << matrix2.rows() << "x" << matrix2.columns()
                  << ")\n";
        return;
    }

    std::cout << winograd(matrix1, matrix2);
}

void performStrassenMultiplication(const Matrix &matrix1, const Matrix &matrix2) {
    if (!isValidMatrix(matrix1, 1) || !isValidMatrix(matrix2, 2)) {
        return;
    }

    if (matrix1.rows() != matrix1.columns() || matrix2.rows() != matrix2.columns()) {
        std::cout << "Matrices must be square\n";
        return;
    }

    if (!IsPowerOfTwo(matrix1.rows())) {
        std::cout << "Matrix size must be a power of 2\n";
        return;
    }

    std::cout << Multiply::strassenAlg(matrix1, matrix2);
}

#include <fstream>

int main() {    int choice = 0;

    while ((choice = menu()) != EXIT_PROGRAM) {
        switch (choice) {
            case STANDARD_MULTIPLICATION:
                performStandardMultiplication(Matrix::fromFile(kFirstMatrixPath), Matrix::fromFile(kSecondMatrixPath));
                break;
            case WINOGRAD_MULTIPLICATION:
                performWinogradMultiplication(Matrix::fromFile(kFirstMatrixPath), Matrix::fromFile(kSecondMatrixPath),
                                              Multiply::winograd);
                break;
            case WINOGRAD_OPTIMIZED_MULTIPLICATION:
                performWinogradMultiplication(Matrix::fromFile(kFirstMatrixPath), Matrix::fromFile(kSecondMatrixPath),
                                              Multiply::winogradOpt);
                break;
            case STRASSEN_MULTIPLICATION:
                performStrassenMultiplication(Matrix::fromFile(kFirstMatrixPath), Matrix::fromFile(kSecondMatrixPath));
                break;
            case TIME_MEASURE:

                TimeMeasure(0, 100, 100, "/home/max/c/bmstu_aa/lab_02/vm21u004/src/data/nullToHundred.csv");
                TimeMeasure(1, 100, 100, "/home/max/c/bmstu_aa/lab_02/vm21u004/src/data/oneToHundred.csv");
                TimeMeasure(2, 128, 100, "/home/max/c/bmstu_aa/lab_02/vm21u004/src/data/twoToHundred.csv");
                break;
            case EDIT_MATRICES:
                int matrixChoice;
                do {
                    std::cout << "Which matrix file do you want to edit? (1 or 2): ";
                    std::cin >> matrixChoice;
                    if (matrixChoice == 1 || matrixChoice == 2) {
                        std::system((std::string("nano ") +
                                     std::string(matrixChoice == 1 ? kFirstMatrixPath : kSecondMatrixPath)).c_str());
                    }
                } while (matrixChoice == 1 || matrixChoice == 2);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
