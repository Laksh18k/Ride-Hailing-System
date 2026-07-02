# 🚕 Ride-Hailing System (AVL Trees)

A high-performance Command Line Interface (CLI) application built in C that simulates a ride-hailing platform (like Uber or Ola). This project leverages advanced data structures—specifically **Self-Balancing AVL Trees**—to manage Drivers, Passengers, and Bookings, ensuring lightning-fast $O(\log N)$ time complexity for insertions, deletions, and searches.

## ✨ Features

* **$O(\log N)$ Entity Management:** Fast and efficient CRUD operations for thousands of Drivers, Passengers, and Bookings using custom-built AVL Trees.
* **Geographical Matching:** Utilizes Euclidean distance mathematics to instantly locate and assign the nearest available driver (Cab or Bike) within a 5km radius of the passenger.
* **Advanced Querying & Analytics:** 
  * Identifies the Top 3 highest-earning drivers using sorting algorithms.
  * Tracks and displays the most frequent Driver-Passenger pairs.
  * Performs fast Range Searches for passenger IDs.
* **Ride Lifecycle Management:** Handles the complete flow from ride request, driver assignment (status updates), ride completion, and dynamic fare calculation based on vehicle type.
* **Persistent State Management:** Seamlessly saves and loads system data to and from CSV files (`drivers.csv`, `passenger.csv`, `bookings.csv`), ensuring no data is lost between sessions.

## 🛠️ Tech Stack & Tools

* **Language:** C
* **Core Concepts:** Advanced Data Structures, File Handling (I/O), Memory Management, Pointer Manipulation
* **Algorithms:** AVL Tree Balancing (LL, LR, RL, RR Rotations), Euclidean Distance, Sorting
* **Compiler:** GCC

## 🧠 Data Structures & Algorithms Highlights

* **Self-Balancing AVL Trees:** Implemented strictly balanced binary search trees from scratch. Features custom `getHeight`, `getBalance`, and four-way rotation functions to maintain a balance factor of -1, 0, or 1 across all nodes.
* **Spatial Distance Calculation:** Uses `<math.h>` to calculate the straight-line Euclidean distance $\sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$ for nearest-neighbor driver matching.
* **Inorder Traversals:** Utilized for generating sorted lists of available vehicles, printing booking histories, and exporting data to CSVs.

## ⚙️ How to Compile and Run

Make sure you have a C compiler (like GCC) installed on your system.

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/Laksh18k/Ride-Hailing-System.git](https://github.com/Laksh18k/Ride-Hailing-System.git)
   cd Ride-Hailing-System
