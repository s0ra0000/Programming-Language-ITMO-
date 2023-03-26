///*** 1.3.1 ***///
// Возвращает 1 если в числе одна цифра, иначе 0
int is_single_digit(int n) {
    if (n < 0) { 
        return 0;
    } 
     else if(n > 9) {
            return 0;
    }
    else {
        return 1;
    }
}

// Возвращает 1 если в числе ровно две цифры, иначе 0
int is_double_digit(int n) {
    if (n < 10) { 
        return 0;
    } 
    else {
        if (n > 99) {
            return 0;
        }
        else {
            return 1;
        }
    }
}

///*** 1.3.2 ***///
int is_sorted3(int a, int b, int c) {
    if(a > b && b > c) return -1;
    else if(a < b && b < c) return 1;
    else return 0;
}

///*** 1.3.3 ***///
int max3(int a, int b, int c) {
    int max = a;
    if(b>max) max = b;
    if(c > max) max = c;
    else return max;
    return max;
}

///*** 1.3.4 ***///
void fizzbuzz(int a){
    if(a<=0){
        return printf("no");}
    else{
    if(a%15==0) return printf("fizzbuzz");
    else if(a%3 ==0) return printf("fizz");
    else if(a%5 == 0) return printf("buzz");
    else return 0}
}
