#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <stdio.h>

struct FileContent {
    char *content;
    size_t size;
    char *mime_type;
};

// Reads file content and returns structure with content and metadata
struct FileContent* readFile(const char *filepath);

// Frees memory allocated for FileContent structure
void freeFileContent(struct FileContent *file);

// Returns MIME type string based on file extension
const char* getMimeType(const char *filepath);

// Checks if file exists in filesystem
int fileExists(const char *filepath);

#endif // FILEUTILS_H
