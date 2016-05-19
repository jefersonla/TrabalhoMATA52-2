#include <stdio.h>
#include <conio.h>
#define max 255 // Tamanho dos vetores deixa esse mesmo?

int i,j;
int n;
float unit[max], fracRe[max], w[max], p[max], m;
int y[max],x[max],fp=-1,fw;

void get()
{
    scanf("%d",&n);

    for(i=0; i<n; i++)
        scanf("%f", &p[i]);

    for(i=0; i<n; i++)
        scanf("%f",&w[i]);

    scanf("%f",&m);
}

void show()
{
    float s=0;                          //Fracionada
    for(i=0; i<n; i++)
    {
        s += fracRe[i]*p[i];
    }
    printf("%.1f",s);

    for(i=0; i<n; i++)
    {
        if(fracRe[i] != 0.0)
            printf("\ni%d %.1f\t",i+1,fracRe[i]);
    }



    s=0;                             //Binaria
    for(i=0; i<n; i++)
    {
        if(x[i]==1)
            s += p[i];
    }

    printf("\n%.1f ",s);

    for(i=0; i<n; i++)
        if(x[i]==1)
        {
            printf("\ni%d",i+1);
        }

}

//Arrange the item based on high profit per Unit
void sort()
{
    float t, t1, t2;
    for(i=0; i<n; i++)
        unit[i] = p[i] / w[i];
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(unit[i]  < unit[j])
            {
                t2 = unit[i];
                unit[i] = unit[j];
                unit[j] = t2;
                t = p[i];
                p[i] = p[j];
                p[j] = t;
                t1 = w[i];
                w[i] = w[j];
                w[j] =t1;
            }
        }
    }
}

float bound(float cp,float cw,int k)
{
    float b = cp;
    float c = cw;
    for(i=k; i<=n; i++)
    {
        c = c+w[i];
        if( c < m)
            b = b +p[i];
        else
            return (b+(1-(c-m)/ w[i])*p[i]);
    }
    return b;
}

void knapsack(int k,float cp,float cw)
{
    if(cw+w[k] <= m)
    {
        y[k] = 1;
        if(k <= n)
            knapsack(k+1,cp+p[k],cw+w[k]);
        if(((cp+p[k]) > fp) && ( k == n))
        {
            fp = cp+p[k];
            fw = cw+w[k];
            for(j=0; j<=k; j++)
                x[j] = y[j];
        }
    }
    if(bound(cp,cw,k) >= fp)
    {
        y[k] = 0;
        if( k <= n)
            knapsack(k+1,cp,cw);
        if((cp > fp) && (k == n))
        {
            fp = cp;
            fw = cw;
            for(j=0; j<=k; j++)
                x[j] = y[j];
        }
    }
}

void Rknapsack()
{
    int k = 0;
    float cp = 0;
    float cw = 0;
    int j;

    for(j = 0; j<n; j++)
    {
        fracRe[j] = 0;
    }

    while((cw < m)&&(k < n))
    {
        if(cw + w[k] <= m)
        {
            fracRe[k] = 1;
            cw += w[k];
            cp += p[k];
            k++;
        }
        else
        {
            fracRe[k] = (m - cw)/w[k];
            cw = m;
            cp += fracRe[k]*p[k];
            i++;
        }
    }
}

int main()
{
    get();
    sort();
    knapsack(0,0.0,0.0);
    Rknapsack();
    show();
    system ("pause");
}
