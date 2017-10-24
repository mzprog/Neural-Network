#include <stdio.h>
#include "ann.c"

int main(){

	int lay[5]={3,4,5,3,1};
	int i;
	double inp[3];
	double * outp;
	if(INIT_NETWORK(lay,5)!=0){
		printf("not working INIT_NETWORK\n");
		return 1;
	}
	else 
		printf("Network Initailized\n");

	printf("enter 3 data to your network:\n");
	for(i=0;i<3;i++)
		scanf("%lf",&inp[i]);
	outp=forward(inp);
	printf("the output:%g\n",*outp);
	return 0;
}
