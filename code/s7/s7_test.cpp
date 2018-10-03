#include "s7.h"

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr

static s7_pointer cube(s7_scheme* s7, s7_pointer args)
{
    if (s7 == nullptr)
    {
        std::cerr << "error: s7_scheme* s7 is nullptr\n";
        return nullptr;
    }

    s7_pointer x = s7_car(args);

    if (!s7_is_number(x))
    {
        return s7_wrong_type_arg_error(s7, "cube", 1, x, "a real");
    }

    double double_x = s7_number_to_real(s7, x);
    return s7_make_real(s7, static_cast<s7_double>(double_x * double_x * double_x));
}

s7_scheme* init_scheme()
{
    s7_scheme* s7 = s7_init();

    s7_define_function(s7, "cube", cube, 1, 0, false, "(cube number) computes the cube of number");

    return s7;
}

bool do_stuff(s7_scheme* s7)
{
    if (s7 == nullptr)
    {
        std::cerr << "error: scheme* sc is nullptr\n";
        return false;
    }

    s7_load(s7, "hello_world.scm");

    /* eval a C string as Scheme code */
    std::string hello_world_string = "(display \"Hello world!\n\")";
    s7_eval_c_string(s7, hello_world_string.c_str());

    std::string cube_string = "(display (string-append \"5.0 cubed is \" (number->string (cube 5.0)) \"\n\"))";
    s7_eval_c_string(s7, cube_string.c_str());

    std::string see_you_string = "(display \"See you!\n\")";
    s7_eval_c_string(s7, see_you_string.c_str());

    return true;
}

int main(void)
{
    s7_scheme* s7 = init_scheme();

    if (s7 == nullptr)
    {
        std::cerr << "error occurred in init_scheme function.\n";
        return 1;
    }

    if (!do_stuff(s7))
    {
        std::cerr << "error occurred in do_stuff function.\n";
        free(s7);
        return 1;
    }

    free(s7);
    return 0;
}
