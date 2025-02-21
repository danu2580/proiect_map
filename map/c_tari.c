#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_COUNTRIES 5  // 100
#define MAX_NAME_LEN 10  // 50
#define MAX_COLORS 5     // 10

typedef struct {
    char name[MAX_NAME_LEN];
    int neighbors[MAX_COUNTRIES]; // Lista vecinilor
    int neighborCount;            // Numărul de vecini
} Country;

// Funcție pentru a verifica dacă o culoare poate fi atribuită
bool canColor(int countryIndex, int colorIndex, int countryColors[], int numCountries, int adjacencyMatrix[MAX_COUNTRIES][MAX_COUNTRIES]) {
    for (int i = 0; i < numCountries; i++) {
        // Dacă țara curentă este vecină cu alta și au aceeași culoare
        if (adjacencyMatrix[countryIndex][i] == 1 && countryColors[i] == colorIndex) {
            return false;
        }
    }
    return true;
}

// Funcție recursivă pentru colorarea hărții
bool colorMap(int numCountries, int numColors, int countryIndex, int countryColors[], int adjacencyMatrix[MAX_COUNTRIES][MAX_COUNTRIES]) {
    if (countryIndex == numCountries) {
        return true; // Toate țările au fost colorate
    }

    for (int colorIndex = 1; colorIndex <= numColors; colorIndex++) {
        if (canColor(countryIndex, colorIndex, countryColors, numCountries, adjacencyMatrix)) {
            countryColors[countryIndex] = colorIndex; // Atribuie culoarea curentă

            if (colorMap(numCountries, numColors, countryIndex + 1, countryColors, adjacencyMatrix)) {
                return true; // Dacă funcționează, continuă
            }

            countryColors[countryIndex] = 0; // Resetare (backtracking)
        }
    }
    return false; // Nu există soluție validă
}

void printMatrix(int matrix[MAX_COUNTRIES][MAX_COUNTRIES], int numCountries) {
    printf("Matricea de adiacență:\n");
    for (int i = 0; i < numCountries; i++) {
        for (int j = 0; j < numCountries; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Exemplu de input
    int numCountries = 4;
    Country countries[MAX_COUNTRIES] = {
            {"A", {1, 2}, 2},
            {"B", {0, 2, 3}, 3},
            {"C", {0, 1, 3}, 3},
            {"D", {1, 2}, 2}
    };

    int numColors = 3;
    char colorNames[MAX_COLORS][MAX_NAME_LEN] = {"Red", "Green", "Blue"};

    // Construim matricea de adiacență
    int adjacencyMatrix[MAX_COUNTRIES][MAX_COUNTRIES] = {0};
    for (int i = 0; i < numCountries; i++) {
        for (int j = 0; j < countries[i].neighborCount; j++) {
            int neighbor = countries[i].neighbors[j];
            adjacencyMatrix[i][neighbor] = 1;
            adjacencyMatrix[neighbor][i] = 1;
        }
    }

    printMatrix(adjacencyMatrix, numCountries);

    // Vectorul culorilor
    int countryColors[MAX_COUNTRIES] = {0};

    // Colorarea hărții
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
