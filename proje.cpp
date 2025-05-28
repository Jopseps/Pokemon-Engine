#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

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
        maxHealth, health = 1;
        attackPower = 1;
        allPokemons.push_back(this);
    }

    Pokemon(string n, int h, int aP){
        name = n;
        maxHealth, health = h;
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

    }

}


class Fire : public Pokemon{
    public:
    
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

class Team{
    public:
    string teamName;
    vector<Pokemon> teamMembers;
    unsigned int teamMemberCount = 0;
    
    Team(string tN){
        teamName = tN;
    }
    Team(){
        teamName = "Unknown";
    }

    void addMember(Pokemon &addedMember){
        teamMembers.push_back(addedMember);
        addedMember.assignedTeam = this;
        teamMemberCount ++;
    }

    void displayMembers(){
        for(int i = 1; i <= 20; i++){cout << "-"; if(i == 10) cout << "Team " << teamName;}; cout << endl;

            if(teamMemberCount != 0){
                cout << "Members of "<< teamName << ":" << endl;
                for(int i = 0; i < teamMemberCount; i++){
                            cout << i + 1 << ". " << teamMembers[i].name << "   " << teamMembers[i].level << "   " << teamMembers[i].exp << "/" << teamMembers[i].levelUpThreshold << endl;
                        }
            }else cout << teamName << " doesn't have members yet" << endl;
        


        for(int i = 1; i <= 34; i++)cout << "-"; cout << endl;

    }


};







int main(){
    Charizard charizard;
    Machamp machamp;
    Eiscue eiscue;
    Jolteon jolteon;

    assignTypeFeatures();

    eiscue.pokedex();

    Team OGLER = {"OGLER"};

    OGLER.addMember(charizard);
    OGLER.addMember(machamp);
    OGLER.addMember(eiscue);
    OGLER.addMember(jolteon);

    OGLER.displayMembers();
}
