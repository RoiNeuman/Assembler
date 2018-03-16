#include "parser.h"
#include "memoryManager.h"
#include "lineAnalyzer.h"

static int _parseLine(ParsedFile *pfp, FILE *fp);

/* Parse a given source file */
ParsedFile *parseFile(FILE *fp, char *fName)
{
    ParsedFile *pfp;
    int lineLength;

    /* Allocating memory for the ParsedFile object */
    pfp = initializeParsedFile(fName);

    do { /* Parse all the file's lines */
        lineLength = _parseLine(pfp, fp);
    } while (lineLength != READING_ERROR && lineLength != READING_EOF);

    if (lineLength == READING_ERROR) {
        return NULL;
    }

    return pfp;
}

/* Parse the next line from the given file */
static int _parseLine(ParsedFile *pfp, FILE *fp)
{
    int length;
    char *line;
    Boolean hasError;

    line = NULL;
    length = readFileLine(&line, fp, pfp->fName);
    incrementErrorLoggerLine();

    if (length == READING_ERROR || length == READING_EOF) {
        return length;
    }

    /* Analyze the line */
    hasError = analyzeLine(pfp, line, length);

    if (hasError) { /* This line contain an error */
        return READING_ERROR;
    }

    /* Checking if it's the last line in the file */
    if (*(line + length - 1) != EOF) {
        /* Not the last line in the file */
        return length;
    } else {
        /* Last line in the file */
        return READING_EOF;
    }
}

/* Return the next index in the line which is not a white character */
int clearWhiteCharacters(const char *line, const int length, int index)
{
    while (index != length && isWhiteCharacter(*(line + index))) {
        index++;
    }
    return index;
}

/* Return the next index in the line which is not a white character or comma */
int clearWhiteCharOrComma(const char *line, const int length, int index)
{
    while (index != length && isWhiteCharOrComma(*(line + index))) {
        index++;
    }
    return index;
}

/* Read the next word from a line */
/* Return the next index after the word */
int readNextWord(const char *line, int index, int *start, int *end)
{
    *start = index;
    while (isWhiteCharacter(*(line + index)) == false && *(line + index) != EOF) {
        index++;
    }
    *end = index - 1;
    return index;
}