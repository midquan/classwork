/**
 * Copyright (C) 2018 David C. Harrison - All Rights Reserved.
 * You may not use, distribute, or modify this code without
 * the written permission of the copyright holder.
 */


/*
Michael Quan
142906
Lab 1
*/ 
 

/*
 * Find the plain-text password PASSWD of length PWLEN for the user USERNAME 
 * given the encrypted password CRYPTPASSWD.
 */
 
#define _GNU_SOURCE
#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 
void crackSingle(char *username, char *cryptPasswd, int pwlen, char *passwd) { 
    
    //String of all possible values for password
    char possible[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    //Needed for crypt_r to work and needed to be initialized to 0 
    //Using crypt_r to ensure no race condition and corrupted data, idea taken from Piazza
    struct crypt_data data; 
    data.initialized = 0; 

    //Size of tested char string which is 4, +1 due to crypt_r
    char tested[5];
    
    //Salt size = 2 according to instructions, +1 due to crypt_r 
    char salt[3];
    strncpy(salt, username, 2);
    
    //4 for loops for each charecter in the password 
    for(int first = 0; first < sizeof(possible); first++){
        for(int second = 0; second < sizeof(possible); second++ ){
            for(int third = 0; third < sizeof(possible); third++){
                for(int four = 0; four < sizeof(possible); four++){
                    //set memory to 0, if not included causes issues with crypt_r
                    memset(tested, 0, sizeof(tested));
                    tested[0] = possible[first];
                    tested[1] = possible[second];
                    tested[2] = possible[third];
                    tested[3] = possible[four];
                    char *encrypt = crypt_r(tested, salt, &data);
                    
                    //boolean to determine whether encrypted password is same as the cryptPasswd, if so then copy onto passwd
                    bool foundpwd = (strcmp(cryptPasswd, encrypt) == 0);
                    if (foundpwd){
                        strncpy(passwd, tested, 5);
                        return; 
                    }                        
                }
            }
        }
    } 
}

/*
 * Find the plain-text passwords PASSWDS of length PWLEN for the users found
 * in the old-style /etc/passwd format file at pathe FNAME.
 */
void crackMultiple(char *fname, int pwlen, char **passwds) {
    
    //Open file and put it into input
    FILE *input;
    input = fopen(fname, "r");
    
    //Strings created for username, password, and fgets buffer
    char username[30];
    char cryptPasswd[14];
    char buffer[500];
    

    //Continue until input is null 
    if (input != 0){
        //counter to ensure passwds inserted right, fgets for accessing file
        for(int count = 0; fgets(buffer, sizeof(buffer), input) != NULL; count++){
            
            //copy username and password from file into crackSingle then put cracked password into passwds
            strcpy(username, strtok(buffer, ":"));
            strcpy(cryptPasswd, strtok(NULL, ":"));
            crackSingle(username,cryptPasswd, pwlen, passwds[count]);
        }    
    } 
    
    //fclose to close file
    fclose(input);
    return;
} 

/*
 * Find the plain-text passwords PASSWDS of length PWLEN for the users found
 * in the old-style /etc/passwd format file at pathe FNAME.
 */
void crackSpeedy(char *fname, int pwlen, char **passwds) {

    //Open file and put it into input
    FILE *input;
    input = fopen(fname, "r");

    //Strings created for username, password, and fgets buffer    
    char username[30];
    char cryptPasswd[14];
    char buffer[500];
    
    //Continue until input is null 
    if (input != 0){
        //counter to ensure passwds inserted right, fgets for accessing file
        for(int count = 0; fgets(buffer, sizeof(buffer), input) != NULL; count++){
            
            //copy username and password from file into crackSingle then put cracked password into passwds
            strcpy(username, strtok(buffer, ":"));
            strcpy(cryptPasswd, strtok(NULL, ":"));
            crackSingle(username,cryptPasswd, pwlen, passwds[count]);
        }    
    } 

    //fclose to close file
    fclose(input);
    return;    
} 

/*
 * Find the plain-text password PASSWD of length PWLEN for the user USERNAME 
 * given the encrypted password CRYPTPASSWD withoiut using more than MAXCPU
 * percent of any processor.
 */
void crackStealthy(char *username, char *cryptPasswd, int pwlen, char *passwd, int maxCpu) { }
