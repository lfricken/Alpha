Window settings such as Anti-Aliasing, Texture Smoothing, and Resolution can be changed in the window.ini file
PRESS SPACE WHEN THE GAME STARTS


Gameplay:
Esc Key - MENU

Scroll Wheel - Zoom Camera in and out
Left Mouse - Fire Armor Piercing Rounds
Right Mouse - Fire High Velocity Rounds

T - Camera Tracking Toggle
W - Thrust Forward
S - Thrust Backward
A - Rotate CCW
D - Rotate CW
Q - Thrust Left
E - Thrust Right
Space - Force Field Toggle



Other:
~ - GUI Interact Mode Toggle. Type in the text box and press Enter to take control of other ships, choices are "ship_1", "ship_2", "ship_3", without quotes
O - View Physics Objects
P - Pause Toggle
F - Display FPS to console
M - Display Mouse coordinates to console



MECHANICS

Ships are made out of Modules, which you see as squares. They have "health" and "armor" attributes, which are 1000 and 0 by default. 
When health passes below 0, the Module goes into a destroyed state, and no longer collides with projectiles.
Armor reduces incoming damage by N amount, so dealing 75 damage to an object with 50 armor means it only recieves 25 damage.
Armor Pierce is an attribute that damage can have. Pierce cancels that much armor. So in the above example, 75 damage and 20 pierce would mean 20 armor would be ignored, letting 45 damage go through.


The black modules are Armor Modules(unless named), they have the same health as other modules, but have an armor value of 500, used to protect other modules
The green modules are unspecified modules that have 1000 health and 0 armor, has no function
The blue module in the middle of the ships is a Force Field Module, it repels projectiles, but if you destroy it, it stops working.
There is a reactor which produces energy which is needed to fire and move the ship
There are Capacitors which store energy produced, they fill with orange to represent stored energy.

Armor peircing rounds are blue, and do 100 damage with 500 pierce.
High velocity rounds are green, and do 500 damage with 0 pierce.


