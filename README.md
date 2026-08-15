# MiniGame

A C++ text-based RPG console game built using object-oriented principles, dynamic scaling formulas, and smart pointer memory management.

## Features

* **Character Creation**: Select from 7 starting character archetypes ("New character", "Bandit", "Punchman", "Archer", "Lumberjack", "Robber") by name or list index, and assign a custom player nickname.
* **Turn-Based Combat**: Engaging turn-based combat system where players fight enemies. Includes a flee mechanic with a 75% success chance (failing allows the enemy to attack first).
* **Weighted Enemy Spawning**: Enemies spawn dynamically based on difficulty probability tiers: Easy (70% chance), Medium (20% chance), and Hard (10% chance). Features 12 unique enemy types ranging from Rat to Demon.
* **Dynamic Combat Calculations**: Features random damage spreads, critical hits dealing 1.5x damage, and armor reduction (`armor / 5.0`). Player base damage scales with level (`weapon damage + level * 2`).
* **Weapon Shop & Inventory**: Browse 12 unique weapons with level requirements and gold prices. Equip, store, and swap purchased weapons seamlessly via the inventory menu.
* **Armor System & Shop**: Upgrade player armor class up to Class 4. Upgrade prices scale quadratically (`armorClass * armorClass * 100`).
* **Player Progression & Rewards**: Victory in battle grants XP and gold scaled with player level (`money * (level * 7 + 100) / 100`, `xp * (level * 5 + 100) / 100`) and increments total kills. Leveling up increases maximum HP (`90 + level * 11`) and restores health.
* **Scaling Healing System**: Spend gold to restore HP to maximum or a targeted health amount. Cost per HP scales with level (`0.25 + level * 0.02`).
* **In-Game Manuals**: Inspect detailed statistical breakdowns for all enemies and weapons directly from the game menu.

## Technologies Used

* **C++ & OOP Architecture**: Modular design separating game state and entity logic across `GameManager`, `Player`, `Enemy`, and `Weapon` classes.
* **Smart Pointers**: Utilizes `std::unique_ptr` for managing the active player instance (`myPlayer`) and dynamic combat enemy instances.
* **Modern Randomness**: Powered by `<random>` (`std::mt19937` and `std::uniform_int_distribution`) for combat damage, critical hit rolls, and enemy tier generation.
* **Standard Template Library (STL)**: Standard containers and utilities including `std::vector`, `std::pair`, `std::string`, and standard stream I/O.
