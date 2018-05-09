# UPCZork

// ==========================================
// Title:  UPCZork - The Forest
// Author: Enrique Puyol Martín
// Date:   10/05/2018
// ==========================================

Resume
==================
UPCZork - The Forest is a conversational game based on the classic game 'Zork'. You wake up in the middle of the night in a magic forest and you need to find your way out. You have weapons to pick and be able to fight the enemies back, armours to protect yourself, potions to recover the damage taken and keys to open locked doors.

Map
==================

         | [Entrance] | <------> | [Mountain] |
               ^                       ^
               |                       |
               v                       v
      | [Treasure Room] | -------> | [Woods] | <-----> | [Cave] |
                                       ^                   |
                                       |                   |
                                       v                   v
               | [Lake] | <------> | Clear] |         | [Exit] |
                                    (Start)            (Finish)

Items
==================
Types of items:

- Keys: To unlock chests and doors
- Weapons: To fight enemies
- Armours: To protect yourself
- Potions: To heal yourself
- Chests: Which contains items inside

Enemies
==================
Types of enemies:
- Doors: Regarding programming, doors are considered enemies. I decided to make it this way so I could use the variable 'blockingExits'   instead of making a new hole class. At player experience, you are not able to notice difference.
- Enemies: Normal enemies which attacks you and you can kill them. Enemies can contain items and even other enemies inside.

Commands
==================
The game contains the following commands:
- Look (room)      = Gets information about the room (items, enemies, neighbours, locked doors...)

       (direction) = Gets the name of the neighbour in that direction
       (item)      = Gets the info of an item, depending on the item it gives diferent information
       (enemy)     = Gets the stats of the enemy, and its items.
      
- Go (direction)   = Moves the player to another room
-  Pick (item)              = Picks an item from the room
        (item) from (item2) = Picks an item inside the item2
        
- Examine (item) = Looks at the stats of an item of your inventory
- Drop (item)    = Drop an item of your inventory
- Use (item)     = Uses a potion to heal yourself
- Inventory      = Looks all the items in your inventory
- Stats          = Looks at the stats of the player (does not show weapon stats)
- Equip (item)   = Equips yourself with an armour
- Unequip (item) = Unequip yourself of the armour equipped
- Attack (enemy) with (item) = Attacks an enemy with a weapon
- Unlock (item) with (item)  = Unlocks a door or chest with its key
- Put (item) in (item2) = Puts an item from my inventory inside item2

Other commands:
- Help = Get help of the commands inside the game
- Quit = Quits the game
- Hi/Hello = Say hi to the game!


Guide to play and finish the game
==================
You start in 'Clear', from there you should follow the next steps to complete the game:
1. Pick sword
2. Go west
3. Attack wolf with sword

  3.1. Attack ghost_wolf with sword (until it dies)
  
4. Pick wood_key from wolf
5. Unlock wood_chest with wood_key
6. Pick iron_key from wood_chest

  6.1. Pick basic_potion from wood_chest (optional)
  
  6.2. Use basic_potion (recommended)
  
7. Go east
8. Unlock iron_door with iron_key
9. Go north
10. Pick axe from corpse
11. Pick armor from corpse
12. Go North
13. Pick superpotion

  13.1. Use superpotion
  
14. Go west
15. Attack guard with axe (until it dies)
16. Pick spear from guard
17. Attack spectral_guard with spear
18. Go south
19. Pick ancient_key from gold_chest
20. Pick magic_button
21. Unlock tunnel with magic_button
22. Go east
23. Go east
24. Attack wildfire with spear
25. Unlock ancient_door with ancient_key
26. Go south

You now have completed the game.

Relevant facts
==================
Some enemies only appear as 'ghosts', so are only alive when we kill its "father" enemy. While they arent alive, they are stored in a secret room inaccessible inside the game. And when the "father" enemy dies, we change its parent (room) to the actual. This ghost room is also used to stored broken keys. Right now only one ghost can appear per enemy, but we could change the variable 'afterDeathEnemy' to a list to make it multiple ghosts.
Doors have been programmed as enemies, but have different behavious. This is because like the real enemies, doors blocks directions until they are unlocked. So instead of making a new class just for the doors, I made an enemyType variable and used the Enemy class for the doors. This could be also used to make doors destructible (but in this game they arent).
You can die in the game, which would force you to quit the game.

When the console shows up text. Some keywords are highlighted in green. This is to help the player identify which things are interactible and which not. The color of the text also change when typing an input. So it is easier to difference different actions.

I struggled making enemies block you ways. Because at first I was doubting on the way to program it. I finally decided to make an array of booleans.
Programming the doors were the most difficult thing to do in this game. Because I didnt know how to consider them. I finally decided to make it "enemies" so I could recycle the enemy variable 'blockingExits'.
Enemies and Doors can block more than one direction thanks to the array 'blockingExits'. Although in the final version there is no enemy which does this.

Classes created
==================
UPCZork (main)

Entity
  - Player
  - Room
  - Item
  - Enemy
  
World

Common  

License
==================
MIT License

Copyright (c) [2018] Enrique Puyol Martín

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
