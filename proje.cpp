#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#include "tools.h"

class Team;


// 1:61
class Pokemon;

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


vector<Pokemon*> allPokemons;

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
    
    string type;
   
    vector<string> strengths;

    // Counters this Pokemon
    vector<string> weaknesses;

    

    Team* assignedTeam;

    Trainer* assignedTrainer;

    // Bunda static aşşa tarafa int yazıp postalıyon
    // Static sadece hangi tarafta static olduğunu belirtmek içün
    static int PokemonCount;
    Pokemon(){
        name = "Unknown";
        maxHealth = 1;
        health = 1;
        attackPower = 1;
        allPokemons.push_back(this);
    }
    
    Pokemon(string n, int h, int aP){
        name = n;
        maxHealth = h;
        health = h;
        attackPower = aP;
        allPokemons.push_back(this);
        
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
        if(exp >= levelUpThreshold) levelUp();
    }

    void levelUp(){
        while(exp >= levelUpThreshold){
            level++;
            exp -= levelUpThreshold;
            levelUpThreshold =  solidLevelUpThreshold * pow(level, 2/3);
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
        cout << "Type: " << type << endl;
        cout << "Level: " << level << endl;
        cout << "Experience: " << exp << "/" << levelUpThreshold << "\n" << endl;
        cout << "Strong against: "; 
        
        if(size(strengths) >= 1){
            for(int i = 0; i < size(strengths); i++){
                cout << strengths[i];
                if(i != size(strengths)) cout << ", ";
            }
            cout << endl;
        }
            else{cout << "This Pokemon isn't strong against any type" << endl;}

        cout << "Weak against: "; 
        
        if(size(weaknesses) >= 1){
            for(int i = 0; i < size(weaknesses); i++){
                cout << weaknesses[i];
                if(i != size(weaknesses)) cout << ", ";
            }
            cout << endl;
        }
            else{cout << "This Pokemon isn't weak against any type" << endl;}

        for(int i = 1; i <= 29; i++) cout << "-"; cout << endl << endl;


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

    int calculateDamage(const Pokemon &attackedPokemon){
        int damage = attackPower;

        if(checkStrenghts(attackedPokemon.type) == true){
            damage *= 2;
        }
        if(checkWeakness(attackedPokemon.type) == true){
            damage /= 2;
        }

        return damage;
    }

    int damage(Pokemon &attackedPokemon, int dmg){
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

    void attack(Pokemon &attackedPokemon){
        gainExp(damage(attackedPokemon, calculateDamage(attackedPokemon))) ;
    }
};

int Pokemon::PokemonCount = 0;


void assignTypeFeatures(){
    for(int i = 0; i < size(allPokemons); i++){
        if(allPokemons[i]->type == "Fire"){
            allPokemons[i]->strengths.push_back("Ice");
            allPokemons[i]->strengths.push_back("Grass");
            allPokemons[i]->weaknesses.push_back("Water");
            allPokemons[i]->weaknesses.push_back("Rock");
        }

        if(allPokemons[i]->type == "Ice"){
            allPokemons[i]->strengths.push_back("Dragon");
            allPokemons[i]->strengths.push_back("Grass");
            allPokemons[i]->weaknesses.push_back("Fire");
            allPokemons[i]->weaknesses.push_back("Ice");
        }
        if(allPokemons[i]->type == "Fighting"){
            allPokemons[i]->strengths.push_back("Ice");
            allPokemons[i]->strengths.push_back("Rock");
            allPokemons[i]->weaknesses.push_back("Fairy");
            allPokemons[i]->weaknesses.push_back("Water");
        }
        if(allPokemons[i]->type == "Electric"){
            allPokemons[i]->strengths.push_back("Water");
            allPokemons[i]->strengths.push_back("Steel"); // Mana
            allPokemons[i]->weaknesses.push_back("Grass");
            allPokemons[i]->weaknesses.push_back("Electric");
        }
         if(allPokemons[i]->type == "Grass"){
            allPokemons[i]->strengths.push_back("Water");
            allPokemons[i]->strengths.push_back("Rock");
            allPokemons[i]->weaknesses.push_back("Grass");
            allPokemons[i]->weaknesses.push_back("Fire");
        }

    }

}


class Fire : public Pokemon{
    public:
    
    virtual void fire(){
        cout << name << " breathed fire!" << endl;
    }

    virtual void fire(Pokemon &attackedPokemon){
        cout << name << " used fire on " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon);
    }
};



class Fighting : public Pokemon{
    public:
    
    virtual void fight(){
        cout << name << " showed its fighting skills!" << endl;
    }

    virtual void fight(Pokemon &attackedPokemon){
        cout << name << " throwed a solid punch to " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon);
    }
};

class Water : public Pokemon{
    public:
    virtual void spray(){
        cout << name << " sprayed water!" << endl;
    }

    virtual void spray(Pokemon &attackedPokemon){
        cout << name << " sprayed pressured water on " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon);
    }
};

class Ice : public Pokemon{
    public:
    
    virtual void freeze(){
        cout << name << " rained a few snowflakes!" << endl;
    }

    virtual void freeze(Pokemon &attackedPokemon){
        cout << name << " freezed " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon);
    }
};

class Electric : public Pokemon{
    public:
    
    virtual void electrocute(){
        cout << name << " casually lighted a light bulb!" << endl;
    }
    
    virtual void electrocute(Pokemon &attackedPokemon){
        cout << name << " electrocuted " << attackedPokemon.name << "!" << endl;
        attack(attackedPokemon);
    }
};

class Grass : public Pokemon{
    public:
    
    virtual void ivy(){
        cout << name << " showed up a bunch of vines out of the grass!" << endl;
    }
    
    virtual void ivy(Pokemon &attackedPokemon){
        cout << name << " catched " << attackedPokemon.name << " with vines!" << endl;
        attack(attackedPokemon);
    }
};


class Charizard : public Fire{
    public:
    Charizard(){
        name = "Charizard"; 
        maxHealth = health = 75;
        attackPower = 17;
        type = "Fire";
    }
};

class Machamp : public Fighting{
    public:
    Machamp(){
        name = "Machamp";
        maxHealth = health = 96;
        attackPower = 11;
        type = "Fighting";
    }
};

class Eiscue : public Ice{
    public:
    Eiscue(){
        name = "Eiscue";
        maxHealth = health = 64;
        attackPower = 16;
        expGainMultiplier = 1.5;
        type = "Ice";
    }
};

class Jolteon : public Electric{
    public:
    Jolteon(){
        name = "Jolteon";
        maxHealth = health = 80;
        attackPower = 15;
        type = "Electric";
    }
};

class Plusle : public Electric{
    public:
    Plusle(){
        name = "Plusle";
        maxHealth = health = 60;
        attackPower = 20;
        expGainMultiplier = 1.25;
        type = "Electric";
    }
};

class Team{
    public:
    string teamName;
    vector<Pokemon*> teamMembers;
    unsigned int teamMemberCount = 0;
    
    Team(string tN){
        teamName = tN;
    }
    Team(){
        teamName = "Unknown";
    }

    void addMember(Pokemon &addedMember){
        teamMembers.push_back(&addedMember);
        addedMember.assignedTeam = this;
        teamMemberCount ++;
    }

    void displayMembers(){
        for(int i = 1; i <= 20; i++){cout << "-"; if(i == 10) cout << "Team " << teamName;}; cout << endl;

            if(teamMemberCount != 0){
                cout << "Members of "<< teamName << ":" << endl;
                for(int i = 0; i < teamMemberCount; i++){
                            cout << i + 1 << ". " << teamMembers[i]->name << "   " << teamMembers[i]->level << "   " << teamMembers[i]->exp << "/" << teamMembers[i]->levelUpThreshold << endl;
                        }
            }else cout << teamName << " doesn't have members yet" << endl;
        


        for(int i = 1; i <= 34; i++)cout << "-"; cout << endl;

    }

    void healAllPokemons(){
        for(int i = 0; i < size(teamMembers); i++){
            teamMembers[i]->health = teamMembers[i]->maxHealth;
        }
    }


};

class Battle{
    public:
    Team *Team1;
    Team *Team2;
    vector<string> roundLog;

    int round = 1;
    int selectedPokemon = 1;
    int selectedAttackingPokemon = 1;

    // 1 is for Team1 and 2 is for Team2
    int whosTurn = 2;
    
    // Example _C_harizard            _ _ there to here
    int characterBetweenTwo = 20;

    void addTeam(Team *addedTeam, int teamSlot){
        if(teamSlot == 1) Team1 = addedTeam;
        if(teamSlot == 2) Team2 = addedTeam;
    }


    void displayBattlingTeam(Team &currentTeam){
        cout << endl;


        int tempCharacterCount;

        
        
        // Names
        for(int i = 0; i < currentTeam.teamMemberCount; i++){               // Pointerdan her daim -> Arrow operator (goat) çıkıyo
            tempCharacterCount = characterBetweenTwo - CalculateStringLength(currentTeam.teamMembers[i]->name);
            cout << currentTeam.teamMembers[i]->name;
            
            for(int i = 0; i < tempCharacterCount; i++){
                cout << " ";
            }

        }

        cout << endl;
        
        // Health
        for(int i = 0; i < currentTeam.teamMemberCount; i++){
            tempCharacterCount = characterBetweenTwo - (CalculateStringLength(currentTeam.teamMembers[i]->health) + CalculateStringLength(currentTeam.teamMembers[i]->health) + 1);
            cout << currentTeam.teamMembers[i]->health << "/" << currentTeam.teamMembers[i]->maxHealth;
            
            for(int i = 0; i < tempCharacterCount; i++){
                cout << " ";
            }

        }

        cout << endl;

    }

    void displayArrow(int selectedColumn){
        for(int i = 0; i < selectedColumn - 1; i++){
                for(int i = 0; i < characterBetweenTwo; i++){
                    cout << " ";
                }
            }

            cout << "  ↑" << endl;

    }

    // It works like frame_generate()
    void updateBattleArena(Team &currentTeam, bool isItThisTeamsTurn){
        int tempCharacterCount;

        displayBattlingTeam(currentTeam);

        // Arrow
        if(isItThisTeamsTurn == false){
            displayArrow(selectedPokemon);
        }
    }
    void updateRound(){
        if(whosTurn == 1){
            updateBattleArena(*Team1, true);
            updateBattleArena(*Team2, false);

        }
        if(whosTurn == 2){
            updateBattleArena(*Team1, false);
            updateBattleArena(*Team2, true);

        }


    }  
    
    Pokemon selectAttackedPokemon(Team *attackedTeam){
        int currentSelectedPokemon = 1;
        char pressedButton = '0';
        Pokemon *SelectedAttackingPokemonPtr = nullptr;
        cout << "Hello" << endl;
        while(SelectedAttackingPokemonPtr == nullptr){
            pressedButton = getArrowKey(); 
            if(pressedButton == 'd'){
                if(currentSelectedPokemon < size(attackedTeam->teamMembers)) currentSelectedPokemon++;
            }
            if(pressedButton == 'a'){
                if(currentSelectedPokemon > 1) currentSelectedPokemon--;
            }
            if(pressedButton == '\n'){
                cout << "Press enter again to confirm" << endl;
                pressedButton = getArrowKey(); 
                if(pressedButton == '\n'){
                    SelectedAttackingPokemonPtr = attackedTeam->teamMembers[currentSelectedPokemon - 1];
                    return *SelectedAttackingPokemonPtr;
                }
            }
        }
    }

    Pokemon getAttackingPokemon(){
        if(whosTurn == 1){
            return *Team1->teamMembers[selectedAttackingPokemon - 1];
        }
        if(whosTurn == 2){
            return *Team2->teamMembers[selectedAttackingPokemon - 1];
        }
    }

    void drawAttackGUI(Pokemon *attackedPokemon){
        cout << "Select a Pokemon to attack " << attackedPokemon->name << endl;
        Pokemon *attackingPokemon;
        if(whosTurn == 1){
            displayBattlingTeam(*Team1);
            *attackingPokemon = selectAttackedPokemon(Team1);

        };
        if(whosTurn == 2){
            displayBattlingTeam(*Team2);
            *attackingPokemon = selectAttackedPokemon(Team2);

        };



    }

    void attack(Pokemon *attackedPokemon){
        //drawAttackGUI();
 


    }


    






};

/*void updateBattle(){


}

void battle(Team &Team1, Team &Team2){


}*/






int main(){
    Charizard charizard;
    Machamp machamp;
    Eiscue eiscue;
    Jolteon jolteon;

    Plusle plusle;

    assignTypeFeatures();

    eiscue.pokedex();

    Team OGLER = {"OGLER"};

    OGLER.addMember(charizard);
    OGLER.addMember(machamp);
    OGLER.addMember(eiscue);
    OGLER.addMember(jolteon);

    OGLER.displayMembers();

    

    Team Hacilar = {"Hacilar"};
    Hacilar.addMember(plusle);
    Hacilar.displayMembers();

    eiscue.gainExp(1050);
    
    OGLER.displayMembers();

    Battle Battle1;
    Battle1.addTeam(&OGLER, 1);
    Battle1.addTeam(&Hacilar, 2);
    Battle1.updateRound();
}


