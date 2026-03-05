// Compilation command: g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -o problem2 problem2.cpp
// TKU211231 - Data Structures and Algorithms
// Assignment 03 - Problem 2: DynArray Procedural Implementation

#include <iostream>
using namespace std;

// ============================================================
// STRUCT DEFINITION (copied exactly as required)
// ============================================================
struct DynArray {
    int* data;      // pointer to heap-allocated buffer
    int size;       // number of elements in use
    int capacity;   // total allocated slots
};

// ============================================================
// HELPER: resize (internal use only)
// Doubles the capacity of the array
// ============================================================
void resize(DynArray& a) {
    int newCapacity = a.capacity * 2;       // Step 1: hitung kapasitas baru (double)
    int* newData = new int[newCapacity];    // Step 2: alokasi buffer baru di heap

    for (int i = 0; i < a.size; i++) {     // Step 3: salin semua elemen lama ke buffer baru
        newData[i] = a.data[i];
    }

    delete[] a.data;                        // Step 4: bebaskan buffer lama
    a.data = newData;                       // Step 5: arahkan pointer ke buffer baru
    a.capacity = newCapacity;               // Step 6: update kapasitas
}

// ============================================================
// 1. initArray
// O(1) - hanya alokasi awal, tidak bergantung pada n
// ============================================================
void initArray(DynArray& a) {
    a.capacity = 2;             // kapasitas awal = 2
    a.size = 0;                 // belum ada elemen
    a.data = new int[a.capacity]; // alokasi heap buffer sebesar capacity
}

// ============================================================
// 2. freeArray
// O(1) - hanya dealokasi dan reset, tidak bergantung pada n
// ============================================================
void freeArray(DynArray& a) {
    delete[] a.data;   // bebaskan heap buffer
    a.data = nullptr;  // hindari dangling pointer
    a.size = 0;        // reset size
    a.capacity = 0;    // reset capacity
}

// ============================================================
// 3. pushBack
// O(1) amortized - biasanya O(1), sesekali O(n) saat resize
// ============================================================
void pushBack(DynArray& a, int value) {
    if (a.size == a.capacity) {  // cek apakah buffer penuh
        resize(a);               // jika penuh: double capacity (O(n))
    }
    a.data[a.size] = value;      // sisipkan value di posisi akhir
    a.size++;                    // increment size
}

// ============================================================
// 4. insertAt
// O(n) - harus geser elemen-elemen ke kanan
// ============================================================
void insertAt(DynArray& a, int index, int value) {
    if (a.size == a.capacity) {  // cek kapasitas, resize jika penuh
        resize(a);
    }

    // Geser elemen dari index ke akhir, satu posisi ke kanan
    // Mulai dari belakang agar tidak menimpa data
    for (int i = a.size; i > index; i--) {
        a.data[i] = a.data[i - 1];
    }

    a.data[index] = value;  // sisipkan value di posisi index
    a.size++;               // increment size
}

// ============================================================
// 5. removeAt
// O(n) - harus geser elemen-elemen ke kiri
// ============================================================
void removeAt(DynArray& a, int index) {
    // Geser elemen dari index+1 ke akhir, satu posisi ke kiri
    for (int i = index; i < a.size - 1; i++) {
        a.data[i] = a.data[i + 1];
    }
    a.size--;  // decrement size (elemen terakhir tidak perlu dihapus eksplisit)
}

// ============================================================
// 6. getAt
// O(1) - akses langsung ke array via index
// ============================================================
int getAt(const DynArray& a, int index) {
    return a.data[index];  // kembalikan elemen di posisi index
}

// ============================================================
// 7. setAt
// O(1) - akses langsung ke array via index
// ============================================================
void setAt(DynArray& a, int index, int value) {
    a.data[index] = value;  // set elemen di posisi index ke value
}

// ============================================================
// 8. printDynArr
// O(n) - iterasi semua elemen untuk dicetak
// ============================================================
void printDynArr(const DynArray& a) {
    cout << "[";
    for (int i = 0; i < a.size; i++) {
        cout << a.data[i];
        if (i < a.size - 1) cout << ", ";  // koma antar elemen, kecuali elemen terakhir
    }
    cout << "] (size=" << a.size << ", cap=" << a.capacity << ")\n";
}

// ============================================================
// MAIN - Demonstrasi semua fungsi sesuai urutan di soal
// ============================================================
int main() {
    DynArray arr;
    initArray(arr);

    // 1. pushBack hingga resize terpicu
    // capacity awal = 2
    // push ke-1: size=1, cap=2  -> tidak resize
    // push ke-2: size=2, cap=2  -> tidak resize
    // push ke-3: size==cap -> RESIZE! cap jadi 4, lalu size=3
    // push ke-4: size=4, cap=4  -> tidak resize
    // push ke-5: size==cap -> RESIZE! cap jadi 8, lalu size=5
    for (int i = 1; i <= 5; i++) pushBack(arr, i * 10);
    printDynArr(arr);  // [10, 20, 30, 40, 50] (size=5, cap=8)

    // 2. insertAt - sisipkan 25 di index 2
    // Sebelum : [10, 20, 30, 40, 50]
    // Index   :   0   1   2   3   4
    // Setelah : [10, 20, 25, 30, 40, 50]
    insertAt(arr, 2, 25);
    printDynArr(arr);  // [10, 20, 25, 30, 40, 50] (size=6, cap=8)

    // 3. removeAt - hapus elemen di index 0 (nilai 10)
    // Sebelum : [10, 20, 25, 30, 40, 50]
    // Setelah : [20, 25, 30, 40, 50]
    removeAt(arr, 0);
    printDynArr(arr);  // [20, 25, 30, 40, 50] (size=5, cap=8)

    // 4. getAt / setAt
    cout << "Element at index 2: " << getAt(arr, 2) << "\n";  // 30
    setAt(arr, 2, 99);
    printDynArr(arr);  // [20, 25, 99, 40, 50] (size=5, cap=8)

    freeArray(arr);  // bebaskan semua memori

    return 0;
}
