#ifndef LISPRUINER_H_INCLUDED
#define LISPRUINER_H_INCLUDED

short unsigned int inArgPos(const char* argu, int argc, char* argv[]);

void helpDisplay();
void versionDisplay();
void shortHelp();

void ruinFile(FILE* file, int verbose);

#endif // LISPRUINER_H_INCLUDED
