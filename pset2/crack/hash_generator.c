#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <crypt.h>
#include <ctype.h>


bool valid_password(char* pass, int size)
{
    int n = strlen(pass);
    if (!(n >= 0 && n <= size))
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        if(!isalnum(pass[i]))
        {
            return false;
        }
    }

    return true;
}

int main(int argc, string argv[])
{
    if (argc != 1)
    {
        printf("Usage: ./des\n");
        return 1;
    }

    char* password;
    do {
        password = get_string("Enter password: ");

    }
    while(!valid_password(password, 6));

    char* salt;
    do {
        salt = get_string("Enter salt: ");
    }
    while(!valid_password(salt, 2));

    char* hash = crypt(password, salt);
    printf("password is: %s\n", password);
    printf("salt is: %s\n", salt);
    printf("hashed password is: %s\n", hash);

}



