#include <iostream>
#include <iomanip> //для работы setw

using namespace std;

int checkNumber() {//проверка корректности целого числа
    int k;
    cin >> k;
    while (cin.fail() || k < 0 || k == 0 || cin.get() != '\n') {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "\nНеккоректное число, повторите ввод: ";
        cin >> k;
    }
    return k;
}

int checkNumber1() {//проверка корректности целого числа
    int k;
    cin >> k;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "\nНеккоректное число, повторите ввод: ";
        cin >> k;
    }
    return k;
}

int sum_strok(int r, int c, double** mat) {//вывод суммы строк, где есть хоть одно отрицательное число
    double sum, p;
    for (int i = 0; i < r; i++) {
        sum = 0;
        p = 0;
        for (int j = 0; j < c; j++) {
            sum += mat[i][j];
            if (mat[i][j] < 0) {
                p = 1;
            }
        }
        if (p == 1) {
            cout << "В строке " << i << " есть отрицательное число, сумма строки: " << sum << endl;
        }
    }
    return 0;
}

void clear_memory(int r, double** mat) {
    for (int i = 0; i < r; i++) {       //перебирает строки массива
        free(mat[i]);                   //очищает место в памяти для строки из массива
    }
    free(mat);                          //очищает место в памяти для масива
}

void output(int r, int c, double** mat) {//вывод матрицы на экран
    for (int i = 0; i < r; i++) {        //перебирает адреса ячейки по столбцам
        for (int j = 0; j < c; j++) {    // перебирает адреса ячейки построкам
            cout << setw(3) << mat[i][j] << setw(3);//вывод значения ячейки на экран
        }
        cout << endl;
    }
}

int random_num(int r, int  c, double** mat) {//заполнение матрицы 
    int num;
    for (int i = 0; i < r; i++) {        //перебирает адреса ячейки по столбцам
        for (int j = 0; j < c; j++) {    //перебирает адреса ячейки построкам
            cout << "[" << i << "] [" << j << "]:";
            num = checkNumber1();
            cout << endl;
            mat[i][j] = num;
        }
    }
    return **mat;
}

int **index(int DIM1, int DIM2, double** mat, int *len) {
    (*len) = 0;
    int** mat_id = (int**)malloc(2 * sizeof(int*));//создание матрицы
    for (int i = 0; i < 2; i++) {
        mat_id[i] = (int*)malloc(sizeof(int));
    }

    for (int y = 0; y < DIM1; y++) {
        for (int x = 0; x < DIM2; x++) {
            bool ok_normal = true;
            bool ok_invert = true;
            for (int j = 0; j < DIM1; j++) {
                if (mat[y][j] != mat[j][x]) {
                    ok_normal = false;
                }
                if (mat[y][j] != mat[(DIM1 - 1) - j][x]) {
                    ok_invert = false;
                }
                if (ok_normal == false && ok_invert == false) { break; }
            }
            if (ok_normal || ok_invert) {
                (*len)++;
                for (int i = 0; i < 2; i++) {
                    mat_id[i] = (int*)realloc(mat_id[i], (*len) * sizeof(int));
                }
                mat_id[0][(*len) - 1] = x; // столбец
                mat_id[1][(*len) - 1] = y; // строка
                //cout << "Столбец: " << x << ", Строка: " << y << endl;
            }
        }
    }
    return mat_id;
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    srand(time(NULL));
    int r, c;//ввод количества строк и столбцов в матрице
    cout << "Задайте размер матрицы N x N: ";
    r = checkNumber();
    c = r;
    double** mat = (double**)malloc(r * sizeof(double*));//создание матрицы
    for (int i = 0; i < r; i++) {
        mat[i] = (double*)malloc(c * sizeof(double));
    }
    random_num(r, c, mat);//заполнение матрицы
    output(r, c, mat);//вывод матрицы на экран
    sum_strok(r, c, mat); //вывод суммы строк, где есть хоть одно отрицательное число
    cout << "Искомые номера для k-ых строки (столбца): " << endl;
    int len;
    int **mat_id = index(r, c, mat, &len);
    for (int i = 0; i < len; i++) {
        cout << "Столбец: " << mat_id[0][i] << ", Строка: " << mat_id[1][i] << endl;
    }
    clear_memory(r, mat); //очистка памяти
    for (int i = 0; i < 2; i++) {
        free(mat_id[i]);
    }
    free(mat_id);
    cout << "-------------------------------------" << endl;
    //проверка на утечку
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();
    return 0;
}
