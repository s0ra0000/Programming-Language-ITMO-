///*** 3.2.1 ***///
#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
  int64_t value;
} item;

#define STACK_ITEM_PRI PRId64

struct maybe_item {
  bool valid;
  item value;
};

static const struct maybe_item none_int = {0, {0}};

static struct maybe_item some_int(int64_t value) {
  return (struct maybe_item){true, {value}};
}

// Опишите непрозрачную структуру stack_int 
struct stack_int;



struct stack_int *stack_int_create();

void stack_int_destroy(struct stack_int *s);

bool stack_int_empty(struct stack_int const *s);
bool stack_int_full(struct stack_int const *s);

// Опишите функции:
// stack_int_push (первый аргумент структура, второй типа item, возвращает bool)
bool stack_int_push(struct stack_int *s, item i);
// stack_int_pop (аргумент структура, возвращает maybe_item) 
struct maybe_item stack_int_pop(struct stack_int *s);

void stack_int_print(struct stack_int const*);
#endif

///*** 3.2.3 ***///
static struct stack_interface {
    struct stack_int_interface{
        struct stack_int* (*create)();
        bool (*empty)(struct stack_int const *s);
        bool (*full)(struct stack_int const *s);
        void (*destroy)(struct stack_int *s);
        bool (*push)(struct stack_int *s,item i);
        struct maybe_item (*pop)(struct stack_int* s);
    } int64; 
} const stack = {{stack_int_create, stack_int_empty, stack_int_full,
                  stack_int_destroy, stack_int_push, stack_int_pop}};

//3.2.4
static bool divides(int64_t x, int64_t y) { return x % y == 0; }
static void print_int_space(int64_t x) {printf("%" PRId64 " ", x); }
static int64_t read_int() { int64_t x; scanf("%" PRId64, &x); return x; }

void print_divisors(int64_t n) {
  if (n > 0) {
  for (int64_t i = 1; i <= n; i = i + 1){
    if (divides(n, i)){
            print_int_space(i); 
        }    
    }
      printf("$");
  }
  else printf("No");
}