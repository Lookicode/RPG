# 🌟 Text RPG Game – Semester Project (BI-PA2 @ FIT CTU)

A fun and challenging **text-based RPG** written in C++ as a first-year programming assignment. Explore rooms, survive combat, uncover secrets, and shape your adventure through typed commands!

---

## 🕹️ Key Features

- 🧍‍♂️ **Hero Creation**
  - Create your hero on the fly or define them in a text file.

- 🏰 **Room Exploration**
  - Navigate a structured world of rooms using a mix of menu choices and direct input.
  - Coordinates are based on a Cartesian system for defining rooms, mobs, and dialogues.

- ⚔️ **Turn-Based Combat**
  - Simple combat system with automatic turns.
  - If the hero’s health drops below 5, they’re allowed to flee from battle.

- 🎲 **Random Events**
  - Each move has a 15% chance to trigger a surprise combat encounter.
  - Alternatively, you might trigger a mishap (e.g., tripping or falling from a tree).
  - Never both at once!

- 💾 **Game State Management**
  - Supports live **import/export** of game state at runtime.
  - Invalid input lines in config files are gracefully skipped.

- 💬 **Command System**
  - Use the `help` command to list all available keywords and actions.

- 🐣 **Easter Egg**
  - Type `whoisyourdaddy` for a powerful Warcraft III-style cheat that boosts your hero's stats to god-tier. 😈

- 🧟 **Permadeath**
  - If your hero dies, it’s game over — no retries!

- 💰 **Loot & Rewards**
  - Defeating enemies earns gold to make your hero stronger.

---

## 📂 Input File Examples

You can find examples of input formats in:

- `input.txt`
- `in.txt`

Sections include `WORLD`, `MOB`, and more. The parser uses internal states to process them correctly and skip bad lines when necessary.

---

## 🧠 Reflection

> 🤓 *This was my first real project after just 7 months of learning to code in C++. It features some world-class overengineering, and `if-else` chains longer than a 1080p screen.*  
>
> That said, it’s a surprisingly complete and functional game — and I’m genuinely proud of what I built back then. 💙  
>
> *Would I refactor it someday? Maybe. But it’s a beautiful piece of student nostalgia as it stands.*

---

Enjoy exploring the world — and beware the monsters! ⚔️🗺️🐉
