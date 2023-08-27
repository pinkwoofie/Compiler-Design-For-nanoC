void main()
{
    // Testing for keywords

    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        int j = i * 2;
        printf("j = %d\n", j);
    }

    char t = 'h';

    if (t != 'h')
    {
        printf("False\n");
    }
    else
    {
        printf("True\n");
    }

    
    // Testing for identifiers and constants

    // integer constants
    int _h_1_M = 656569;
    int _i_2_N = 0;
    int _j_3_P = -5687;

    // character constants
    char _a_5 = '@';
    char _a_6 = '\?';
    char _a_7 = '\n';
    char _a_8 = '\v';
    char _a_9 = 'Q';

    // string literals
    char *s1 = "Testing string literal s1. //This is not a comment.\n";
    char *s2 = "Testing string literal s2. /* This is not a comment. */";

    
    // Testing for punctuators

    int arr[5];
    int temp = 0;
    int flag = 5 % 2 + 4 / 2 - 3 * 2;

    int bit1 = 1;
    (bit1 != 1) ? printf("bit1 is not 1\n") : printf("bit1 is 1\n");


    // Testing for comments

    /*
    Checking for multi line comment. This is not a string literal.
    // further, this is a comment inside of comment, so it won't be treated as a single-line comment
    */

    // This is a single line comment

    return 0;
}