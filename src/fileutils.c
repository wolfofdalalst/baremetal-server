#include "fileutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Reads file from filesystem and returns content with metadata
struct FileContent* readFile(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(file);
        return NULL;
    }
    
    struct FileContent *fileContent = malloc(sizeof(struct FileContent));
    if (!fileContent) {
        fclose(file);
        return NULL;
    }
    
    fileContent->content = malloc(file_size + 1);
    if (!fileContent->content) {
        free(fileContent);
        fclose(file);
        return NULL;
    }
    
    size_t bytes_read = fread(fileContent->content, 1, file_size, file);
    fileContent->content[bytes_read] = '\0';
    fileContent->size = bytes_read;
    
    fileContent->mime_type = strdup(getMimeType(filepath));
    
    fclose(file);
    return fileContent;
}

// Frees memory allocated for FileContent structure
void freeFileContent(struct FileContent *file) {
    if (file) {
        if (file->content) {
            free(file->content);
        }
        if (file->mime_type) {
            free(file->mime_type);
        }
        free(file);
    }
}

// Returns MIME type string based on file extension
const char* getMimeType(const char *filepath) {
    const char *ext = strrchr(filepath, '.');
    if (!ext) {
        return "application/octet-stream";
    }
    
    if (strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0) {
        return "text/html";
    } else if (strcmp(ext, ".css") == 0) {
        return "text/css";
    } else if (strcmp(ext, ".js") == 0) {
        return "application/javascript";
    } else if (strcmp(ext, ".json") == 0) {
        return "application/json";
    } else if (strcmp(ext, ".png") == 0) {
        return "image/png";
    } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
        return "image/jpeg";
    } else if (strcmp(ext, ".gif") == 0) {
        return "image/gif";
    } else if (strcmp(ext, ".txt") == 0) {
        return "text/plain";
    } else {
        return "application/octet-stream";
    }
}

// Checks if file exists in filesystem
int fileExists(const char *filepath) {
    struct stat buffer;
    return (stat(filepath, &buffer) == 0);
}
