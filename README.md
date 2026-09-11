# Interpreter
### **Interpreter for a Model Programming Language** 

## 📌 Overview  
This project is an **interpreter** for a custom model programming language, implemented in C++.  
It performs **lexical analysis, parsing, semantic analysis, and execution** of programs written in the model language.  

## **Project Structure**  

| **Component**    | **Description** |
|------------------|----------------|
| `Lex`            | Stores token type and value (e.g., `NUM`, `ID`, `IF`) |
| `Ident`          | Table of identifiers (variable names and values) |
| `Scanner`        | Lexical analyzer (converts code into tokens) |
| `Parser`         | Syntactic analyzer (validates program structure) |
| `Executer`       | Executes the parsed program |
| `Interpretator`  | Manages the execution process |

## **How to Use**  

### **1️⃣ Prerequisites**  
Ensure you have **G++ (GCC) installed**:  
```sh
g++ --version
```
If not, install it (Ubuntu/Debian):  
```sh
sudo apt update && sudo apt install g++
```

---

### **2️⃣ Compilation**  
Compile the interpreter:  
```sh
g++ -o interpreter main.cpp
```

---

### **3️⃣ Running the Interpreter**  
Run the interpreter with a test script:  
```sh
./interpreter tests1.txt
```

---

## 📝 **Example Program (`tests1.txt`)**  
```txt
program {
    int x;
    x = 10;
    while (x > 0) {
        write(x);
        x = x - 1;
    }
    write("Done!");
}
```
📌 This program initializes `x = 10`, decrements it, and prints `"Done!"` at the end.  

---

##  **How It Works**  

### **1️⃣ Lexical Analysis (`Scanner`)**  
Breaks the input program into tokens.  

Input code:  
```txt
if (x > 5) write(x);
```
Output tokens:  
```
(LEX_IF, "if")
(LEX_LPAREN, "(")
(LEX_ID, "x")
(LEX_GTR, ">")
(LEX_NUM, "5")
(LEX_RPAREN, ")")
(LEX_WRITE, "write")
(LEX_ID, "x")
(LEX_SEMICOLON, ";")
```

---

### **2️⃣ Parsing (`Parser`)**  
Checks syntax and builds a parse tree.  

Example tree for `x = 5 + 3;`  
```
Assignment: x =
    Expression: (5 + 3)
```

---

### **3️⃣ Execution (`Executer`)**  
Runs the program using **reverse Polish notation (RPN)**.  

Expression:  
```txt
x = 5 + 3;
```
Turns into:  
```
5 3 + x =
```
Then executes it step by step.  

---

## 📖 **Model Language Syntax**  
The model programming language follows **a structured syntax with control flow statements**.  

✔ **Program structure:**  
```txt
program { <declarations> <statements> }
```
✔ **Variable declarations:**  
```txt
int x;
string name = "Alice";
```
✔ **Control flow:**  
```txt
if (x > 5) { write(x); } else { x = 0; }
while (x > 0) { x = x - 1; }
```
✔ **Input/Output:**  
```txt
read(x);
write(x, "Hello");
```
✔ **Operations:**  
- Arithmetic: `+`, `-`, `*`, `/`  
- Comparison: `<`, `>`, `<=`, `>=`, `==`, `!=`  
- Boolean logic: `and`, `or`, `not`  

📌 **For a full specification, check [model_lang_practical_task.pdf](docs/model_lang_practical_task.pdf).**  

---

## 🔮 **Future Improvements**  
- Add **functions** and **procedures**  
- Implement **arrays**  
- Improve **error handling**  

---

## **License**  
This project is open-source under the **MIT License**.  

---

##  **Author**  
**mariealanie**  
