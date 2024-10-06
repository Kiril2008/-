#include <iostream>
using namespace std;

// функція для видалення рядка з двовимірного динамічного масиву
void deleteRow(int**& matrix, int& rows, int cols, int rowIndex) {
    if (rowIndex < 0 || rowIndex >= rows) {
        cout << "неправильний індекс рядка!" << endl;
        return;
    }

    // створюємо новий масив на один рядок менше
    int ** newMatrix = new int*[rows - 1];
    int newRow = 0;

    for (int i = 0; i < rows; ++i) {
        if (i == rowIndex) continue; // пропускаємо рядок, який треба видалити
        newMatrix[newRow++] = matrix[i]; // копіюємо інші рядки
    }

    // видаляємо рядок та оригінальний масив
    delete[] matrix[rowIndex];
    delete[] matrix;

    matrix = newMatrix; // переприсвоюємо новий масив
    rows--; // зменшуємо кількість рядків
}

// функція для виведення матриці
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // створюємо матрицю
    int rows = 3, cols = 3;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols] {i + 1, i + 2, i + 3};
    }

    // виводимо початкову матрицю
    cout << "Початкова матриця:" << endl;
    printMatrix(matrix, rows, cols);
    // видаляємо рядок
    int rowToDelete = 1;
    deleteRow(matrix, rows, cols, rowToDelete);
    // виводимо матрицю після видалення рядка
    cout<< "Матриця після видалення рядка" << rowToDelete << ":" << endl;
    printMatrix(matrix, rows, cols);

    // очищаємо память
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}


//2
#include <iostream>
using namespace std;

// функція для транспонування матриці
int** transposeMatrix(int** matrix, int rows, int cols) {
    // створюємо нову транспоновану матрицю
    int** transposed = new int*[cols];
    for (int i = 0; i < cols; ++i) {
        transposed[i] = new int[rows];
    }

    // транспонуємо рядки і стовпці
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

// функція для виведення матриці
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // створюємо початкову матрицю
    int rows = 3, cols = 3;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols] {i + 1, i + 2, i + 3};
    }

    // виводимо початкову матрицю
    cout << "початкова матриця:" << endl;
    printMatrix(matrix, rows, cols);

    // транспонуємо матрицю
    int** transposed = transposeMatrix(matrix, rows, cols);

    // виводимо транспоновану матрицю
    cout << "транспонована матриця:" << endl;
    printMatrix(transposed, cols, rows);

    // очищаємо пам'ять
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    for (int i = 0; i < cols; ++i) {
        delete[] transposed[i];
    }
    delete[] transposed;

    return 0;
}

//3

#include <iostream>
#include <cstring> // для strcmp
using namespace std;

// клас для роботи з динамічними масивами для збереження імен і телефонів
class PhoneBook {
private:
    char** names;
    char** phones;
    int size;
public:
    // конструктор
    PhoneBook() {
        size = 0;
        names = nullptr;
        phones = nullptr;
    }

    // функція для додавання контакту
    void addContact(const char* name, const char* phone) {
        // створюємо нові масиви на один контакт більше
        char** newNames = new char*[size + 1];
        char** newPhones = new char*[size + 1];

        // копіюємо старі дані
        for (int i = 0; i < size; ++i) {
            newNames[i] = names[i];
            newPhones[i] = phones[i];
        }

        // додаємо нові контакти
        newNames[size] = new char[strlen(name) + 1];
        newPhones[size] = new char[strlen(phone) + 1];
        strcpy(newNames[size], name);
        strcpy(newPhones[size], phone);

        // видаляємо старі масиви
        delete[] names;
        delete[] phones;

        names = newNames;
        phones = newPhones;
        size++;
    }

    // пошук контакту за ім'ям
    void findByName(const char* name) const {
        for (int i = 0; i < size; ++i) {
            if (strcmp(names[i], name) == 0) {
                cout << "Знайдено: " << name << " - " << phones[i] << endl;
                return;
            }
        }
        cout << "Ім'я не знайдено!" << endl;
    }

    // пошук контакту за номером телефону
    void findByPhone(const char* phone) const {
        for (int i = 0; i < size; ++i) {
            if (strcmp(phones[i], phone) == 0) {
                cout << "Знайдено: " << names[i] << " - " << phone << endl;
                return;
            }
        }
        cout << "Телефон не знайдено!" << endl;
    }

    // зміна номера телефону за ім'ям
    void modifyContact(const char* name, const char* newPhone) {
        for (int i = 0; i < size; ++i) {
            if (strcmp(names[i], name) == 0) {
                delete[] phones[i]; // видаляємо старий номер
                phones[i] = new char[strlen(newPhone) + 1];
                strcpy(phones[i], newPhone);
                cout << "Телефонний номер оновлено для " << name << endl;
                return;
            }
        }
        cout << "Ім'я не знайдено!" << endl;
    }

    // деструктор
    ~PhoneBook() {
        for (int i = 0; i < size; ++i) {
            delete[] names[i];
            delete[] phones[i];
        }
        delete[] names;
        delete[] phones;
    }
};

int main() {
    // створюємо телефонну книгу
    PhoneBook phoneBook;

    // додаємо контакти
    phoneBook.addContact("Vlad", "123-456-7890");
    phoneBook.addContact("Alice", "098-765-4321");

    // пошук за ім'ям
    phoneBook.findByName("Vlad");

    // пошук за номером телефону
    phoneBook.findByPhone("066-555-541");

    // зміна номера телефону
    phoneBook.modifyContact("Joh", "1234-542-32442");
    phoneBook.findByName("Jon");

    return 0;
}


