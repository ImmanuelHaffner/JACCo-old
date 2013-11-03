



int a[100][100],b[100][100],c[100][100];

main()
{
int i,j,k;



        for (i=0; i<100; i++)
        {
                for (j=0; j<100; j++)
                {
                        a[i][j] = 1;
                        b[i][j] = 1;
                }
        }
        for (i=0; i<100; i++)
        {
                for (j=0; j<100; j++)
                {
                        c[i][j] = 0;
                        for (k=0; k<100; k++)
                        {
                                c[i][j] = c[i][j] + a[i][k] * b[k][j];
                        }
                }
        }
        for (i=0; i<100; i++)
        {
                for (j=0; j<100; j++)
                {
                        if (c[i][j] != 100)
                        {
                                puts("ERROR");
                                return 0;
                        }
                }
        }
 i=5;

 return 0;
}
