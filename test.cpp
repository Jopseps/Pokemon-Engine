#include <iostream>
using namespace std;

class Trainer{};

class Pokemon{
    public:
    Trainer* assignedTrainer = nullptr;

    void assignTrainer(Trainer* );
};