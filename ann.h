#ifndef _ANN_H_
#define _ANN_H_

#define uint16 unsigned short

//define the neurals structure
struct neurals{
	double x;//the input 
	double a;//the output
	double bais;
};
//define struct for both weight and deltaW
struct matrix{
	double weightV;
	double deltaW;
};

//define the layers structure
struct layers{
	struct neurals * neural;//pointer to array of neural for a single layer
	uint16 size;
	struct matrix ** weight;//the weight's matrix for this layer and the next one


};

struct layers * layer=0;
uint16 layers_count;
double * output_val=0;
int INIT_NETWORK(int *layer_number,int layer_size);//preparing the neural network

double * forward(double * data);//entring an array of double and the result is the array of the output

double sigmoid(double value);
#endif
