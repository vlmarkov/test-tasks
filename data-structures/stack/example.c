#include <stack.h>


int main(int argc, char const *argv[])
{
    stack_t *stack = stack_create();
    if (stack == NULL)
    {
        return -1;
    }

    stack_print(stack);

    stack_push(stack, 5);
    stack_print(stack);

    stack_pop(stack);
    stack_print(stack);

    stack_destroy(&stack);

    return 0;
}
