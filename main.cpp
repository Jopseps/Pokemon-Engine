#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#include "tools.h"

class Team;
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
vector<string> convertStrenght(string wantedType);
vector<string> convertWeakness(string wantedType);

#include "Pokemons.h"

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
                            cout << i + 1 << ". " << teamMembers[i]->name << "   " << teamMembers[i]->level << "   " << teamMembers[i]->exp << "/" << teamMembers[i]->levelUpThreshold;
                            cout << "   " << teamMembers[i]->health << "/" <<teamMembers[i]->maxHealth << endl;
                        }
            }else cout << teamName << " doesn't have members yet" << endl;
        


        for(int i = 1; i <= 34; i++)cout << "-"; cout << endl;

    }

    void healAllPokemons(){
        for(int i = 0; i < size(teamMembers); i++){
            teamMembers[i]->health = teamMembers[i]->maxHealth;
        }
    }

    bool isTeamDown(){
        for(int i = 0; i < teamMemberCount; i++){
            if(teamMembers[i]->health > 0) return false;
        }
        return true;
    }


};

vector<string> convertStrenght(string wantedType);
vector<string> convertWeakness(string wantedType);

class Battle{
    public:
    Team *Team1;
    Team *Team2;

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
        int tempCharacterCount;

        cout << endl;

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
            tempCharacterCount = characterBetweenTwo - (CalculateStringLength(currentTeam.teamMembers[i]->type[0]) + CalculateStringLength(currentTeam.teamMembers[i]->type[1]) + 2);
            cout << currentTeam.teamMembers[i]->type[0] << ", " << currentTeam.teamMembers[i]->type[1];
            
            }else if(currentTeam.teamMembers[i]->type.size() > 0){
                tempCharacterCount = characterBetweenTwo - (CalculateStringLength(currentTeam.teamMembers[i]->type[0]));
                cout << currentTeam.teamMembers[i]->type[0];
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


                                                    // Who's turn
    Pokemon *selectAttackedPokemon(Team *attackedTeam, int wT){
        selectedPokemon = 1;
        bool isPokemonSelected = false;
        char pressedButton = '0';
        Pokemon *SelectedAttackedPokemonPtr = nullptr;
        while(isPokemonSelected == false){
            cout << endl << "Select a pokemon to attack" << endl;
            // cout << "DEBUG | selectedPokemon = " << selectedPokemon << endl;
            // cout << "DEBUG | size(attackedTeam->teamMembers) = " << size(attackedTeam->teamMembers) << endl;
            // cout << "DEBUG | attackedTeam->teamName = " << attackedTeam->teamName << endl;
            if(whosTurn == 1){
            updateBattleArena(*Team1, true);
            cout << endl;
            cout << endl;
            updateBattleArena(*Team2, false);
            }
            else if(whosTurn == 2){
            updateBattleArena(*Team1, false);
            cout << endl;
            updateBattleArena(*Team2, true);
            cout << endl;
            }   
            
            pressedButton = '0';
            pressedButton = getArrowKey(); 
            if(pressedButton == 'd'){
                if(selectedPokemon < size(attackedTeam->teamMembers)) selectedPokemon++;
            }
            else if(pressedButton == 'a'){
                if(selectedPokemon > 1) selectedPokemon--;
            }
            else if(pressedButton == 'y' || pressedButton == 'Y'){
                // cout << "Pokemon selected | DEBUG" << endl;
                    SelectedAttackedPokemonPtr = attackedTeam->teamMembers[selectedPokemon - 1];
                    isPokemonSelected = true;

                    while((pressedButton = getchar()) != '\n' && pressedButton != EOF){
                        continue;
                    }

                return SelectedAttackedPokemonPtr;
            }
            else if(pressedButton != 'a' && pressedButton != 'd' && pressedButton != 'y' && pressedButton != 'Y'){
                cout << "Invalid button try again" << endl;
                pressedButton = '0';
                
            }
            while((pressedButton = getchar()) != '\n' && pressedButton != EOF){
                continue;
            }
        }
    return nullptr;
    }

    Pokemon *selectAttackingPokemon(Team *attackingTeam, Pokemon *attackedPokemon, int wT){
        selectedPokemon = 1;
        bool isPokemonSelected = false;
        char pressedButton = '0';
        Pokemon *SelectedAttackingPokemonPtr = nullptr;
        while(isPokemonSelected == false){
            cout << endl << "Select a pokemon to attack " << attackedPokemon->name << endl;
            if(whosTurn == 1){
            updateBattleArena(*Team1, false);
            cout << endl;
            updateBattleArena(*Team2, true);
            cout << endl;
            }
            if(whosTurn == 2){
            updateBattleArena(*Team1, true);
            cout << endl;
            cout << endl;
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
                // cout << "Pokemon selected | DEBUG" << endl;
                if(attackingTeam->teamMembers[selectedPokemon - 1]->health == 0){
                    cout << "This Pokemon is fainted" << endl; 

                    while((pressedButton = getchar()) != '\n' && pressedButton != EOF){
                        continue;
                    }
                }else{
                    SelectedAttackingPokemonPtr = attackingTeam->teamMembers[selectedPokemon - 1];
                    isPokemonSelected = true;
                    
                    while((pressedButton = getchar()) != '\n' && pressedButton != EOF){
                        continue;
                    }

                return SelectedAttackingPokemonPtr;
                }
            }
            else if(pressedButton != 'a' && pressedButton != 'd' && pressedButton != 'y' && pressedButton != 'Y'){
                cout << "Invalid button try again" << endl;
                pressedButton = '0';
            }
            while((pressedButton = getchar()) != '\n' && pressedButton != EOF){
                continue;
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

    void displayAttackMove(const Pokemon *attackedPokemon, const Pokemon *attackingPokemon){
        int tempCharacterCount;

        if(attackingPokemon->attackNames.size() > 1 && !attackingPokemon->attackNames[1].empty()){

            tempCharacterCount = characterBetweenTwo - CalculateStringLength(attackingPokemon->attackNames[0]);

            cout << attackingPokemon->attackNames[0];
            for(int i = 0; i < tempCharacterCount; i++){
            cout << " ";
            }
            cout << attackingPokemon->attackNames[1];
        
        }else if(size(attackingPokemon->attackNames) > 0){
            tempCharacterCount = characterBetweenTwo - (CalculateStringLength(attackingPokemon->attackNames[0]));

            cout << attackingPokemon->attackNames[0];

        }else{
            tempCharacterCount = characterBetweenTwo;
        }

        cout << endl;

        // Checking if the attack is strong or weak
        if(attackingPokemon->attackNames.size() > 1 && !attackingPokemon->attackNames[1].empty()){
            bool isItStrong0 = checkIfStrong(convertAttackMove(attackingPokemon->attackNames[0]), attackedPokemon);
            bool isItStrong1 = checkIfStrong(convertAttackMove(attackingPokemon->attackNames[1]), attackedPokemon);
            bool isItWeak0 = checkIfWeak(convertAttackMove(attackingPokemon->attackNames[0]), attackedPokemon);
            bool isItWeak1 = checkIfWeak(convertAttackMove(attackingPokemon->attackNames[1]), attackedPokemon);
            
            if(isItStrong0 == true && isItWeak0 == false){
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Strong");
                cout << "Strong";


            }else if(isItWeak0 == true && isItStrong0 == false){
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Weak");
                cout << "Weak";


            }else{
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Normal");
                cout << "Normal";
            }
            
            for(int i = 0; i < tempCharacterCount; i++){
            cout << " ";
            }

            if(isItStrong1 == true && isItWeak1 == false){
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Strong");
                cout << "Strong";


            }else if(isItWeak1 == true && isItStrong1 == false){
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Weak");
                cout << "Weak";


            }else{
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Normal");
                cout << "Normal";
            }
        
        }else if(size(attackingPokemon->attackNames) > 0 && !attackingPokemon->attackNames[0].empty()){
            bool isItStrong0 = checkIfStrong(convertAttackMove(attackingPokemon->attackNames[0]), attackedPokemon);
            bool isItWeak0 = checkIfWeak(convertAttackMove(attackingPokemon->attackNames[0]), attackedPokemon);
            // tempCharacterCount = characterBetweenTwo - (CalculateStringLength(attackingPokemon->attackNames[0]));
            if(isItStrong0 == true && isItWeak0 == false){
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Strong");
                cout << "Strong";


            }else if(isItWeak0 == true && isItStrong0 == false){
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Weak");
                cout << "Weak";


            }else{
                tempCharacterCount = characterBetweenTwo - CalculateStringLength("Normal");
                cout << "Normal";
            }

        }else{
            tempCharacterCount = characterBetweenTwo;
        }
        cout << endl;
    }



    string selectAttackMove(const Pokemon &attackedPokemon, const Pokemon &attackingPokemon){
        bool isMoveSelected = false;
        int selectedMoveOrder = 1;
        string selectedMove;
        char pressedButton;
        cout << "Select an Attack Move to attack " << attackedPokemon.name << "!" << endl << endl;

        while(isMoveSelected == false){
            displayAttackMove(&attackedPokemon, &attackingPokemon);
            displayArrow(selectedMoveOrder);

            pressedButton = '0';
            pressedButton = getArrowKey(); 
            if(pressedButton == 'd'){
                if(selectedMoveOrder < size(attackingPokemon.attackNames)) selectedMoveOrder++;
            }
            if(pressedButton == 'a'){
                if(selectedMoveOrder > 1) selectedMoveOrder--;
            }
            if(pressedButton == 'y' || pressedButton == 'Y'){
                // cout << "Attack Move selected | DEBUG" << endl;
                    selectedMove = attackingPokemon.attackNames[selectedMoveOrder - 1];
                    isMoveSelected = true;
                    
                    while((pressedButton = getchar()) != '\n' && pressedButton != EOF){
                        continue;
                    }

                    return selectedMove;
            }
            else if(pressedButton != 'a' && pressedButton != 'd' && pressedButton != 'y' && pressedButton != 'Y'){
                cout << "Invalid button try again" << endl;
                pressedButton = '0';
            }
            while((pressedButton = getchar()) != '\n' && pressedButton != EOF){
                continue;
            }

        }
    return "0";    
    }

    string convertAttackMove(string attackMove){
        if(attackMove == "Fire"){
            return "Fire";}
        if(attackMove == "Fight"){
            return "Fighting";}
        if(attackMove == "Spray"){
            return "Water";}
        if(attackMove == "Freeze"){
            return "Ice";}
        if(attackMove == "Electrocute"){
            return "Electric";}
        if(attackMove == "Ivy"){
            return "Grass";}
        if(attackMove == "Boulder"){
            return "Rock";}
        if(attackMove == "Blade"){
            return "Steel";}
        else return "Nothing";
    }


    bool checkIfStrong(string attackType, const Pokemon *attackedPokemon){
        for(int i = 0; i < size(convertStrenght(attackType)); i++){
            for(int j = 0; j < size(attackedPokemon->type); j++){
                if(convertStrenght(attackType)[i] == attackedPokemon->type[j]){
                    return true;
                }
            }
        }
        return false;
    }

    bool checkIfWeak(string attackType, const Pokemon *attackedPokemon){
        for(int i = 0; i < size(convertWeakness(attackType)); i++){
            for(int j = 0; j < size(attackedPokemon->type); j++){
                if(convertWeakness(attackType)[i] == attackedPokemon->type[j]){
                    return true;
                }
            }
        }
    return false;
    }


    void preAttack(Team *attackedTeam, Team *attackingTeam, int wT){
        Pokemon *attackedPokemon = selectAttackedPokemon(attackedTeam, wT);
        Pokemon *attackingPokemon = selectAttackingPokemon(attackingTeam, attackedPokemon, wT);
        string attackMove = selectAttackMove(*attackedPokemon, *attackingPokemon);
        string attackType = convertAttackMove(attackMove);
        battleAttack(attackedPokemon, attackingPokemon, attackType);
    }

    void battleAttack(Pokemon *attackedPokemon, Pokemon *attackingPokemon, string attackType){
        bool isItStrong = checkIfStrong(attackType, attackedPokemon);
        bool isItWeak = checkIfWeak(attackType, attackedPokemon);

        battleDamage(attackingPokemon->attackPower, attackedPokemon, isItStrong, isItWeak);
    }

    void battleDamage(int dmg, Pokemon *attackedPokemon, bool strong, bool weak){
        int damage = dmg;
        if(strong == true) damage *= 2;
        if(weak == true) damage /= 2;

        if(attackedPokemon->health == 0){
            attackedPokemon->health = 0;
            cout << attackedPokemon->name << " is already fainted, are you mad?" << endl;

        }
        else if(attackedPokemon->health <= damage){
            attackedPokemon->health = 0;
            cout << attackedPokemon->name << " is fainted" << endl;

        }
        else if(attackedPokemon->health > damage){
            attackedPokemon->health -= damage;
            cout << attackedPokemon->name << " got " << damage << " damage!" << endl;
        }
    }


    void startBattle(bool healAll){
        round = 1;
        whosTurn = 2;

        if(healAll == true){
            Team1->healAllPokemons();
            Team2->healAllPokemons();  
        }
        
        while(true){   
            if(whosTurn == 1) battleRound(Team2, Team1, 1);
            if(whosTurn == 2) battleRound(Team1, Team2, 2);

            if(Team2->isTeamDown() == true){
                cout << endl << Team1->teamName << " won the battle!" << endl << endl;
                break;
            }
            if(Team1->isTeamDown() == true){
                cout << endl << Team2->teamName << " won the battle!" << endl << endl;
                break;
            }

            if(whosTurn == 1) whosTurn = 2;
            else if(whosTurn == 2) whosTurn = 1;

            round++;
        }

    }

    void battleRound(Team *attackedTeam, Team *attackingTeam, int wT){
        cout << endl << "*-----------------------*" << endl;
        cout << "     Round " << round << endl;
        cout << "     " << attackingTeam->teamName << "'s turn!" << endl;
        cout << "*-----------------------*" << endl;
        preAttack(attackedTeam, attackingTeam, wT);
    }
};


// Includes Pokemon and Battle functions
// and also initialization
#include "PokemonTools.h"

int main(){
    Charizard charizard;
    Crabominable crabominable;
    Eiscue eiscue;
    Jolteon jolteon;

    Plusle plusle;
    Rockruff rockruff;
    Registeel registeel;
    Kartana kartana;

    assignTypeFeatures();

    Trainer trainer1 = {"Chuck", 1.5};
    crabominable.assignTrainer(&trainer1);

    eiscue.pokedex();
    kartana.pokedex();

    Team OGLER = {"OGLER"};

    OGLER.addMember(charizard);
    OGLER.addMember(crabominable);
    OGLER.addMember(eiscue);
    OGLER.addMember(jolteon);

    OGLER.displayMembers();


    Team Hacilar = {"Hacilar"};
    Hacilar.addMember(plusle);
    Hacilar.addMember(rockruff);
    Hacilar.addMember(registeel);
    Hacilar.addMember(kartana);
    Hacilar.displayMembers();

    eiscue.gainExp(1000);
    
    OGLER.displayMembers();

    kartana.blade();
    kartana.blade(rockruff);

    Battle Battle1;
    Battle1.addTeam(&OGLER, 1);
    Battle1.addTeam(&Hacilar, 2);

    Battle1.startBattle(true);
}