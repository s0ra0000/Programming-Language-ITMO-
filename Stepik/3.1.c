///*** 3.1.1 ***///
const union ins program[] = {
    {BC_IREAD},
    {.as_arg64 = {BC_PUSH, .arg = 10}},
    {BC_ISUB},
    {.as_arg64 = {BC_PUSH, .arg = 2}},
    {BC_IDIV},
    { BC_IPRINT },
    { BC_STOP }
};

///*** 3.1.2 ***///
/* Описание инструкций (см. предыдущий шаг) */
enum opcode { BC_PUSH, BC_IPRINT, BC_IREAD, BC_IADD, BC_STOP };

struct bc_noarg {
  enum opcode opcode;
};
struct bc_arg64 {
  enum opcode opcode;
  int64_t arg;
};
union ins {
  enum opcode opcode;
  struct bc_arg64 as_arg64;
  struct bc_noarg as_noarg;
};

/* ------------------------ */

struct vm_state {
  const union ins *ip;
  struct stack data_stack;
};

/* Начальная вместимость стека задаётся определением STACK_CAPACITY */
struct vm_state state_create(const union ins *ip) {
  return (struct vm_state){.ip = ip,
                           .data_stack = stack_create(STACK_CAPACITY)};
}

// Как правильно деинициализировать состояние, освободить все ресурсы?
void state_destroy(struct vm_state *state) {
    stack_destroy(&(state->data_stack));
    free(state);
}


/* Вы можете использовать эти функции: */
void print_int64(int64_t);
struct maybe_int64 maybe_read_int64();

struct stack stack_create(size_t size);
void stack_destroy(struct stack *s);
bool stack_push(struct stack *s, int64_t value);
struct maybe_int64 stack_pop(struct stack *s);

/* Опишите цикл интерпретации с выборкой и выполнением команд (пока не выполним STOP) */
void interpret(struct vm_state *state) {
 for (;;) {
    switch (state->ip->opcode) {
    case BC_PUSH: {
      stack_push(&(state->data_stack),state->ip->as_arg64.arg);
      break;
    }
    case BC_IREAD: {
      struct maybe_int64 val = maybe_read_int64();
      if(val.valid){
          stack_push(&(state->data_stack),val.value);
      }
      break;
    }
    case BC_IADD: {
      struct maybe_int64 val_1 = stack_pop(&(state->data_stack));
      struct maybe_int64 val_2 = stack_pop(&(state->data_stack));
      if(val_1.valid && val_2.valid){
          stack_push(&(state->data_stack),val_1.value+val_2.value);
      }
      break;
    }
    case BC_IPRINT: {
      struct maybe_int64 val = stack_pop(&(state->data_stack));
      if(val.valid){
          print_int64(val.value);
      }
      break;
    }
    case BC_STOP: return;
    default:
      err("Not implemented");
      return;
    }
    state->ip = state->ip + 1;
  }
}

void interpret_program(const union ins *program) {
  struct vm_state state = state_create(program);
  interpret(&state);
  state_destroy(&state);
}

///*** 3.1.3 ***///
/* Вам доступны:


struct maybe_int64 {
    int64_t value; 
    bool valid; 
};

struct maybe_int64 some_int64(int64_t i);

extern const struct maybe_int64 none_int64;

void maybe_int64_print( struct maybe_int64 i );
struct maybe_int64 maybe_read_int64();
void print_int64(int64_t i)
*/

void interpret_push(struct vm_state* state) {
  stack_push(&(state->data_stack), state->ip->as_arg64.arg);
}

void interpret_iread(struct vm_state* state ) {
     struct maybe_int64 val = maybe_read_int64();
      if(val.valid){
          stack_push(&(state->data_stack),val.value);
      }
}
void interpret_iadd(struct vm_state* state ) {
   struct maybe_int64 val_1 = stack_pop(&(state->data_stack));
      struct maybe_int64 val_2 = stack_pop(&(state->data_stack));
      if(val_1.valid && val_2.valid){
          stack_push(&(state->data_stack),val_1.value+val_2.value);
      }
}
void interpret_iprint(struct vm_state* state ) {
  struct maybe_int64 val = stack_pop(&(state->data_stack));
      if(val.valid){
          print_int64(val.value);
      }
}

/* Подсказка: можно выполнять программу пока ip != NULL,
    тогда чтобы её остановить достаточно обнулить ip */
void interpret_stop(struct vm_state* state ) {
  state->ip = NULL;
}

typedef void (*functionCode)(struct vm_state*);

functionCode interpreters[] = {
  [BC_PUSH] = interpret_push,
  [BC_IREAD] = interpret_iread,
  [BC_IADD] = interpret_iadd,
  [BC_IPRINT] = interpret_iprint,
  [BC_STOP] = interpret_stop
};



void interpret(struct vm_state* state) {
  while(state->ip != NULL){
      functionCode fcode = interpreters[state->ip->opcode];
      fcode(state);
      if(!state->ip){
          break;
      }
      state->ip++;
  }
}