// Documentation
/*
    Pedro Augusto Faria - Computer Engineering student
    This file implements the function definitions for the graphical ascii
    based features, and the game logic aswell.
*/


// Protection against multi-include
#ifndef SRC_H
#define SRC_H

// Included headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "src.h"


// Function definitions

/*
    displayMenu() implements a simple ascii menu for the game. It does not require
    any arguments and returns nothing. 
*/
void displayMenu(void) {
    printf(

        CLEAR_TERMINAL // ANSI escape sequence that clears the terminal
        
        "____________________________________________________________\n"
        "|                                                           |\n"                                                          
        "|                      "GREEN_COLOR"Hack the World!"RESET_COLOR"                      |\n"   
        "|                                                           |\n"   
        "|    "GREEN_COLOR"You are a young, newbie hacker trying to earn some"RESET_COLOR"     |\n"   
        "|    "GREEN_COLOR"illicit money. Hack everything, and show the world"RESET_COLOR"     |\n"   
        "|    "GREEN_COLOR"what you can do. Give those NSA bastards a lesson!"RESET_COLOR"     |\n"   
        "|                                                           |\n"   
        "|                      "GREEN_COLOR"Press:"RESET_COLOR"                               |\n"   
        "|                       "LIGHT_BLUE_COLOR"'S' to start"RESET_COLOR"                        |\n"   
        "|                       "RED_COLOR"'Q' to quit"RESET_COLOR"                         |\n"   
        "|                                                           |\n"
        "|         "GREEN_COLOR"And do not forget, stopping your jorney"RESET_COLOR"           |\n" 
        "|         "GREEN_COLOR"will make NSA to get you, and you will"RESET_COLOR"            |\n" 
        "|         "GREEN_COLOR"need to start it all over again!"RESET_COLOR"                  |\n"
        "|                                                           |\n"     
        "_____________________________________________________________\n"
        
    );
}


/*
    displayLoadingBar() implements an ascii loading bar for the game. The loading
    bars represent the business progress for that instance, like in the Adventure
    Capitalist game. 

    The function receives 9 arguments:
        int x: The x position to be printed in the terminal
        int y: The y position to be printed in the terminal
        char* name: The name of the loading bar
        double profit: The profit from one completion of that loading bar
        double frequency: Times the bar finishes per second
        int length: The number of slots for a full loading bar
        int curr_state: The current number of slots that are loaded
        int too_fast: The loading bat is too fast to be loaded
*/
void displayLoadingBar(int x, int y, char* name, double profit, double exp_gain, double cooldown, int length, int curr_state, int too_fast){

    if ((int)strlen(name) > 49)
    {
        puts("Error: Name of Loading Bar exceeded the limit for neat formatting");
        exit(EXIT_FAILURE);
    }

    printf("\033[%d;%dH", y, x);

    printf(
    "____________________________________________________________\n"
    "|                                                           |\n"
    "|     "LIGHT_BLUE_COLOR"%-50s"RESET_COLOR"    |\n"
    "|                                                           |\n"
    "|       "LIGHT_BLUE_COLOR"Profit: %-10.2e"RESET_COLOR"                                  |\n"
    "|    "LIGHT_BLUE_COLOR"Exp. Gain: %-10.2e"RESET_COLOR"                                  |\n"
    "|    "LIGHT_BLUE_COLOR"Cooldown : %4.2lf"RESET_COLOR"                                  |\n"
    "|                                                           |\n"

    , name, profit, exp_gain, cooldown
    );

    printf(" ");

    if (too_fast)
    {
        printf(LIGHT_BLUE_COLOR);
        for (int i = 0; i < length; i++)
        {
            printf("#");
        }
        printf(RESET_COLOR);
        printf("\n");
    }
    else
    {
        printf(GREEN_COLOR);
        for (int i = 0; i < curr_state; i++)
        {
            printf("#");
        }
        
        printf(RED_COLOR);
        for (int i = curr_state; i < length; i++)
        {
            printf("#");
        }
        printf(RESET_COLOR);
        printf("\n");
    }

    return;
}


/*
    displayShopping() implements an ascii shopping menu for the game. The shopping contains new hacking enterprises
    for the player to buy and increase his profit.

    The function receives 4 arguments:
        struct hacking_enterprise** enterprises: An array of pointers to hacking_enterprise structures that control the behavior of the shop
        int n_enterprises: The number of enterprises in the struct array
        double money: The player's money at the moment
        int buying_option: The current selected option for buying by the player
*/
void displayShopping(struct hacking_enterprise** enterprises, int n_enterprises, double money, int buying_option){
    
    printf(

        CLEAR_TERMINAL // ANSI escape sequence that clears the terminal

        "________________________________________________________________\n"
        "|                                                              |\n"                                                          
        "|                     "GREEN_COLOR"The Hacking Shop:"RESET_COLOR"                        |\n"   
        "|                                                              |\n"   
        "|    "GREEN_COLOR"Here you will find new hacking enterprises to expand"RESET_COLOR"      |\n"   
        "|    "GREEN_COLOR"your hacking empire. But they come at a cost, so be"RESET_COLOR"       |\n"   
        "|    "GREEN_COLOR"aware, and choose wisely. Also, some of them are"RESET_COLOR"          |\n"
        "|    "GREEN_COLOR"dangerous for you to get caught. Be careful!"RESET_COLOR"              |\n"
        "|                                                              |\n"   
        "|                                                              |\n"   
        "|             "GREEN_COLOR"Press the number of the enterprise"RESET_COLOR"               |\n"
        "|             "GREEN_COLOR"to select it, and then press 'B' to"RESET_COLOR"              |\n"
        "|             "GREEN_COLOR"buy it, if it has a price, or 'D' to"RESET_COLOR"             |\n"
        "|             "GREEN_COLOR"dismiss and choose another one. Also,"RESET_COLOR"            |\n"
        "|             "GREEN_COLOR"press 'Q' to go back into the mainpage"RESET_COLOR"           |\n"
        "|                                                              |\n"
        "|                  "GREEN_COLOR"Your Money:"RESET_COLOR" "LIGHT_BLUE_COLOR"%-20.2e"RESET_COLOR"            |\n"
        "|                                                              |\n"
        "|                      "GREEN_COLOR"Current Selected:"RESET_COLOR"                       |\n"
        "|                                                              |\n"
        "|     "LIGHT_BLUE_COLOR"(%2d): %-50s"RESET_COLOR" |\n"
        "|     "LIGHT_BLUE_COLOR"Price: %-10.2lf"RESET_COLOR"                                        |\n"
        "|                                                              |\n"     
        "________________________________________________________________\n"

        , money, buying_option, enterprises[buying_option]->name, enterprises[buying_option]->cost

    );

    for (int i = 0; i < n_enterprises; i++)
    {
        char description_part1[57] = "", description_part2[57] = "", description_part3[57] = "";

        int description_length = strlen(enterprises[i]->description);

        // Copy the first 56 characters of the description to description_part1
        if (description_length > 0) {
            strncpy(description_part1, enterprises[i]->description, description_length < 56 ? description_length : 56);
            description_part1[56] = '\0'; // Null-terminate the string
        }

        // Copy the next 56 characters of the description to description_part2
        if (description_length > 56) {
            strncpy(description_part2, enterprises[i]->description + 56, description_length < 112 ? description_length - 56 : 56);
            description_part2[56] = '\0'; // Null-terminate the string
        }

        // Copy the remaining characters of the description to description_part3
        if (description_length > 112) {
            strncpy(description_part3, enterprises[i]->description + 112, description_length - 112);
            description_part3[56] = '\0'; // Null-terminate the string
        }

        printf(

            "|                                                              |\n"
            "|      %-15s                                               |\n"
            "|                                                              |\n"
            "|     "GREEN_COLOR"(%-2d):"RESET_COLOR" %-50s |\n"
            "|     "GREEN_COLOR"Price:"RESET_COLOR" %-10.2lf                                        |\n"
            "|     "GREEN_COLOR"Min. Experience:"RESET_COLOR" %-10.2lf                              |\n"
            "|     "GREEN_COLOR"Profit:"RESET_COLOR" %-10.2lf                                       |\n"
            "|     "GREEN_COLOR"Exp. Gain:"RESET_COLOR" %-10.2lf                                    |\n"
            "|     "GREEN_COLOR"Cooldown:"RESET_COLOR" %6.2lf                                         |\n"
            "|                                                              |\n"
            "|     "GREEN_COLOR"Description:"RESET_COLOR"                                             |\n"
            "|                                                              |\n"
            "|     %-56s |\n"
            "|     %-56s |\n"
            "|     %-56s |\n"
            "|                                                              |\n"
            "________________________________________________________________\n"
            
            , enterprises[i]->on ? LIGHT_BLUE_COLOR"AVAILABLE"RESET_COLOR : RED_COLOR"SOLD OUT"RESET_COLOR, i, enterprises[i]->name, enterprises[i]->cost
            , enterprises[i]->min_experience, enterprises[i]->profit, enterprises[i]->exp_gain ,enterprises[i]->cooldown 
            , description_part1, description_part2, description_part3
        
        );
    }
}


// void displayLoadingBar(int x, int y, char* name, double profit, double cooldown, int length, int curr_state, int too_fast)

// test main function that will be commented later
int main(){

    // Declare an array of pointers to hacking_enterprise structs
    hacking_enterprise* enterprises[3];

    // Allocate memory for one element
    enterprises[0] = malloc(sizeof(hacking_enterprise));
    enterprises[1] = malloc(sizeof(hacking_enterprise));
    enterprises[2] = malloc(sizeof(hacking_enterprise));

    // Check if the memory was successfully allocated
    if (enterprises[0] == NULL) {
        fprintf(stderr, "Failed to allocate memory for hacking_enterprise.\n");
        exit(1);
    }

    // Initialize the elements
    enterprises[0]->name = strdup("Phishing old people with girl profile pic");
    enterprises[0]->description = strdup("Old people love a 20s, everyone knows that. You'll only need a few feet pics, and you're good to go.");
    enterprises[0]->profit = 10;
    enterprises[0]->cooldown = 2;
    enterprises[0]->cost = FREE;
    enterprises[0]->exp_gain = 1;
    enterprises[0]->min_experience = 0;
    enterprises[0]->on = AVAILABLE;

    enterprises[1]->name = strdup("Hacking soda machines");
    enterprises[1]->description = strdup("They are just there, standing, waiting for you  to hack them. And they are everywhere. Why not? You just need a little equipment.");
    enterprises[1]->profit = 25;
    enterprises[1]->cooldown = 5;
    enterprises[1]->min_experience = 10;
    enterprises[1]->exp_gain = 2;
    enterprises[1]->cost = 120;
    enterprises[1]->on = AVAILABLE;

    enterprises[2]->name = strdup("Blackmail your friend using his furry content");
    enterprises[2]->description = strdup("You know that he has  ca lot of furry content, and he is ashamed of it. Why not use it to your advantage? You'll need a little experience though.");
    enterprises[2]->profit = 125;
    enterprises[2]->cooldown = 15;
    enterprises[2]->min_experience = 60;
    enterprises[2]->exp_gain = 5;
    enterprises[2]->cost = FREE;
    enterprises[2]->on = AVAILABLE;

    displayShopping(enterprises, 3, 1000.0, 0);

    printf("\n\n\n\n\n\n");

    return 0;
}

#endif






