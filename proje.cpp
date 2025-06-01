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
    
    vector<string> type;
   
    

    

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
        
        if(type.size() > 1 && type[1] != ""){
            cout << "Type: " << type[0] << " " << type[1] << endl;
        }else if(type.size() > 0){
            cout << "Type: " << type[0] << endl;
        }else{
            cout << "Type: Unknown" << endl;
        }

        cout << "Level: " << level << endl;
        cout << "Experience: " << exp << "/" << levelUpThreshold << "\n" << endl;
        
        /*
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
        */

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
                                        // This types strenghts and weaknesses
    void attack(Pokemon &attackedPokemon, vector<string> s, vector<string> w){
        gainExp(damage(attackedPokemon, calculateDamage(attackedPokemon, s, w))) ;
    }
};

int Pokemon::PokemonCount = 0;







class Fire : public Pokemon{
    public:
    static vector<string> strengths;

    // Counters this Pokemon
    static vector<string> weaknesses;
    
    string attackName = "Fire";
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

    string attackName = "Fight";
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
    
    string attackName = "Spray";
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
    
    string attackName = "Freeze";
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
    
    string attackName = "Electrocute";
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
    
    string attackName = "Ivy";
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
    
    string attackName = "Boulder";
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

    string attackName = "Blade";
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

class Machamp : public Fighting{
    public:
    Machamp(){
        name = "Machamp";
        maxHealth = health = 96;
        attackPower = 11;
        type.push_back("Fighting");
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

        // Type
        for(int i = 0; i < currentTeam.teamMemberCount; i++){               // Pointerdan her daim -> Arrow operator (goat) çıkıyo
            tempCharacterCount = characterBetweenTwo - CalculateStringLength(currentTeam.teamMembers[i]->type[0]);
            
            if(currentTeam.teamMembers[i]->type.size() > 1 && currentTeam.teamMembers[i]->type[1] != ""){

            tempCharacterCount = characterBetweenTwo - (CalculateStringLength(currentTeam.teamMembers[i]->type[0]) + CalculateStringLength(currentTeam.teamMembers[i]->type[1]));
            
            }else if(currentTeam.teamMembers[i]->type.size() > 0){
                tempCharacterCount = characterBetweenTwo - (CalculateStringLength(currentTeam.teamMembers[i]->type[0]));
            }else{
                tempCharacterCount = characterBetweenTwo;
            }


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
        drawAttackGUI();
        


    }
                                                    // Who's turn
    Pokemon *selectAttackedPokemon(Team *attackedTeam, int wT){
        selectedPokemon = 1;
        bool isPokemonSelected = false;
        char pressedButton = '0';
        Pokemon *SelectedAttackedPokemonPtr = nullptr;
        cout << "Hello" << endl;
        while(isPokemonSelected == false){
            cout << "DEBUG | selectedPokemon = " << selectedPokemon << endl;
            cout << "DEBUG | size(attackedTeam->teamMembers) = " << size(attackedTeam->teamMembers) << endl;
            cout << "DEBUG | attackedTeam->teamName = " << attackedTeam->teamName << endl;
            if(whosTurn == 1){
            updateBattleArena(*Team1, true);
            updateBattleArena(*Team2, false);
            }
            if(whosTurn == 2){
            updateBattleArena(*Team1, false);
            updateBattleArena(*Team2, true);
            }   
            
            pressedButton = '0';
            pressedButton = getArrowKey(); 
            if(pressedButton == 'd'){
                if(selectedPokemon < size(attackedTeam->teamMembers)) selectedPokemon++;
            }
            if(pressedButton == 'a'){
                if(selectedPokemon > 1) selectedPokemon--;
            }
            if(pressedButton == 'y' || pressedButton == 'Y'){
                cout << "Pokemon selected | DEBUG" << endl;
                    SelectedAttackedPokemonPtr = attackedTeam->teamMembers[selectedPokemon - 1];
                    isPokemonSelected = true;
                    return SelectedAttackedPokemonPtr;
            }
            else if(pressedButton != 'a' && pressedButton != 'd' && pressedButton != 'y' && pressedButton != 'Y' || pressedButton != '\n'){
                cout << "Invalid button try again" << endl;
            }
            

        }
    return nullptr;
    }

    Pokemon *selectAttackingPokemon(Team *attackingTeam, int wT){
        selectedPokemon = 1;
        bool isPokemonSelected = false;
        char pressedButton = '0';
        Pokemon *SelectedAttackingPokemonPtr = nullptr;
        cout << "Hello" << endl;
        while(isPokemonSelected == false){
            if(whosTurn == 1){
            updateBattleArena(*Team1, false);
            updateBattleArena(*Team2, true);
            }
            if(whosTurn == 2){
            updateBattleArena(*Team1, true);
            updateBattleArena(*Team2, false);
            }  

            pressedButton = '0';
            pressedButton = getArrowKey(); 
            if(pressedButton == 'd'){
                if(selectedPokemon < size(attackingTeam->teamMembers)) selectedPokemon++;
            }
            if(pressedButton == 'a'){
                if(selectedPokemon > 1) selectedPokemon--;
            }
            if(pressedButton == 'y' || pressedButton == 'Y'){
                cout << "Pokemon selected | DEBUG" << endl;
                    SelectedAttackingPokemonPtr = attackingTeam->teamMembers[selectedPokemon - 1];
                    isPokemonSelected = true;
                    return SelectedAttackingPokemonPtr;
            }
            else if(pressedButton != 'a' && pressedButton != 'd' && pressedButton != 'y' && pressedButton != 'Y'){
                cout << "Invalid button try again" << endl;
            }
             

        }
    return nullptr;
    }

    
    Pokemon getAttackingPokemon(){
        if(whosTurn == 1){
            return *Team1->teamMembers[selectedAttackingPokemon - 1];
        }
        if(whosTurn == 2){
            return *Team2->teamMembers[selectedAttackingPokemon - 1];
        }
    }

    void displayBattleInfo(){



    }

    /*void selectAttackMove(const Pokemon *attackingPokemon){
        int selectedMove = 1;
        cout << "Select the attack type to attack" << endl;

        
        if(size(attackingPokemon->type) > 1){
            

        }



    }*/

    void displayAttackMove(const Pokemon *attackedPokemon, const Pokemon *attackingPokemon){
        cout << endl;


        int tempCharacterCount;


        tempCharacterCount = characterBetweenTwo - CalculateStringLength(attackingPokemon->type[0]);
        
        if(attackingPokemon->type.size() > 1 && attackingPokemon->type[1] != ""){

            tempCharacterCount = characterBetweenTwo - (CalculateStringLength(attackingPokemon->type[0]) + CalculateStringLength(attackingPokemon->type[1]));
        
        }else if(attackingPokemon->type.size() > 0){
            tempCharacterCount = characterBetweenTwo - (CalculateStringLength(attackingPokemon->type[0]));
        }else{
            tempCharacterCount = characterBetweenTwo;
        }


        for(int i = 0; i < tempCharacterCount; i++){
            cout << " ";
        }

        

        

        cout << endl;

    }

    void drawAttackGUI(){

        cout << "Select a Pokemon to attack"<<  endl;
        Pokemon *attackedPokemon;
        if(whosTurn == 1){
            displayBattlingTeam(*Team1);
            attackedPokemon = selectAttackedPokemon(Team2, whosTurn);

        };
        if(whosTurn == 2){
            displayBattlingTeam(*Team2);
            attackedPokemon = selectAttackedPokemon(Team1, whosTurn);

        };
        
        cout << "Select a Pokemon to attack " << attackedPokemon->name <<  endl;
        Pokemon *attackingPokemon;
        if(whosTurn == 1){
            displayBattlingTeam(*Team1);
            attackingPokemon = selectAttackingPokemon(Team1, whosTurn);

        };
        if(whosTurn == 2){
            displayBattlingTeam(*Team2);
            attackingPokemon = selectAttackingPokemon(Team2, whosTurn);

        };

        



    }

    void preAttack(Team *attackedTeam, Team *attackingTeam, int wT){
        battleAttack(selectAttackedPokemon(attackedTeam, wT), selectAttackingPokemon(attackingTeam, wT));
    }

    void battleAttack(Pokemon *attackedPokemon, Pokemon *attackingPokemon){
        

        
        //drawAttackGUI();
 


    }


    






};

/*void updateBattle(){


}

void battle(Team &Team1, Team &Team2){


}*/

vector<string> Fire::strengths;
vector<string> Fire::weaknesses;
vector<string> Fighting::strengths;
vector<string> Fighting::weaknesses;
vector<string> Water::strengths;
vector<string> Water::weaknesses;
vector<string> Ice::strengths;
vector<string> Ice::weaknesses;
vector<string> Electric::strengths;
vector<string> Electric::weaknesses;
vector<string> Grass::strengths;
vector<string> Grass::weaknesses;
vector<string> Rock::strengths;
vector<string> Rock::weaknesses;
vector<string> Steel::strengths;
vector<string> Steel::weaknesses;

void assignTypeFeatures(){
    // Fire
    Fire::strengths.push_back("Ice");
    Fire::strengths.push_back("Grass");
    Fire::weaknesses.push_back("Water");
    Fire::weaknesses.push_back("Rock");

    // ICE
    Ice::strengths.push_back("Dragon");
    Ice::strengths.push_back("Grass");
    Ice::weaknesses.push_back("Fire");
    Ice::weaknesses.push_back("Ice");

    // FIGHTING
    Fighting::strengths.push_back("Ice");
    Fighting::strengths.push_back("Rock");
    Fighting::weaknesses.push_back("Fairy");
    Fighting::weaknesses.push_back("Water");

    // ELECTRIC
    Electric::strengths.push_back("Water");
    Electric::strengths.push_back("Steel"); // Mana
    Electric::weaknesses.push_back("Grass");
    Electric::weaknesses.push_back("Electric");

    // GRASS
    Grass::strengths.push_back("Water");
    Grass::strengths.push_back("Rock");
    Grass::weaknesses.push_back("Grass");
    Grass::weaknesses.push_back("Fire");
    
    // ROCK
    Rock::strengths.push_back("Fire");
    Rock::strengths.push_back("Ice");
    Rock::weaknesses.push_back("Fighting");
    Rock::weaknesses.push_back("Steel");

    // STEEL
    Steel::strengths.push_back("Ice");
    Steel::strengths.push_back("Rock");
    Steel::weaknesses.push_back("Electric");
    Steel::weaknesses.push_back("Fire");
    Steel::weaknesses.push_back("Water");

}






int main(){
    Charizard charizard;
    Machamp machamp;
    Eiscue eiscue;
    Jolteon jolteon;

    Plusle plusle;
    Rockruff rockruff;
    Registeel registeel;
    Kartana kartana;

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
    Hacilar.addMember(rockruff);
    Hacilar.addMember(registeel);
    Hacilar.addMember(kartana);
    Hacilar.displayMembers();

    eiscue.gainExp(1050);
    
    OGLER.displayMembers();

    kartana.blade();
    kartana.blade(charizard);

    Battle Battle1;
    Battle1.addTeam(&OGLER, 1);
    Battle1.addTeam(&Hacilar, 2);
    Battle1.updateRound();
}


