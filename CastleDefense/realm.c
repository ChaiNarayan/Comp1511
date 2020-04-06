// Assignment 2 19T2 COMP1511: Castle Defense

// This program was written by Chaitanya Narayan (z5254637)
// on 24th July 2019

//Castle CSE is under attack by our Enemies from The Lair. 
//King Marc of House Chee, First of His Name, Protector of the Realm, 
//has commissioned you to build His defenses and protect His Castle.
//In this assignment, you will be implementing Castle Defense,
//a program that simulates an imaginary Realm that is under attack. 
//You will be creating Lands in the Realm as well as building Towers to 
//defend a Castle.

// Version 1.0.0 (2019-07-22): Assignment released.
// Version 1.0.1 (2019-07-22): Fix minor style issue with print_tower.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "realm.h"

#define KILLED 1
#define SURVIVED 0
////////////////////////////////////////////////////////////////////////

// `struct realm` represents a realm, which represents the state of the
// entire program. It is mainly used to point to a linked list of 
// locations, though you may want to add other fields to it.
//
// You may need to add fields to struct realm.
struct realm {
    struct location *castle;
    int castle_defense;
    struct location *lair;
};

// `struct location` represents a location, which could be a land,
// a tower, or a castle. Each of those places has a different type
// of information that this struct will need to store.
//
// You will need to add fields to struct location.
struct location {
    char name[MAX_NAME_LENGTH];
    struct enemy *enemies;
    struct location *next;
    int uses;
    int power;
    int type;
    int effect;
    int defense;
};

// `struct enemy` represents an enemy, which will move through the
// realm (to each location). Towers can deal damage to it, and
// it can deal damage to the Castle.
//
// You will need to add fields to struct enemy.
struct enemy {

    char name[MAX_NAME_LENGTH];
    struct enemy *next;
    int max_hp;
    int cur_hp;
    
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Function prototypes for helper functions
static Location new_location(char *name);
static void print_tower(char *name, int power, int uses, Effect effect);
static void print_land(char *name);
static void print_castle(char *name, int defense);
static void print_enemy(char *name, int cur_hp, int max_hp);
static int apply_damage_per_tower(Location curr);

// Add prototypes for any extra functions you create here.
static Location tower_initialise(char *name);
static Enemy enemy_initialise(char *name);
////////////////////////////////////////////////////////////////////////

// You need to implement the following 9 functions.
// In other words, write code to make the function work as described 
// in realm.h.

// Create a new realm, and return a pointer to it.
Realm new_realm(void) {
    struct realm *realm = malloc(sizeof(struct realm));
    realm->lair = new_location("Lair");
    realm->castle = new_location("Castle");
    realm->castle_defense = 100;
    if (realm->lair != NULL && realm->castle != NULL) {
        realm->lair->next = realm->castle;
    }

    return realm;
}

static Location new_location(char *name) {
    
    Location l_node = malloc(sizeof (struct location));
    
    strcpy(l_node->name,name);
    l_node->enemies = NULL;
    l_node->next = NULL;
    l_node->uses = 0;
    l_node->type = TYPE_LAND;
    l_node->power = 0; 
    l_node->effect = 0;
    
    //If the location is the castle then let defense equal #STARTING_CASTLE_HP;    
    //If its not the castle then let defense equal 0
    if (strcmp(name, "Castle") == 0) {
        l_node->defense = STARTING_CASTLE_HP;
    } else {
        l_node->defense = 0;
    }
    
    return l_node;
}

/*///////////////////////////////////////////////////////////////////////
                            Stage 1 Functions                          
///////////////////////////////////////////////////////////////////////*/

// Add a new location to the realm.
void add_location(Realm realm, char *name) {
    struct location *curr = realm->lair;
    while (curr->next != realm->castle) {
        curr = curr->next;
    }
    Location node2 = new_location(name);
    curr->next = node2;
    node2->next = realm->castle;

}

// Print out the realm.
void print_realm(Realm realm) {
    struct location *curr = realm->lair;
    //Loop to the end of the realm 
    while (curr != NULL) {
    
        
        //Printing Castles
        if (curr == realm->castle) {
            print_castle(curr->name, curr->defense);
        } 
        
        //Printing Lands
        //By doing uses equals to 0 we can convert towers into lands
        else if (curr->uses == 0) {
            print_land(curr->name);
        }
        
        //Printing Towers
        else if (curr->type == TYPE_TOWER) {
            print_tower(curr->name, curr->power, curr->uses, EFFECT_NONE);
        } 
        
        
        //Printing Enemies
        Enemy curr_enem = curr->enemies;
        
        while (curr_enem != NULL) {
            print_enemy(curr_enem->name, curr_enem->cur_hp, curr_enem->max_hp);
            curr_enem = curr_enem->next;
        }
        
        curr = curr->next;
    }
}
/*///////////////////////////////////////////////////////////////////////
                            Stage 2 Functions                          
///////////////////////////////////////////////////////////////////////*/

// Add a new tower to the realm.
int new_tower(Realm realm, char *prev_name, char *name, int power, int uses) {
    
    //Calling function for tower     
    Location new_tower = tower_initialise(name);
    
    strcpy(new_tower->name,name);
    new_tower->uses = uses;
    new_tower->power = power;
    
    //If invalid stats are input return the error
    if (power < 1 || uses < 1) {
        return ERROR_INVALID_STAT;
    }    
    Location curr = realm->lair;
    while (strcmp(prev_name, curr->name) != 0) {
        
        if (curr->next == NULL) {
            return ERROR_NO_LOCATION;
        }
        curr = curr->next;
    }

    new_tower->next = curr->next;
    curr->next = new_tower;
    
    
    return SUCCESS;
  
}

// Add an enemy to the realm.
int new_enemy(Realm realm, char *location_name, char *name, int hp) {
    struct location *curr = realm->lair;
    
    //If invalid stats are input
    if (hp < 1) {
        return ERROR_INVALID_STAT;
    }
    //Calling the enemy function
    Enemy new_enemy = enemy_initialise(name);
    
    strcpy(new_enemy->name,name);
    new_enemy->max_hp = hp;
    new_enemy->cur_hp = hp;
    
    curr = realm->lair;
    while (strcmp(location_name, curr->name) != 0) {

        if (curr->next == NULL) {
            return ERROR_NO_LOCATION;
        }
        
        curr = curr->next;
    }

    //Adding single enemies    
    if (curr->enemies == NULL) {
        curr->enemies = new_enemy;
    }
    
    //Adding multiple enemies added at the tail of current enemies
    else { 
        struct enemy *enemy_cur = curr->enemies;
        
        while (enemy_cur->next != NULL) {            
            enemy_cur = enemy_cur->next;
        }
        
        enemy_cur->next = new_enemy;
    }
    
    return SUCCESS;
}

// Advance enemies towards the castle.
int advance_enemies(Realm realm) {
    struct location *curr = realm->lair;
    struct enemy *prev = NULL;
    while (curr != NULL ) {
        struct enemy *curr_enem = curr->enemies;
        curr->enemies = prev;
        prev = curr_enem;
        curr = curr->next;
    }   
    //Counting how many enemies pass the castle and freeing enemies
    int enemy_counter = 0;
    struct enemy *curr_enem = prev;
    while (curr_enem != NULL) {
        prev = curr_enem->next;
        free(curr_enem);
        curr_enem = prev;
        enemy_counter++;
    }
    
    return enemy_counter;
}

/*///////////////////////////////////////////////////////////////////////
                            Stage 3 Functions                          
///////////////////////////////////////////////////////////////////////*/

// Apply damage from the enemies at each tower to that tower.
int apply_damage(Realm realm) {
    
    int number_of_enemies_hit = 0;
    struct location *curr = realm->lair;
    while (curr != NULL) {
        if (curr->enemies != NULL && curr->uses != 0) {
            
            //Counting how many enemies are being damaged by a tower
            number_of_enemies_hit += apply_damage_per_tower(curr);

        }
        if (curr->next == NULL) {
            struct enemy *list = curr->enemies;
            while (list != NULL) {
                curr->defense = curr->defense - list->cur_hp;
                list = list->next;
            }
        }
        curr = curr->next;
    }
    return number_of_enemies_hit;
}

// Destroy the realm, and free any associated memory.
void destroy_realm(Realm realm) {
    
    struct location *curr = realm->lair;
    struct location *temp_next = curr->next;
    //To loop through the location nodes
    while (curr != NULL) {
        //The enemies at each location exist
        if (curr->enemies != NULL) {
            struct enemy *list = curr->enemies;
            //To loop through the enemies list
            while (list != NULL) {
                struct enemy *temp = list->next;
                free(list);
                list = temp;
            }
        }
        temp_next = curr->next;
        free(curr);
        curr = temp_next;
    }
    free(realm);
}

/*///////////////////////////////////////////////////////////////////////
                            Stage 4 Functions                          
///////////////////////////////////////////////////////////////////////*/

// Apply the specified buff to the relevant towers or enemies.
int apply_buff(Realm realm, char *search_term, Buff buff, int amount){
    return 0;
}

/*///////////////////////////////////////////////////////////////////////
                            Stage 5 Functions                          
///////////////////////////////////////////////////////////////////////*/

// Apply the specified effect to each tower whose name matches the
// specified search term.
int apply_effect(Realm realm, char *search_term, Effect effect) {
    return 0;
}

////////////////////////////////////////////////////////////////////////

//This function initialises all the values to be ued inside the location struct   
static Location tower_initialise(char *name) {
    
    Location t_node = malloc(sizeof (struct location));
    
    strcpy(t_node->name, name);
    t_node->enemies = NULL;
    t_node->next = NULL;
    t_node->uses = 0;
    t_node->power = 0;
    t_node->type = TYPE_TOWER;

    return t_node;
}
//This function initialises all the values to be ued inside the enemy struct   
static Enemy enemy_initialise(char *name) {
    
    Enemy e_node = malloc(sizeof (struct enemy));
    
    strcpy (e_node->name, name);
    e_node->next = NULL;
    e_node->max_hp = 0;
    e_node->cur_hp = 0;
    return e_node;
}

//This function performs the damage process for one enemy and multiple enemies   
static int apply_damage_per_tower(Location curr) {
    struct enemy *list = curr->enemies;
    struct enemy *prev_enemy = NULL;
    int hit_enemies = 0;
    int damage = curr->power;
    
    while (list != NULL) {
        list->cur_hp = list->cur_hp - damage;
        int enemy_status = SURVIVED;
        if (list->cur_hp < 1) {
            struct enemy *temp = list;       
            //Damaging one enemy
            if (list == curr->enemies) {
                curr->enemies = list->next;
            } 
            //Damaging multiple enemies
            else {
                prev_enemy->next = list->next; 
            }
            list = list->next;
            free(temp);
            enemy_status = KILLED;
        }
        //If the enemy survives
        if (enemy_status == SURVIVED ) {
            prev_enemy = list;
            list = list->next;
        }
        hit_enemies++;
    }
    curr->uses = curr->uses - 1;
    if (curr->uses < 1) {
        curr->power = 0;
        curr->effect = 0;
    }
    return hit_enemies;
}

////////////////////////////////////////////////////////////////////////
//                    Provided print functions                        //
//         NOTE: YOU SHOULD NOT MODIFY THE FOLLOWING FUNCTIONS        //
////////////////////////////////////////////////////////////////////////

static void print_tower(char *name, int power, int uses, int effect) {
    printf("%32s [pow: %3d | uses: %3d]", name, power, uses);
    if (effect == EFFECT_NONE) {
        printf(" {%c}", EFFECT_NONE_CHAR);
    } else if (effect == EFFECT_ICE) {
        printf(" {%c}", EFFECT_ICE_CHAR);
    } else if (effect == EFFECT_BOUNCE) {
        printf(" {%c}", EFFECT_BOUNCE_CHAR);
    }
    printf("\n");
}

static void print_land(char *name) {
    printf("%32s [____________________]\n", name);
}

static void print_castle(char *name, int defense) {
    printf("%32s [Castle Defenses: %3d]\n", name, defense);
}

static void print_enemy(char *name, int cur_hp, int max_hp) {
    printf("%40s [hp: %d/%d]\n", name, cur_hp, max_hp);
}

////////////////////////////////////////////////////////////////////////
//              End of provided print functions                        //
////////////////////////////////////////////////////////////////////////



