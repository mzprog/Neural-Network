#include "ann.h"
#include <stdlib.h>
#include <math.h>



double sigmoid(double value){

	return 1/(1 + exp(-value));

}


int INIT_NETWORK(int * layer_number,int layer_size){

	int i,j,k;

	//check if the data from user is valid
	if(layer_size<=0)
		return -1;
	for(i=0;i<layer_size;i++)
		if(layer_number[i]<=0)
			return -1;
	layers_count=layer_size;
	// allocate the layers structures
	layer=(struct layers*) malloc(layer_size* sizeof(struct layers));
	if(layer==NULL)
		return -1;
	//allocate the neurals for the layers
	for(i=0;i<layer_size;i++)
	{
		layer[i].size=layer_number[i];
		layer[i].neural=(struct neurals *) malloc(sizeof(struct neurals)*layer_number[i]);
		if(layer[i].neural==NULL)
			return -1;
		if(i==layer_size-1)
			break;

		layer[i].weight=(struct matrix **) malloc(layer_number[i]*sizeof(struct matrix *));//allocate weight raw
		if(layer[i].weight==NULL)
			return -1;
		for(j=0;j<layer_number[i];j++)
		{
			layer[i].weight[j]=(struct matrix *) malloc(layer_number[i+1]*sizeof(struct matrix));//allocate weight column
			if(layer[i].weight[j]==NULL)
				return -1;
			for(k=0;k<layer_number[i+1];k++)//give the weights and the bais random values.
			{
				layer[i].weight[j][k].weightV=(double) 3/(rand()%20+1)-1.5;
			}
		}	
		layer[i].neural[j].bais=3/(rand()%20+1) -1.5;
	}



	for(j=0;j<layer_number[i];j++)
		layer[i].neural[j].bais=3/(rand()%20+1)-1.5;
	output_val=(double *)malloc(sizeof(double)*layer[i].size);
	if(output_val==NULL)
		return -1;
	layer[i].weight=NULL;//the output layer doesn't have weights.
//we have a bug here by the pointer.
for(k=0;k<layers_count-1;k++){
	printf("on layer:%d\n",k);
	for(j=0;j<layer[k].size;j++)
	{
		//for(i=0;i<layer[k+1].size;i++)
			printf("%p\t",(void *)layer[k].weight[j]);
		printf("|\n");
	}

}


	return 0;
}

double * forward(double * data){


	int i,j,k;
	double sum;
	for(i=0;i<layer[0].size;i++)
		layer[0].neural[i].a=data[i];//we put it in the var a because input doesn't need activation functions

	for(k=0;k<layers_count-2;k++)//this loop to all layers.
		for(j=0;j<layer[k+1].size;j++)
		{
printf("k=%d\tj=%d to %d\ti to %d  \n",k,j,layer[k+1].size,layer[k].size);	

printf("weight=%lf\n",layer[0].weight[1][0].weightV);

			sum=0;
			for(i=0;i<layer[k].size;i++){
printf("##i=%d\tj=%d\tk=%d\n",i,j,k);			
				sum+=layer[k].neural[i].a*layer[k].weight[i][j].weightV;//the sum here
printf("i=%d\n",i);
			}
printf("ok2\n");			
			sum+=layer[k+1].neural[j].bais;//finaly add the bais
printf("ok3\n");	
			layer[k+1].neural[j].x=sum;//then assign it to the x input
printf("ok4\n");	
			layer[k+1].neural[j].a=sigmoid(layer[k+1].neural[j].x);//at the end assign the value of activation funtion to var a.
printf("ok5\n");			
		}
printf("out\n");	
	for(i=0;i<layer[k].size;i++)
		output_val[i]=layer[k].neural[i].a;
printf("ok6\n");
	return output_val;

}
