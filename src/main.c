#include "./bison+flex/y.tab.h"



int main(int argc, char **argv) {
    int status = yyparse();
    if (status == 0) {
        print_query(q);
    }
    return status;
}