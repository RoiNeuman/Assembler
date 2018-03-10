#include "parser.h"
#include "memoryManager.h"
#include "errors.h"
#include "utils.h"

static int _parseLine(ParsedFile *pfp, FILE *fp);
static void _analyzeLine(const char *line, int length);
static int _clearWhiteCharacters(const char *line, int length, int index);
static int _readNextWord(const char *line, int index, int *start, int *end);

/* Parse a given source file */
ParsedFile *parseFile(FILE *fp, char *fName)
{
    ParsedFile *pfp;
    int lineLength;

    /* Allocating memory for the ParsedFile object */
    pfp = (ParsedFile *)autoDispMalloc(sizeof(ParsedFile));

    if (pfp == NULL) {
        logError(outOfMemory, "Allocating parseFile struct, parseFile()");
        return NULL;
    }

    pfp->fName = fName;

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

    line = NULL;
    length = readFileLine(&line, fp, pfp->fName);

    if (length == READING_ERROR || length == READING_EOF) {
        return length;
    }

    /* Analyze the line */
    _analyzeLine(line, length);

    /* Checking if it's the last line in the file */
    if (*(line + length - 1) != EOF) {
        /* Not the last line in the file */
        return length;
    } else {
        /* Last line in the file */
        return READING_EOF;
    }
}

/* Analyze the given line */
static void _analyzeLine(const char *line, const int length)
{
    int lineIndex, startOfWord, endOfWord;
    LineType lineType;

    lineIndex = _clearWhiteCharacters(line, length, FIRST_INDEX);

    if (lineIndex == length) return; /* End of Line */

    lineIndex = _readNextWord(line, lineIndex, &startOfWord, &endOfWord);

    if (isComment(line, startOfWord)) return; /* Skipping comment line */

    /*lineType = _filterFirstWord(line, startOfWord, endOfWord);*/
}

/* Return the next index in the line which is not a white character */
static int _clearWhiteCharacters(const char *line, const int length, int index)
{
    while (index != length && isWhiteCharacter(*(line + index))) {
        index++;
    }
    return index;
}

/* Read the next word from a line */
/* Return the next index after the word */
static int _readNextWord(const char *line, int index, int *start, int *end)
{
    *start = index;
    while (isWhiteCharacter(*(line + index)) == false) {
        index++;
    }
    *end = index - 1;
    return index;
}