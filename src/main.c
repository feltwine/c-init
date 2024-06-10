#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong usage of cinit!\n");
        fprintf(stderr, "Correct usage: cinit <name of project>\n");
        return 1;
    }

    const char *projectName = argv[1];
    struct stat st;
    if (stat(projectName, &st) == 0) {
        fprintf(stderr, "Project %s already exists.\n", projectName);
        return 1;
    }

    if (mkdir(projectName, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
        fprintf(stderr, "Error: Failed to make directory %s.\n", projectName);
        return 1;
    }

    if (chdir(projectName) != 0) {
        fprintf(stderr, "Error: Failed to change directory to %s.\n", projectName);
        return 1;
    }
    
    /*** create src/main.c ***/
    if (mkdir("src", S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
        fprintf(stderr, "Error: Failed to create src directory.\n");
        return 1;
    } else {
        printf("Created src/ folder\n");
        
        FILE *file = fopen("src/main.c", "w");
        if (file == NULL) {
            fprintf(stderr, "Error: Unable to create file src/main.c.\n");
            return 1;
        }
        fprintf(file, "#include <stdio.h>\n\n");
        fprintf(file, "int main()\n");
        fprintf(file, "{\n");
        fprintf(file, "    printf(\"Hello, World!\\n\");\n");
        fprintf(file, "    return 0;\n");
        fprintf(file, "}\n");
        fclose(file);
    }
    printf("Created src/main.c file\n");


    FILE *file;

    /*** create premake5.lua ***/
    file = fopen("premake5.lua", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to create file premake5.lua.\n");
        return 1;
    }
    fprintf(file, "workspace \"%s\"\n", projectName);
    fprintf(file, "    configurations { \"Debug\", \"Release\" }\n\n");
    fprintf(file, "project \"%s\"\n", projectName);
    fprintf(file, "    kind \"ConsoleApp\"\n");
    fprintf(file, "    language \"C\"\n");
    fprintf(file, "    targetdir \"bin/%{cfg.buildcfg}\"\n");
    fprintf(file, "    files { \"src/**.c\" }\n");
    fclose(file);
    printf("Created premake5.lua file\n");

    /*** create README.md ***/
    file = fopen("README.md", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to create file README.md.\n");
        return 1;
    }
    fprintf(file, "# %s\n\n", projectName);
    fprintf(file, "This is a simple project created by cinit.\n\n");
    fprintf(file, "## Usage\n\n");
    fprintf(file, "1. Install premake: [Premake website](https://premake.github.io/download.html)\n");
    fprintf(file, "2. Run premake to generate project files:\n");
    fprintf(file, "   ```\n");
    fprintf(file, "   premake5 [action]\n");
    fprintf(file, "   ```\n");
    fprintf(file, "   Replace `[action]` with your desired action (e.g., `vs2019`, `gmake`, etc.).\n");
    fclose(file);
    printf("Created README.md file\n");

    /*** create .gitignore ***/
    file = fopen(".gitignore", "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to create file .gitignore.\n");
        return 1;
    }
    fprintf(file, "# Ignore object files and executables\n");
    fprintf(file, "*.o\n");
    fprintf(file, "*.out\n");
    fprintf(file, "*.exe\n");
    fprintf(file, "\n# Ignore build directories\n");
    fprintf(file, "bin/\n");
    fprintf(file, "obj/\n");
    fclose(file);
    printf("Created .gitignore file\n");

    system("git init");
    return 0;
}
