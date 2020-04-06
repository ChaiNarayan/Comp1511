// Assignment 2 19T2 COMP1511: Castle Defense
// test_realm.c
//
// This file allows you to automatically test the functions you
// implement in realm.c.
//
// This program was written by Chaitanya Narayan (z5254637)
// on 10/08/2019
//
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

#include "realm.h"

//Stage 1 tests
static void test_new_realm();
void test_print_realm();
void test_add_location();
void test_thirty_two_location_name();
void test_thirty_three_location_name();

//Stage 2 tests
//Tests for towers
void test_two_towers();
void test_tower_different_locations ();

//Tests for enemies
void test_enemy_at_Lair();
void test_two_enemy_at_Lair();
void test_enemy_at_different_locations();

//Tests for advancing enemies
void test_enemy_advance_past_Lair();
void test_enemy_advance_past_Castle();
void test__multiple_enemy_advance_past_Castle();
void test_advance_multiple_enemies_multiple_locations();

//Stage 3 tests
//Tests for damage
void test_kill_one_enemy_at_tower();
void test_kill_one_enemy_at_each_tower();
void test_kill_second_enemy_but_first_survives();
void test_kill_middle_enemy_but_others_survive(); 
void test_tower_into_land();
void test_enemy_initial_hp_as_damage_castle();
void test_enemy_current_hp_as_damage_to_castle();

int main(void) {
    printf("\n================== Castle Defense Tests ==================\n");
    //Stage 1 Adding and Printing Realm
    test_new_realm();
    test_print_realm();
    test_add_location();
    test_thirty_two_location_name();
    test_thirty_three_location_name();
    
    //Stage 2 Towers, Enemies and Advancing
    //New Tower
    test_two_towers();
    test_tower_different_locations ();
    
    //New Enemy
    test_enemy_at_Lair();
    test_two_enemy_at_Lair();
    test_enemy_at_different_locations();
    
    //Advancing Enemy
    test_enemy_advance_past_Lair();
    test_enemy_advance_past_Castle();
    test__multiple_enemy_advance_past_Castle();
    test_advance_multiple_enemies_multiple_locations();
    
    //Stage 3 Damage and Destroy
    //Damage
    test_kill_one_enemy_at_tower();
    test_kill_one_enemy_at_each_tower();
    test_kill_second_enemy_but_first_survives();
    test_kill_middle_enemy_but_others_survive();
    test_tower_into_land();
    test_enemy_initial_hp_as_damage_castle();
    test_enemy_current_hp_as_damage_to_castle();
}

////////////////////////////////////////////////////////////////////////
//                  Castle Defense Test Functions                     //
////////////////////////////////////////////////////////////////////////

//Stage 1: Adding to Realm, Printing out Realm

// This function checks that a realm is actually being created.
void test_new_realm() {
    printf(">> Testing new_realm\n");

    printf("... Creating new realm.\n");
    Realm realm = new_realm();

    printf("... Checking it is not null.\n");
    assert(realm != NULL);
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
}



// This function will print out an empty realm - it should not crash.
void test_print_realm() {
    printf(">> Testing print_realm\n");
    Realm realm = new_realm();

    printf("... This should show an empty realm - it should not crash.\n");

    print_realm(realm);
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
}

// This function will add new locations and try to print them.
void test_add_location() {
    printf(">> Testing add_location.\n");
    Realm realm = new_realm();

    printf("... Adding locations.\n");
    add_location(realm, "First_Location");
    add_location(realm, "Second_Location");
    add_location(realm, "Third_Location");

    printf("... This should show an realm with three extra locations.\n");
    print_realm(realm);
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
}


//This function tests if the names of locations can be 32 characters
void test_thirty_two_location_name() {
    printf(">> Testing 32 character length location name.\n");
    Realm realm = new_realm();
    
    printf("... Adding locations.\n");
    add_location(realm, "This_is_thirty_two_characters!!!");
    
    printf("... This should show location with a 32 character length name.\n");
    assert(realm != NULL);
    print_realm(realm);
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
}



//This function tests if the character length of names are 32 characters max
void test_thirty_three_location_name() {
    printf(">> Testing 33 character length location name.\n");
    Realm realm = new_realm();
    
    printf("... Adding locations.\n");
    add_location(realm, "This_is_thirty_three_characters!!!");
    
    printf("... This should remove the two !! from the end of the set name.\n");
    assert(realm != NULL);
    print_realm(realm);
    printf("... As the !! were removed the max length is 32 characters.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
}

  
//Stage 2: New Tower, New Enemy, Advance Enemy
//Stage 2: New Tower

//This function tests if two towers can be placed in the Lair simultaneously
void test_two_towers() {
    printf(">> Testing 2 towers in the Lair.\n");
    Realm realm = new_realm();
    
    printf("... Adding towers.\n");
    printf("... Adding Tower1 with 10 power and 10 uses.\n");
    
    new_tower(realm, "Lair", "Tower1", 10, 10);
    
    printf("... Adding Tower2 with 20 power and 5 uses.\n");
    new_tower(realm, "Lair", "Tower2", 20, 5);
    
    printf("... This should print two towers at the Lair.\n");
    assert(realm != NULL);
    print_realm(realm);
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
}

//This function tests if towers can be added to various locations, 
//the Lair and Castle
void test_tower_different_locations () {
    printf(">> Testing add towers at different locations.\n");
    Realm realm = new_realm();
    
    printf("... Adding locations.\n");
    add_location(realm, "First_Location");
    add_location(realm, "Second_Location");
    add_location(realm, "Third_Location");
    
    printf("... Adding towers at locations.\n");
    new_tower(realm, "Lair", "Tower1", 10, 10);
    new_tower(realm, "First_Location", "Tower2", 10, 10);
    new_tower(realm, "Second_Location", "Tower2", 20, 20);
    new_tower(realm, "Third_Location", "Tower3", 30, 30);
    new_tower(realm, "Castle", "Tower4", 40, 40);
    
    printf("... This should print a tower at each location in the Realm.\n");
    assert(realm != NULL);
    print_realm(realm);
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//Stage 2: New Enemy

//This function tests if an enemy can be created at the Lair
void test_enemy_at_Lair() {
    printf(">> Testing new_enemy.\n");
    Realm realm = new_realm();
    
    printf("... Adding Enemy1 to Lair.\n");
    new_enemy(realm, "Lair", "Enemy1", 50);
    
    printf("... This should show a single enemy at the Lair.\n");
    assert(realm != NULL);
    print_realm(realm);    
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
}

//This function tests if multiple enemies can be created at one location at once
void test_two_enemy_at_Lair() {
    printf(">> Testing adding two enemies at one location.\n");
    Realm realm = new_realm();
    
    printf("... Adding Enemy1 to Lair.\n");
    new_enemy(realm, "Lair", "Enemy1", 100);

    printf("... Adding Enemy2 to Lair.\n");
    new_enemy(realm, "Lair", "Enemy2", 200);
    
    printf("... This should show two enemies at the Lair.\n");
    assert(realm != NULL);
    print_realm(realm); 
    printf("... Test successful.\n");

    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//This function tests if enemies can be placed at different types of locations
void test_enemy_at_different_locations() {
    printf(">> Testing adding two enemies at one location.\n");
    Realm realm = new_realm();

    printf("... Adding locations and towers.\n");
    add_location(realm, "First_Location");
    new_tower(realm, "First_Location", "Tower1", 10, 10);
    add_location(realm, "Second_Location");
    new_tower(realm, "Second_Location", "Tower2", 20, 20);
    add_location(realm, "Third_Location");
    
    printf("... Adding enemies at locations.\n");
    new_enemy(realm, "Lair", "Enemy1", 10);
    new_enemy(realm, "Tower1", "Enemy2", 20);
    new_enemy(realm, "Tower2", "Enemy3", 30);
    new_enemy(realm, "Third_Location", "Enemy4", 40);
    
    printf("... This should show enemies at different types of locations.\n");
    assert(realm != NULL);
    print_realm(realm); 
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//Stage 2: Advance enemies

//This function tests if enemies can advance from the Lair
void test_enemy_advance_past_Lair() {
    printf(">> Testing if enemies can advance from the Lair location type.\n");
    Realm realm = new_realm();
    
    printf("... Add two enemies at the Lair.\n");
    new_enemy(realm, "Lair", "Enemy1", 10);
    new_enemy(realm, "Lair", "Enemy2", 20);
    print_realm(realm);
    
    printf("... Advance the enemy past the Lair.\n");
    assert(advance_enemies(realm) == 0);
    printf("... The enemies should be at the Castle now.\n");
    print_realm(realm);
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
    
}

//This tests if one enemy has advanced past the Castle
void test_enemy_advance_past_Castle() {
    printf(">> Testing if one enemy has advanced past the Castle.\n");
    Realm realm = new_realm();
    
    printf("... Add one enemy at the Castle.\n");
    new_enemy(realm, "Castle", "Enemy1", 10);
    print_realm(realm);
    
    printf("... Advance the enemy past the Castle.\n");
    advance_enemies(realm);
    
    printf("... Print out the realm to see if the enemy has advanced.\n");
    assert(advance_enemies(realm) == 0);
    print_realm(realm);
    
    printf("... The previously input enemy has advanced.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//This function tests if multiple enemies can advance the Castle simultaneously
void test__multiple_enemy_advance_past_Castle() {
    printf(">> Testing if multiple enemies can advance past the Castle.\n");
    Realm realm = new_realm();
    
    printf("... Add the enemies to the Castle.\n");
    new_enemy(realm, "Castle", "Enemy1", 10);
    new_enemy(realm, "Castle", "Enemy2", 20);
    print_realm(realm);
    
    printf("... Advance the enemy past the Castle.\n");
    advance_enemies(realm);
    
    printf("... Print out the realm to see if the enemies have advanced.\n");
    assert(advance_enemies(realm) != 2);
    print_realm(realm);
    
    printf("... The previously input enemies have advanced.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//This function tests if all the enemies at all locations can advance at once
void test_advance_multiple_enemies_multiple_locations() {
    printf(">> Testing if multiple enemies can advance at all locations.\n");
    Realm realm = new_realm();
    
    printf("... Adding locations and enemies.\n");
    new_enemy(realm, "Lair", "Enemy0", 5);
    add_location(realm, "First_Location");
    new_enemy(realm, "First_Location", "Enemy1", 10);
    add_location(realm, "Second_Location");
    new_enemy(realm, "Second_Location", "Enemy2", 20);
    add_location(realm, "Third_Location");
    new_enemy(realm, "Third_Location", "Enemy3", 30);
    new_enemy(realm, "Castle", "Enemy4", 40);
    print_realm(realm);
    
    printf("... Advance the enemies until they all have passed the Castle.\n");
    assert(advance_enemies(realm) == 1);
    print_realm(realm);
    printf("\n");
    
    assert(advance_enemies(realm) == 1);
    print_realm(realm);
    printf("\n");
    
    assert(advance_enemies(realm) == 1);
    print_realm(realm);
    printf("\n");
    
    assert(advance_enemies(realm) == 1);
    print_realm(realm);
    printf("\n");
    
    assert(advance_enemies(realm) == 1);
    print_realm(realm);
    printf("\n");
    
    printf("... The previously input enemies have advanced past the Castle.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//Stage 3: Damage and Destroy
//Stage 3: Damage

//This function tests if one enemy at a tower can be killed
void test_kill_one_enemy_at_tower() {
    printf(">> Testing if an enemy dies after a tower hits.\n");
    Realm realm = new_realm();
    
    printf("... Adding tower and enemy.\n");
    new_tower(realm, "Lair", "Tower1", 10, 10);
    new_enemy(realm, "Tower1", "Enemy1", 5);
    print_realm(realm);
    
    printf("... Now deal damage to the enemy and kill it.\n");    
    assert(apply_damage(realm) == 1);
    print_realm(realm);
    
    printf("... The previously input enemy is dead.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//This function tests if enemies can be killed at different locations
void test_kill_one_enemy_at_each_tower() {
    printf(">> Testing if all enemies die after each tower hits.\n");
    Realm realm = new_realm();
    
    printf("... Adding locations, towers and enemies.\n");
    new_tower(realm, "Lair", "Tower1", 10, 10);
    new_enemy(realm, "Tower1", "Enemy1", 5);
    add_location(realm, "Location1");
    new_tower(realm, "Location1", "Tower2", 20, 20);
    new_enemy(realm, "Tower2", "Enemy2", 10);
    print_realm(realm);
    printf("\n");
    
    printf("... Now deal damage to the enemies and kill them.\n");    
    assert(apply_damage(realm) == 2);
    print_realm(realm);
    
    printf("... The previously input enemies are dead.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//This function will have 2 enemies which are damaged by a tower
//The second enemy should die but the first enemy should survive and advance
void test_kill_second_enemy_but_first_survives() {
    printf(">> Testing if first enemy survives but second dies.\n");
    printf(">> After second dies the remaining enemy advances.\n");
    Realm realm = new_realm();
    
    printf("... Adding towers and enemies.\n");
    new_tower(realm, "Lair", "Tower1", 10, 10);
    new_enemy(realm, "Tower1", "Enemy1", 20);
    new_enemy(realm, "Tower1", "Enemy2", 5);
    print_realm(realm);
    printf("\n");
    
    printf("... Now deal damage to the enemies but only kill Enemy2.\n");    
    assert(apply_damage(realm) == 2);
    print_realm(realm);
    printf("\n");
    
    printf("... The second enemy is dead and the first is alive.\n");
    printf("... Advance the remaining enemy.\n");
    assert(advance_enemies(realm) == 0);
    print_realm(realm);
    printf("\n");
    
    printf("... The enemies have advanced.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//This function will damage 3 enemies and kill the middle one.
//The other two should survive and advance.
void test_kill_middle_enemy_but_others_survive() {
    printf(">> Testing if middle enemy dies but others survive.\n");
    printf(">> After first survives it advances.\n");
    Realm realm = new_realm();
    
    printf("... Adding towers and enemies.\n");
    new_tower(realm, "Lair", "Tower1", 10, 10);
    new_enemy(realm, "Tower1", "Enemy1", 20);
    new_enemy(realm, "Tower1", "Enemy2", 5);
    new_enemy(realm, "Tower1", "Enemy3", 30);
    print_realm(realm);
    printf("\n");
    
    printf("... Now deal damage to the enemies and only kill Enemy2.\n");    
    assert(apply_damage(realm) == 3);
    print_realm(realm);
    printf("\n");
    
    printf("... The middle enemy is dead and the rest are alive.\n");
    printf("... Advance the remaining enemies.\n");
    assert(advance_enemies(realm) == 0);
    print_realm(realm);
    printf("\n");
    
    printf("... The enemies have advanced.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");
}

//This function tests if one Tower turns into a land after its uses finish.
//This function also tests if a different tower stays as a tower since its 
//uses is not 0.
void test_tower_into_land() {
    printf(">> Testing if a tower turns into a land after its uses go to 0.\n");
    Realm realm = new_realm();
    
    printf("... Adding the towers and enemies.\n");
    new_tower(realm, "Lair", "Tower-to-Land", 10, 1);
    new_enemy(realm, "Tower-to-Land", "Enemy1", 10);
    new_tower(realm, "Lair", "Tower", 10, 2);
    new_enemy(realm, "Tower", "Enemy2", 10);
    print_realm(realm);
    printf("\n");
    
    printf("... The towers use their power once.\n");
    assert(apply_damage(realm) == 2);
    print_realm(realm);
    printf("\n");
    
    printf("... The Tower-to-Land successfully turned into a land.\n");
    printf("... The Tower successfully stayed as a tower.\n");
    
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}    

//This function tests if an enemy deals damage to the Castle 
//based on its initial hp.
void test_enemy_initial_hp_as_damage_castle() {
    printf(">> Testing if an enemy deals its initial hp as damage"); 
    printf(" to the Castle.\n");
    Realm realm = new_realm();
    
    printf("... Adding the enemy to the Castle.\n");
    new_enemy(realm, "Castle", "Enemy1", 10);
    print_realm(realm);
    printf("\n");
    
    printf("... The enemy attacks once.\n");
    assert(apply_damage(realm) == 0);
    print_realm(realm);
    printf("\n");
    
    printf("... The Castle's hp has been reduced by the enemy's hp.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

//This function tests if an enemy that survives past a tower and reaches 
//the Castle deals its current hp as damage to the Castle.
void test_enemy_current_hp_as_damage_to_castle() {
    printf(">> Testing if a damaged enemy deals its current hp as damage"); 
    printf(" to the Castle.\n");
    Realm realm = new_realm();
    
    printf("... Adding the tower and enemy.\n");
    new_tower(realm, "Lair", "Tower1", 30, 30);
    new_enemy(realm, "Tower1", "Enemy1", 50);
    print_realm(realm);
    printf("\n");
    
    printf("... The tower attacks the enemy.\n");
    assert(apply_damage(realm) == 1);
    print_realm(realm);
    printf("\n");
    
    printf("... The enemy survives and advances to the Castle.\n");
    assert(advance_enemies(realm) == 0);
    print_realm(realm);
    printf("\n");
    
    printf("... The enemy reaches the castle and attacks once.\n");
    assert(apply_damage(realm) == 0);
    print_realm(realm);
    printf("\n");
    
    printf("... The Castle's hp has been reduced by the enemy's current hp.\n");
    printf("... Test successful.\n");
    
    printf("... Destroying realm.\n");
    destroy_realm(realm);
    
    printf("\n");

}

