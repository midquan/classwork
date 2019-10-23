/* 
Sphere.c
Michael Quan
midquan
Lab 7 
Find volume and surface area from an inputted radius
*/
#include<stdio.h>
#include<math.h>

int main(){
	const double pi = 3.141592654;
	double rad,vol,surf;
	
	printf("Enter the radius of the sphere: ");
	scanf("%lf", &rad);
	vol = 4.0/3.0 * pi * pow(rad,3) ;
	surf = 4.0 * pi * pow(rad,2);
	printf("The volume is %f and the surface area is %f.\n", vol, surf);
	return 0;
}