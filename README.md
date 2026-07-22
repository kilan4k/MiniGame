# MiniGame

A simple text-based RPG console game written in C++. 

## Current Features
* **Flexible Character Creator**: Choose your starting hero archetype by typing its name or number. Supports case-insensitive input, custom nicknames, and starting weapons management.
* **Interactive Weapon Shop**: Browse through 12 unique weapons, check stats, requirements, and purchase or equip them using either their name or ID index.
* **Player Progression**: A working XP and level-up system. The experience needed for the next level increases with each new level.
* **Dynamic Combat Stats**: Damage and critical strike chances are calculated dynamically on the fly based on your currently equipped weapon and character level.
* **Diverse Weapons**: 12 different weapon types. Each weapon has its unique damage, critical damage chance, cost, ownership state, and level required for unlocking.
* **Diverse Enemies**: 12 different enemy types (from a weak Rat to a powerful Demon). Each enemy has its own unique health, damage, armor, critical hit chance, gold, and XP reward.
* **Combat Mechanics**: Basic damage system with random damage ranges, armor reduction, and critical hits.

## What is Next?
* **Battle Loop**: A full turn-based combat system loop in the console where the player fights sequentially spawned enemies.
* **Inventory Management**: A dedicated menu to inspect and swap between all owned weapons.
* **Difficulty Settings**: Easy, Medium, and Hard modes that change which enemies are more likely to appear.

## Technologies Used
* C++ (OOP principles, Pointer-based weapon system, Safe memory management, STL containers)
