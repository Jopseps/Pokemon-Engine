#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Pokemon{
    public:

    string name;
    int health;
    int maxHealth; // Its for my combat system
    int attackPower;

    float exp = 0;
    int level = 1;
    float solidLevelUpThreshold = 500; // I'll use this to have a constant value for calculating levelUpThreshold
    float levelUpThreshold = 500; // I'll be using this to calculate the exp need for leveling up
    float expGainMultiplier = 1;
    
    vector<string> type;
    vector<string> attackNames;
    

    

    Team* assignedTeam;

    Trainer* assignedTrainer;

    static int PokemonCount;
    Pokemon(){
        name = "Unknown";
        maxHealth = 1;
        health = 1;
        attackPower = 1;
        assignedTrainer = nullptr;
        assignedTeam = nullptr;
        allPokemons.push_back(this);
    }
    
    Pokemon(string n, int h, int aP){
        name = n;
        maxHealth = h;
        health = h;
        attackPower = aP;
        assignedTrainer = nullptr;
        assignedTeam = nullptr;
        allPokemons.push_back(this);
        
    }


    void assignTrainer(Trainer* currentAssignedTrainer){
        assignedTrainer = currentAssignedTrainer;
    }

    void unassignTrainer(){
        assignedTrainer = nullptr;
    }
    

    void gainExp(float amount){
        if(assignedTrainer != nullptr){
            exp += amount * expGainMultiplier * assignedTrainer->trainerExpMultiplier;
        }else{
            exp += amount * expGainMultiplier;
        }
        if(exp >= levelUpThreshold) levelUp();
    }

    void levelUp(){
        while(exp >= levelUpThreshold){
            level++;
            exp -= levelUpThreshold;
            levelUpThreshold =  (int)(solidLevelUpThreshold * ((pow(level, 4/3) * level / 2) * 3/4));
        }
    }



    // Retired levelUp function
    /*void levelUp(int quantity){
        level += quantity;
        exp -= levelUpThreshold;
        levelUpThreshold =  solidLevelUpThreshold * pow(level, 2/3);
        if(exp >= levelUpThreshold) levelUp(1);
    }*/

    void pokedex(){
        for(int i = 1; i <= 20; i++){cout << "-"; if(i == 10) cout << " Pokedex ";}; cout << endl;
        cout << "Name: " << name << endl;
        cout << "Health: " << health << "/" << maxHealth << endl;
        cout << "Attack Power: " << attackPower << endl;
        
        if(type.size() > 1 && type[1] != ""){
            cout << "Type: " << type[0] << ", " << type[1] << endl;
        }else if(type.size() > 0){
            cout << "Type: " << type[0] << endl;
        }else{
            cout << "Type: Unknown" << endl;
        }

        cout << "Level: " << level << endl;
        cout << "Experience: " << exp << "/" << levelUpThreshold << "\n" << endl;
        
        
        cout << "Strong against: "; 

        if(size(type) > 1 && !type[1].empty()){

            for(int i = 0; i < size(convertStrenght(type[0])); i++){
                cout << convertStrenght(type[0])[i];
                if(i != size(convertStrenght(type[0])) - 1) cout << ", ";
            }
            cout << "; ";
            for(int i = 0; i < size(convertStrenght(type[1])); i++){
                cout << convertStrenght(type[1])[i];
                if(i != size(convertStrenght(type[1])) - 1) cout << ", ";
            }
            
            cout << endl;
        }
        else if(size(type) == 1){
            
            for(int i = 0; i < size(convertStrenght(type[0])); i++){
                cout << convertStrenght(type[0])[i];
                if(i != size(type)) cout << ", ";
            }
            
            cout << endl;
        }
        else{cout << "This Pokemon isn't strong against any type" << endl;}


    


        cout << "Weak against: "; 
        
        if(size(type) > 1 && !type[1].empty()){

            for(int i = 0; i < size(convertWeakness(type[0])); i++){
                cout << convertWeakness(type[0])[i];
                if(i != size(convertWeakness(type[0])) - 1) cout << ", ";
            }
            cout << "; ";
            for(int i = 0; i < size(convertWeakness(type[1])); i++){
                cout << convertWeakness(type[1])[i];
                if(i != size(convertWeakness(type[1])) - 1) cout << ", ";
            }
            
            cout << endl;
        }
        else if(size(type) == 1){
            
            for(int i = 0; i < size(convertWeakness(type[0])); i++){
                cout << convertWeakness(type[0])[i];
                if(i != size(type)) cout << ", ";
            }
            
            cout << endl;
        }
        else{cout << "This Pokemon isn't weak against any type" << endl;}
        

    }

    // Can be merged Birleştirilebilir mana
    virtual bool checkStrenghts(string searchedType, vector<string> s){
        for(int i = 0; i < size(s); i++){
            if(searchedType == s[i]) return true;
        }
        return false;
    }

    virtual bool checkWeakness(string searchedType, vector<string> w){
        for(int i = 0; i < size(w); i++){
            if(searchedType == w[i]) return true;
        }
        return false;
    }

    int calculateDamage(const Pokemon &attackedPokemon, vector<string> s, vector<string> w){
        int damage = attackPower;
        if(attackedPokemon.type.size() > 1){
            if(checkStrenghts(attackedPokemon.type[0], s) == true || checkStrenghts(attackedPokemon.type[1], s) == true){
            damage *= 2;
            }
        }else if(attackedPokemon.type.size() == 1){
            if(checkStrenghts(attackedPokemon.type[0], s) == true){
            damage *= 2;
        }
        
        if(attackedPokemon.type.size() > 1){
            if(checkWeakness(attackedPokemon.type[0], w) == true || checkWeakness(attackedPokemon.type[1], w) == true){
            damage /= 2;
            }
        }else if(attackedPokemon.type.size() == 1){
            if(checkWeakness(attackedPokemon.type[0], w) == true){
            damage /= 2;
        }
        }

        return damage;
        }
    return damage;
    }

    int basicDamage(Pokemon &attackedPokemon, int dmg){
        if(attackedPokemon.health <= dmg){
            attackedPokemon.health = 0;
            cout << attackedPokemon.name << " is fainted" << endl;
            return dmg;

        }
        if(attackedPokemon.health > dmg){
            attackedPokemon.health -= dmg;
            cout << attackedPokemon.name << " got " << dmg << " damage!" << endl;
            return dmg;
        }
        return 0;
    }
                                        // This types strenghts and weaknesses
    void attack(Pokemon &attackedPokemon, vector<string> s, vector<string> w){
        gainExp(basicDamage(attackedPokemon, calculateDamage(attackedPokemon, s, w))) ;
    }

};

int Pokemon::PokemonCount = 0;







class Fire : public Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;
    
    virtual void fire(){
        cout << name << " breathed fire!" << endl;
    }

    virtual void fire(Pokemon &attackedPokemon){
        cout << name << " used fire on " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon, strengths, weaknesses);
    }
};



class Fighting : public virtual Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;

    virtual void fight(){
        cout << name << " showed its fighting skills!" << endl;
    }

    virtual void fight(Pokemon &attackedPokemon){
        cout << name << " throwed a solid punch to " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon, strengths, weaknesses);
    }
};

class Water : public virtual Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;
    
    virtual void spray(){
        cout << name << " sprayed water!" << endl;
    }

    virtual void spray(Pokemon &attackedPokemon){
        cout << name << " sprayed pressured water on " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon, strengths, weaknesses);
    }
};

class Ice : public virtual Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;
    
    virtual void freeze(){
        cout << name << " rained a few snowflakes!" << endl;
    }

    virtual void freeze(Pokemon &attackedPokemon){
        cout << name << " freezed " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon, strengths, weaknesses);
    }
};

class Electric : public virtual Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;
    
    virtual void electrocute(){
        cout << name << " casually lighted a light bulb!" << endl;
    }
    
    virtual void electrocute(Pokemon &attackedPokemon){
        cout << name << " electrocuted " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon, strengths, weaknesses);
    }
};

class Grass : public virtual Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;
    
    virtual void ivy(){
        cout << name << " showed up a bunch of vines out of the grass!" << endl;
    }
    
    virtual void ivy(Pokemon &attackedPokemon){
        cout << name << " catched " << attackedPokemon.name << " with vines!" << endl;
        attack(attackedPokemon, strengths, weaknesses);
    }
};

class Rock : public virtual Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;
    
    virtual void boulder(){
        cout << name << " pulled a bunch of rocks out of the ground!" << endl;
    }
    
    virtual void boulder(Pokemon &attackedPokemon){
        cout << name << " throwed a huge boulder on " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon, strengths, weaknesses);
    }
};

class Steel : public virtual Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;

    
        // Slice
    virtual void blade(){
        cout << name << " sliced an apple!" << endl;
    }
    
    virtual void blade(Pokemon &attackedPokemon){
        cout << name << " made a quick slice move on " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon, strengths, weaknesses);
    }
};


class Charizard : public Fire{
    public:
    Charizard(){
        name = "Charizard"; 
        maxHealth = health = 75;
        attackPower = 17;
        type.push_back("Fire");
    }
};

class Crabominable : public Fighting, public Ice{
    public:
    Crabominable(){
        name = "Cramobinable";
        maxHealth = health = 70;
        attackPower = 14;
        type.push_back("Fighting");
        type.push_back("Ice");
    }
};

class Eiscue : public Ice{
    public:
    Eiscue(){
        name = "Eiscue";
        maxHealth = health = 64;
        attackPower = 16;
        expGainMultiplier = 1.5;
        type.push_back("Ice");
    }
};

class Jolteon : public Electric{
    public:
    Jolteon(){
        name = "Jolteon";
        maxHealth = health = 80;
        attackPower = 15;
        type.push_back("Electric");
    }
};

class Plusle : public Electric{
    public:
    Plusle(){
        name = "Plusle";
        maxHealth = health = 60;
        attackPower = 20;
        expGainMultiplier = 1.25;
        type.push_back("Electric");
    }
};

class Rockruff : public Rock{
    public:
    Rockruff(){
        name = "Rockruff";
        maxHealth = health = 90;
        attackPower = 12;
        type.push_back("Rock");
    }
};

class Registeel : public Steel{
    public:
    Registeel(){
        name = "Registeel";
        maxHealth = health = 100;
        attackPower = 8;
        type.push_back("Steel");
    }
};

class Kartana : public Grass, public Steel{
    public:
    Kartana(){
        name = "Kartana";
        maxHealth = health = 50;
        attackPower = 25;
        type.push_back("Steel");
        type.push_back("Grass");
    }
};