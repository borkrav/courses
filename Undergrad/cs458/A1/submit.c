/*
 * A very simple program to submit a file - use at your own risk ;)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SUBMIT_DIRECTORY "/usr/share/submit"
#define LOG_FILE "submit.log"

#define MIN(x,y) ((x) < (y) ? (x) : (y))

static
int copyFile(const char* src, const char* dst)
{
  char buffer[512];
  unsigned int i, len;
  FILE *source, *dest;
  int c;

  source = fopen(src, "r");
  if (source == NULL) {
    fprintf(stderr, "Failed to open source file: %s\n", src);
    return -1;
  }
  
  i = 0;
  c = fgetc(source);
  while (c != EOF) {
    buffer[i]  = (unsigned char) c;
    c = fgetc(source);
    i++;
  }

  len = i;
  fclose(source);

  dest = fopen(dst, "w+");
  if (dest == NULL) {
    fprintf(stderr, "Failed to open destination file: %s\n", dst);
    return -1;
  }

  for(i = 0; i < len; i++) 
    fputc(buffer[i], dest);

  fclose(dest);

  return 0;
}

static 
int logEntry(const char *msg)
{
  uid_t userid;
  gid_t groupid;
  struct passwd *entry;
  char *pathname, *safepath, *ptr;
  pid_t pid;
  struct stat buf;
  int status, fd;

  userid = getuid();
  groupid = getgid();
  entry = getpwuid(userid);
  if (entry == NULL) {
    fprintf(stderr, "Failed to find pwd entry\n");
    return -1;
  }

  pathname = malloc(6 + strlen(entry->pw_name) + 1 + strlen(LOG_FILE) + 1);
  if (pathname == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return -1;
  }

  safepath = malloc(6 + strlen(entry->pw_name) + 1);
  if (safepath == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return -1;
  }

  strcpy(pathname, "/home/");
  strcat(pathname, entry->pw_name);
  strcpy(safepath, pathname);
  strcat(pathname, "/");
  strcat(pathname, LOG_FILE);    

  ptr = realpath(pathname, NULL);
  if (ptr == NULL) {    
    fd = creat(pathname, S_IWUSR | S_IRUSR);
    if (fd < 0) {
      fprintf(stderr, "Failed to create log file: %s\n", pathname);
      return -1;
    }
    if (fchown(fd, userid, groupid) < 0) {
      fprintf(stderr, "Failed to change ownership of log file:  %s\n", 
	      pathname);
      return -1;
    }
  }
  else {
    if (strncmp(ptr, safepath, strlen(safepath))) {
      fprintf(stderr, "Invalid log file: %s\n", ptr);
      return -1;
    }
  
    if (stat(pathname, &buf) != 0) {
      fprintf(stderr, "Failed to stat\n");
      return -1;
    }
    
    if (buf.st_uid != userid) {
      fprintf(stderr, "Not your log file: %s\n", pathname);
      return -1;
    }
  }  

  pid = fork();

  // error
  if (pid < 0) {
    fprintf(stderr, "Fork failed\n");
    return -1;
  }

  // parent
  if (pid > 0) {
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) == 0 || WEXITSTATUS(status) < 0)
      return -1;
  }
  else {

    // child

    if (freopen(pathname, "a", stdout) == NULL) {
      fprintf(stderr, "Failed to redirect stdout\n");
      return -1;
    }

    execlp("echo", "echo", msg, NULL);

    // reached only in case of error
    return -1;
  }

  return 0;
}

static
void usage2(const char* cmd) 
{
  char buffer[192];
  unsigned int idx;

  snprintf(buffer, sizeof(buffer), "Usage: %s pathname logmessage", cmd);
  idx = MIN(sizeof(buffer), strlen(cmd) + strlen("Usage:  pathname logmessage"));
  buffer[idx] = '\0';
  puts(buffer);
}

static
void usage(const char* cmd)
{
  usage2(cmd);
}

int main(int argc, char* argv[])
{
  char *forbidden_char, *src, *dst, *msg;

  forbidden_char = (char*) malloc(sizeof(char));
  if (forbidden_char == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return 1;
  }
  
  forbidden_char[0] = '/';
  
  if (argc != 3) {
    usage(argv[0]);
    return 1;
  }
  
  src = argv[1];
  msg = argv[2];

  printf("Submitting ");
  printf(src);
  printf("\n");

  if (index(src, (int)(forbidden_char[0])) != NULL) {
    fprintf(stderr, "File name includes slash\n");
    return 1;
  }
  
  dst = malloc(strlen(SUBMIT_DIRECTORY) + 1 + strlen(src) + 1);
  if (dst == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return 1;
  }
  
  strcpy(dst, SUBMIT_DIRECTORY);
  strcat(dst, "/");
  strcat(dst, src);
  
  // perform submit operation
  if (copyFile(src, dst) < 0)
    return 1;

  // log name of submitted file
  if (logEntry(msg) < 0)
    return 1;

  return 0;
}

