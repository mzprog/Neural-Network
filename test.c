#include <stdio.h>
#include "ann.c"

int main(){

	int lay[5]={2,4,5,3,1};
	int i;
	int steps=0;
	double inp[2],tar[1];

	double * outp;
	if(INIT_NETWORK(lay,5)!=0){
		printf("not working INIT_NETWORK\n");
		return 1;
	}
	else 
		printf("Network Initailized\n");
	while(1){
		printf("enter 2 data to your network:\n");
		for(i=0;i<2;i++)
			scanf("%lf",&inp[i]);
		printf("enter your target value:\n");
		scanf("%lf",&tar[0]);

		outp=forward(inp);
		printf("the output:%g\n",*outp);

		while(cost_fx(tar)>0.005)
		{
			printf("correction number %d.\n",++steps);
			printf("\tcost_fx=%lf\n",cost_fx(tar));
			backProp(tar);
			printf("new output:%g\n",*forward(inp));
		}
	}

	return 0;
}
