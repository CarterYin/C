#include <stdio.h>
int book[15][50]={0},n,a[15],sum=0;
void dfs(int i)
{
	int j;
	if(i>n)
	{
		
		sum++;
		if(sum<=3)
		{
			for(i=1;i<=n;i++)
			{
				printf("%d ",a[i]);
			}
			printf("\n");
		}
		return;
	}
	for(j=1;j<=n;j++)
	{
		if(book[1][j]==0&&book[2][j+i]==0&&book[3][j-i+13]==0)
		{
			a[i]=j;
			book[1][j]=1;
			book[2][j+i]=1;
			book[3][j-i+13]=1;
			dfs(i+1);
			book[1][j]=0;
			book[2][j+i]=0;
			book[3][j-i+13]=0;
		}
	}
	return;
}
int main()
{
	scanf("%d",&n);
	dfs(1);	
	printf("%d",sum);
	return 0;
 } 