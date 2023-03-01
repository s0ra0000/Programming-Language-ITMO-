///*** 1.7.1 ***///
void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

///*** 1.7.2 ***///
void normalize( int* a) {
   while(*a >0 && *a%2==0){
       *a = *a/2;
   }
    
}

///*** 1.7.3 ***///
void factorize( int n, int* a, int* b )
{
  if(n>1){
      for(int i=2; i<=n/2; i++){
          if(n%i!=0){
              *a = 1;
              *b = n;
          }
          else{
              *a = i;
              *b = n/i;
              break;
          }
      }
      
  } else{
    *a = 1;
    *b = n;
  }
}

///*** 1.7.4 ***///
void array_reverse(int* array, int size) {
    int a;
    int start = 0;
    size--;
    while( size > start){
        a = array[start];
        array[start] = array[size];
        array[size] = a;
        size--;
        start++;
    }
   
}

void array_reverse_ptr(int* array, int* limit) {
    int a;
    int start = 0;
    int size = limit - array;
	size--;
    while(size > start){
        a = array[start];
        
        array[start] = array[size];
        array[size] = a;
        size--;
        start++;
    }
}

///*** 1.7.5 ***///
void array_fib(int* array, int* limit) {
   int a = 1;
    int tmp = 0;
	int b= 0;
	    int size = limit-array;
    for(int i=0;i<size;i++){
        array[i] = a;
        tmp=b;
        b=a;
        a=tmp+a;
           
    }
}

///*** 1.7.6 ***///
// position -- адрес указателя на первый элемент E в массиве,
// для которого predicate(E) выполняется.
// Функция возвращает 0 если элемент не найден.
int array_contains(int* array, int* limit, int** position) {
    
    for( int *i = array + 1;
              i < limit; 
              i++ )
    {
        if(predicate(*i)){
            *position = i;
            return 1;
        }
    }
    *position = NULL;
    return 0;
}

///*** 1.7.7 ***///
int is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

int string_count(char* str) { 
    int i=0;
    int sum = 0;
    while(str[i]!= '\0'){
        sum++;
               i++;
   }
    return sum;
}

int string_words(char* str)  {
   int sum = 0;
     int i=0;
   while(str[i] !=  '\0'){
      if(is_whitespace(str[i])){
         i++;
      }
       else{
           while(!is_whitespace(str[i])){
               if(str[i] == '\0') break;
              i++;
           }
           sum++;
       }
   }
    return sum;
}


