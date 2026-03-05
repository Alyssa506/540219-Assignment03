// Compilation command: g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -o problem3 problem3.cpp
// TKU211231 - Data Structures and Algorithms
// Assignment 03 - Problem 3: Linear Search vs Binary Search

#include <iostream>
using namespace std;

// ============================================================
// 1. linearSearch
// O(n) worst case - harus cek satu per satu dari depan
// O(1) best case  - elemen pertama langsung cocok
// ============================================================
int linearSearch(int* arr, int n, int target) {
    for (int i = 0; i < n; i++) {   // iterasi dari index 0 sampai n-1
        if (arr[i] == target) {      // cek apakah elemen saat ini == target
            return i;                // ketemu! kembalikan indexnya
        }
    }
    return -1;  // tidak ditemukan
}

// ============================================================
// 2. binarySearch
// O(log n) worst case - tiap iterasi ruang pencarian dibagi 2
// O(1) best case      - elemen tengah langsung cocok
// SYARAT: array harus sudah terurut (sorted)
// ============================================================
int binarySearch(int* arr, int n, int target) {
    int lo = 0;
    int hi = n - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;   // hindari integer overflow (vs (lo+hi)/2)

        if (arr[mid] == target) {
            return mid;                  // ketemu! kembalikan indexnya
        } else if (arr[mid] < target) {
            lo = mid + 1;               // target ada di separuh kanan
        } else {
            hi = mid - 1;               // target ada di separuh kiri
        }
    }
    return -1;  // tidak ditemukan
}

// ============================================================
// 3. generateSortedArray
// Alokasi array sorted: {0, 2, 4, 6, ..., 2*(n-1)}
// Caller bertanggung jawab untuk delete[] hasilnya
// O(n) - mengisi n elemen
// ============================================================
int* generateSortedArray(int n) {
    int* arr = new int[n];          // alokasi di heap
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;             // isi: 0, 2, 4, 6, ..., 2*(n-1)
    }
    return arr;
}

// ============================================================
// HELPER: print hasil pencarian dengan rapi
// ============================================================
void printResult(const string& algo, int index, int target) {
    if (index != -1) {
        cout << "  " << algo << ": target " << target
             << " ditemukan di index " << index << "\n";
    } else {
        cout << "  " << algo << ": target " << target
             << " TIDAK ditemukan (return -1)\n";
    }
}

// ============================================================
// MAIN - Demonstrasi pada array ukuran n = {10, 100, 1000}
// ============================================================
int main() {
    int sizes[] = {10, 100, 1000};

    for (int n : sizes) {
        cout << "========================================\n";
        cout << "Array size n = " << n << "\n";
        cout << "Array: {0, 2, 4, ..., " << 2 * (n - 1) << "}\n";
        cout << "----------------------------------------\n";

        int* arr = generateSortedArray(n);

        // --- Kasus 1: cari nilai yang ADA (elemen di midpoint) ---
        int midIndex  = n / 2;
        int existVal  = arr[midIndex];   // pasti ada di array

        cout << "[Cari nilai yang ADA: " << existVal << "]\n";
        int li1 = linearSearch(arr, n, existVal);
        int bi1 = binarySearch(arr, n, existVal);
        printResult("Linear Search", li1, existVal);
        printResult("Binary Search", bi1, existVal);

        // Validasi: kedua algoritma harus sepakat
        if (li1 == bi1) {
            cout << "  ✓ Kedua algoritma SEPAKAT di index " << li1 << "\n";
        } else {
            cout << "  ✗ TIDAK sepakat! Linear=" << li1
                 << " Binary=" << bi1 << "\n";
        }

        cout << "\n";

        // --- Kasus 2: cari nilai yang TIDAK ADA ---
        int notExistVal = 2 * n + 99;   // pasti di luar range array

        cout << "[Cari nilai yang TIDAK ADA: " << notExistVal << "]\n";
        int li2 = linearSearch(arr, n, notExistVal);
        int bi2 = binarySearch(arr, n, notExistVal);
        printResult("Linear Search", li2, notExistVal);
        printResult("Binary Search", bi2, notExistVal);

        if (li2 == bi2 && li2 == -1) {
            cout << "  ✓ Kedua algoritma SEPAKAT: tidak ditemukan (-1)\n";
        } else {
            cout << "  ✗ TIDAK sepakat! Linear=" << li2
                 << " Binary=" << bi2 << "\n";
        }

        cout << "\n";

        delete[] arr;   // bebaskan memori (caller responsibility)
    }

    return 0;
}
