
# 🃏 FreeCell Game in C (Stack-based Implementation)

This is a console-based implementation of the **FreeCell** card game written in **C**, using fundamental **data structures like stacks (LIFO)** to manage cards and movements.

The project was developed as part of a Data Structures course to demonstrate mastery over dynamic memory, linked lists, and stack operations.

---

## 🎯 Game Objective

Move all 52 cards to the **four foundation piles** (by suit, ascending from Ace to King), using:
- 🗂️ Free cells (temporary holding)
- 📁 Tableau columns
- 🎯 Foundations

---

## 🛠️ Key Features

- 🧠 Stack-based design for card movements
- 🎲 Shuffled deck initialization
- 👨‍💻 Console UI with keyboard inputs
- 🪜 Validity checks for legal moves
- 💾 Dynamic memory allocation and freeing

---

## 📚 Data Structures Used

- **Stack (Pile)**: implemented via linked lists to manage columns and cells.
- **Card** structure with fields:
  - `value` (1–13)
  - `suit` (♠, ♥, ♦, ♣)
- **GameState** struct: holds all the arrays of stacks (columns, free cells, foundations).

---

## 🚀 How to Run

### 1. Compile

```bash
gcc main.c game.c stack.c -o freecell
```

> Replace `main.c`, `game.c`, etc. by your actual file names.


## 🧠 Learning Outcomes

- Mastery of stack operations in C
- Game state management using dynamic data structures
- Input parsing and validation
- Clean code structure in procedural C

---

## 📬 Author

> Developed by **Hamza Bouda**  
> 💼 [LinkedIn](https://www.linkedin.com/in/hamza-bouda)  
> 💌 hamza.bouda@outlook.com

---

