vector<string> convertStrenght(string wantedType){
    vector<string> returnedStrenghts;
    if(wantedType == "Fire"){
        returnedStrenghts.push_back("Ice");
        returnedStrenghts.push_back("Grass");
        return returnedStrenghts;
    }
    if(wantedType == "Water"){
        returnedStrenghts.push_back("Fire");
        returnedStrenghts.push_back("Rock");
        return returnedStrenghts;
    }
    if(wantedType == "Ice"){
        returnedStrenghts.push_back("Dragon");
        returnedStrenghts.push_back("Grass");
        return returnedStrenghts;
    }
    if(wantedType == "Fighting"){
        returnedStrenghts.push_back("Ice");
        returnedStrenghts.push_back("Rock");
        return returnedStrenghts;
    }
    if(wantedType == "Electric"){
        returnedStrenghts.push_back("Water");
        returnedStrenghts.push_back("Steel");
        return returnedStrenghts;
    }
    if(wantedType == "Grass"){
        returnedStrenghts.push_back("Water");
        returnedStrenghts.push_back("Rock");
        return returnedStrenghts;
    }
    if(wantedType == "Rock"){
        returnedStrenghts.push_back("Fire");
        returnedStrenghts.push_back("Ice");
        return returnedStrenghts;
    }
    if(wantedType == "Steel"){
        returnedStrenghts.push_back("Ice");
        returnedStrenghts.push_back("Rock");
        return returnedStrenghts;
    }
    else return returnedStrenghts;
}

vector<string> convertWeakness(string wantedType){
    vector<string> returnedWeaknesses;
    if(wantedType == "Fire"){
        returnedWeaknesses.push_back("Water");
        returnedWeaknesses.push_back("Rock");
        return returnedWeaknesses;
    }
    if(wantedType == "Ice"){
        returnedWeaknesses.push_back("Fire");
        returnedWeaknesses.push_back("Ice");
        return returnedWeaknesses;
    }
    if(wantedType == "Fighting"){
        returnedWeaknesses.push_back("Fairy");
        returnedWeaknesses.push_back("Water");
        return returnedWeaknesses;
    }
    if(wantedType == "Electric"){
        returnedWeaknesses.push_back("Grass");
        returnedWeaknesses.push_back("Electric");
        return returnedWeaknesses;
    }
    if(wantedType == "Grass"){
        returnedWeaknesses.push_back("Grass");
        returnedWeaknesses.push_back("Fire");
        return returnedWeaknesses;
    }
    if(wantedType == "Rock"){
        returnedWeaknesses.push_back("Fighting");
        returnedWeaknesses.push_back("Steel");
        return returnedWeaknesses;
    }
    if(wantedType == "Steel"){
        returnedWeaknesses.push_back("Fire");
        returnedWeaknesses.push_back("Water");
        return returnedWeaknesses;
    }
    else return returnedWeaknesses;
}


void assignTypeFeatures(){
    for(int i = 0; i < allPokemons.size(); i++){
        allPokemons[i]->attackNames.clear();
        if(allPokemons[i]->type.size() > 1){
            if(allPokemons[i]->type[0] == "Fire"){
            allPokemons[i]->attackNames.push_back("Fire");}

            if(allPokemons[i]->type[0] == "Fighting"){
            allPokemons[i]->attackNames.push_back("Fight");}

            if(allPokemons[i]->type[0] == "Water"){
            allPokemons[i]->attackNames.push_back("Spray");}

            if(allPokemons[i]->type[0] == "Ice"){
            allPokemons[i]->attackNames.push_back("Freeze");}

            if(allPokemons[i]->type[0] == "Electric"){
            allPokemons[i]->attackNames.push_back("Electrocute");}

            if(allPokemons[i]->type[0] == "Grass"){
            allPokemons[i]->attackNames.push_back("Ivy");}

            if(allPokemons[i]->type[0] == "Rock"){
            allPokemons[i]->attackNames.push_back("Boulder");}

            if(allPokemons[i]->type[0] == "Steel"){
            allPokemons[i]->attackNames.push_back("Blade");}

            
            if(allPokemons[i]->type[1] == "Fire"){
            allPokemons[i]->attackNames.push_back("Fire");}

            if(allPokemons[i]->type[1] == "Fighting"){
            allPokemons[i]->attackNames.push_back("Fight");}

            if(allPokemons[i]->type[1] == "Water"){
            allPokemons[i]->attackNames.push_back("Spray");}

            if(allPokemons[i]->type[1] == "Ice"){
            allPokemons[i]->attackNames.push_back("Freeze");}

            if(allPokemons[i]->type[1] == "Electric"){
            allPokemons[i]->attackNames.push_back("Electrocute");}

            if(allPokemons[i]->type[1] == "Grass"){
            allPokemons[i]->attackNames.push_back("Ivy");}

            if(allPokemons[i]->type[1] == "Rock"){
            allPokemons[i]->attackNames.push_back("Boulder");}

            if(allPokemons[i]->type[1] == "Steel"){
            allPokemons[i]->attackNames.push_back("Blade");}
            
        }else if(allPokemons[i]->type.size() == 1){
            if(allPokemons[i]->type[0] == "Fire"){
            allPokemons[i]->attackNames.push_back("Fire");}

            if(allPokemons[i]->type[0] == "Fighting"){
            allPokemons[i]->attackNames.push_back("Fight");}

            if(allPokemons[i]->type[0] == "Water"){
            allPokemons[i]->attackNames.push_back("Spray");}

            if(allPokemons[i]->type[0] == "Ice"){
            allPokemons[i]->attackNames.push_back("Freeze");}

            if(allPokemons[i]->type[0] == "Electric"){
            allPokemons[i]->attackNames.push_back("Electrocute");}

            if(allPokemons[i]->type[0] == "Grass"){
            allPokemons[i]->attackNames.push_back("Ivy");}

            if(allPokemons[i]->type[0] == "Rock"){
            allPokemons[i]->attackNames.push_back("Boulder");}

            if(allPokemons[i]->type[0] == "Steel"){
            allPokemons[i]->attackNames.push_back("Blade");}
        }
    }
}