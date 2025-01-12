#include <stdio.h>// burdaki bazi fonksiyonlari ilk sorudan aldim
#include <stdlib.h>

int rowsMain, columnsMain, rowsFilter, columnsFilter;//bu sefer iki matris icin boyut aliyoruz

void matrixPrinter(int** matrix, int rows, int columns)//matris yazdirmak icin bir fonksiyon
{
	for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int** getMatrix(int rows, int columns)//ilk sorudan aldım matrisi hafizaya alan fonksiyon
{  
    int **matrice = (int **)malloc(rows * sizeof(int *));
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

    for(int i=0;i<=rows-1;i++)
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

int** convulator(int** matrixMain, int** matrixFilter, int rowsConv, int columnsConv, int rowsFilter, int columnsFilter)// asıl convulation hesaplarinin yapildigi fonksiyon
{
	int sumFilter = 0; //filter matrisinin elemanları toplamını saklayacak degisken dongude kullanabilmek icin basta 0 atadim
	int **matrixConv = (int **)malloc(rowsConv * sizeof(int *));//cikti matrise hafiza atadigim dongu
    if (matrixConv == NULL)
    {
        printf("Memory allocation failed!\n");
        return 0;
    }

	for (int i = 0; i < rowsConv; i++)
    {
        matrixConv[i] = (int *)malloc(columnsConv * sizeof(int));
        if (matrixConv[i] == NULL)
        {
            printf("Memory allocation failed!\n");
            return 0;
        }
    }

	for (int i = 0; i < rowsConv; i++) //hafiza atadık ama assagidaki dongude kullanabilmek icin elemanlarini sifir yapmam gerekiyordu.
    {
        for (int j = 0; j < columnsConv; j++)
        {
			matrixConv[i][j] = 0;
		}
	}

	for (int i = 0; i < rowsFilter; i++)// filtre matrisinin elemanlarinin toplamini hesaplayan dongu
    {
        for (int j = 0; j < columnsFilter; j++)
        {
			sumFilter = sumFilter + matrixFilter[i][j];
		}
	}

	for (int i = 0; i < rowsConv; i++)// convulation islemini yapan dongu, ic ice 4 dongu kullandim cunku hem iki boyutlu sonuc matris icinde donuyoruz hem de iki boyutlu ana matris icinde
    {
        for (int j = 0; j < columnsConv; j++)
        {
			for (int m = 0; m < rowsFilter; m++)
    		{
				for (int n = 0; n < columnsFilter; n++)
				{
					matrixConv[i][j] = matrixConv[i][j] + matrixFilter[m][n] * matrixMain[m+i][n+j];
				}
			}
			matrixConv[i][j] = matrixConv[i][j]/sumFilter;
        }
    }
	printf("\n");
	return matrixConv;
}

int main()
{
    char rotationSide;
    printf("Enter number of rows of your main matrice: ");
    scanf("%d",&rowsMain);
    printf("\n");
    printf("Enter number of columns of your main matrice: ");
    scanf("%d",&columnsMain);
    printf("\n");

	printf("Enter number of rows of your convolution matrice: ");
    scanf("%d",&rowsFilter);
    printf("\n");
    printf("Enter number of columns of your filtration matrice: ");
    scanf("%d",&columnsFilter);
    printf("\n");

    int** matrixMain = getMatrix(rowsMain, columnsMain);
	printf("Your main matrix: \n");
	matrixPrinter(matrixMain, rowsMain, columnsMain);

	int** matrixFilter = getMatrix(rowsFilter, columnsFilter);
	printf("Your filtration matrix: \n");
	matrixPrinter(matrixFilter, rowsFilter, columnsFilter);
    
	int rowsConv = rowsMain-rowsFilter+1;
	int columnsConv = columnsMain-columnsFilter+1;
	int** matrixConvulated = convulator(matrixMain, matrixFilter, rowsMain, columnsMain, rowsFilter, columnsFilter);
    printf("Your convulated matrix is:\n");
	matrixPrinter(matrixConvulated, rowsConv, columnsConv);

    return(0);
}

