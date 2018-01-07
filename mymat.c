/******************************************************************************

                            NAME - ELI BRACHA.
        matrix calculator support adding, subbing, multiplying and more .

*******************************************************************************/

#include "mat.h"

void start(matrix *a, matrix *b, matrix *c, matrix *d, matrix *e, matrix *f,matrix *g);
static matrix * select_matrix(int n, matrix *a, matrix *b, matrix *c, matrix *d, matrix *e, matrix *f, matrix *g);
static int validate_commend(char[]);
static int validate_matrix(char input[]);
void print_mat (matrix *);
void read_mat(matrix *,int, double[]);
void add_mat(matrix *mat1,matrix *mat2,matrix *mat3);
void sub_mat(matrix *mat1,matrix *mat2,matrix *mat3);
void mul_mat(matrix *mat1,matrix *mat2,matrix *mat3);
void mul_scalar(matrix *mat,double scalar,matrix *mat2);
void trans_mat(matrix *mat1, matrix *mat2);
void stop();

int main (){
    
    matrix MAT_A,MAT_B,MAT_C,MAT_D,MAT_E,MAT_F,MAT_G;
    
    while(1){              
        printf("Enter Commend To Execute:\n");
    
        start(&MAT_A, &MAT_B, &MAT_C, &MAT_D, &MAT_E, &MAT_F, &MAT_G);
    }
    return 0;

}

void start(matrix *a, matrix *b, matrix *c, matrix *d, matrix *e, matrix *f, matrix *g){

    char input[MAX_INPUT] = {0};

    char method[10] = {0};
    char mats [3][6] = {0};
    char params[MAX_INPUT] = {0};

    enum states {COMMEND, START, PARAMS, END_OF_COMMEND};
    enum option_states {MATRIX_PARAM, NUMBER_PARAM, COMMA};
    enum methods {READ_MAT = 1, PRINT_MAT, ADD_MAT, SUB_MAT, MUL_MAT, MUL_SCALAR, TRANS_MAT, STOP};

    int state = START;
    int option_state = MATRIX_PARAM;

    int i = 0; int j = 0; int k = 0; int l = 0; int q = 0;

    int ch;
    int option;
    int param;
    int mat;
    int flag = 1;

    fgets(input, MAX_INPUT, stdin);

    while((ch =(int) input[i++])){

        switch(state){

            case START:
                if(ch == '\n' || ch == '\t' || ch == ' ')
                    continue;
                else if(isdigit(ch)){
                    printf("Error: Digit At The Beginning Of The Commend\n");
                    exit(0);
                }else if(!isalpha(ch)){
                    printf("Error: Not Character At The Beginning Of The Commend\n");
                    exit(0);
                }else if(isupper(ch)){
                    printf("Error: Upper Case in The Begining Of The Commend\n");
                    exit(0);
                }else{
                    method[j++] = ch;
                    state = COMMEND;
                }
                break;

            case COMMEND: 
                if(isdigit(ch)){
                    printf("Error: Unknown Digit In Commend\n");
                    exit(0);
                }else if(j > 10){
                    printf("Error: Unknown Commend Name(Too long)\n");
                    exit(0);
                }else if(!isalpha(ch) && ch != '_'){
                    printf("Error: Unknown Commend Name(Characters Unrecognized)\n");
                    exit(0);
                }
                method[j++] = ch;
                if(option = validate_commend(method)){
                    state = END_OF_COMMEND;
                    continue;
                }
                break;


            case END_OF_COMMEND:
                
                if((ch == '\n' || ch == '\t' || ch == ' ') && validate_commend(method)){
                    state = PARAMS;
                    continue;
                }

                switch (ch){
                    case '\'' :
                    case '\"':
                        printf("Error: Quotation Marks At The End Of Commend\n");
                        exit(0);
                    case ';' :
                    case ',' :
                        printf("Error: Comma At The End Of Commend\n");
                        exit(0);
                    default:
                        printf("Error: Extraneous Character At The End Of Commend Name\n");
                        exit(0);
                }
                break;

            case PARAMS:
            
                if(ch == '\n' || ch == '\t' || ch == ' '){
                    continue;
                }
                    
                if(option == READ_MAT)   
                    switch(option_state){
                        case MATRIX_PARAM:
                            if(islower(ch) &&  ch != '_'){
                                printf("Error: Matrix Name As Lower Case\n");
                                exit(0);
                            }if(isdigit(ch)){
                                printf("Error: Matrix Name As Digit\n");
                                exit(0);
                            }if(!isalpha(ch) &&  ch != 95){
                                printf("Error: Matrix Name As Unrecognized Character\n");
                                exit(0);
                            }else {
                                mats[k][l++] = ch;
                                if( l >= 5 || ch == ','){
                                    if(!(mat = validate_matrix(mats[0]))){
                                        printf("Error: Matrix Name Invalid\n");
                                        exit(0);
                                    }else
                                        option_state = COMMA;
                                } 
                            }
                            break;

                        case NUMBER_PARAM:
                            if((ch == ',' && isdigit(params[q-1]))){
                                option_state = COMMA;
                            }else if(isdigit(ch) || ch == '-'){
                                params[q++] = ch;
                                flag = 0;
                                break;
                            }else{
                                printf("Error: Expected A Legitimate Number Between Commas\n");
                                exit(0);
                            }

                        case COMMA: 
                            if(ch == ','){
                                if(q)
                                    params[q++] = ',';
                                option_state = NUMBER_PARAM;
                                break;
                            }else{
                                printf("Error: Expected Character After Parameter\n");
                                exit(0);
                            }   
                    }
                    
                else if(option == PRINT_MAT){
                    if(islower(ch) &&  ch != '_'){
                            printf("Error: Matrix Name As Lower Case\n");
                            exit(0);
                    }if(isdigit(ch)){
                            printf("Error: Matrix Name As Digit\n");
                            exit(0);
                    }if(!isalpha(ch) &&  ch != 95){
                            printf("Error: Matrix Name As Unrecognized Character\n");
                            exit(0);
                    }else {
                        mats[k][l++] = ch;
                        if( l >= 5 ){
                            if(!(mat = validate_matrix(mats[0]))){
                                printf("Error: Matrix Name Invalid\n");
                                exit(0);
                            }
                        } 
                    }
                    break;
                }
                
                 else if(option == ADD_MAT || option == SUB_MAT || option == MUL_MAT || option == TRANS_MAT)   
                    switch(option_state){
                        case MATRIX_PARAM:
                            if(islower(ch) &&  ch != '_'){
                                printf("Error: Matrix Name In Lower Case\n");
                                exit(0);
                            }if(isdigit(ch)){
                                printf("Error: Matrix Name As Digit\n");
                                exit(0);
                            }else {
                                mats[k][l++] = ch;
                                if( l >= 5 ){
                                    if(!(validate_matrix(mats[k]))){
                                        printf("Error: Matrix Name Invalid\n");
                                        exit(0);
                                    }else
                                        l = 0;
                                        k++;
                                        mats[k][6] = '\0';
                                        option_state = COMMA;
                                } 
                            }
                            break;

                        case COMMA: 
                            if(ch == ','){
                                if(q)
                                    params[q++] = ',';
                                option_state = MATRIX_PARAM;
                                break;
                            }else{
                                printf("Error: Expected Comma Between Parameters\n");
                                exit(0);
                            }   
                    }

                else if(option == MUL_SCALAR)   
                    switch(option_state){
                        case MATRIX_PARAM:
                         if(islower(ch) &&  ch != '_'){
                                printf("Error: Matrix Name In Lower Case\n");
                                exit(0);
                            }if(isdigit(ch)){
                                printf("Error: Matrix Name As Digit\n");
                                exit(0);
                            }else {
                                mats[k][l++] = ch;
                                if( l >= 5 ){
                                    if(!(validate_matrix(mats[k]))){
                                        printf("Error: Matrix Name Invalid\n");
                                        exit(0);
                                    }else
                                        l = 0;
                                        k++;
                                        mats[k][6] = '\0';
                                        option_state = COMMA;
                                } 
                            }
                            break;

                        case NUMBER_PARAM:
                            if((ch == ',' && isdigit(params[q-1]))){
                                option_state = COMMA;
                            }else if(isdigit(ch) || ch == '-'){
                                params[q++] = ch;
                                flag = 0;
                                break;
                            }else{
                                printf("Error: Expected A Legitimate Number Between Commas\n");
                                exit(0);
                            }

                        case COMMA: 
                            if(ch == ','){
                                if(q)
                                    params[q++] = ',';
                                if(isdigit(params[0]) || (params[0] =='-' && isdigit(params[1]))){
                                    option_state = MATRIX_PARAM;
                                }else if(validate_matrix(mats[0])){
                                    option_state = NUMBER_PARAM;
                                }
                                break;
                            }else{
                                printf("Error: Expected Comma Between Parameters\n");
                                exit(0);
                            }   
                    }
            }
    }
    
    if((!isdigit(params[q-1]) && option == READ_MAT)){
            printf("Error: Unknown Comma, Character Or End Of Input\n");
            exit(0);
    }
    
    if(option == READ_MAT){
        double all_numbers[16] = {0};
        char number[100] = {0};
        int len = strlen(params);
        int cint = 0;
        int i = 0;
        int l,k;
        for(l = 0; l <= len ; l++){
            if(!isdigit(params[l]) && params[l] != '-'){
                for (k = 0; k < i; ++k){
                    if(k == 0 && number[k] == '-'){
                        continue;
                    }
                    else if(!isdigit(number[k])){
                        printf("Error: Not Legitimate Number\n");
                        exit(0);
                    }
                }
		int  j;
                all_numbers[cint++] = atof(number);
                for (j = 0; j < i; ++j)
                    number[j] = '\0';
                i=0;
                continue;
            }
           number[i++] =  params[l];
        }
        if(all_numbers[0]){
            flag = 0;
            matrix * tempMat = select_matrix(mat,a,b,c,d,e,f,g);
            read_mat(tempMat,cint,all_numbers);
        }
    }
    
    else if(option == PRINT_MAT){
        matrix * tempMat = select_matrix(mat,a,b,c,d,e,f,g);
        print_mat(tempMat);
        flag = 0;
    }
    
    else if(option == ADD_MAT || option == SUB_MAT || option == MUL_MAT || option == TRANS_MAT){
        int mat1, mat2, mat3;
        mat1 = validate_matrix(mats[0]);
        mat2 = validate_matrix(mats[1]);
        
        if(option == ADD_MAT || option == SUB_MAT || option == MUL_MAT)
            mat3 = validate_matrix(mats[2]);
        
        switch(option){
            case ADD_MAT:
                add_mat(select_matrix(mat1,a,b,c,d,e,f,g),select_matrix(mat2,a,b,c,d,e,f,g),select_matrix(mat3,a,b,c,d,e,f,g));
                break;
            case SUB_MAT:
                sub_mat(select_matrix(mat1,a,b,c,d,e,f,g),select_matrix(mat2,a,b,c,d,e,f,g),select_matrix(mat3,a,b,c,d,e,f,g));
                break;
            case MUL_MAT:
                mul_mat(select_matrix(mat1,a,b,c,d,e,f,g),select_matrix(mat2,a,b,c,d,e,f,g),select_matrix(mat3,a,b,c,d,e,f,g));
                break;
            case TRANS_MAT:
                trans_mat(select_matrix(mat1,a,b,c,d,e,f,g),select_matrix(mat2,a,b,c,d,e,f,g));
                break;
        }
        
        flag = 0;
    }
    
    else if(option == MUL_SCALAR){
        double scalar = 0;
        char number[100] = {0};
        int len = strlen(params);
        int cint = 0;
        int i = 0;
        int t,k;

        for(t = 0; t <= len ; t++){
            if(params[t] == 44){
                for (k = 0; k < i; ++k){
                    if(k == 0 && number[k] == '-'){
                        continue;
                    }
                    else if(!isdigit(number[k])){
                        printf("Error: Not Legitimate Number\n");
                        exit(0);
                    }
                }
                scalar = atof(number);
                continue;
            }
           number[i++] =  params[t];
        }
        
        if(scalar){
            flag = 0;
            int mat1, mat2;
            mat1 = validate_matrix(mats[0]);
            mat2 = validate_matrix(mats[1]);
            mul_scalar(select_matrix(mat1,a,b,c,d,e,f,g),scalar,select_matrix(mat2,a,b,c,d,e,f,g));
        }
    }
    if(option == STOP) { 
        printf("Exiting Program...\n ");
        stop();
    }
    
    if(flag){
        printf("Error: Incomplete Commend\n");
        exit(0);   
    }
}


static int validate_commend(char input[]){

    if(strcmp(input,"read_mat") == 0)
        return 1;
    else if(strcmp(input,"print_mat")== 0)
        return 2;
    else if (strcmp(input,"add_mat") == 0)
        return 3;
    else if(strcmp(input,"sub_mat") == 0 )
        return 4;
    else if(strcmp(input,"mul_mat") == 0 )
        return 5;
    else if(strcmp(input,"mul_scalar") == 0)
        return 6;
    else if(strcmp(input,"trans_mat") == 0)
        return 7;
    else if(strcmp(input,"stop") == 0)
        return 8;
        
    return 0;

}

static int validate_matrix(char input[]){

    if(strcmp(input,"MAT_A") == 0)
        return 1;
    else if(strcmp(input,"MAT_B")== 0)
        return 2;
    else if (strcmp(input,"MAT_C") == 0)
        return 3;
    else if(strcmp(input,"MAT_D") == 0)
        return 4;
    else if(strcmp(input,"MAT_E") == 0)
        return 5;
    else if(strcmp(input,"MAT_F") == 0)
        return 6;
    else if(strcmp(input,"MAT_G") == 0)
        return 7;

    return 0;

}

static matrix * select_matrix(int n, matrix *a, matrix *b, matrix *c, matrix *d, matrix *e, matrix *f, matrix *g){
    switch(n){
        case 1:
            return a;
        case 2:
            return b;
        case 3:
            return c;
        case 4:
            return d;
        case 5:
            return e;
        case 6:
            return f;
        case 7:
            return g;
    }

}
