#include <stdio.h>
#include <string.h>

//#define ONLINE_JUDGE 1

#define u_int unsigned int

const char * const g_CONCEPTS = "PUI";
const char * const g_UNITS = "WVA";
const u_int g_CONCEPTS_COUNT = strlen(g_CONCEPTS);

const char * const g_PREFIXES = "mkM";
const u_int g_PREFIXES_COUNT = strlen(g_PREFIXES);
const double g_PREFIXES_MULTUPLIERS [] = {0.001, 1000.0, 1000000.0};

struct DataField
{
    DataField (const char & symbol, const double & value, const char & unit) { f_concept = symbol; f_value = value; f_unit = unit; };
    DataField (const DataField & field) { f_concept = field.f_concept; f_value = field.f_value; f_unit = field.f_unit; }
    ~DataField() {};
    DataField & operator = (const DataField & field) { f_concept = field.f_concept; f_value = field.f_value; f_unit = field.f_unit; return *this; }

    char f_concept;
    double f_value;
    char f_unit;
};

void processTestCase (const u_int & i);

DataField decodeDataField (const bool & lastDataFieldInLine);
DataField calculateResult (const DataField & firstField, const DataField & secondField);
void printResult (const u_int & caseIndex, const DataField & resultField);

void readAndNormalizeValue (double & value, char & currentSymbol);
u_int findSymbolIndex (const char & symbol, const char * const word);
void omitLineEnding ();

int main ()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    u_int testCases = 0;
    scanf("%u", &testCases);
    omitLineEnding();

    for (u_int i = 0; i < testCases; i++)
    {
        processTestCase(i);
    }

    return 0;
}

void processTestCase (const u_int & i)
{
    DataField firstField = decodeDataField(false);
    DataField secondField = decodeDataField(true);

    DataField resultField = calculateResult (firstField, secondField);
    printResult(i, resultField);
}

DataField decodeDataField (const bool & lastDataFieldInLine)
{
    DataField result ('\0', 0, '\0');

    char previousSymbol = '\0', currentSymbol = '\0';
    while (
            ((currentSymbol = getchar()) != '=')
            && (currentSymbol != '\n')
            && (currentSymbol != EOF)
        )
    {
        previousSymbol = currentSymbol;
    }

    if (currentSymbol != '=')
    {
        return result;/*parsing error - no '='*/
    }

    u_int conceptIndex = findSymbolIndex(previousSymbol, g_CONCEPTS);
    if (conceptIndex >= g_CONCEPTS_COUNT)
    {
        return result;/*parsing error - no P/U/W*/
    }

    double bufValue = 0;
    readAndNormalizeValue(bufValue, currentSymbol);

    //SAVE RESULT...
    result.f_concept = previousSymbol;
    result.f_value = bufValue;
    result.f_unit = g_UNITS[conceptIndex];
    //..SAVE RESULT

    if (
            lastDataFieldInLine
            && (currentSymbol != '\n')
            && (currentSymbol != EOF)
        )
    {
        omitLineEnding();
    }
    
    return result;
}

DataField calculateResult (const DataField & firstField, const DataField & secondField)
{
    DataField defaultResult ('\0', 0, '\0');

    DataField power (defaultResult), voltage (defaultResult), current (defaultResult);
    DataField * thirdField = NULL;
    bool isPowerDefined = false, isVoltageDefined = false, isCurrentDefined = false;

    char firstConcept = firstField.f_concept;
    char secondConcept = secondField.f_concept;

    switch (firstConcept)
    {
        case 'P':
            power = firstField;
            isPowerDefined = true;
            break;
        case 'U':
            voltage = firstField;
            isVoltageDefined = true;
            break;
        case 'I':
            current = firstField;
            isCurrentDefined = true;
            break;
        default:
            return defaultResult;/*error*/
    }

    switch (secondConcept)
    {
        case 'P':
            power = secondField;
            isPowerDefined = true;
            break;
        case 'U':
            voltage = secondField;
            isVoltageDefined = true;
            break;
        case 'I':
            current = secondField;
            isCurrentDefined = true;
            break;
        default:
            return defaultResult;/*error*/
    }
    
    u_int conceptIndex = -1;
    if (isPowerDefined && isVoltageDefined)
    {
        current.f_unit = power.f_unit / voltage.f_unit;
        thirdField = &current;
        conceptIndex = 2;
    }
    else if (isPowerDefined && isCurrentDefined)
    {
        voltage.f_unit = power.f_unit / current.f_unit;
        thirdField = &voltage;
        conceptIndex = 1;
    }
    else if (isVoltageDefined && isCurrentDefined)
    {
        power.f_unit = voltage.f_unit * current.f_unit;
        thirdField = &power;
        conceptIndex = 0;
    }
    else
    {
        return defaultResult;/*error*/
    }

    (*thirdField).f_concept = g_CONCEPTS[conceptIndex];
    (*thirdField).f_unit = g_UNITS[conceptIndex];
    return *thirdField;
}

void printResult (const u_int & caseIndex, const DataField & resultField)
{
    printf("Problem #%u\n", caseIndex + 1);
  
    printf("%c=%.2lf%c\n\n", resultField.f_concept, resultField.f_value, resultField.f_unit);
}

void readAndNormalizeValue (double & value, char & currentSymbol)
{
    scanf("%lf", &value);
    currentSymbol = getchar();
    u_int prefixIndex = findSymbolIndex(currentSymbol, g_PREFIXES);
    if (prefixIndex < g_PREFIXES_COUNT)
    {
        value *= g_PREFIXES_MULTUPLIERS[prefixIndex];
    }
}

u_int findSymbolIndex (const char & symbol, const char * const word)
{
    u_int index = strchr(word, symbol) - &word[0];
    return index;
}

void omitLineEnding ()
{
    char symbol = '\0';
    while (
            ((symbol = getchar()) != '\n')
            && (symbol != EOF)
        );//no action
}