#include "printer.h"

const char* query_type_string[] = {
	[CREATE_T] = "CREATE",
	[MATCH_T] = "MATCH",
	[SET_T] =  "SET",
	[DELETE_T] = "DELETE"
};

const char* property_operation_string[] = {
	[EQUALS] =  "EQUALS",
	[NOT_EQUALS] = "NOT_EQUALS",
	[LESS_THAN] =  "LESS_THAN",
	[GREATER_THAN] = "GREATER_THAN",
    [CONTAINS] = "CONTAINS"
};

void print_tab(int indent_level) {
    for (int i = 0; i < indent_level; i++) {
        printf("\t");
    }
}

void print_value(struct property* prop) {
    switch (prop->value.type) {
        case BOOL:
            printf("value: %s\n\n", prop->value.as_bool ? "true" : "false");
            break;
        case INT:
            printf("value: %d\n\n",  prop->value.as_int);
            break;
        case DOUBLE:
            printf("value: %f\n\n",  prop->value.as_double);
            break;
        case STRING:
            printf("value: %s\n\n",  prop->value.as_string);
            break;
    }
}

void print_filter(struct query q) {
    struct filter* filter = q.as_match.filter;
            
    if (filter) {
        printf("where conditions:\n");
    }

    while (filter != NULL) {
        if (filter->operation == AND_T) {
            print_tab(1);
            printf("AND\n");
        } else if (filter->operation == OR_T) {
            print_tab(1);
            printf("OR\n");
        }

        print_tab(2);
        printf("field name: %s\n", filter->property.name);

        print_tab(2);
        printf("operation: %s\n", property_operation_string[filter->prop_op]);

        print_tab(2);
        print_value(&(filter->property));

        filter = filter->next_filter;
    }

}


void print_query(struct query q) {
    printf("PARSED QUERY: \n\n");

    printf("query type: %s\n", query_type_string[q.type]);
    printf("var name: %s\n", q.var_name);
    printf("node label: %s\n\n", q.label);
    
    struct property* prop;
    
    switch (q.type) {
        case CREATE_T:
            prop = q.as_create.prop;

            if (prop != NULL) {
                printf("properties: \n");
            }

            while(prop != NULL) {
                print_tab(2);
                printf("name: %s\n", prop->name);

                print_tab(2);
                print_value(prop);

                prop = prop->next_prop;
            }
            break;

        case MATCH_T:
            print_filter(q);
            printf("return value: %s", q.as_match.return_value);
            break;

        case SET_T:
            print_filter(q);
            printf("changed properties:\n");
            prop = q.as_set.prop;

            while(prop != NULL) {
                print_tab(2);
                printf("name: %s\n", prop->name);

                print_tab(2);
                print_value(prop);

                prop = prop->next_prop;
            }
            break;

        case DELETE_T:
            print_filter(q);
            printf("deleted: %s\n", q.as_delete.delete_value);
            break;
    }
}