My Design Preferences:

Now in this project I want to build a Pokemon based zoo game
to achieve this I need to modify some of the classes and names


1. class Animal -> class Pokemon

2. class Flyable, Swimmable -> class Fire, Fighting, Water, Grass, Electric, Ice, Steel, Rock etc.
    basically the types from pokemon

3. Different Pokemons has different attacks, for example:
    Electric type Pokemons can cast Electrocute attack
    Rock type Pokemons can use Boulder attack

    Pokemons that have two types such as Kartana can use both type's attacks
    
    Kartana's Pokedex:
        ---------- Pokedex ----------
            Name: Kartana
            Health: 50/50
            Attack Power: 25
            Type: Steel, Grass
            Level: 1
            Experience: 0/500
            
            Strong against: Ice, Rock; Water, Rock
            Weak against: Fire, Water; Grass, Fire
        -----------------------------

    Kartana can cast Ivy attack and Blade attack on enemies

4. Types have both Strenghts and Weaknesses:
    A Fighting attack is strong against Rock type Pokemon
    Like that A Fire attack is weak against a Water type Pokemon

    Strong attacks deal more damage, weak attack deal less damage

    The strength of the attack is calculated by looking at Pokemon's all types
    Same as the weakness of the attacks

5. Experience System
    Pokemons can gain Experience with the damage they dealt

    When a Pokemon gains enough Exp, that Pokemon can level up
    The Experience needed for the leveling up threshold scales with levels
    For example a Pokemon can level up to level 2 with 500 Exp
    but for higher levels the threshold increase exponentially

    And some Pokemons can have Experience multipliers such as Eiscue
    Experience multipliers increases the Experience gains

6. Trainers can boost the Experience gain of the Pokemon
    Trainers can add an additional multiplier to the experience gain of the Pokemon
    With a trainer its eaiser to level up a Pokemon

7. Battle Mechanic:
    At the start of the round the Turn Owner has to select a Pokemon to attack
    Then The Turn Owner can select a Pokemon
    And then The Turn Owner can select an Attack Move
    
    Before selecting an Attack Move
    Turn Owner can see the indicating "Strong" "Weak" or "Normal" text
    These show if the Attack Move is strong against the attacked Pokemon

    After the Turn Owner selected its Attack Move the turn passes to the other Team





Thats it the rest of the project can be used with the instuctions