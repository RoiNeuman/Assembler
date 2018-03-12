#include <ctype.h>
#include "dataLine.h"
#include "parser.h"
#include "errors.h"

Boolean _analyzeDataLine(ParsedFile *pfp, const char *line, const int length, int lineIndex)
{
    int sign, c, data;
    Boolean hasError;

    hasError = false;
    lineIndex = clearWhiteCharacters(line, length, lineIndex);
    while (lineIndex != length && hasError == false) {
        data = 0;
        sign = 1;
        if ((c = *(line + lineIndex)) == '-' || c == '+') { /* Checking the number's sign */
            sign = c == '-' ? -1 : 1;
            lineIndex++;
        }
        while (lineIndex != length && isdigit(c = *(line + lineIndex))) {
            data = (data * 10) + (c - '0');
            lineIndex++;
        }
        if (lineIndex != length && c != EOF) {
            logError(undefinedData, NULL);
            pfp->hasError = true;
            break;
        }
        hasError = addData(pfp, (data * sign));
        lineIndex = clearWhiteCharOrComma(line, length, lineIndex);
    }
    return hasError;
}

Boolean _analyzeStructLine(ParsedFile *pfp, const char *line, const int length, int lineIndex)
{
    int sign, c, data;
    Boolean hasError;

    hasError = false;
    lineIndex = clearWhiteCharacters(line, length, lineIndex);
    while (lineIndex != length && hasError == false) {
        if ((c = *(line + lineIndex)) == '\"') { /* String data */
            lineIndex++;
            while (lineIndex != length && (c = *(line + lineIndex)) != '\"' && isascii(c) && c != EOF && hasError == false) {
                hasError = addData(pfp, c);
                lineIndex++;
            }
            if (hasError) {
                break;
            }
            if (c != '\"') { /* Checking ending quotation mark */
                pfp->hasError = true;
                logError(missedQuotationMark, "Closing quotation mark.");
                break;
            }
        } else if (c == '-' || c == '+' || isdigit(c)) { /* Number data */
            data = 0;
            sign = 1;
            if (c == '-' || c == '+') { /* Checking the number's sign */
                sign = c == '-' ? -1 : 1;
                lineIndex++;
            }
            while (lineIndex != length && isdigit(c = *(line + lineIndex)) && c != EOF) {
                data = (data * 10) + (c - '0');
                lineIndex++;
            }
            if (lineIndex != length && c != EOF) {
                logError(undefinedData, NULL);
                pfp->hasError = true;
                break;
            }
            hasError = addData(pfp, (data * sign));
        } else {
            pfp->hasError = true;
            break;
        }
        lineIndex = clearWhiteCharOrComma(line, length, lineIndex);
    }
    return hasError;
}

Boolean _analyzeStringLine(ParsedFile *pfp, const char *line, const int length, int lineIndex)
{
    int c;
    Boolean hasError;

    hasError = false;
    lineIndex = clearWhiteCharacters(line, length, lineIndex);
    if (lineIndex != length && (c = *(line + lineIndex)) == '\"') {
        while (lineIndex != length && (c = *(line + lineIndex)) != '\"' && isascii(c) && c != EOF && hasError == false) {
            hasError = addData(pfp, c);
            lineIndex++;
        }
        if (c != '\"' && hasError == false) { /* Checking ending quotation mark */
            pfp->hasError = true;
            logError(missedQuotationMark, "Closing quotation mark.");
        }
    } else {
        pfp->hasError = true;
        logError(missedQuotationMark, "Opening quotation mark.");
    }
    return hasError;
}

Boolean _analyzeEntryLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord)
{

}

Boolean _analyzeExternLine(ParsedFile *pfp, const char *line, const int length, int lineIndex, int startOfWord, int endOfWord)
{

}