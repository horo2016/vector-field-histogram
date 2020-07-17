#include <stdlib.h>
#include <math.h>

#include "histogram_grid.h"
#include "polar_histogram.h"

//
// Polar histogram-related functions.
//

hist_t * hist_init(int alpha, double threshold, double density_a, double density_b) {
  /* Create a histogram pointer and allocate memory to it. */
  hist_t * hist = malloc(sizeof(hist_t));

  /* Is there enough memory for the histogram? */
  if (NULL == hist) {
    free(hist);
    return NULL;
  }

  // TODO: `assert` that alpha is a divider of 360.

  /* Initialize the histogram parameters. */
  hist->alpha = alpha;//直方图的分辨率
  hist->sectors = 360 / alpha;//直方图的扇区
  hist->threshold = threshold;
  hist->density_a = density_a;//
  hist->density_b = density_b;
  
  hist->densities = (int *)malloc(hist->sectors * sizeof(int));

  if (hist->densities == NULL) {
    free(hist);
    return NULL;
  }

  /* Initialize all densities to 0. */
  for (int i = 0; i < hist->sectors; ++i) {
    hist->densities[i] = 0;//所有的扇区清0
  }

  return hist;
}
//直方图根据栅格图的数据进行更新
void hist_update(hist_t * hist, grid_t * grid) {
  int dim = grid->dimension;//栅格总长度
  double dens_a = 100;//hist->density_a;
  double dens_b = 2;//hist->density_b;
  double sqrtv;
  /* Calculate densities based on grid. */
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {

     // if(grid->cells[i * dim + j] == 0)
	//	  continue;
      /* Calculate the angular position (beta) of this cell. */
	  //求出当前栅格相对中心的角度
      double beta = atan2((double)(j - dim/2), (double)(i - dim/2));
	  double degree = beta*180/3.1415926;
	  
     // printf("beta %f  \n",beta);
      /* Calculate the obstacle density of this cell. */
    //  double density = pow(grid->cells[i * dim + j], 2);//求平方
	  double density = grid->cells[i * dim + j];
	  printf("atan2 beta %f val :%f \n",degree,density);
	  //printf("%d cells density is %f \n",i * dim + j,density);
	//  sqrtv = sqrt(pow(i - dim/2, 2) + pow(j - dim/2, 2));
	//  printf("%f \n",sqrtv);
    //  density *= dens_a - dens_b * sqrt(pow(i - dim/2, 2) + pow(j - dim/2, 2));
    //  printf("%d cells density is %f \n",i * dim + j,density);
      /* Add density to respective point in the histogram. */
	  if(degree >0 && degree <=90){
		   hist->densities[0] += density;
	  }
		  else  if(degree >90 && degree <=180){
			   hist->densities[1] += density;
		  }
		  else  if(degree >-180 && degree <=-90){
			   hist->densities[2] += density;
		  }
		  else  if(degree >-90 && degree <=0)
		  {
			   hist->densities[3] += density;
		  }
		   
      //hist->densities[(int) floor(beta / hist->alpha)] += density;
	 //  hist->densities[(int) floor(degree)] += density;
	 // printf("%d densities: %d \n",(int) floor(beta / hist->alpha),hist->densities[(int) floor(beta / hist->alpha)]);
    }
  }
  printf("%f %f %f %f\n",hist->densities[0],hist->densities[1],hist->densities[3],hist->densities[3]);
}


