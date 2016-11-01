#include <stdio.h>                                                                                                                                                      
#include <time.h>

typedef struct FunctionParameter
{
        int m_nLeft; 
        int m_nRight; //Also indicates the size the array
}FuncPara;

typedef void (*SortSet)( int ndata[],FuncPara fp,int(*rule)(int x,int y));

struct SortAlgorithm
{
        SortSet m_funSort;
        char m_strName[30];
};

int
rule1( int x, int y )
{
        return x - y;
}

int
rule2( int x, int y )
{
        return y - x;
}

/*
 * Evaluation of the bubble sort algorithm:
 *      
 *      Average time complexity: O( N ^ 2 ).
 *
 *      Be sensitive to data.
 *
 *************************************************************************************/

void
BubbleSort( int ndata[],FuncPara fp,int (*rule)( int x,int y ) )
{
        /* Funtion      : Bubble sort a set of data
         * Precondition : Incoming a rule function, according to the rule function to sort.
         * Postcondition: NO
         */

        int i,j;

        for( i = 0; i < fp.m_nRight - 1; i++ )
        {
                int nfage = 1;
                for( j = 0; j < fp.m_nRight - i - 1; j++ )
                {
                        if( rule( ndata[j],ndata[j+1] ) > 0 )
                        {
                                ndata[j]        = ndata[j] ^ ndata[ j+1 ];
                                ndata[ j+1 ]    = ndata[j] ^ ndata[ j+1 ];
                                ndata[j]        = ndata[j] ^ ndata[ j+1 ];
                                nfage = 0;
                        }
                }
                if( nfage )
                        break;
        }
}

/*
 * Evaluation of the insert sort algorithm:
 *      
 *      Average time complexity: O( N ^ 2 ).
 *
 *      Is very sensitive to data.
 *
 *************************************************************************************/

void
InsertSort( int ndata[],FuncPara fp,int (*rule)( int x,int y ) )
{
        /* Funtion      : Insert sort a set of data. 
         * Precondition : Incoming a rule function, .
         * Postcondition: NO
         */

        int i,j;
        for( i = 1; i < fp.m_nRight; i++ )
        {
                int ntemp = ndata[i];
                for( j = i; j > 0 && rule( ntemp, ndata[j - 1] ) < 0; j-- )
                {
                        ndata[j] = ndata[ j - 1 ];
                }
                ndata[j] = ntemp;
        }
}


/*
 * Evaluation of the select sort algorithm:
 *      
 *      Average time complexity: O( N ^ 2 ).
 *
 *      Is very sensitive to data.
 *
 *************************************************************************************/

void
SelectSort( int ndata[],FuncPara fp,int (*rule)( int x,int y ) )
{
        /* Funtion      : Select sort a set of data. use rule function to determine the collation of data.
         * Precondition : Incoming a rule function.
         * Postcondition: NO
         */

        int i,j;
        for( i = 0; i < fp.m_nRight - 1 ; i++ )
        {
                int min = i;
                for( j = i + 1; j < fp.m_nRight; j++ )
                {
                        if( rule( ndata[j],ndata[min] ) < 0 )
                        {
                                min = j;
                        }
                }
                if( min != i )
                {
                        ndata[i]        = ndata[i] ^ ndata[min];
                        ndata[min]      = ndata[i] ^ ndata[min];
                        ndata[i]        = ndata[i] ^ ndata[min];
                }
        }
}

/*
 * Evaluation of the select sort algorithm:
 *      
 *      Average time complexity: O( N log N ).
 *
 *      Unstable ordering.
 *
 *************************************************************************************/

void
QuickSort( int ndata[],FuncPara fp,int (*rule)( int x,int y ) )
{
        /* Funtion      : Quick sort a set of data, use rule function to determine the collation of data.
         * Precondition : Incoming a rule function, temporarily not used.
         * Postcondition: No
         */
        int i,j;
        int iPivot = ( fp.m_nLeft + fp.m_nRight ) / 2;
        int nPivot = ndata[iPivot];
        for( i = fp.m_nLeft,j = fp.m_nRight; i < j; )
        {
                while( !( i >= iPivot || nPivot < ndata[i]) )
                        i++;
                if ( i < iPivot )
                {
                        ndata[iPivot]   = ndata[i];
                        iPivot          = i;
                }
                while( !( j <= iPivot || nPivot > ndata[j]) )
                        j--;
                if ( j > iPivot )
                {
                        ndata[iPivot]   = ndata[j];
                        iPivot          = j;
                }
        }
        ndata[iPivot] = nPivot;
        if( iPivot - fp.m_nLeft > 1 )
        {
                FuncPara mfp = {fp.m_nLeft,iPivot - 1};
                QuickSort( ndata,mfp,rule );
        }                                                                                                                                                               
        if( fp.m_nRight - iPivot > 1 )
        {
                FuncPara mfp = { iPivot + 1,fp.m_nRight };
                QuickSort( ndata,mfp,rule );
        }
}

void 
Print( int ndata[], int nsize )
{
        /* function     : print a array.
         */

        int i;
        for( i = 0; i < nsize; i++ )
        {
                if( i % 10 == 0 )
                        printf("\n");

                printf("%d ",ndata[i] );
        }
        printf("\n");
}

void 
SortAggregateScheduling( struct SortAlgorithm nfun[],int nsize )
{
        /* function     : Responsible for all the sorting functions.
         * precondition : Incoming for all function set.
         * postcondition: No
         */
        int i;
        clock_t start,stop;
        for( i = 0; i < nsize; i++ )
        {
                int arr[] = {6,9,1,5,3,8,2,0,7,4};
                int nsize = sizeof( arr)  / sizeof( arr[0] );
                FuncPara fp = {0,nsize};

                printf("Sort before: ");
                Print( arr,nsize );

                start = clock();
                nfun[i].m_funSort( arr,fp,rule1 );
                stop = clock();

                printf("Sort after: ");
                Print( arr,nsize );
                printf("%s\t,Total use time: %f \n\n ", nfun[i].m_strName,( (double)( stop - start ) ) / CLOCKS_PER_SEC );
        }                                                                                                                                                               
}

int
main(void)
{
        struct SortAlgorithm sa[] = {
                BubbleSort,     "Bubble Sort",
                InsertSort,     "Insert Sort",
                SelectSort,     "Select Sort",
                QuickSort,      "Quick  Sort"
        };
        int nsize = sizeof( sa ) / sizeof( sa[0] );
        SortAggregateScheduling( sa,nsize );

        return 0;
}                                                                                                                                                                       
