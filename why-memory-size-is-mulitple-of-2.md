# Why is memory size a multiple of 2?

Memory sizes are in multiples of two because computers operate on a **binary system**. All data and memory addresses are represented by bits, which can only be a 0 or a 1. This base-2 nature makes powers of two the most efficient and logical way to build and manage memory.

---

## The Role of Binary Addressing 💻

The core reason lies in **binary addressing**. Each memory location needs a unique address, and these addresses are binary numbers. The number of bits available for an address determines the maximum number of memory locations that can be accessed.

The relationship is exponential: with '$n$' address lines, a computer can access exactly $2^n$ unique memory locations.

* **1 address line** can access $2^1$ = 2 memory locations.
* **2 address lines** can access $2^2$ = 4 memory locations (addresses: 00, 01, 10, 11).
* **33 address lines** are required to access $2^{33}$ bytes, which equals 8 gigabytes (GB).

Designing hardware (CPUs, memory controllers) around powers of two is far simpler and more efficient. A memory module with a capacity that isn't a power of two would lead to wasted addressing space and more complex, slower hardware. This fundamental design principle has become a universal standard, leading to the familiar memory sizes we see today (e.g., 4GB, 8GB, 16GB, 32GB).