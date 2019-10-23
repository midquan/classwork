/**
 * Copyright (C) 2018 David C. Harrison - All Rights Reserved.
 * You may not use, distribute, or modify this code without
 * the express written permission of the copyright holder.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>

#define BYTES 2048

#define four04 "<html>\n  <h1>Error 404</h1>\n  <h3>File not found</h3>\n</html>\n"

#define four03 "<html>\n  <h1>Error 403</h1>\n  <h3>Permision Denied</h3>\n</html>\n"

#define four01 "<html>\n  <h1>Error 401</h1>\n  <h3>Forbidden</h3>\n</html>\n"

#define two01 "<html>\n  <h1>Error 201</h1>\n  <h3>File Created</h3>\n</html>\n"

#define err "<html>\n  <h1>Error</h1>\n  <h3>Unrecognized Command</h3>\n</html>\n"

#define logged "<html>\n  <h1>Logged In</h1>\n</html>\n"

static void binary(int sock, char *fname) {
    int fd;
    int bytes;
    void *buffer[BYTES];
    if ((fd = open(fname, O_RDONLY)) != -1) {
        while ((bytes = read(fd, buffer, BYTES)) > 0)
            write(sock, buffer, bytes); 
   }
}

static void getRequest(int sock, char* url, char* head, char* ver, char* cookie) {
   char* file = url++;
   char verif[1024];

   strncpy(verif, file, 1024);
   char* dir = strtok(verif, "/");

   char tok[strlen(dir) + 1];

   for(int i = 0; i < strlen(dir); i++) {
      tok[i] = dir[i] - 1;
   }

   tok[strlen(dir)] = '\r';

   if(strcmp(tok, cookie) != 0) {
      char* resp = malloc(1024);
      strncpy(resp, "\n", 1024);
      strncat(resp, ver, 1024);
      strncat(resp, "\n", 1024);
      strncat(resp, "401 FORBIDDEN\n\n", 1024);
      strncat(resp, four01, strlen(four01));

      write(sock, resp, strlen(resp));
      return;
   }

   char path[1024];
   getcwd(path, sizeof(path));

   if (strlen(url) <= 1)
   {
      file = "/index.html";
   }
   
   strncat(path, file, sizeof(path));

   FILE *fptr = fopen(path, "r");

   if (fptr == NULL)
   {
      char* resp = malloc(1024);
      strncpy(resp, ver, 1024);
      strncpy(resp, "\n", 1024);
      strncat(resp, "404 ERROR\n\n", 1024);
      strncat(resp, four04, strlen(four04));

      write(sock, resp, strlen(resp));
      return;
   }
   
   struct stat fileStat;
   stat(path, &fileStat);
   char cont[24];
   sprintf(cont, "%lu", fileStat.st_size);

   char* resp = malloc(1024);
   strncpy(resp, ver, 1024);
   strncpy(resp, "\n", 1024);
   strncat(resp, "200 OK\n", 1024);
   strncat(resp, "Content-Length: ", 1024);
   strncat(resp, cont, 1024);
   strncat(resp, "\n\n", 1024);

   const int size = fileStat.st_size + 1 + strlen(head) + strlen(resp);
   char* buff = malloc(size);

   strncpy(buff, head, size);
   strncat(buff, resp, size);

   char* line = NULL;
   size_t len = 0;

   while (getline(&line, &len, fptr) != -1) {
      strncat(buff, line, size);
   }

   write(sock, buff, size);

   fclose(fptr);
   free(line);
}

static void postRequest(int sock, char* url, char* head, char* ver, char* cont, char* cookie) {
   char path[1024];
   getcwd(path, sizeof(path));
   strncat(path, url, 1024);

   const char sl[2] = "/";

   char* file = strrchr(url, '/');
   file++;

   if(strcmp(file, "users") == 0) {

      char* resp = malloc(1024);
      strncpy(resp, "\n", 1024);
      strncat(resp, ver, 1024);
      strncat(resp, "\n", 1024);
      strncat(resp, "403 DENIED\n\n", 1024);
      strncat(resp, four03, strlen(four03));

      write(sock, resp, strlen(resp));

      return;
   }

   if(strncmp(file, "login?", 6) == 0) {
      char log[1024];
      getcwd(log, sizeof(log));
      strncat(log, "/users", 1024);

      strtok(file, "=");

      char* usr = strtok(NULL, "&");
      strtok(NULL, "=");
      char* pass = strtok(NULL, "\0");

      FILE* ptr = fopen(log, "r");

      char* line = NULL;
      size_t len = 0;
      bool in = false;

      while (getline(&line, &len, ptr) != -1) {
         char* u = strtok(line, ":");
         char* p = strtok(NULL, "\n");

         if (strcmp(usr, u) == 0 &&
             strcmp(pass, p) == 0) {
            in = true;
            break;
         }
      }
   
      if(in) {
         char tok[strlen(usr)];

         for(int i = 0; i < strlen(usr); i++) {
            tok[i] = usr[i] - 1;
         }

         char* resp = malloc(1024);
         strncpy(resp, "\n", 1024);
         strncat(resp, ver, 1024);
         strncat(resp, "\n", 1024);
         strncat(resp, "200 OK\n", 1024);
         strncat(resp, "Set-Cookie: ", 1024);
         strncat(resp, usr, 1024);
         strncat(resp, "=", 1024);
         strncat(resp, tok, 1024);
         strncat(resp, "\n\n", 1024);
         strncat(resp, logged, strlen(logged));

         write(sock, resp, strlen(resp));
      } else {
         char* resp = malloc(1024);
         strncpy(resp, "\n", 1024);
         strncat(resp, ver, 1024);
         strncat(resp, "\n", 1024);
         strncat(resp, "403 DENIED\n\n", 1024);
         strncat(resp, four03, strlen(four03));

         write(sock, resp, strlen(resp));
      }
      return;
   }

   char* dir = strtok(url, sl);

   char create[1024];

   if(strcmp(dir, file)) {
      char tok[strlen(dir) + 1];

      for(int i = 0; i < strlen(dir); i++) {
         tok[i] = dir[i] - 1;
      }

      tok[strlen(dir)] = '\r';

      if(strcmp(tok, cookie) != 0) {
         char* resp = malloc(1024);
         strncpy(resp, "\n", 1024);
         strncat(resp, ver, 1024);
         strncat(resp, "\n", 1024);
         strncat(resp, "401 FORBIDDEN\n\n", 1024);
         strncat(resp, four01, strlen(four01));

         write(sock, resp, strlen(resp));
         return;
      }

      strncpy(create, dir, 1024);
      mkdir(dir, 0700);

      while(dir != NULL) {
         dir = strtok(NULL, "/");

         if(strcmp(dir, file) == 0) {
            break;
         }

         strncat(create, "/", 1024);
         strncat(create, dir, 1024);
         mkdir(create, 0700);
      }

   }

   FILE *fptr = fopen(path, "w+");

   if (fptr == NULL) {
      char* resp = malloc(1024);
      strncpy(resp, ver, 1024);
      strncpy(resp, "\n", 1024);
      strncat(resp, "403 DENIED\n\n", 1024);
      strncat(resp, four03, strlen(four03));

      write(sock, resp, strlen(resp));

      return;
   }

   fprintf(fptr, "%s\n", cont);

   char* resp = malloc(1024);
   strncpy(resp, ver, 1024);
   strncpy(resp, "\n", 1024);
   strncat(resp, "201 CREATED\n\n", 1024);
   strncat(resp, two01, strlen(two01));

   write(sock, resp, strlen(resp));
}

void httpRequest(int sock, char *request) {
   const char space[2] = " ";
   const char nl[2] = "\n";
   const char col[2] = ":";

   //printf("%s\n", request);

   size_t size = strlen(request);

   char req[size];
   strncpy(req, request, size);

   char buff[1024];

   char* cmd = strtok(req, space);
   strncpy(buff, cmd, 1024);
   strncat(buff, " ", 1024);

   char* url = strtok(NULL, space);
   strncat(buff, url, 1024);
   strncat(buff, " ", 1024);

   char* version = strtok(NULL, nl);
   strncat(buff, version, 1024);

   strtok(NULL, col);
   char* host = strtok(NULL, nl);
   host++;
   strncat(buff, "\nHost: ", 1024);
   strncat(buff, host, 1024);

   strtok(NULL, col);
   char* usrage = strtok(NULL, nl);
   usrage++;
   strncat(buff, "\nUser-Agent: ", 1024);
   strncat(buff, usrage, 1024);

   strtok(NULL, col);
   char* accept = strtok(NULL, nl);
   accept++;
   strncat(buff, "\nAccept: ", 1024);
   strncat(buff, accept, 1024);

   char cookie[1024];
   
   for(char* hdr = strtok(NULL, col); hdr != NULL; hdr = strtok(NULL, col)) {
      
      if(strcmp(hdr, "Cookie") == 0) {
         hdr = strtok(NULL, "=");
         hdr = strtok(NULL, nl);
         puts(hdr);
         strcpy(cookie, hdr);
         break;
      }

      strtok(NULL, nl);
   }

   strncat(buff, "\n", 1024);

   if (strcmp(cmd, "GET") == 0)
   {
      getRequest(sock, url, buff, version, cookie);
   } 
   else if (strcmp(cmd, "POST") == 0)
   {   
      char* cont = strstr(request, "\n\r\n");
     
      cont += 3;

      postRequest(sock, url, buff, version, cont, cookie);
   } 
   else 
   {
      char* resp = malloc(1024);
      strncpy(resp, "\n", 1024);
      strncat(resp, version, 1024);
      strncat(resp, "\n", 1024);
      strncat(resp, "Error\n\n", 1024);
      strncat(resp, err, strlen(err));

      write(sock, resp, strlen(resp));
   }
}
