#include<stdio.h>

int main()
{

	float U=10; // Freestream flow velocity
	float nu=1.4/100000; // Dynamic viscosity
	float dx = 0.0001; // Grid size
	int numX=1/dx; // Number of cells in the x-direction
	int numY=0.025/dx; // Number of cells in the y-direction
	int i=0, j=0;
	
	float Ux[numY+1]={0}; // Array that holds x-Velocity values for current row 
	float Uy[numY+1]={0}; // Array that holds y-Velocity values for current row 
	float Ux_iPlus1[numY+1]={0}; // Array that holds x-Velocity values for next row 
	float Uy_iPlus1[numY+1]={0}; // Array that holds x-Velocity values for next row 
	
	FILE *fp;
	for(i=0;i<=numY;i++)
	{
		Ux[i]=U;
	}
	Ux[0]=0;

    fp = fopen("results.csv", "a+");
    fprintf(fp, "x-coord,y-coord,z-coord,u,v\n");
  
    for(i=0; i<=numX; i++)
    {
    	j=0;
    	Ux[0]=0;
	Ux[numY]=U;
	Uy[0]=0;
	Uy_iPlus1[0]=0;
    	Ux_iPlus1[0]=0;
    	fprintf(fp, "%d,%d,0,%f,%f\n",i,j,Ux[j],Uy[j]);
	
	for(j=1; j<=numY-1; j++)
	    {
		Ux_iPlus1[j]=Ux[j]+(nu/dx)*((Ux[j+1]-2*Ux[j]+Ux[j-1])/Ux[j])-((Ux[j+1]-Ux[j-1])/2)*(Uy[j]/Ux[j]);
		Uy_iPlus1[j]=Uy_iPlus1[j-1]-0.5*(Ux_iPlus1[j]-Ux[j]+Ux_iPlus1[j-1]-Ux[j-1]);
		fprintf(fp, "%d,%d,0,%f,%f\n",i,j,Ux[j],Uy[j]);
	    }
	
	for(j=1; j<=numY-1; j++)
	    {
		Ux[j]=Ux_iPlus1[j];
		Ux_iPlus1[j]=0;
	    }
	
	printf("Step %d of %d\n",i,numX); // Print progress info on the screen	
	
    }
	fclose(fp);
}
