// Documentation
/*
    Pedro Augusto Faria - Computer Engineering student
    This header file implements prototypes and data structures for the 
    graphical ascii based features for the game.
*/

// Included headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


// Defined MACRO
#define CLEAR_TERMINAL "\033[2J\033[H" // ANSI escape sequence that clears the terminal
#define RED_COLOR   "\033[31m"
#define GREEN_COLOR "\033[32m"
#define LIGHT_BLUE_COLOR "\033[96m"
#define RESET_COLOR "\033[0m" // Reset text color to default

#define LOADING_BAR_LENGTH 59
#define LOADING_BAR_VERTICAL_SPACING 11
#define TRUE 1
#define FALSE 0
#define AVAILABLE 1
#define SOLD_OUT 0
#define BLOCKED 2

#define LOADING_BAR_MIN_COOLDOWN 0.002f

#define ENTERPRISE_NUM 5

#define FREE 0


// types and globalss
typedef struct hacking_enterprise {

    char* name;
    char* description;
    double profit;
    double exp_gain;
    double cooldown;
    double cost;
    double min_experience;
    int on;

} hacking_enterprise;


// Function prototypes

void displayMenu(void);

void displayLoadingBar(int x, int y, char* name, double profit, double exp_gain, double cooldown, int length, int curr_state, int too_fast);

void displayShopping(struct hacking_enterprise** enterprises, int n_enterprises, double money, int buying_option);
