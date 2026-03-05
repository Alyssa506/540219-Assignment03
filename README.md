# Assignment 03 - Data Structures and Algorithms

**Nama:** Alyssa Nursadrina
**NIM:** 24/540219/TK/59925

---

## Deskripsi Solusi

### Problem 1 : Algorithm Analysis
Menganalisis tiga potongan kode (Snippet A, B, C) menggunakan standard cost model di mana setiap assignment, perbandingan, operasi aritmatika, dan akses array dihitung sebagai 1 unit biaya. Analisis mencakup:
- Perhitungan T(n) secara eksak dengan anotasi tiap baris
- Penyederhanaan ke notasi Big-O
- Penjelasan perbedaan best case dan worst case

Hasil :
- **Snippet A** : Loop bersarang dengan pola segitiga → **O(n²)**. Best case = Worst case.
- **Snippet B** : Binary search, ruang pencarian dibagi dua tiap iterasi → **O(log n)**. Best case O(1), worst case O(log n).
- **Snippet C** : Tiga loop bersarang, loop terdalam berjalan ⌈n/2⌉ kali → **O(n³)**. Best case = Worst case.

---

### Problem 2 : DynArray — Procedural Implementation
Implementasi resizable array menggunakan `struct` dan free functions, tanpa menggunakan class, template, maupun `std::vector`.

Struktur `DynArray` terdiri dari:
- `int* data` → pointer ke buffer di heap
- `int size` → jumlah elemen yang sedang digunakan
- `int capacity` → total slot yang dialokasikan

Strategi resize menggunakan **doubling** (kapasitas digandakan saat penuh):
1. Alokasi buffer baru berukuran 2× capacity
2. Salin semua elemen lama ke buffer baru
3. Hapus buffer lama dengan `delete[]`
4. Update pointer dan capacity

Fungsi yang diimplementasikan beserta kompleksitasnya:
- `initArray()` → O(1)
- `freeArray()` → O(1)
- `pushBack()` → O(1) amortized, O(n) saat resize
- `insertAt()` → O(n)
- `removeAt()` → O(n)
- `getAt()` → O(1)
- `setAt()` → O(1)
- `printDynArr()` → O(n)

---

### Problem 3 : Linear Search vs Binary Search

**Part A — Implementasi**

Dua algoritma pencarian diimplementasikan dan dibandingkan:

- **Linear Search** : menelusuri array dari index 0 hingga n−1 secara berurutan. Mengembalikan index pertama jika ditemukan, atau −1 jika tidak ada. Kompleksitas: O(n).
- **Binary Search (iteratif)** : bekerja pada array terurut, membagi ruang pencarian menjadi setengah setiap iterasi. Menggunakan rumus `mid = lo + (hi - lo) / 2`. Kompleksitas: O(log n).
- **generateSortedArray(n)** : mengalokasikan array berisi bilangan genap `{0, 2, 4, ..., 2(n-1)}` di heap.

Program diuji pada n = 10, 100, dan 1000, dengan dua skenario: mencari nilai yang ada dan nilai yang tidak ada. Kedua algoritma dikonfirmasi menghasilkan index yang sama.

**Part B — Complexity Comparison Table**
Analisis perbandingan kompleksitas waktu Linear Search dan Binary Search pada best, worst, dan average case. Disimpulkan bahwa Binary Search lebih efisien untuk n besar karena pertumbuhan logaritmik jauh lebih lambat dari linear.

---

### Problem 4 : Amortized Analysis of pushBack
Analisis tertulis mengenai biaya amortized dari operasi `pushBack` pada DynArray, mencakup:
- **Part A** : Trace 12 pemanggilan pushBack, mencatat size, capacity, dan cost tiap operasi
- **Part B** : Total cost T₁₂, rata-rata biaya per operasi, dan pembuktian deret geometri → O(n) total, O(1) amortized
- **Part C** : Perbandingan strategi doubling vs fixed increment (+4). Doubling → O(n) total, fixed increment → O(n²) total karena deret aritmatika

---

## Cara Kompilasi

```bash
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -o problem2 problem2.cpp
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -o problem3 problem3.cpp
```

---

## Known Issues / Limitations

**(Problem 1 : Algorithm Analysis)**
- Hanya menganalisis kompleksitas waktu; kompleksitas ruang tidak dibahas
- Big-O mengabaikan konstanta dan suku orde rendah, sehingga kurang akurat untuk nilai n yang kecil
- Optimasi dari compiler (misal flag `-O2`) tidak dimodelkan dan dapat mengubah jumlah operasi aktual
- Analisis tidak memperhitungkan efek hardware seperti cache dan branch prediction
- Model biaya yang digunakan adalah penyederhanaan — setiap operasi dianggap bernilai sama (1 unit), padahal pada kenyataannya biaya tiap operasi bisa berbeda-beda

**(Problem 2 : DynArray — Procedural Implementation)**
- Strategi doubling dapat menyebabkan hingga ~50% kapasitas tidak terpakai setelah resize
- Tidak exception-safe dan tidak thread-safe
- Hanya mendukung tipe data `int`, tidak generic
- Tidak ada shrinking — kapasitas tidak pernah dikurangi meski banyak elemen dihapus, sehingga bisa boros memori
- Tidak ada pengecekan batas index — memanggil `getAt`, `setAt`, `insertAt`, atau `removeAt` dengan index tidak valid akan menyebabkan undefined behavior

**(Problem 3 : Linear Search vs Binary Search)**
- Penggunaan raw pointer (`new[]` / `delete[]`) berpotensi menyebabkan memory leak jika tidak dikelola dengan benar
- Implementasi Binary Search tidak menjamin pengembalian index pertama jika terdapat elemen duplikat
- Perbandingan efisiensi yang dilakukan bersifat teoritis (Big-O) dan tidak mengukur waktu eksekusi nyata
- Binary Search hanya valid pada array yang sudah terurut; memberikan array tidak terurut akan menghasilkan output yang tidak dapat diprediksi

**(Problem 4 : Amortized Analysis of pushBack)**
- Analisis bersifat teoritis dan tidak mempertimbangkan overhead alokasi memori di sistem nyata
- Strategi fixed increment lebih hemat memori, namun total cost menjadi O(n²) sehingga sangat tidak efisien untuk n besar
- Strategi doubling membuat total cost O(n) dan amortized O(1), namun dapat mengakibatkan pemborosan memori hingga setengah kapasitas setelah resize

---

## Waktu Pengerjaan
± 4–5 hari
