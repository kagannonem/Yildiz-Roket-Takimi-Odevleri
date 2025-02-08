#include <stdio.h>
#include <cstring> // strlen strcmp
#include <vector>// vector<bool>
#include <ctime>
#include <cstdlib>

#define MAX_ATTEMPTS 6

using namespace std;

//tahmini değerlendiren fonksiyon
void checkGuess(const char* target, const char* guess, char* feedback) 
{
    int targetLength = strlen(target);
    vector<bool> used(targetLength, false);

    for (int i = 0; i < targetLength; ++i) 
    {
        feedback[i] = '-';
    }
    feedback[targetLength] = '\0';

    //dogru pozisyondaki dogru harfleri bul
    for (int i = 0; i < targetLength; ++i)
    {
        if (guess[i] == target[i])
        {
            feedback[i] = '*'; // * doğru harf doğru pozisyon sembolu
            used[i] = true;    // kontrol edilmis olarak isaretle
        }
    }

    // harf doğru ama yanlis yerde kontrolu
    for (int i = 0; i < targetLength; ++i) 
    {
        if (feedback[i] == '*') continue; // kontrol edilmisleri gec
        for (int j = 0; j < targetLength; ++j) 
        {
            if (guess[i] == target[j] && !used[j]) 
            {
                feedback[i] = '?'; // ? doğru harf yanlis pozisyon isareti
                used[j] = true;   // kontrol edilmis olarak isaretle
                break;
            }
        }
    }
}

int main() 
{
    // kelime listesi
    const char* wordList[] = {"yildiz", "teknik", "roket", "takimi", "aviyonik", "ekip"};
    int wordCount = sizeof(wordList) / sizeof(wordList[0]);

    // random number generator
    srand(static_cast<unsigned>(time(0)));
    const char* targetWord = wordList[rand() % wordCount];

    int wordLength = strlen(targetWord);
    char guess[50];    // tahmin icin hafiza
    char feedback[50]; // feedback icin hafiza
    int attempts = 0;

    printf("Welcome to Wordle!\n");
    printf("Guess the %d-letter word. You have %d attempts.\n", wordLength, MAX_ATTEMPTS);

    while (attempts < MAX_ATTEMPTS) 
    {
        printf("Attempt %d/%d: Enter your guess: ", attempts + 1, MAX_ATTEMPTS);
        scanf("%s", guess);

        // tahmin uzunlugunu kontrol et
        if (strlen(guess) != wordLength) {
            printf("Your guess must be exactly %d letters long.\n", wordLength);
            continue;
        }

        // tahmini kontrol et
        checkGuess(targetWord, guess, feedback);
        printf("Feedback: %s\n", feedback);

        // dogru tahmin ciktisi
        if (strcmp(guess, targetWord) == 0) {
            printf("Congratulations! You guessed the word \"%s\" in %d attempts!\n", targetWord, attempts + 1);
            return 0;
        }

        attempts++;
    }
    // tahmin hakki tukendiginde cikti
    printf("Sorry, you've used all your attempts. The word was \"%s\".\n", targetWord);
    return 0;
}
