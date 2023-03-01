///*** 2.2.1 ***///
// вы можете реализовать эти функции для более удобного считывания чисел
int64_t read_int64(){
    int64_t x;
    scanf("%"  SCNd64, &x);
    return x;
}
size_t read_size(){
    size_t y;
    scanf("%zu", &y);
    return y;}

// заполнить уже выделенный массив array размера size числами
void array_int_fill( int64_t* array, size_t size ) {
        for(int64_t i=0; i<size; i++){
            array[i] = read_int64();
        }
}

// Считать размер массива в *size, выделить память под массив и заполнить его числами.
int64_t* array_int_read( size_t* size ) {
        *size = read_size();
        int64_t* array = malloc(sizeof(int64_t)*(*size));
        array_int_fill(array,*size);
        return array;
   
}

///*** 2.2.2 ***///
int64_t* array_int_min( int64_t* array, size_t size ) {
    if(size == 0) return NULL;
    int64_t m = array[0];
    
    int64_t* addr = &array[0];
     for(int64_t i=1; i<size; i++){
         if(array[i] < m){
             m = array[i];
             addr = &array[i];
         }
         else continue;
     }
    return addr;
}

///*** 2.2.3 ***///
// эти функции вы уже реализовали на предыдущих шагах
int64_t* array_int_read( size_t* size );
int64_t* array_int_min( int64_t* array, size_t size); 

// Выводит None если x == NULL, иначе число, на которое указывает x.
void intptr_print( int64_t* x ) {
    size_t size = 0;
    int64_t* array = NULL;
    array = array_int_read(&size);
    x = array_int_min(array,size);
    if(x == NULL){
        char* p = NULL;
        printf( "%s", p);
    }
    else 
        printf("%" PRId64 ,*x);   
    free(array);
}

void perform() {
  int64_t x;
  intptr_print(&x);
}

///*** 2.2.4 ***///
// Вам доступны эти функции из прошлых заданий
size_t read_size();
void array_int_fill( int64_t* array, size_t size );
int64_t* array_int_read( size_t* size );
  
int64_t** marray_read( size_t* rows, size_t** sizes ) {
    int64_t** marray = NULL;
    *rows = read_size();
    *sizes = malloc(sizeof(size_t)*(*rows));
    marray = malloc(sizeof(int64_t)*(*rows));
    for(size_t i=0; i < *rows; i++){
        marray[i] = array_int_read(*sizes+i);
    }
    return marray;
}
void marray_print(int64_t** marray, size_t* sizes, size_t rows) {
    for( size_t i = 0; i < rows; i = i + 1 ) {
        array_int_print( marray[i], sizes[i] );
        print_newline();
    }
}

///*** 2.2.5 ***///
void marray_free( int64_t** marray, size_t rows ) {
 if(marray !=NULL){
     for(size_t i=0; i < rows; i++){
         free(*(marray+i));
     }
     free(marray);
 }
}


///*** 2.2.6 ***///
// Вам доступны следующие функции:
size_t read_size();
int64_t* array_int_min( int64_t* array, size_t size );
int64_t** marray_read( size_t* rows, size_t* sizes[] );
void marray_free( int64_t** marray, size_t rows );
void marray_print(int64_t** marray, size_t* sizes, size_t rows);


// Указатель на минимальное из двух чисел.
// если хотя бы одно число NULL, то возвращать второе
// если оба числа NULL результат NULL
int64_t* int64_ptr_min(int64_t* x, int64_t* y) {
  if(x == NULL){
      return y;
  }
    else if(y == NULL){
        return x;
    } 
    else{
        if(*x>*y) return y;
        else return x;
    }
}

// Вернуть адрес минимального элемента массива массивов
int64_t* marray_int_min( int64_t** marray, size_t* sizes, size_t rows ) {
    int64_t* min = NULL;
  if(marray != NULL){
      for(size_t i = 0; i<rows;i++){
              min = int64_ptr_min(min, array_int_min(marray[i], sizes[i]));
      }
      return min;
  }
     return min;
}

// Вычесть m изо всех элементов массива
void marray_normalize( int64_t** marray, size_t sizes[], size_t rows, int64_t m ) {
   if(marray != NULL){
      for(size_t i = 0; i < rows; i++){
          for(size_t j=0; j < sizes[i]; j++){
              marray[i][j] = marray[i][j] - m;
         }
      }
   }
}

// Прочитать, найти минимум и нормализовать массив, вывести результат
void perform() {  
    size_t rows;
    size_t* sizes;
    int64_t** marray = marray_read(&rows,&sizes);

    int64_t* minimum = marray_int_min(marray,sizes,rows);
    if(minimum != NULL){
        marray_normalize(marray,sizes,rows,*minimum);
        marray_print(marray,sizes,rows);
        marray_free(marray,rows);
        free(minimum);
        free(sizes);
    }
    else{
        marray_free(marray,rows);
        free(minimum);
        free(sizes);
  }
    
}