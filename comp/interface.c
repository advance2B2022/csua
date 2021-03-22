
#include <stdio.h>
#include <stdlib.h>
#include "csua.h"



CS_Compiler* CS_create_compiler() {
    MEM_Storage storage;
    CS_Compiler *compiler;    
    storage = MEM_open_storage(0);
    compiler = (CS_Compiler*)MEM_storage_malloc(storage, sizeof(CS_Compiler));
    compiler->storage = storage;
    compiler->expr_list = NULL;
    compiler->stmt_list = NULL;
    compiler->decl_list = NULL;
    compiler->current_block = NULL;
    compiler->function_count = 0;
    compiler->function_list = NULL;
    
    cs_set_current_compiler(compiler);
    
    return compiler;
}

void CS_delete_compiler(CS_Compiler* compiler) {
    MEM_Storage storage = compiler->storage;
    MEM_dispose(storage);
}

void CS_compile(CS_Compiler* compiler, FILE *fin) {
    extern int yyparse(void);
    extern FILE *yyin;
    yyin = fin;
    if (yyin == NULL) {
        fprintf(stderr, "cannot open file\n");
        exit(1);
    }
    if (yyparse()) {
        fprintf(stderr, "Parse Error");
        exit(1);
    }    
}

