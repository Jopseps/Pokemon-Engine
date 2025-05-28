#pragma once

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Team;

class Trainer{
    public:
    string trainerName;
    float trainerExpMultiplier;
    Trainer(string tN, float tEM){
        trainerName = tN;
        trainerExpMultiplier = tEM;
    }

    Trainer(){
        trainerName = "Unknown";
        trainerExpMultiplier = 1;
    }
};

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
    
    static string type;
   
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;

    Team* assignedTeam;

    Trainer* assignedTrainer;

    // Bunda static aşşa tarafa int yazıp postalıyon
    // Static sadece hangi tarafta static olduğunu belirtmek içün
    static int PokemonCount;
    Pokemon(){
        name = "Unknown";
        maxHealth, health = 1;
        attackPower = 1;
        
        if(type == "Fire"){
            strengths.push_back("Ice");
            strengths.push_back("Grass");
            weaknesses.push_back("Water");
            weaknesses.push_back("Rock");
        }
    }

    Pokemon(string n, int h, int aP){
        name = n;
        maxHealth, health = h;
        attackPower = aP;
    }


    void assignTrainer(Trainer* currentAssignedTrainer){
        assignedTrainer = currentAssignedTrainer;
    }

    void unassignTrainer(){
        assignedTrainer = nullptr;
    }
    

    void gainExp(float amount){
        if(assignedTrainer != nullptr){        // Arrow operator GOATED !del
            exp += amount * expGainMultiplier * assignedTrainer->trainerExpMultiplier;
        }else{
            exp += amount * expGainMultiplier;
        }
    }

    void levelUp(int quantity){
        level += quantity;
        exp -= levelUpThreshold;
        levelUpThreshold =  solidLevelUpThreshold * pow(level, 2/3);
        
    }

    void pokedex(){
        for(int i = 1; i <= 20; i++){cout << "-"; if(i == 10) cout << " Pokedex ";}; cout << endl;
        cout << "Name: " << name << endl;
        cout << "Health: " << health << "/" << maxHealth << endl;
        cout << "Attack Power: " << attackPower << endl;
        cout << "Level: " << level << endl;
        cout << "Experience: " << exp << "/" << levelUpThreshold << "\n" << endl;
        cout << "Strong against: "; 
        
        if(size(strengths) >= 1){
            for(int i = 0; i < size(strengths); i++){
                cout << strengths[0];
                if(i != size(strengths)) cout << ", ";
            }
            cout << endl;
        }
            else{cout << "This Pokemon isn't strong against any type" << endl;}

        cout << "Weak against: "; 
        
        if(size(weaknesses) >= 1){
            for(int i = 0; i < size(weaknesses); i++){
                cout << weaknesses[0];
                if(i != size(weaknesses)) cout << ", ";
            }
            cout << endl;
        }
            else{cout << "This Pokemon isn't weak against any type" << endl;}

        for(int i = 1; i <= 29; i++) cout << "-"; cout << endl;


    }

    // Can be merged Birleştirilebilir mana
    virtual bool checkStrenghts(string searchedType){
        for(int i = 0; i < size(strengths); i++){
            if(searchedType == strengths[i]) return true;
        }
        return false;
    }

    virtual bool checkWeakness(string searchedType){
        for(int i = 0; i < size(weaknesses); i++){
            if(searchedType == weaknesses[i]) return true;
        }
        return false;
    }
};

int Pokemon::PokemonCount = 0;



class Fire : public Pokemon{
    public:
    string type = "Fire";
    virtual void fire(){
        cout << name << " breathed fire!" << endl;
    }
};

class Fighting : public Pokemon{
    public:
    virtual void fight(){
        cout << name << " showed its fighting skills!" << endl;
    }
};

class Water : public Pokemon{
    public:
    virtual void spray(){
        cout << name << " sprayed water!" << endl;
    }
};

class Ice : public Pokemon{
    public:
    virtual void freeze(){
        cout << name << " rained a few snowflakes!" << endl;
    }
};

class Electric : public Pokemon{
    public:
    virtual void electrocute(){
        cout << name << " casually lighted a light bulb!" << endl;
    }
};

class Charizard : public Fire{
    public:
    Charizard(){
        name = "Charizard"; 
        maxHealth = health = 75;
        attackPower = 17;
    }
};

class Machamp : public Fighting{
    public:
    Machamp(){
        name = "Machamp";
        maxHealth = health = 96;
        attackPower = 11;
    }
};

class Eiscue : public Ice{
    public:
    Eiscue(){
        name = "Eiscue";
        maxHealth = health = 64;
        attackPower = 16;
        expGainMultiplier = 1.5;
    }
};

class Jolteon : public Electric{
    public:
    Jolteon(){
        name = "Jolteon";
        maxHealth = health = 80;
        attackPower = 15;
        
    }
};