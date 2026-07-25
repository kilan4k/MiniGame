# MiniGame

A simple text-based RPG console game written in C++. 

## Current Features
* **Flexible Character Creator**: Choose your starting hero archetype by typing its name or number. Supports case-insensitive input, custom nicknames, and starting weapons management. There are 7 unique starting classes available (including Bandit, Punchman, Archer, etc.).
* **Interactive Weapon Shop & Inventory**: Browse through 12 unique weapons, check stats, requirements, and purchase them using either their name or ID index. The shop also acts as an inventory menu, allowing you to equip previously bought weapons seamlessly.
* **Player Progression**: A working XP and level-up system. The experience needed for the next level increases dynamically (`100 * level * 1.5`), and leveling up increases max HP and base damage.
* **Dynamic Combat Stats**: Damage and critical strike chances are calculated dynamically on the fly based on your currently equipped weapon and character level. Base damage is increased by `level * 2`.
* **Diverse Weapons**: 12 different weapon types, ranging from Fists and Knives to a Light Saber and Deadly Staff. Each weapon has its unique damage, critical damage chance, cost, ownership state, and level required for unlocking.
* **Diverse Enemies & Scaling**: 12 different enemy types ranging from a weak Rat to a powerful Demon. Enemies are spawned dynamically based on weighted difficulty tiers (Easy, Medium, Hard). Each enemy has its own unique health, damage, armor, critical hit chance, gold, and XP reward.
* **Advanced Combat Mechanics**: A full turn-based combat system loop in the console. It features a damage system with random damage ranges, armor damage reduction, and critical hits that deal 1.5x damage. Players can also attempt to flee battles with a 75% success chance.
* **Healing System**: A dynamic healing menu where players can spend gold to restore HP. The price per HP scales with the player's level.

## What is Next?
* **Save & Load System**: Implement file I/O operations to save and load player progress, inventory, gold, and stats to a local file.
* **Armor System & Shop**: Expand the shop to allow players to purchase and equip different armor sets to increase their armor class and reduce incoming damage.
* **Dungeons & Boss Fights**: Introduce multi-stage dungeon runs with special high-stakes boss encounters and unique rewards.

## Technologies Used
* **C++**: Built using core OOP principles (Encapsulation and Abstraction through `Player`, `Enemy`, and `Weapon` classes).
* **Memory Management**: Safe dynamic memory allocation and pointer-based interactions for active enemies and equipped weapons.
* **Standard Template Library (STL)**: Extensive use of `std::vector` for entity management and `std::string` for text handling.
* **Random Generation**: Utilizing modern `<random>` library (`std::mt19937` and `std::uniform_int_distribution`) for accurate RNG in damage calculations, enemy spawning, and critical hits.
