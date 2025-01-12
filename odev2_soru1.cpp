#include <stdio.h>
#include <stdlib.h>

int rows, columns;

int** getMatrice(int rows, int columns) //matrisi hafızaya alan ve cikti olarak veren fonksyion 
{  
    int **matrice = (int **)malloc(rows * sizeof(int *)); //2d array oldugu icin memory allocation yapmamiz gerekiyor zira c sadece tek boyutlu arraylarda otomatik allocation yapiyor.
    if (matrice == NULL)
    {
        printf("Memory allocation failed!\n");
        return 0;
    }

    for (int i = 0; i < rows; i++)
    {
        matrice[i] = (int *)malloc(columns * sizeof(int));
        if (matrice[i] == NULL)
        {
            printf("Memory allocation failed!\n");
            return 0;
        }
    }

    for(int i=0;i<=rows-1;i++)//matris elemanlarini tek tek kullanicidan aldigim dongu
    {
        for(int j=0;j<=columns-1;j++)
        {
            printf("Enter [%d,%d] element of your matrice: ", i+1,j+1);
            scanf("%d", &matrice[i][j]);
            printf("\n");
        }
    }

    return matrice;
}

void rotate(int** matrice, int rows, int columns, char rotationSide)//matrisi istenen yone donduren fonksiyon, bir cikti vermiyor sadece yazdirma islemi yapiyor.
{
    int **rotatedMatrice = (int **)malloc(columns * sizeof(int *));//dondugunde matris boyutlari degisiyor dolayisiyla yeni bir matris tanimlayip hafiza atamak gerekiyor
    if (rotatedMatrice == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < columns; i++)
    {
        rotatedMatrice[i] = (int *)malloc(rows * sizeof(int));
        if (rotatedMatrice[i] == NULL)
        {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++)
            {
                free(rotatedMatrice[j]);
            }
            free(rotatedMatrice);
            exit(1);
        }
    }

    if (rotationSide == 'l' || rotationSide == 'L') //sola donduren dongu
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                rotatedMatrice[columns - j - 1][i] = matrice[i][j];//algoritmayi kagit ustunde karalayip buldum
            }
        }
    }
    else if (rotationSide == 'r' || rotationSide == 'R') //saga donduren dongu
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                rotatedMatrice[j][rows - i - 1] = matrice[i][j];
            }
        }
    }
    else
    {
        printf("\nInvalid entry enter L or R.\n");
        return;
    }

    printf("\nRotated Matrix:\n"); //dondurulmus matrisi yazdiran dongu
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%d ", rotatedMatrice[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < columns; i++)//hafizayi bosaltan dongu
    {
        free(rotatedMatrice[i]);
    }
    free(rotatedMatrice);
}


int main() //main fonksiyon kendini acikliyor
{
    char rotationSide;
    printf("Enter number of rows: ");
    scanf("%d",&rows);
    printf("\n");
    printf("Enter number of columns: ");
    scanf("%d",&columns);
    printf("\n");

    int** matrice = getMatrice(rows, columns);
    
    printf("Your matrix is:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }

    printf("\nPick if you want to rotate left or right (L/R): ");
    scanf(" %c", &rotationSide);
    rotate(matrice, rows, columns, rotationSide);

    return(0);
}