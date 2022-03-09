#ifndef _WEB_FILES_H_
#define _WEB_FILES_H_
//Do Not Edit AUTOGENERATED
typedef struct ExpFiles {
char* name;
char* contents;
uint16_t size;
} expectedFiles;
static char data_name[] = "/data.csv";
static char data_contents[] = "\x23\x74\x69\x6d\x65\x2c\x20\x64\x61\x72\x6b\x5f\x41\x44\x43\x2c\x20\x64\x61\x72\x6b\x5f\x56\x2c\x20\x61\x63\x74\x69\x76\x65\x5f\x41\x44\x43\x2c\x20\x61\x63\x74\x69\x76\x65\x5f\x56\x2c\x20\x74\x65\x6d\x70\x5f\x41\x44\x43\x2c\x20\x74\x65\x6d\x70\x5f\x46\x0a";
static uint16_t data_size = 64;

static char index_name[] = "/index.htm";
static char index_contents[] = "\x3c\x21\x44\x4f\x43\x54\x59\x50\x45\x20\x68\x74\x6d\x6c\x3e\x0a\x3c\x68\x74\x6d\x6c\x3e\x0a\x3c\x68\x65\x61\x64\x3e\x0a\x20\x20\x3c\x6d\x65\x74\x61\x20\x68\x74\x74\x70\x2d\x65\x71\x75\x69\x76\x3d\x22\x43\x6f\x6e\x74\x65\x6e\x74\x2d\x74\x79\x70\x65\x22\x20\x63\x6f\x6e\x74\x65\x6e\x74\x3d\x22\x74\x65\x78\x74\x2f\x68\x74\x6d\x6c\x3b\x20\x63\x68\x61\x72\x73\x65\x74\x3d\x75\x74\x66\x2d\x38\x22\x3e\x0a\x20\x20\x3c\x74\x69\x74\x6c\x65\x3e\x45\x53\x50\x20\x49\x6e\x64\x65\x78\x3c\x2f\x74\x69\x74\x6c\x65\x3e\x0a\x20\x20\x3c\x73\x74\x79\x6c\x65\x3e\x0a\x20\x20\x20\x20\x62\x6f\x64\x79\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x62\x61\x63\x6b\x67\x72\x6f\x75\x6e\x64\x2d\x63\x6f\x6c\x6f\x72\x3a\x74\x65\x61\x6c\x3b\x0a\x20\x20\x20\x20\x20\x20\x63\x6f\x6c\x6f\x72\x3a\x77\x68\x69\x74\x65\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x3c\x2f\x73\x74\x79\x6c\x65\x3e\x0a\x3c\x2f\x68\x65\x61\x64\x3e\x0a\x3c\x62\x6f\x64\x79\x20\x69\x64\x3d\x22\x69\x6e\x64\x65\x78\x22\x3e\x0a\x20\x20\x3c\x68\x31\x3e\x53\x65\x64\x69\x20\x53\x65\x6e\x73\x6f\x72\x3a\x20\x44\x61\x74\x61\x20\x3c\x2f\x68\x31\x3e\x0a\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x2f\x64\x61\x74\x61\x2e\x63\x73\x76\x22\x20\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x3d\x22\x64\x61\x74\x61\x2e\x63\x73\x76\x22\x3e\x44\x6f\x77\x6e\x6c\x6f\x61\x64\x20\x46\x69\x6c\x65\x3c\x2f\x61\x3e\x0a\x3c\x2f\x62\x6f\x64\x79\x3e\x0a\x3c\x2f\x68\x74\x6d\x6c\x3e\x0a";
static uint16_t index_size = 345;

static char god_name[] = "/god";
static char god_index_name[] = "/god/index.htm";
static char god_index_contents[] = "\x3c\x21\x44\x4f\x43\x54\x59\x50\x45\x20\x68\x74\x6d\x6c\x3e\x0a\x3c\x68\x74\x6d\x6c\x3e\x0a\x3c\x68\x65\x61\x64\x3e\x0a\x20\x20\x3c\x6d\x65\x74\x61\x20\x68\x74\x74\x70\x2d\x65\x71\x75\x69\x76\x3d\x22\x43\x6f\x6e\x74\x65\x6e\x74\x2d\x74\x79\x70\x65\x22\x20\x63\x6f\x6e\x74\x65\x6e\x74\x3d\x22\x74\x65\x78\x74\x2f\x68\x74\x6d\x6c\x3b\x20\x63\x68\x61\x72\x73\x65\x74\x3d\x75\x74\x66\x2d\x38\x22\x3e\x0a\x20\x20\x3c\x74\x69\x74\x6c\x65\x3e\x54\x53\x53\x20\x47\x6f\x64\x20\x4d\x6f\x64\x65\x3c\x2f\x74\x69\x74\x6c\x65\x3e\x0a\x20\x20\x3c\x73\x74\x79\x6c\x65\x3e\x0a\x20\x20\x20\x20\x74\x61\x62\x6c\x65\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x62\x6f\x72\x64\x65\x72\x2d\x63\x6f\x6c\x6c\x61\x70\x73\x65\x3a\x20\x63\x6f\x6c\x6c\x61\x70\x73\x65\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x74\x64\x2c\x20\x74\x68\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x74\x65\x78\x74\x2d\x61\x6c\x69\x67\x6e\x3a\x20\x6c\x65\x66\x74\x3b\x0a\x20\x20\x20\x20\x20\x20\x70\x61\x64\x64\x69\x6e\x67\x2d\x6c\x65\x66\x74\x3a\x20\x32\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x20\x20\x70\x61\x64\x64\x69\x6e\x67\x2d\x72\x69\x67\x68\x74\x3a\x20\x32\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x20\x20\x66\x6f\x6e\x74\x2d\x73\x69\x7a\x65\x3a\x20\x32\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x62\x6f\x64\x79\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x62\x61\x63\x6b\x67\x72\x6f\x75\x6e\x64\x2d\x63\x6f\x6c\x6f\x72\x3a\x44\x69\x6d\x47\x72\x61\x79\x3b\x0a\x20\x20\x20\x20\x20\x20\x63\x6f\x6c\x6f\x72\x3a\x20\x73\x6e\x6f\x77\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x68\x31\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x66\x6f\x6e\x74\x2d\x73\x69\x7a\x65\x3a\x20\x34\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x68\x32\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x6d\x61\x72\x67\x69\x6e\x3a\x20\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x0a\x20\x20\x20\x20\x70\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x66\x6f\x6e\x74\x2d\x73\x69\x7a\x65\x3a\x20\x32\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x2e\x74\x61\x62\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x64\x69\x73\x70\x6c\x61\x79\x3a\x20\x69\x6e\x6c\x69\x6e\x65\x2d\x62\x6c\x6f\x63\x6b\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x6d\x61\x72\x67\x69\x6e\x2d\x6c\x65\x66\x74\x3a\x20\x32\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x2e\x73\x6d\x61\x6c\x6c\x5f\x70\x5f\x73\x70\x61\x63\x69\x6e\x67\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x6d\x61\x72\x67\x69\x6e\x3a\x20\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x23\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x62\x61\x63\x6b\x67\x72\x6f\x75\x6e\x64\x2d\x63\x6f\x6c\x6f\x72\x3a\x20\x23\x43\x38\x30\x30\x30\x30\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x63\x6f\x6c\x6f\x72\x3a\x20\x73\x6e\x6f\x77\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x62\x6f\x72\x64\x65\x72\x3a\x20\x32\x70\x78\x20\x73\x6f\x6c\x69\x64\x20\x73\x6e\x6f\x77\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x62\x6f\x72\x64\x65\x72\x2d\x72\x61\x64\x69\x75\x73\x3a\x20\x32\x35\x70\x78\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x70\x61\x64\x64\x69\x6e\x67\x3a\x20\x32\x30\x70\x78\x20\x33\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x6d\x61\x72\x67\x69\x6e\x3a\x20\x32\x30\x70\x78\x20\x32\x30\x70\x78\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x74\x65\x78\x74\x2d\x64\x65\x63\x6f\x72\x61\x74\x69\x6f\x6e\x3a\x20\x6e\x6f\x6e\x65\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x64\x69\x73\x70\x6c\x61\x79\x3a\x69\x6e\x6c\x69\x6e\x65\x2d\x62\x6c\x6f\x63\x6b\x3b\x0a\x20\x20\x20\x20\x7d\x0a\x20\x20\x3c\x2f\x73\x74\x79\x6c\x65\x3e\x0a\x20\x20\x3c\x73\x63\x72\x69\x70\x74\x3e\x0a\x20\x20\x20\x20\x20\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x72\x65\x71\x75\x65\x73\x74\x55\x70\x64\x61\x74\x65\x28\x29\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x63\x6f\x6e\x73\x74\x20\x48\x74\x74\x70\x20\x3d\x20\x6e\x65\x77\x20\x58\x4d\x4c\x48\x74\x74\x70\x52\x65\x71\x75\x65\x73\x74\x28\x29\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x63\x6f\x6e\x73\x74\x20\x75\x72\x6c\x20\x3d\x20\x22\x68\x74\x74\x70\x3a\x2f\x2f\x74\x73\x73\x2e\x6c\x6f\x63\x61\x6c\x2f\x67\x6f\x64\x2f\x6d\x65\x61\x73\x75\x72\x65\x2e\x74\x78\x74\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x48\x74\x74\x70\x2e\x6f\x70\x65\x6e\x28\x22\x47\x45\x54\x22\x2c\x20\x75\x72\x6c\x29\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x48\x74\x74\x70\x2e\x73\x65\x6e\x64\x28\x29\x3b\x0a\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x48\x74\x74\x70\x2e\x6f\x6e\x72\x65\x61\x64\x79\x73\x74\x61\x74\x65\x63\x68\x61\x6e\x67\x65\x20\x3d\x20\x28\x65\x29\x3d\x3e\x20\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x69\x66\x28\x21\x21\x48\x74\x74\x70\x2e\x72\x65\x73\x70\x6f\x6e\x73\x65\x54\x65\x78\x74\x29\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x76\x61\x72\x20\x6d\x65\x61\x73\x75\x72\x65\x41\x72\x72\x20\x3d\x20\x48\x74\x74\x70\x2e\x72\x65\x73\x70\x6f\x6e\x73\x65\x54\x65\x78\x74\x2e\x74\x72\x69\x6d\x28\x29\x2e\x73\x70\x6c\x69\x74\x28\x27\x2c\x27\x29\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x76\x61\x72\x20\x69\x64\x41\x72\x72\x20\x3d\x20\x5b\x22\x74\x69\x6d\x65\x22\x2c\x20\x22\x61\x6d\x62\x5f\x61\x64\x63\x22\x2c\x20\x22\x61\x6d\x62\x5f\x76\x6f\x6c\x74\x22\x2c\x20\x22\x61\x63\x74\x5f\x61\x64\x63\x22\x2c\x20\x22\x61\x63\x74\x5f\x76\x6f\x6c\x74\x22\x2c\x20\x22\x74\x65\x6d\x70\x5f\x61\x64\x63\x22\x2c\x20\x22\x74\x65\x6d\x70\x5f\x66\x22\x5d\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x69\x64\x41\x72\x72\x2e\x66\x6f\x72\x45\x61\x63\x68\x28\x28\x65\x6c\x65\x6d\x65\x6e\x74\x2c\x69\x6e\x64\x65\x78\x29\x20\x3d\x3e\x20\x64\x6f\x63\x75\x6d\x65\x6e\x74\x2e\x67\x65\x74\x45\x6c\x65\x6d\x65\x6e\x74\x42\x79\x49\x64\x28\x65\x6c\x65\x6d\x65\x6e\x74\x29\x2e\x69\x6e\x6e\x65\x72\x48\x54\x4d\x4c\x20\x3d\x20\x6d\x65\x61\x73\x75\x72\x65\x41\x72\x72\x5b\x69\x6e\x64\x65\x78\x5d\x29\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x73\x65\x74\x54\x69\x6d\x65\x6f\x75\x74\x28\x72\x65\x71\x75\x65\x73\x74\x55\x70\x64\x61\x74\x65\x2c\x20\x31\x30\x30\x30\x29\x3b\x0a\x20\x20\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x20\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x5f\x4f\x6e\x4f\x76\x65\x72\x28\x29\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x76\x61\x72\x20\x62\x75\x74\x74\x6f\x6e\x20\x3d\x20\x64\x6f\x63\x75\x6d\x65\x6e\x74\x2e\x67\x65\x74\x45\x6c\x65\x6d\x65\x6e\x74\x42\x79\x49\x64\x28\x22\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x22\x29\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x62\x75\x74\x74\x6f\x6e\x2e\x73\x74\x79\x6c\x65\x2e\x62\x61\x63\x6b\x67\x72\x6f\x75\x6e\x64\x43\x6f\x6c\x6f\x72\x20\x3d\x20\x22\x23\x41\x34\x30\x30\x30\x30\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x20\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x5f\x4f\x6e\x4f\x75\x74\x28\x29\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x76\x61\x72\x20\x62\x75\x74\x74\x6f\x6e\x20\x3d\x20\x64\x6f\x63\x75\x6d\x65\x6e\x74\x2e\x67\x65\x74\x45\x6c\x65\x6d\x65\x6e\x74\x42\x79\x49\x64\x28\x22\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x22\x29\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x62\x75\x74\x74\x6f\x6e\x2e\x73\x74\x79\x6c\x65\x2e\x62\x61\x63\x6b\x67\x72\x6f\x75\x6e\x64\x43\x6f\x6c\x6f\x72\x20\x3d\x20\x22\x23\x43\x38\x30\x30\x30\x30\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x7d\x0a\x20\x20\x20\x20\x20\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x5f\x4f\x6e\x43\x6c\x69\x63\x6b\x28\x29\x7b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x76\x61\x72\x20\x62\x75\x74\x74\x6f\x6e\x20\x3d\x20\x64\x6f\x63\x75\x6d\x65\x6e\x74\x2e\x67\x65\x74\x45\x6c\x65\x6d\x65\x6e\x74\x42\x79\x49\x64\x28\x22\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x22\x29\x3b\x0a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x62\x75\x74\x74\x6f\x6e\x2e\x73\x74\x79\x6c\x65\x2e\x62\x61\x63\x6b\x67\x72\x6f\x75\x6e\x64\x43\x6f\x6c\x6f\x72\x20\x3d\x20\x22\x23\x38\x30\x30\x30\x30\x30\x22\x3b\x0a\x20\x20\x20\x20\x20\x20\x7d\x0a\x20\x20\x3c\x2f\x73\x63\x72\x69\x70\x74\x3e\x0a\x3c\x2f\x68\x65\x61\x64\x3e\x0a\x3c\x62\x6f\x64\x79\x20\x6f\x6e\x6c\x6f\x61\x64\x3d\x22\x72\x65\x71\x75\x65\x73\x74\x55\x70\x64\x61\x74\x65\x28\x29\x3b\x22\x3e\x0a\x20\x20\x3c\x68\x31\x3e\x54\x65\x61\x6d\x20\x53\x65\x64\x69\x20\x53\x65\x6e\x73\x6f\x72\x3a\x20\x44\x65\x76\x69\x63\x65\x20\x3c\x2f\x68\x31\x3e\x0a\x20\x20\x3c\x68\x32\x3e\x4c\x61\x74\x65\x73\x74\x20\x4d\x65\x61\x73\x75\x72\x65\x6d\x65\x6e\x74\x3a\x20\x3c\x2f\x68\x32\x3e\x0a\x20\x20\x20\x20\x3c\x70\x20\x63\x6c\x61\x73\x73\x3d\x22\x73\x6d\x61\x6c\x6c\x5f\x70\x5f\x73\x70\x61\x63\x69\x6e\x67\x22\x3e\x3c\x73\x70\x61\x6e\x20\x63\x6c\x61\x73\x73\x3d\x22\x74\x61\x62\x22\x3e\x3c\x2f\x73\x70\x61\x6e\x3e\x54\x69\x6d\x65\x3a\x20\x3c\x73\x70\x61\x6e\x20\x69\x64\x3d\x74\x69\x6d\x65\x3e\x4e\x6f\x20\x4d\x65\x61\x73\x75\x72\x65\x6d\x65\x6e\x74\x20\x53\x69\x6e\x63\x65\x20\x43\x6f\x6e\x6e\x65\x63\x74\x65\x64\x3c\x2f\x73\x70\x61\x6e\x3e\x3c\x2f\x70\x3e\x20\x0a\x20\x20\x3c\x74\x61\x62\x6c\x65\x3e\x0a\x20\x20\x20\x20\x3c\x74\x72\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x68\x3e\x3c\x2f\x74\x68\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x68\x3e\x41\x44\x43\x20\x52\x65\x61\x64\x69\x6e\x67\x3c\x2f\x74\x68\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x68\x3e\x4d\x65\x61\x73\x75\x72\x65\x6d\x65\x6e\x74\x3c\x2f\x74\x68\x3e\x0a\x20\x20\x20\x20\x3c\x2f\x74\x72\x3e\x0a\x20\x20\x20\x20\x3c\x74\x72\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x3e\x41\x6d\x62\x20\x52\x65\x61\x64\x69\x6e\x67\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x20\x69\x64\x3d\x22\x61\x6d\x62\x5f\x61\x64\x63\x22\x3e\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x3e\x3c\x73\x70\x61\x6e\x20\x69\x64\x3d\x22\x61\x6d\x62\x5f\x76\x6f\x6c\x74\x22\x3e\x3c\x2f\x73\x70\x61\x6e\x3e\x20\x56\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x3c\x2f\x74\x72\x3e\x0a\x20\x20\x20\x20\x3c\x74\x72\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x3e\x41\x63\x74\x20\x52\x65\x61\x64\x69\x6e\x67\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x3e\x3c\x73\x70\x61\x6e\x20\x69\x64\x3d\x22\x61\x63\x74\x5f\x61\x64\x63\x22\x3e\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x3e\x3c\x73\x70\x61\x6e\x20\x69\x64\x3d\x22\x61\x63\x74\x5f\x76\x6f\x6c\x74\x22\x3e\x3c\x2f\x73\x70\x61\x6e\x3e\x20\x56\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x3c\x2f\x74\x72\x3e\x0a\x20\x20\x20\x20\x3c\x74\x72\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x3e\x54\x65\x6d\x70\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x20\x69\x64\x3d\x22\x74\x65\x6d\x70\x5f\x61\x64\x63\x22\x3e\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x74\x64\x3e\x3c\x73\x70\x61\x6e\x20\x69\x64\x3d\x22\x74\x65\x6d\x70\x5f\x66\x22\x3e\x3c\x2f\x73\x70\x61\x6e\x3e\x20\x46\x3c\x2f\x74\x64\x3e\x0a\x20\x20\x20\x20\x3c\x2f\x74\x72\x3e\x0a\x20\x20\x3c\x2f\x74\x61\x62\x6c\x65\x3e\x0a\x20\x20\x3c\x64\x69\x76\x20\x6f\x6e\x43\x6c\x69\x63\x6b\x3d\x22\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x5f\x4f\x6e\x43\x6c\x69\x63\x6b\x28\x29\x3b\x22\x20\x0a\x20\x20\x20\x20\x20\x20\x20\x6f\x6e\x6d\x6f\x75\x73\x65\x6f\x76\x65\x72\x3d\x22\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x5f\x4f\x6e\x4f\x76\x65\x72\x28\x29\x3b\x22\x0a\x20\x20\x20\x20\x20\x20\x20\x6f\x6e\x6d\x6f\x75\x73\x65\x6f\x75\x74\x3d\x22\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x5f\x4f\x6e\x4f\x75\x74\x28\x29\x3b\x22\x3e\x0a\x20\x20\x20\x20\x3c\x61\x20\x68\x72\x65\x66\x3d\x22\x2f\x64\x61\x74\x61\x2e\x63\x73\x76\x22\x20\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x3d\x22\x64\x61\x74\x61\x2e\x63\x73\x76\x22\x3e\x0a\x20\x20\x20\x20\x20\x20\x3c\x70\x20\x69\x64\x3d\x22\x64\x6f\x77\x6e\x6c\x6f\x61\x64\x42\x75\x74\x74\x6f\x6e\x22\x3e\x44\x6f\x77\x6e\x6c\x6f\x61\x64\x20\x46\x69\x6c\x65\x3c\x2f\x70\x3e\x0a\x20\x20\x20\x20\x3c\x2f\x61\x3e\x0a\x20\x20\x3c\x2f\x64\x69\x76\x3e\x0a\x3c\x2f\x62\x6f\x64\x79\x3e\x0a\x3c\x2f\x68\x74\x6d\x6c\x3e\x0a";
static uint16_t god_index_size = 3021;

static char favicon_name[] = "/favicon.ico";
static char favicon_contents[] = "\x00\x00\x01\x00\x01\x00\x20\x20\x00\x00\x01\x00\x20\x00\xa8\x10\x00\x00\x16\x00\x00\x00\x28\x00\x00\x00\x20\x00\x00\x00\x40\x00\x00\x00\x01\x00\x20\x00\x00\x00\x00\x00\x00\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x79\x45\x2b\x00\x77\x44\x2a\x01\x7f\x48\x2e\x01\x7d\x47\x2d\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x00\x62\x37\x1f\x1c\x6c\x3d\x24\x7d\x8a\x4f\x34\x7d\x94\x55\x39\x1c\x92\x54\x38\x00\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x00\x64\x38\x20\x0d\x64\x38\x20\x60\x63\x38\x20\xcf\x68\x3a\x21\xfe\x8b\x4f\x33\xfe\x92\x54\x38\xcf\x92\x54\x38\x60\x92\x54\x38\x0d\x92\x54\x38\x00\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x05\x64\x38\x20\x43\x64\x38\x20\xb5\x63\x37\x1f\xf8\x65\x39\x21\xff\x86\x5d\x48\xff\xa6\x76\x60\xff\x93\x56\x3a\xff\x91\x52\x36\xf8\x92\x54\x38\xb5\x92\x54\x38\x43\x92\x54\x38\x05\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x10\x64\x38\x20\x91\x64\x38\x20\xef\x63\x37\x1f\xff\x77\x4d\x36\xff\xac\x88\x76\xff\xde\xc3\xb6\xff\xf4\xec\xe8\xff\xd0\xb5\xaa\xff\xa2\x6d\x55\xff\x91\x53\x37\xff\x92\x54\x38\xef\x92\x54\x38\x91\x92\x54\x38\x10\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x64\x38\x20\xeb\x67\x3b\x23\xff\x99\x73\x5f\xff\xd2\xb2\xa3\xff\xdf\xc0\xb2\xff\xe8\xcd\xc1\xff\xfc\xf8\xf6\xff\xfb\xf8\xf7\xff\xf0\xe7\xe3\xff\xbf\x9b\x8a\xff\x94\x57\x3c\xff\x92\x54\x38\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x63\x37\x1f\xeb\x75\x4b\x34\xff\xcb\xab\x9b\xff\xa9\x85\x72\xff\xa2\x7d\x6a\xff\xe7\xcc\xc0\xff\xfb\xf7\xf6\xff\xc7\xa8\x9a\xff\xcd\xb1\xa4\xff\xea\xde\xd9\xff\xa0\x6b\x52\xff\x91\x52\x36\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x64\x38\x20\xeb\x69\x3e\x26\xff\x77\x4d\x36\xff\x6f\x45\x2e\xff\xaf\x8b\x79\xff\xe9\xce\xc2\xff\xfc\xf8\xf7\xff\xd2\xb8\xac\xff\x9c\x63\x4a\xff\xa2\x6d\x55\xff\x97\x5b\x40\xff\x92\x54\x37\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x64\x38\x20\xeb\x65\x39\x21\xff\x8c\x64\x4f\xff\xca\xa9\x99\xff\xd7\xb7\xa8\xff\xad\x88\x75\xff\xc7\xaa\x9d\xff\xf4\xee\xeb\xff\xe9\xdc\xd6\xff\xb4\x89\x76\xff\x93\x55\x3a\xff\x92\x54\x38\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x63\x37\x1f\xeb\x74\x4a\x33\xff\xd5\xb5\xa6\xff\xc3\xa2\x91\xff\x7d\x54\x3e\xff\x75\x49\x31\xff\x97\x5f\x46\xff\xa8\x77\x60\xff\xe3\xd3\xcb\xff\xf1\xea\xe6\xff\xa0\x69\x51\xff\x91\x52\x36\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x63\x36\x1e\xeb\x78\x4e\x38\xff\xd8\xb8\xa9\xff\x8f\x67\x52\xff\x7b\x51\x3b\xff\xcd\xb0\xa1\xff\xe5\xd5\xce\xff\xa6\x73\x5c\xff\xb6\x8d\x7a\xff\xf4\xee\xeb\xff\xa3\x6e\x57\xff\x91\x52\x36\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x63\x36\x1e\xeb\x78\x4e\x37\xff\xd7\xb7\xa8\xff\x8a\x63\x4d\xff\x92\x6b\x57\xff\xe9\xcf\xc3\xff\xfc\xf8\xf7\xff\xb9\x92\x80\xff\xb3\x87\x74\xff\xf4\xed\xea\xff\xa3\x6e\x57\xff\x91\x52\x36\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x63\x36\x1e\xeb\x78\x4e\x37\xff\xd7\xb8\xa9\xff\xb0\x8c\x7a\xff\xc4\xa2\x92\xff\xe2\xc7\xba\xff\xf7\xf1\xee\xff\xe4\xd4\xcd\xff\xd3\xb9\xae\xff\xf4\xee\xeb\xff\xa3\x6e\x57\xff\x91\x52\x36\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x63\x36\x1e\xeb\x78\x4e\x38\xff\xda\xbb\xac\xff\xe3\xc5\xb7\xff\xc2\xa0\x90\xff\x8e\x64\x4f\xff\xac\x81\x6d\xff\xe3\xd2\xcb\xff\xfd\xfc\xfc\xff\xf5\xf0\xed\xff\xa3\x6e\x57\xff\x91\x52\x36\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x63\x37\x1f\xeb\x76\x4c\x35\xff\xc1\x9f\x8e\xff\x98\x71\x5d\xff\x6b\x40\x28\xff\x68\x39\x21\xff\x8b\x4e\x32\xff\x99\x5e\x44\xff\xbe\x99\x88\xff\xe1\xd0\xc8\xff\xa1\x6c\x54\xff\x91\x52\x36\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x64\x38\x20\xeb\x67\x3b\x23\xff\x6d\x42\x2b\xff\x63\x37\x1f\xff\x63\x37\x1f\xea\x67\x3a\x22\x8f\x8f\x52\x36\x8f\x92\x53\x37\xea\x91\x52\x36\xff\x9a\x60\x46\xff\x94\x58\x3c\xff\x92\x54\x38\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x64\x38\x20\xeb\x64\x38\x20\xff\x63\x37\x1f\xf6\x64\x38\x20\xab\x64\x38\x20\x3a\x60\x36\x1e\x03\x96\x56\x3a\x03\x92\x54\x38\x3a\x92\x54\x38\xab\x92\x53\x37\xf6\x92\x54\x38\xff\x92\x54\x38\xeb\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x2c\x64\x38\x20\xe8\x64\x38\x20\xc8\x64\x38\x20\x56\x64\x38\x20\x0a\x64\x38\x20\x00\x64\x38\x20\x00\x92\x54\x38\x00\x92\x54\x38\x00\x92\x54\x38\x0a\x92\x54\x38\x56\x92\x54\x38\xc8\x92\x54\x38\xe8\x92\x54\x38\x2c\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x1e\x64\x38\x20\x66\x64\x38\x20\x17\x64\x38\x20\x00\x64\x38\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x92\x54\x38\x00\x92\x54\x38\x00\x92\x54\x38\x17\x92\x54\x38\x66\x92\x54\x38\x1e\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x64\x38\x20\x00\x64\x38\x20\x01\x64\x38\x20\x01\x64\x38\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x92\x54\x38\x00\x92\x54\x38\x01\x92\x54\x38\x01\x92\x54\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xfe\x7f\xff\xff\xfc\x3f\xff\xff\xf0\x0f\xff\xff\xc0\x03\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x80\x01\xff\xff\x83\xc1\xff\xff\x8f\xf1\xff\xff\x9f\xf9\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff";
static uint16_t favicon_size = 4286;

static expectedFiles genFiles[] =
{{data_name, data_contents, data_size},
{index_name, index_contents, index_size},
{god_index_name, god_index_contents, god_index_size},
{favicon_name, favicon_contents, favicon_size}};
static expectedFiles genDir[] =
{{god_name, NULL, 0}};
static int numFiles = 4;
static int numDirs = 1;

#endif /* _WEB_FILES_H_ */