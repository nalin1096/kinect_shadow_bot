// kinect_data.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <NuiApi.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265
#define elevation_angle 5

#define rs_rw joint_vectors[0]   //right shoulder to right wrist
#define rs_rh joint_vectors[1]   //right shoulder to right hip
#define re_rs joint_vectors[2]   //right elbow to right shoulder
#define re_rw joint_vectors[3]   //right elbow to right wrist
#define ls_lw joint_vectors[4]   //left shoulder to left wrist
#define ls_lh joint_vectors[5]   //left shoulder to left hip
#define le_ls joint_vectors[6]   //left elbow to left shoulder
#define le_lw joint_vectors[7]   //left elbow to left wrist
#define rh_rs joint_vectors[8]   //right hip to right shoulder
#define rh_rk joint_vectors[9]   //right hip to right knee
#define rk_rh joint_vectors[10]   //right knee to right hip
#define rk_ra joint_vectors[11]   //right knee to right ankle
#define lh_ls joint_vectors[12]   //left hip to left shoulder
#define lh_lk joint_vectors[13]   //left hip to left knee
#define lk_lh joint_vectors[14]   //left knee to left hip
#define lk_la joint_vectors[15]   //left knee to left ankle

using namespace std;

NUI_SKELETON_FRAME myframe;

struct vector {
	float x, y, z;
};

struct angle {
	double joint_angle;
	int servo_angle;
};

class joints {
	vector joint_data[12];
public:
	joints(int i) {
		myframe.SkeletonData.
	}
};

class skeleton : public joints{
private:
	angle angle_info[8];
	vector joint_vectors[2];
public:
	skeleton(int i) :right_shoulder(i), right_wrist(i), right_hip(i)
	{}
	vector calculate_vector(vector src, vector dest) {
		vector link_vector;
		link_vector.x = 0;
		link_vector.y = dest.y - src.y;
		link_vector.z = dest.z - src.z;
		return link_vector;
	}

	double calculate_angle (vector v1, vector v2){
		double temp_joint_angle;
		temp_joint_angle = acos(((v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z)) / (sqrt(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2)) * sqrt(pow(v2.x, 2) + pow(v2.y, 2) + pow(v2.z, 2)))) * 180 / PI;
	}

	void get_data() {
		rs_rw = calculate_vector(right_shoulder::get_coords(), right_wrist::get_coords());   //shoulder to wrist
		rs_rh = calculate_vector(right_shoulder::get_coords(), right_hip::get_coords());  //shoulder to hip

	}

	void get_angle() {
		angle_info[0].joint_angle = calculate_angle(rs_rw, rs_rh);
		printf("SHOULDER ANGLE : %f\n", angle_info[0].joint_angle - 5);   //subtract the correction value
	}
};

void kinect_setup() {
	int flag = 1;
	while (flag) {
		NuiSkeletonGetNextFrame(0, &myframe);
		for (int i = 0; i < 1; i++) {
			if (myframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED) {
				if (myframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT].z > 2.9 && myframe.SkeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT].z < 3.1) {
					cout << "CENTER IS READY, GO SHADOW !!!!" << endl;
					flag = 0;
				}
			}
		}
	}
	return;
}

int main()
{
	NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	NuiSkeletonGetNextFrame(0, &myframe);
	NuiCameraElevationSetAngle(elevation_angle);

	kinect_setup();
	
	while (1) {
		NuiSkeletonGetNextFrame(0, &myframe);
		for (int i = 0; i < 1; i++) {
			if (myframe.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED) {
				skeleton lab_rat (i);
				lab_rat.get_data();
				lab_rat.get_angle();
			}
		}
	}
	return 0;
}

