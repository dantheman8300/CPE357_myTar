#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdint.h>
#include<string.h>
#include<grp.h>
#include<pwd.h>
#include<arpa/inet.h>
#include<time.h>
#include<math.h>
#include<string.h>

#define PERMS 11
#define NAME_LENGTH 100
#define NAME_OFFSET 0
#define MODE_LENGTH 8
#define MODE_OFFSET 100
#define UID_LENGTH 8
#define UID_OFFSET 108
#define GID_LENGTH 8
#define GID_OFFSET 116
#define SIZE_LENGTH 12
#define SIZE_OFFSET 124
#define MTIME_LENGTH 12
#define MTIME_OFFSET 136
#define CHKSUM_LENGTH 8
#define CHKSUM_OFFSET 148
#define TYPEFLAG_LENGTH 1
#define TYPEFLAG_OFFSET 156
#define LINKNAME_LENGTH 100
#define LINKNAME_OFFSET 157
#define MAGIC_LENGTH 6
#define MAGIC_OFFSET 257
#define VERSION_LENGTH 2
#define VERSION_OFFSET 263
#define UNAME_LENGTH 32
#define UNAME_OFFSET 265
#define GNAME_LENGTH 32
#define GNAME_OFFSET 297
#define DEVMAJOR_LENGTH 8
#define DEVMAJOR_OFFSET 329
#define DEVMINOR_LENGTH 8
#define DEVMINOR_OFFSET 337
#define PREFIX_LENGTH 155
#define PREFIX_OFFSET 345

#define BLOCKSIZE 512
#define PERMISSION_WIDTH 10

#define PADCHAR '$'
#define NAME_SZ 100

typedef struct Header *headerPtr;

struct Header {
  char name[NAME_LENGTH];
  mode_t mode;
  uid_t uid;
  gid_t gid;
  off_t size;
  time_t mtime;
  uint8_t chksum[CHKSUM_LENGTH];
  uint8_t typeflag[TYPEFLAG_LENGTH];
  uint8_t linkname[LINKNAME_LENGTH];
  uint8_t magic[MAGIC_LENGTH];
  uint8_t version[VERSION_LENGTH];
  char uname[UNAME_LENGTH];
  char gname[GNAME_LENGTH];
  uint8_t devmajor[DEVMAJOR_LENGTH];
  uint8_t devminor[DEVMINOR_LENGTH];
  char prefix[PREFIX_LENGTH];
  /*
  uint8_t uid[UID_LENGTH];
  uint8_t gid[GID_LENGTH];
  uint8_t size[SIZE_LENGTH];
  uint8_t mtime[MTIME_LENGTH];
  uint8_t chksum[CHKSUM_LENGTH];
  uint8_t typeflag[TYPEFLAG_LENGTH];
  uint8_t linkname[LINKNAME_LENGTH];
  uint8_t magic[MAGIC_LENGTH];
  uint8_t version[VERSION_LENGTH];
  uint8_t uname[UNAME_LENGTH];
  uint8_t gname[GNAME_LENGTH];
  uint8_t devmajor[DEVMAJOR_LENGTH];
  uint8_t devminor[DEVMINOR_LENGTH];
  uint8_t prefix[PREFIX_LENGTH];
  */
};

void extractAllFiles(int fin, int v);
int extractFile(int fin, headerPtr headerAddr, int v);
void getData(int fin, int numberDataBlocks, char *data);

void clearHeader(headerPtr header);

int readAndMakeHeader(int fin, headerPtr header);

void printPerms(mode_t mode, uint8_t *t);
void printOwners(char *uname, char *gname);
void printSize(int size);
void printMtime(time_t mtime);
void printName(char *name);

void makeDataBlocks(int fin, int fout);
void printTable(int tar);
void printTableEntry(headerPtr headerAddr);

int numberDataBlocks(headerPtr headerAddr);

/* mark */ 
int convertDecimalToOctal(int decimalNumber);

void make_header(int fd, char *pathname);
void write_file(int fd, struct stat sb, char *pathname);
void set_strict(void);
void printTable_NOV(int tar);
void printTableNames(headerPtr headerAddr);
void print_oneshot_nov(int tar, char *s);
void print_oneshot(int tar, char *s);
void print_DIR(int tar, headerPtr header, char *s);
void print_DIR_nov(int tar, headerPtr header, char *s);
void flushname(headerPtr header);


char det_file_type(struct stat sb);

uint32_t extract_special_int(char *where, int len);

int insert_special_character(char *where, size_t size, int32_t val);
int convertOctalToDecimal(int octalNumber);
int oct2int(uint8_t *oct, int size);
int has_char(char c, char *str);
int get_strict(void);
