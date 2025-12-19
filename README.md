
## 🛠 Features

### 1. Infix to Postfix Conversion

The program uses a modified **Shunting-Yard algorithm** to handle:

* **Basic Operators**: `+`, `-`, `*`, `/` with standard precedence.
* **Unary Negation**: Represented by `N`.
* **Functions**:
* `IF(a, b, c)`: Conditional logic.
* `MIN(a1, a2, ...)` and `MAX(a1, a2, ...)`: Variable number of arguments.


* **Dynamic Argument Counting**: Automatically detects and appends the number of arguments to `MIN` and `MAX` in the postfix output (e.g., `MIN3`).

### 2. Stack-Based Evaluation

The evaluator processes the postfix expression and:

* Prints the operator/function and the current state of the operand stack before every execution.
* Handles **Integer Arithmetic** (truncating division).
* **Error Handling**: Detects and reports division by zero, terminating the current formula evaluation immediately.

---

## 📋 Requirements & Constraints

* **Custom Data Structures**:
* For full points, the stack must be implemented as a **linked list** (manual memory management).
* Standard Template Library (STL) and the `string` class are **forbidden**.


* **Memory Management**: Strict requirements for cleaning up unused memory to avoid leaks.
* **Tokenization**: Each token (operand, operator, or function) is processed individually from the input stream.

---

## 📤 Output Format

For each formula, the program outputs:

1. The complete **Postfix notation**.
2. A step-by-step trace: `[Operator/Function] [Stack Contents]`.
3. The **Final Result** or `ERROR` in case of division by zero.

---

## 🚀 How to Run

1. **Compile**:
```bash
g++ -O3 main.cpp -o calculator

```


2. **Input**: Provide the number of formulas followed by the expressions ending with a dot.
```text
1
IF ( 1 , MIN ( 10 , 20 , 5 ) , 0 ) .

```


3. **Run**:
```bash
./calculator < input.txt

```
