#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cub3d.h"

void test_init_struct()
{
    printf(YELLOW "Testing init_struct...\n" RESET);
        
    t_map map;
    t_vars vars;

    init_struct(&map, &vars);

    if (map.p_x == 0 && map.p_y == 0 && map.p_s == 0 &&
        map.x == 0 && map.y == 0 &&
        vars.i == 0 && vars.j == 0 && vars.k == 0 && vars.l == 0 && vars.m == 0 && vars.n == 0 &&
        map.map == NULL && vars.line == NULL && vars.tmp == NULL)
    {
        printf(GREEN "init_struct test passed. ✅\n" RESET);
    }
    else
    {
        printf(RED "init_struct test failed.\n" RESET);
    }
}

void test_check_map_extension()
{
    printf(YELLOW "Testing check_map_extension...\n" RESET);
    
    //1
    int id = fork();
    if (id == 0)
    {
        check_map_extention("test.cub");
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "1 - check_map_extention valid extension test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "1 - check_map_extention valid extension test failed ❌.\n" RESET);
        }
    }
    //2
    id = fork();
    if (id == 0)
    {
        check_map_extention("test.txt");
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            printf(GREEN "2 - check_map_extention invalid extension test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "2 - check_map_extention invalid extension test failed ❌.\n" RESET);
        }
    }
    //3
    id = fork();
    if (id == 0)
    {
        check_map_extention("invalid");
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            printf(GREEN "3 - check_map_extention no extension test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "3 - check_map_extention no extension test failed ❌.\n" RESET);
        }
    }
    //4
    id = fork();
    if (id == 0)
    {
        check_map_extention(".cub");
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            printf(GREEN "4 - check_map_extention no file name test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "4 - check_map_extention no file name test failed ❌.\n" RESET);
        }
    }

    //5
    id = fork();
    if (id == 0)
    {
        check_map_extention("cub");
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            printf(GREEN "5 - check_map_extention no file name test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "5 - check_map_extention no file name test failed ❌.\n" RESET);
        }
    }
    //6
    id = fork();
    if (id == 0)
    {
        check_map_extention(NULL);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if ((WEXITSTATUS(status) == 1))
        {
            printf(GREEN "6 - check_map_extention NULL test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "6 - check_map_extention NULL test failed ❌.\n" RESET);
        }
    }
    //7
    id = fork();
    if (id == 0)
    {
        check_map_extention("");
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            printf(GREEN "7 - check_map_extention empty test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "7 - check_map_extention empty test failed ❌.\n" RESET);
        }
    }
    //8
    id = fork();
    if (id == 0)
    {
        check_map_extention("#$#@$.cub");
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            // printf("status code %d\n", status);
            printf(GREEN "8 - check_map_extention empty test passed ✅.\n" RESET);
        }
        else
        {
            // printf("status code %d\n", status);
            printf(RED "8 - check_map_extention empty test failed ❌.\n" RESET);
        }
    }
    //9
    id = fork();
    if (id == 0)
    {
        check_map_extention("/.cub");
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
        {
            // printf("status code ---%d\n", status);
            printf(GREEN "9 - check_map_extention empty test passed ✅.\n" RESET);
        }
        else
        {
            // printf("status code %d\n", status);
            printf(RED "9 - check_map_extention empty test failed ❌.\n" RESET);
        }
    }
}


// void test_fill_the_map()
// {
//     printf(YELLOW "Testing fill_the_map...\n" RESET);
        

//     t_map map_data;

//     char *map_file = "test_map.cub";
//     FILE *file = fopen(map_file, "w");
//     if (file)
//     {
//         fprintf(file, "111\n101\n111\n");
//         fclose(file);

//         read_map(&map_data, map_file);

//         if (map_data.map && strcmp(map_data.map[0], "111\n") == 0 &&
//             strcmp(map_data.map[1], "101\n") == 0 &&
//             strcmp(map_data.map[2], "111\n") == 0)
//         {
//             printf(GREEN "fill_the_map test passed ✅.\n" RESET);
//         }
//         else
//         {
//             printf(RED "fill_the_map test failed.\n" RESET);
//         }

//         for (int i = 0; map_data.map[i] != NULL; i++)
//         {
//             free(map_data.map[i]);
//         }
//         free(map_data.map);
//         remove(map_file);
//     }
//     else
//     {
//         printf(RED "Unable to create test map file.\n" RESET);
//     }
// }


// void test_parse_the_map()
// {
//     printf(YELLOW "Testing parse_the_map...\n" RESET);

//     t_map map_data;
//     init_struct(&map_data, NULL);

//     map_data.map = (char **)malloc(sizeof(char *) * 4);
//     map_data.map[0] = strdup("111");
//     map_data.map[1] = strdup("101");
//     map_data.map[2] = strdup("111");
//     map_data.map[3] = NULL;

//     parse_the_map(&map_data);
//     printf(GREEN "parse_the_map test passed ✅.\n" RESET);

//     for (int i = 0; map_data.map[i] != NULL; i++)
//     {
//         free(map_data.map[i]);
//     }
//     free(map_data.map);
// }

// int main()
// {
//     printf(CYAN "Starting tests...\n" RESET);

//     test_init_struct();
//     test_check_map_extension();
//     // test_fill_the_map();

//     printf(CYAN "All tests completed.\n" RESET);

//     return 0;
// }
