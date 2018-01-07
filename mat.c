#include "mat.h"

void read_mat(matrix *mat,int counter, double n[]){

    int stop = 0;
    int j,i;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++){
            if(stop < counter){
                 mat -> matrix[i][j] = n[stop];
                 stop++;
            }else
                mat -> matrix[i][j] = 0;
        }
    }
}
void print_mat (matrix *mat){

  int j,i;

  for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++){
            printf("%.2f\t",mat -> matrix[i][j]);
        }
         printf("\n");
    }
}

void add_mat(matrix *mat1,matrix *mat2,matrix *mat3){

    int j,i;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++){
            mat3 -> matrix[i][j] = mat1 -> matrix[i][j] + mat2 -> matrix[i][j];
        }
    }
}

void sub_mat(matrix *mat1,matrix *mat2,matrix *mat3){

    int j,i;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++){
            mat3 -> matrix[i][j] = mat1 -> matrix[i][j] - mat2 -> matrix[i][j];
        }
    }
}

void mul_mat(matrix *mat1,matrix *mat2,matrix *mat3){
    int i, j, k;
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < ROW; j++)
        {
            mat3 -> matrix[i][j] = 0;
            for (k = 0; k < ROW; k++)
                mat3 -> matrix[i][j] += mat1 -> matrix[i][k]*mat2 -> matrix[k][j];
        }
    }
}

void mul_scalar(matrix *mat1,double scalar,matrix *mat2){

    int i,j;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COLUMN; j++){
            mat2 -> matrix[i][j] = mat1 -> matrix[i][j] * scalar ;
        }
    }
}

void trans_mat(matrix *mat1, matrix *mat2){

    int i,j;

    for(i = 0; i < ROW; i++){
        for(j = 0; i >= j; j++){
            double temp = mat1 -> matrix[i][j];
            mat2-> matrix[i][j] = mat1 -> matrix[j][i] ;
            mat2 -> matrix[j][i] = temp;
        }
    }
}

void stop(){
    exit(0);
}
