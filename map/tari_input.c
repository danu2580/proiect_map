#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COUNTRIES 100
#define MAX_NAME_LEN 50
#define MAX_COLORS 10

// Structură pentru țară
typedef struct {
    char name[MAX_NAME_LEN];
    int neighbors[MAX_COUNTRIES]; // Lista vecinilor (indicele țării)
    int neighborCount;
} Country;

// Funcție pentru a verifica dacă o culoare poate fi atribuită
bool canColor(int countryIndex, int colorIndex, int numCountries, int countryColors[], int adjacencyMatrix[MAX_COUNTRIES][MAX_COUNTRIES]) {
    for (int i = 0; i < numCountries; i++) {
        if (adjacencyMatrix[countryIndex][i] == 1 && countryColors[i] == colorIndex) {
            return false;
        }
    }
    return true;
}

// Funcție recursivă pentru a colora harta
bool colorMap(int numCountries, int numColors, int countryIndex, int countryColors[], int adjacencyMatrix[MAX_COUNTRIES][MAX_COUNTRIES]) {
    if (countryIndex == numCountries) {
        return true; // Toate țările au fost colorate
    }

    for (int colorIndex = 1; colorIndex <= numColors; colorIndex++) {
        if (canColor(countryIndex, colorIndex, numCountries, countryColors, adjacencyMatrix)) {
            countryColors[countryIndex] = colorIndex;

            if (colorMap(numCountries, numColors, countryIndex + 1, countryColors, adjacencyMatrix)) {
                return true;
            }

            countryColors[countryIndex] = 0;
        }
    }

    return false;
}

int main() {
    int numCountries;
    printf("Introduceti numarul de tari: ");
    scanf("%d", &numCountries);

    Country countries[MAX_COUNTRIES];

    // Citim țările și vecinii lor
    for (int i = 0; i < numCountries; i++) {
        printf("Introduceti numele tarii %d: ", i + 1);
        scanf("%s", countries[i].name);

        printf("Introduceti numarul de vecini pentru %s: ", countries[i].name);
        scanf("%d", &countries[i].neighborCount);

        printf("Introduceti indicii vecinilor pentru %s (0-%d):\n", countries[i].name, numCountries - 1);
        for (int j = 0; j < countries[i].neighborCount; j++) {
            scanf("%d", &countries[i].neighbors[j]);
        }
    }

    int numColors;
    printf("Introduceti numarul de culori disponibile: ");
    scanf("%d", &numColors);

    char colorNames[MAX_COLORS][MAX_NAME_LEN];
    for (int i = 0; i < numColors; i++) {
        printf("Introduceti numele culorii %d: ", i + 1);
        scanf("%s", colorNames[i]);
    }

    // Matricea de adiacență
    int adjacencyMatrix[MAX_COUNTRIES][MAX_COUNTRIES] = {0};
    for (int i = 0; i < numCountries; i++) {
        for (int j = 0; j < countries[i].neighborCount; j++) {
            int neighbor = countries[i].neighbors[j];
            adjacencyMatrix[i][neighbor] = 1;
            adjacencyMatrix[neighbor][i] = 1;
        }
    }

    int countryColors[MAX_COUNTRIES] = {0};

    // Colorăm harta
    if (colorMap(numCountries, numColors, 0, countryColors, adjacencyMatrix)) {
        printf("Harta a fost colorată cu succes:\n");
        for (int i = 0; i < numCountries; i++) {
            printf("Țara %s are culoarea %s\n", countries[i].name, colorNames[countryColors[i] - 1]);
        }
    } else {
        printf("Nu s-a putut colora harta cu culorile disponibile.\n");
    }

    return 0;
}
