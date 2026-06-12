# 🎲 Terminal Yahtzee Game in C

An interactive, console-based implementation of the classic Yahtzee dice game written in C, featuring a tactical Human vs. Automated AI matchmaking loop.

---

## 📌 Project Overview
This project brings the classic tabletop dice game into a command-line interface. It handles complex pattern-matching algorithms, turn-based state switches, and an automated computer opponent that makes strategic rolling decisions.

Developed as a **Year 1 Semester 1 Project** for the SE2012-Programming Methodology Module.

---

## 🎮 Core Functionalities
- 🎲 **Multi-Stage Rolling:** Play with a realistic 5-dice framework offering up to 3 sequence rolls per turn.
- 🔒 **Array-Based Keeping:** Freeze high-value dice values between rolls using a dynamic binary selection mask.
- 🤖 **Strategic AI Engine:** The computer opponent uses a built-in decision tree to analyze its dice frequencies, locking pairs or triplets to optimize its scores.
- 📋 **Comprehensive Score Tracking:** Features a structured 13-row score validation matrix.
- 🏆 **End-Game Judgement:** Aggregates cumulative final scores across both scorecards to declare the match winner.

---

## 🛠️ Technical Implementation Details
The game architecture relies on modular programming principles in standard C:
- **Frequency Analysis Array:** Tracks dice combinations efficiently using a 1-indexed counter buffer:  
  `int counts[NUM_SIDES + 1] = {0};`
- **Masking Mechanism:** Passes pointer tracking filters (`toRoll[NUM_DICE]`) across sub-functions to manage locked vs. unlocked states.
- **Recursive Fallbacks:** Protects user inputs against invalid menu options or occupied scorecard slots using smooth recursive function loops.

---

## 🚀 Installation & Execution

### 1. Clone the Workspace
```bash
git clone
https://github.com/it24104259/Yahtzee-Game-in-C.git
cd Yahtzee-Game-in-C
```
2. Compile via GCC Compiler
```bash
gcc Yahtzee_Game.c -o yahtzee
```

3. Run the code
```bash
./yahtzee
```
Environment Note: Run yahtzee.exe if you are executing using windows.

---

## 📋 Comprehensive Category Reference Table
Index	Scoring Group	Calculation Rules 
- 1 - 6	Upper Section	Multiplies the matching face-value dice counts (Ones through Sixes).
- 7	Three of a Kind	Yields (Value of the Triplet × 3) + the sum of remaining non-matching dice.
- 8	Four of a Kind	Yields (Value of the Quadruplet × 4) + the sum of remaining non-matching dice.
- 9	Full House	Awards a flat 25 points if a triplet and a pair are simultaneously held.
- 10	Small Straight	Awards a flat 30 points for a sequence sequence of 4 consecutive values.
- 11	Large Straight	Awards a flat 40 points for a sequence sequence of 5 consecutive values.
- 12	Yahtzee	Awards a flat 50 points if all 5 dice numbers match perfectly.
- 13	Chance	A safety-net option that simply returns the absolute sum of all 5 dice.

---

## 👤 Project Architect
**Ranjula Adikari**

Year 1 Student - SLIIT

---
