//
// Created by liams on 22/08/2016.
//

#include "Human.h"

Human::Human(){

}

int Human::getAction() {
    int action;
    while(!(std::cin >> action)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input, please enter another value." << std::endl;
    }
    return action;
}
