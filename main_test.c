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


void test_parsing_textures()
{
    printf(YELLOW "Testing parsing_textures...\n" RESET);
    
    t_map map_data;

    // Valid texture paths
    map_data.north_txture = strdup("valid_texture_path_north.xpm");
    map_data.south_txture = strdup("valid_texture_path_south.xpm");
    map_data.west_txture = strdup("valid_texture_path_west.xpm");
    map_data.east_txture = strdup("valid_texture_path_east.xpm");

    int id = fork();
    if (id == 0)
    {
        parsing_textures(&map_data);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "parsing_textures valid textures test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "parsing_textures valid textures test failed ❌.\n" RESET);
        }
    }

    // Invalid texture paths
    map_data.north_txture = strdup("invalid_path.xpm");

    id = fork();
    if (id == 0)
    {
        parsing_textures(&map_data);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf(GREEN "parsing_textures invalid textures test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "parsing_textures invalid textures test failed ❌.\n" RESET);
        }
    }
}

void test_define_texture()
{
    printf(YELLOW "Testing define_texture...\n" RESET);
    
    t_map map_data;
    char *splitted[2];

    // Test for valid north texture
    splitted[0] = "NO";
    splitted[1] = "texture_north.xpm";

    int result = define_texture(splitted, &map_data);
    if (result == 1 && strcmp(map_data.north_txture, "texture_north.xpm") == 0)
    {
        printf(GREEN "define_texture north texture test passed ✅.\n" RESET);
    }
    else
    {
        printf(RED "define_texture north texture test failed ❌.\n" RESET);
    }

    // Test for invalid texture key
    splitted[0] = "XX";
    splitted[1] = "texture_invalid.xpm";
    result = define_texture(splitted, &map_data);

    if (result == 4)
    {
        printf(GREEN "define_texture invalid key test passed ✅.\n" RESET);
    }
    else
    {
        printf(RED "define_texture invalid key test failed ❌.\n" RESET);
    }
}

void test_check_duplicated_textures()
{
    printf(YELLOW "Testing check_duplicated_textures...\n" RESET);
    
    t_map map_data;
    map_data.file = malloc(5 * sizeof(char*));

    // Valid textures, no duplication
    map_data.file[0] = strdup("NO texture_north.xpm");
    map_data.file[1] = strdup("SO texture_south.xpm");
    map_data.file[2] = strdup("WE texture_west.xpm");
    map_data.file[3] = strdup("EA texture_east.xpm");
    map_data.file[4] = NULL;

    int id = fork();
    if (id == 0)
    {
        check_duplicated_textures(&map_data);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "check_duplicated_textures no duplicates test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "check_duplicated_textures no duplicates test failed ❌.\n" RESET);
        }
    }

    // Duplicated textures
    map_data.file[2] = strdup("NO texture_north_dup.xpm");
    id = fork();
    if (id == 0)
    {
        check_duplicated_textures(&map_data);
        exit(1);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf(GREEN "check_duplicated_textures duplicate test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "check_duplicated_textures duplicate test failed ❌.\n" RESET);
        }
    }
}

void test_defining_textures()
{
    printf(YELLOW "Testing defining_textures...\n" RESET);
    
    t_map map_data;
    map_data.file = malloc(5 * sizeof(char*));

    // Valid texture keys
    map_data.file[0] = strdup("NO texture_north.xpm");
    map_data.file[1] = strdup("SO texture_south.xpm");
    map_data.file[2] = strdup("WE texture_west.xpm");
    map_data.file[3] = strdup("EA texture_east.xpm");
    map_data.file[4] = NULL;

    int id = fork();
    if (id == 0)
    {
        defining_textures(&map_data);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "defining_textures valid keys test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "defining_textures valid keys test failed ❌.\n" RESET);
        }
    }

}

void test_parsing_colors()
{
    printf(YELLOW "Testing parsing_colors...\n" RESET);
    
    t_map map_data;
    
    // Test valid floor and ceiling color
    map_data.floor_color = strdup("255,255,255");
    map_data.ceiling_color = strdup("128,128,128");
    
    int id = fork();
    if (id == 0)
    {
        parsing_colors(&map_data);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "1 - parsing_colors valid colors test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "1 - parsing_colors valid colors test failed ❌.\n" RESET);
        }
    }

    // Test invalid floor color with missing commas
    map_data.floor_color = strdup("255255255");
    
    id = fork();
    if (id == 0)
    {
        parsing_colors(&map_data);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf(GREEN "2 - parsing_colors invalid colors test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "2 - parsing_colors invalid colors test failed ❌.\n" RESET);
        }
    }
}

void test_define_colors()
{
    printf(YELLOW "Testing define_colors...\n" RESET);

    t_map map_data;
    map_data.floor_color = NULL;
    map_data.ceiling_color = NULL;
    
    // Test for valid floor color definition
    int result = define_colors("255,0,0", &map_data, 'F');
    if (result == 1 && strcmp(map_data.floor_color, "255,0,0") == 0)
    {
        printf(GREEN "1 - define_colors floor color test passed ✅.\n" RESET);
    }
    else
    {
        printf(RED "1 - define_colors floor color test failed ❌.\n" RESET);
    }
    
    // Test for duplicated floor color
    result = define_colors("255,0,0", &map_data, 'F');
    if (result == 0)
    {
        printf(GREEN "2 - define_colors duplicated floor color test passed ✅.\n" RESET);
    }
    else
    {
        printf(RED "2 - define_colors duplicated floor color test failed ❌.\n" RESET);
    }

    // Test for valid ceiling color definition
    result = define_colors("128,128,128", &map_data, 'C');
    if (result == 1 && strcmp(map_data.ceiling_color, "128,128,128") == 0)
    {
        printf(GREEN "3 - define_colors ceiling color test passed ✅.\n" RESET);
    }
    else
    {
        printf(RED "3 - define_colors ceiling color test failed ❌.\n" RESET);
    }
}

void test_check_duplicated_colors()
{
    printf(YELLOW "Testing check_duplicated_colors...\n" RESET);

    t_map map_data;
    map_data.file = malloc(5 * sizeof(char*));
    
    // Test for no duplicated colors
    map_data.file[0] = strdup("F 255,255,255");
    map_data.file[1] = strdup("C 128,128,128");
    map_data.file[2] = NULL;
    
    int id = fork();
    if (id == 0)
    {
        check_duplicated_colors(&map_data);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "1 - check_duplicated_colors no duplication test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "1 - check_duplicated_colors no duplication test failed ❌.\n" RESET);
        }
    }

}
void test_checking_commas()
{
    printf(YELLOW "Testing checking_commas...\n" RESET);

    t_map map_data;
    
    // Test with valid commas
    char *valid_color = strdup("255,255,255");
    int id = fork();
    if (id == 0)
    {
        checking_commas(&map_data, valid_color);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "1 - checking_commas valid commas test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "1 - checking_commas valid commas test failed ❌.\n" RESET);
        }
    }

    // Test with consecutive commas
    char *invalid_color = strdup("255,,255");
    id = fork();
    if (id == 0)
    {
        checking_commas(&map_data, invalid_color);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf(GREEN "2 - checking_commas consecutive commas test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "2 - checking_commas consecutive commas test failed ❌.\n" RESET);
        }
    }

    // Test with missing commas
    invalid_color = strdup("255255255");
    id = fork();
    if (id == 0)
    {
        checking_commas(&map_data, invalid_color);
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf(GREEN "3 - checking_commas missing commas test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "3 - checking_commas missing commas test failed ❌.\n" RESET);
        }
    }
}

// Test case for convert_the_color
void test_convert_the_color()
{
    printf(YELLOW "Testing convert_the_color...\n" RESET);

    t_map map_data;
    char *splitted_color[] = {"255", "128", "64", NULL};

    // Test valid color conversion for floor
    convert_the_color(&map_data, splitted_color, 'f');
    if (map_data.floor == ((255 << 16) | (128 << 8) | 64))
    {
        printf(GREEN "1 - convert_the_color floor conversion test passed ✅.\n" RESET);
    }
    else
    {
        printf(RED "1 - convert_the_color floor conversion test failed ❌.\n" RESET);
    }

    // Test valid color conversion for ceiling
    convert_the_color(&map_data, splitted_color, 'c');
    if (map_data.ceiling == ((255 << 16) | (128 << 8) | 64))
    {
        printf(GREEN "2 - convert_the_color ceiling conversion test passed ✅.\n" RESET);
    }
    else
    {
        printf(RED "2 - convert_the_color ceiling conversion test failed ❌.\n" RESET);
    }

}

// Test case for converting_colors
void test_converting_colors()
{
    printf(YELLOW "Testing converting_colors...\n" RESET);

    t_map map_data;

    // Test valid color input
    char *valid_color = strdup("255,128,64");
    int id = fork();
    if (id == 0)
    {
        converting_colors(&map_data, valid_color, 'f');
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "1 - converting_colors valid color test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "1 - converting_colors valid color test failed ❌.\n" RESET);
        }
    }

    // Test invalid color input (non-digit characters)
    // char *invalid_color = strdup("255,abc,64");
    // id = fork();
    // if (id == 0)
    // {
    //     converting_colors(&map_data, invalid_color, 'f');
    //     exit(0);
    // }
    // else if (id > 0)
    // {
    //     int status;
    //     waitpid(id, &status, 0);
    //     if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
    //     {
    //         printf(GREEN "2 - converting_colors invalid color (non-digit) test passed ✅.\n" RESET);
    //     }
    //     else
    //     {
    //         printf(RED "2 - converting_colors invalid color (non-digit) test failed ❌.\n" RESET);
    //     }
    // }

    // Test with spaces in color input
    char *color_with_spaces = strdup(" 255, 128, 64 ");
    id = fork();
    if (id == 0)
    {
        converting_colors(&map_data, color_with_spaces, 'f');
        exit(0);
    }
    else if (id > 0)
    {
        int status;
        waitpid(id, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf(GREEN "3 - converting_colors valid color with spaces test passed ✅.\n" RESET);
        }
        else
        {
            printf(RED "3 - converting_colors valid color with spaces test failed ❌.\n" RESET);
        }
    }
}

int main()
{
    printf(GREEN "Running tests...\n" RESET);
    test_check_map_extension();
    test_define_texture();
    test_check_duplicated_textures();
    test_defining_textures();
    test_define_colors();
    test_check_duplicated_colors();
    test_convert_the_color();
    test_converting_colors();
    test_checking_commas();
    // test_parsing_colors();


    // test_parsing_textures();

    printf(GREEN "All tests completed.\n" RESET);

    return 0;
}
