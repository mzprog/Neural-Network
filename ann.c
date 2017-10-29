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
	//layer= malloc(layer_size* sizeof(struct layers));
	layer= (struct layers*)calloc(layer_size,sizeof(struct layers));

	if(layer==NULL)
		return -1;
	//allocate the neurals for the layers
	for(i=0;i<layer_size;i++)
	{
		layer[i].size=layer_number[i];
		layer[i].neural=(struct neurals *)calloc(layer[i].size+1,sizeof(struct neurals));//i
		
		if(layer[i].neural==NULL)
			return -1;
		if(i==layer_size-1)
			break;

		layer[i].weight=(struct matrix**)calloc(layer[i].size,sizeof(struct matrix *));//i
		
		if(layer[i].weight==NULL)
			return -1;
		for(j=0;j<layer_number[i];j++)
		{
			layer[i].weight[j]=(struct matrix*)calloc(layer_number[i+1],sizeof(struct matrix));//i+1
			if(layer[i].weight[j]==NULL)
				return -1;
			for(k=0;k<layer_number[i+1];k++)//give the weights and the bais random values.
			{
				layer[i].weight[j][k].weightV=(double) 3/(rand()%20+1)-1.5;
			}
		}	
		layer[i].neural[j].bais=(double)3/(rand()%20+1) -1.5;
	}



	for(j=0;j<layer_number[i];j++)
		layer[i].neural[j].bais=3/(rand()%20+1)-1.5;
	output_val=malloc(sizeof(double)*layer[i].size);
	if(output_val==NULL)
		return -1;

	return 0;
}

double * forward(double * data){


	int i,j,k;
	double sum;
	for(i=0;i<layer[0].size;i++)
		layer[0].neural[i].a=data[i];//we put it in the var a because input doesn't need activation functions

	for(k=0;k<layers_count-1;k++)//this loop to all layers.
		for(j=0;j<layer[k+1].size;j++)
		{

			sum=0;
			for(i=0;i<layer[k].size;i++){
				sum+=layer[k].neural[i].a*layer[k].weight[i][j].weightV;//the sum here
			}
			sum+=layer[k+1].neural[j].bais;//finaly add the bais
			layer[k+1].neural[j].x=sum;//then assign it to the x input
			layer[k+1].neural[j].a=sigmoid(layer[k+1].neural[j].x);//at the end assign the value of activation funtion to var a.
		}
	if(k!=layers_count-1)
		printf("error\n");
	for(i=0;i<layer[k].size;i++)
		output_val[i]=layer[k].neural[i].a;
	return output_val;

}

double  cost_fx(double * target_val){
	double  ret_val,x;
	int i;
	ret_val=0;
	for(i=0;i<layer[layers_count-1].size;i++)
	{
		x=(double) target_val[i]-layer[layers_count-1].neural[i].a;
		ret_val+=x*x;
	}
	return (0.5*ret_val);

}

void backProp(double * target){
				
	int i, j, k,n;//for dimesion of the neurons
	double delta_k,delta_j;//saving the delta 
	//find the bais and  weight delta, and correct it for the last layer
	for(i=0;i<layer[layers_count-1].size;i++){
		delta_k=(target[i]-layer[layers_count-1].neural[i].a)*layer[layers_count-1].neural[i].a*(1 -layer[layers_count-1].neural[i].a);
		//correct the bais
		layer[layers_count-1].neural[i].bais+= learnRate*delta_k;
//here is temporry value for n=0
		for(j=0;j<layer[layers_count-2].size;j++){
			layer[layers_count-2].weight[j][0].weightV+=learnRate*delta_k*layer[layers_count-2].neural[j].a;
			layer[layers_count-2].weight[j][0].deltaW=delta_k;
		}
	}
	//find bais and weight delta for the rest of the layers
	for(k=layers_count-1;k>1;k--)//loop for layers
	{
		for(j=0;j<layer[k-1].size;j++)
		{
			delta_j=0;
			for(n=0;n<layer[k].size;n++)//here new edition
				delta_j+=(layer[k-1].weight[j][n].weightV*layer[k-1].weight[j][n].deltaW);
			delta_j*=(layer[k-1].neural[j].a*(1-layer[k-1].neural[j].a));//final delta j calculation.
			
			//correct the bais
			layer[k-1].neural[j].bais+=(learnRate * delta_j);
			//correct the weights
			for(i=0;i<layer[k-2].size;i++)
			{
				layer[k-2].weight[i][j].weightV+= (learnRate * delta_j *layer[k-2].neural[i].a );
				layer[k-2].weight[i][j].deltaW=delta_j;
			}
		}
	}
}

