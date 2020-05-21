#ifndef __CALCULATE_MEASURE_H
#define __CALCULATE_MEASURE_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <GUI.h>
#include <math.h>

#define BLUE_RANGE						0x00
#define GREEN_RANGE						0x01
#define RED_RANGE							0x02
#define FAR_RED_RANGE					0x03

//L*a*b
static const uint16_t Xref_CIE1931[6] = {10985, 9504, 9807, 9642, 9568, 9497};
static const uint16_t Zref_CIE1931[6] = {3558, 10888, 11822, 8251, 9214, 12261};
//____
static const uint16_t Xref_CIE1964[6] = {11114, 9481, 9729, 9672, 9580, 9442};
static const uint16_t Zref_CIE1964[6] = {3520, 10732, 11614, 8143, 9093, 12064};

//T color
static const uint16_t Tc_tabl[31] = {600, 575, 550, 525, 500, 475, 450, 425, 400, 375, 350, 325, 300, 275, 250, 225, 200, 175, 150, 125, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0};
static const uint16_t u0[31] = {33724, 32931, 32129, 31320, 30505, 29685, 28863, 28039, 27218, 26400, 25591, 24792, 24010, 23247, 22511, 21807, 21142, 20525, 19962, 19462,
																19032, 18880, 18740, 18611, 18494, 18388, 18293, 18208, 18133, 18066, 18006};
static const uint16_t v0[31] = {36051, 36038, 36011, 35968, 35907, 35823, 35714, 35577, 35407, 35200, 34951, 34655, 34308, 33904, 33439, 32909, 32312, 31647, 30921, 30141,
																29326, 28997, 28668, 28342, 28021, 27709, 27407, 27119, 26846, 26589, 26352};
static const float 		t[31] =  {-116.45, -40.77, -23.325, -15.628, -11.324, -8.5955, -6.7262, -5.3762, -4.3633, -3.5814, -2.9641, -2.4681, -2.0637, -1.7298, -1.4512, -0.2168,
																-1.0182, -0.84901, -0.70471, -0.58204, -0.47888, -0.44278, -0.40955, -0.37915, -0.35156, -0.32675, -0.3047, -0.28539, -0.26876, -0.25479, -0.24341};

static const float 		t_sqrt[31] =  {116.4542936, 40.78226208, 23.34642639, 15.65996117, 11.36806826, 8.653474461, 6.800129884, 5.468411693, 4.476425682, 3.718390238, 3.128240529,
																			2.662990351, 2.293219939, 1.99805106, 1.762379482, 1.023231274, 1.427140932, 1.31179952, 1.223362654, 1.157052532, 1.108749771, 1.093642596,
																			1.080616122, 1.06946469, 1.059997374, 1.052029259, 1.045390879, 1.039926657, 1.035486329, 1.031948615, 1.029197954};

//dominant lambda
static const uint16_t lamda_dominant[66] = {380, 385, 390, 395, 400, 405, 410, 415, 420, 425, 430, 435, 440, 445, 450, 455, 460, 465, 470, 475, 480, 485, 490, 495, 500, 505, 510,
																					515, 520, 525, 530, 535, 540, 545, 550, 555, 560, 565, 570, 575, 580, 585, 590, 595, 600, 605, 610, 615, 620, 625, 630, 635, 640, 645,
																					650, 655, 660, 665, 670, 675, 680, 685, 690, 695, 700, 380};		
static const float x34_dominant[66] = {	0.17721519, 0.171875, 0.172131148, 0.172727273, 0.173123487, 0.173134328, 0.172550575, 0.172023941, 0.171428571, 0.170313987, 0.168877521,
																			0.16689529, 0.164416541, 0.161120111, 0.156641662, 0.150985408, 0.143960396, 0.135502671, 0.124142313, 0.109594324, 0.091256205, 0.068761114,
																			0.045377198, 0.023459943, 0.008168028, 0.003858521, 0.013870246, 0.038851802, 0.074339401, 0.114154776, 0.154716276, 0.192840055, 0.229619673,
																			0.265775085, 0.30157957, 0.337396231, 0.373101544, 0.408748569, 0.444062464, 0.478774791, 0.512472036, 0.544786506, 0.575151311, 0.602932786,
																			0.6270366, 0.648233106, 0.66578126, 0.680098565, 0.691485918, 0.700606061, 0.7079568, 0.714059823, 0.719056028, 0.723046092, 0.725992318,
																			0.728271728, 0.729969013, 0.722288439, 0.7319933, 0.732718894, 0.73354232, 0.734375, 0.734627832, 0.734883721, 0.735483871, 0.17721519};

static const float y34_dominant[66] = {	0, 0.0078125, 0.004098361, 0.004545455, 0.004842615, 0.004477612, 0.004760016, 0.004876967, 0.005102041, 0.005788138, 0.006900244, 0.008535284,
																			0.010857251, 0.013793103, 0.017704887, 0.022740193, 0.02970297, 0.039879121, 0.057814485, 0.086842511, 0.132684231, 0.200711322, 0.294951787,
																			0.412703479, 0.538423071, 0.654823151, 0.750186428, 0.812016021, 0.833822666, 0.826163941, 0.805833411, 0.781698565, 0.75432909, 0.724323925,
																			0.692366572, 0.658848333, 0.62445086, 0.589624631, 0.554713903, 0.520202307, 0.486577181, 0.454434115, 0.424232235, 0.396496634, 0.372491145,
																			0.351394916, 0.334019523, 0.319756486, 0.308352218, 0.299300699, 0.2920432, 0.285940177, 0.280943972, 0.276953908, 0.274007682, 0.271728272,
																			0.270030987, 0.277711561, 0.2680067, 0.267281106, 0.26645768, 0.265625, 0.265372168, 0.265116279, 0.264516129, 0};

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
																			
float Calculate_EL_Day(float R_data[], float Spectral_Day_const[]);
float Calculate_EL_Night(float R_data[], float Spectral_Night_const[]);
float Calculate_SP(float EL_day_data, float EL_Night_data);
float Calculate_PPFD_PPL(float R_data[], float Wavelenght[]);
float Calculate_PPFD_PPL_Range(float R_data[], float Wavelenght[], uint8_t Range);
float Calculate_ELr(float R_data[], float Hazard_Retina[]);
float Calculate_ELb(float R_data[], float Hazard_Blue[]);
void Calculate_XYZ1964(float R_data[], float colorimetry_x[], float colorimetry_y[], float colorimetry_z[]);
void Calculate_XYZ1931(float R_data[], float colorimetry_x[], float colorimetry_y[], float colorimetry_z[]);
void Calculate_xy1964(uint16_t colorimetry_XYZ_calculate[]);
void Calculate_xy1931(uint16_t colorimetry_XYZ_calculate[]);
void Calculate_uv(float colorimetry_xy_calculate[]);
void Calculate_uv1976(float colorimetry_xy_calculate[]);
float Calculate_Tc(float R_data[], uint8_t CIE_Type);
void Calculate_Lab(uint16_t colorimetry_XYZ_calculate[], uint8_t CIE_Type, uint8_t Source_Type);
void Calculate_Lambda_Dominant(float R_data[], uint8_t CIE_Type);
int16_t Calculate_deltaEab();
float Calculate_EL_Day_Wt(float R_data[]);
#endif /* __CALCULATE_MEASURE_H */