#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX = 10;

// Safe integer input
int getValidInt(string message, int min, int max) {
    int value;
    while (true) {
        cout << message;
        if (cin >> value && value >= min && value <= max)
            return value;

        cout << "\n   Invalid input! Enter a number between "
             << min << " and " << max << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Display matrix with borders
void displayMatrix(int mat[][MAX], int rows, int cols) {

    cout << "   ╔";
    for (int j = 0; j < cols; j++)
        cout << "═══════" << (j < cols-1 ? "╦" : "╗");
    cout << "\n";

    for (int i = 0; i < rows; i++) {
        cout << "   ║";
        for (int j = 0; j < cols; j++)
            cout << setw(6) << mat[i][j] << " ║";
        cout << "\n";

        if (i < rows - 1) {
            cout << "   ╠";
            for (int j = 0; j < cols; j++)
                cout << "═══════" << (j < cols-1 ? "╬" : "╣");
            cout << "\n";
        }
    }

    cout << "   ╚";
    for (int j = 0; j < cols; j++)
        cout << "═══════" << (j < cols-1 ? "╩" : "╝");
    cout << "\n";
}

// Section header
void printHeader(const string& title) {
    cout << "\n   ╔══════════════════════════════════╗\n";
    cout << "   ║  " << left << setw(34) << title << "║\n";
    cout << "   ╚══════════════════════════════════╝\n\n";
}

// Divider
void printDivider() {
    cout << "   ─────────────────────────────────────\n";
}

int main() {
    int rows, cols;
    int A[MAX][MAX], B[MAX][MAX], result[MAX][MAX];
    int choice;

    cout << "\n";
    cout << "   ╔══════════════════════════════════╗\n";
    cout << "   ║                                  ║\n";
    cout << "   ║     MATRIX ADDITION SYSTEM       ║\n";
    cout << "   ║         Case Study 167           ║\n";
    cout << "   ║                                  ║\n";
    cout << "   ╚══════════════════════════════════╝\n";

    do {
        cout << "\n   ╔══════════════════════════════════╗\n";
        cout << "   ║           M A I N  M E N U       ║\n";
        cout << "   ╠══════════════════════════════════╣\n";
        cout << "   ║   1.  Add Matrices               ║\n";
        cout << "   ║   2.  Exit                       ║\n";
        cout << "   ╚══════════════════════════════════╝\n";

        choice = getValidInt("\n   Enter choice (1-2): ", 1, 2);

        if (choice == 1) {

            cout << "\n   Enter Matrix Size\n";
            printDivider();

            rows = getValidInt("   Rows    (1-10) : ", 1, 10);
            cols = getValidInt("   Columns (1-10) : ", 1, 10);

            printHeader("Enter Matrix A");
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++) {
                    cout << "   A[" << i+1 << "][" << j+1 << "] = ";
                    cin >> A[i][j];
                }

            printHeader("Enter Matrix B");
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++) {
                    cout << "   B[" << i+1 << "][" << j+1 << "] = ";
                    cin >> B[i][j];
                }

            // Perform addition
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    result[i][j] = A[i][j] + B[i][j];

            // Display Results
            cout << "\n   ╔══════════════════════════════════╗\n";
            cout << "   ║            R E S U L T S         ║\n";
            cout << "   ╚══════════════════════════════════╝\n";

            cout << "\n   Matrix A :\n";
            displayMatrix(A, rows, cols);

            cout << "\n              [ + ]\n";

            cout << "\n   Matrix B :\n";
            displayMatrix(B, rows, cols);

            cout << "\n              [ = ]\n";

            cout << "\n   Resultant Matrix (A + B) :\n";
            displayMatrix(result, rows, cols);

            cout << "\n   ╔══════════════════════════════════╗\n";
            cout << "   ║   Addition Completed             ║\n";
            cout << "   ╚══════════════════════════════════╝\n";
        }

    } while (choice != 2);

    cout << "\n   Goodbye! See you next time.\n\n";

    return 0;
}
