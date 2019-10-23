/**
 * Copyright (C) 2018 David C. Harrison - All Rights Reserved.
 * You may not use, distribute, or modify this code without
 * the express written permission of the copyright holder.
 */
 
 /*                           
 * IMPORTANT README INFORMATION
 *
 * In the Users file, username:password must be formatted such that there is always a space after the password. 
 *  
 * IF THIS IS NOT DONE, login will not work correctly. 
 *  
 * LOGIN 
 *  To login and obtain cookie for server: 
 * curl -iX POST "http://localhost:<port>/login?username=<username>&password=<password>"
 *  
 * When you use this command it will give you the cookie which you must hardcode into your curl request in the future.
 *  
 *   
 *   
 * UPLOAD 
 * To Upload file to the server: 
 * curl -b "authToken=<cookie>" -F "file=@<src-file>;filename=<dest-filename>" localhost:<your-port>/<dest-file-path>
 *  
 * When uploading the file, the server does hang however on restart it works fine and the file is written, however there is some extraneous information on it. 
 * Uploads can only occur with the correct authToken for the correct destination file path. 
 *  
 *  
 * DOWNLOAD 
 * To download a file from the server:
 * curl -b "authToken=<cookie>" http://localhost:<your-port>/<file-path-on-server>
 *  
 * Downloads file onto standard out with the given file path
 * Can only occur when given correct authToken for the correct file path on server and if file exists already
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include <errno.h>
#include <stdbool.h> 

#include <sys/types.h>
#include <sys/stat.h>


#define BYTES 2048

static void binary(int sock, char *fname) {
    int fd;
    int bytes;
    void *buffer[BYTES];
    if ((fd = open(fname, O_RDONLY)) != -1) {
        while ((bytes = read(fd, buffer, BYTES)) > 0)
            write(sock, buffer, bytes);
   }
}

//https://stackoverflow.com/questions/9928980/c-extract-word-from-a-string-between-two-words
char *parser(char *request, char *compare1, char *compare2, int offset1, int offset2){
    //printf("parser?");
    const char *p1 = strstr(request, compare1) + offset1;
    const char *p2 = strstr(p1, compare2) - offset2;
    size_t len = p2-p1;
    char *res = (char*)malloc(sizeof(char)*(len+1));
    strncpy(res, p1, len);
    res[len] = '\0';
    //printf("%s\n", res);
    return res; 
}
 
//https://stackoverflow.com/questions/34035169/fastest-way-to-reverse-a-string-in-c 
char *reverse(char *str)
{
    int len = strlen(str); 
    char *p1 = str;
    char *p2 = str + len - 1;

    while (p1 < p2) {
        char tmp = *p1;
        *p1++ = *p2;
        *p2-- = tmp;
    }

    return str;
}

void httpRequest(int sock, char *request) {
	
	printf("\nrequest = %s \n", request);
	char *post = "POST";
	char *get = "GET";
    char *username = "username=";
    char *password = "password="; 
    char *auth = "authToken=";
    char *unauth = "HTTP/1.1 401 Unauthorized\n";
		
 
    //Post for users + upload to file server 
	if(strstr(request,post) != NULL){
        
        //If login http request
        if(strstr(request,username)){
            char *parsed = parser(request,post,"HTTP",6,1); 
            printf("POST Request \n");
            
            char *user = parser(parsed,username,"&",9,0);
            char *pass = parser(request,password,"HTTP",9,1); 
            printf("Given User = %s \n",user);
            printf("Given Password = %s \n",pass);
            
            FILE *users = fopen("users", "r"); 
            if(users == NULL){
                fprintf(stderr, "No users file available"); 
                exit(EXIT_FAILURE);
            }
            
            char *line = NULL; 
            ssize_t read;
            size_t len = 0; 
            char *checkuser; 
            char *checkpass;
            bool loggedon;
            

            
            //Reads users file and compares to given login information
            while((read = getline(&line, &len, users)) != -1){
                checkuser = strtok(line, ":");
                checkpass = strtok(NULL, " "); 
                
                //Added code to mkdir automatically for users and makes directory if not already created. 
                //https://stackoverflow.com/questions/7430248/creating-a-new-directory-in-c
                //Used this code as reference 
                struct stat st = {0};
                char direct[BYTES]; 
                strcpy(direct, "/afs/cats.ucsc.edu/users/i/midquan/CMPS122/Lab3/server/");
                strcat(direct, checkuser); 
                if (stat(direct, &st) == -1) {
                    mkdir(direct, 0700);
                    printf("Made directory for %s \n", checkuser);
                }
                
                //printf("Stat = %d",stat("/some/directory", &st));
                
                //On given correct login give cookie for given user 
                if( (strcmp(user,checkuser) == 0) &&  (strcmp(pass,checkpass) == 0)){
                    printf("Login Accepted \n");
                    char *okay = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\nSet-Cookie: ";
                    char *actualcookie = reverse(user); 
                    
                    char * result = malloc(strlen(okay) + strlen(actualcookie) + 2);
                    strcpy(result, okay);
                    strcat(result, actualcookie);  
                    strcat(result, "\n");
                    write(sock , result , strlen(result));
                    loggedon = true; 
                } 
                
            }
            fclose(users);
            //If username/password combo not found, put 401 
            if(loggedon != true){
                printf("Username/Password not found! \n");
                write(sock , unauth , strlen(unauth));
            }
        }
        
        
        //Forks for upload
        else if(strstr(request,auth)){
            char *cookie = parser(request,auth,"\n",10,1);
            char *allowed = parser(request,"POST /","/",6,0);
            printf("%s \n", allowed); 
            char* setc = reverse(allowed); 
            printf("setc = %s \n", setc); 
            printf("Provided cookie is %s \n", cookie); 

            //Checks cookie to see if allowed to upload
            if(strncmp(cookie,setc,strlen(setc)) == 0){
                printf("Correct cookie provided! \n");   
                
                char *parsed = parser(request,post,"HTTP",6,1); 

                char buffer[BYTES];
                FILE *file = fopen(parsed, "wb");

					while ((read( sock , buffer, 2048) > 0))
					{
                        fwrite(buffer, 1, sizeof(buffer) * 4, file);
                        //fprintf(file, buffer, sizeof(buffer));
                        fputs(buffer,file);
                        
                        printf("reading \n");
                        printf("%s \n",buffer);
                        //count++; 
					} 
					 
                
                char *upload = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\nPost request to upload file!\n";
                write(sock , upload , strlen(upload));   
            }
            //401 if not allowed 
            else{
                write(sock , unauth , strlen(unauth));
            }
        
        //401 if not allowed 
        }
        else{
            write(sock , unauth , strlen(unauth));
        }
    }
    
	//Get request to serve file requested by http 
	if(strstr(request,get) != NULL){
        
        printf("GET Request \n");
        char *cookie = parser(request,auth,"\n",10,1);
        char *allowed = parser(request,"GET /","/",5,0);
        printf("%s \n", allowed); 
        char* setc = reverse(allowed); 
        printf("setc = %s \n", setc); 
        printf("Provided cookie is %s \n", cookie);
        
        //Checks if given cookie is allowed to download from server
        if(strncmp(cookie,setc,strlen(setc)) == 0){
            printf("Correct cookie provided! \n");   
            char *parsed = parser(request,get,"HTTP",5,1); 
            
            
            //call binary with given file to send
            binary(sock,parsed); 
            char *served = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\nGet request to serve file!\n";
            write(sock , served , strlen(served));
        
        }
        //Incorrect cookie = 401 
        else{
            write(sock , unauth , strlen(unauth));
        }
        
	}
}