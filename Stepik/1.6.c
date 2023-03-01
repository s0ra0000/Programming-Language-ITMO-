///*** 1.6.1 ***///
int main() {
    int a = read_int();
    if(a>10) printf("No");
    else{
        for(int i = a; i<=10; i++){
            printf("%d ",i);
        }
    }
    return 0;
}

///*** 1.6.2 ***///
int is_square(int x){
    if(x == 0 || x==1 ) return 1;
    else{
        int i = 1;
        while(i <= x/2){
            if(i*i == x){
                return 1;    
            }        i++;
        } return 0;
    }
}

///*** 1.6.3 ***///
/* Возвращает 1 если a делится на b
  (остаток от деления a на b -- ноль)
   0 если не делится.
*/
int divides(int a, int b) { 
    return a % b == 0; 
}

/* Переводит вывод на новую строку. 
*/
void print_newline() { 
    printf("\n"); 
}

/* Выводит одну строчку: число n, двоеточие и все его делители, большие единицы, до самого n включительно.
Например, для числа 8 это:
"8: 2 4 8 "
В конце этой строчки должен быть пробел.
*/
void divisors(int n) {
    printf("%d: ",n);
    for(int i = 2; i <= n; i++){
        if(divides(n,i) == 1){
            printf("%d ",i);
        }
    }
    print_newline();
}

/* Выводит делители для всех чисел от 1 до limit включительно
Каждая строчка -- в формате, заданном функцией divisors.
*/
void all_divisors(int limit) {
    for(int i=1; i<=limit; i++){
          divisors(i);
    }
}


int main() {
    all_divisors(100);
    return 0;
}

///*** 1.6.4 ***///
int is_prime(int x){
    if(x < 2) return 0;
    else{
        for(int i = 2; i <= x/2; i++){
            if(x % i == 0) return 0;
        }
        return 1;
    }
}