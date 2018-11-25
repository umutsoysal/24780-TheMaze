#ifndef FWRK3D_FP_GAME_24780
#define FWRK3D_FP_GAME_24780

class CameraObject
{
public:
	double x, y, z;
	double h, p, b;

	double fov, nearZ, farZ;

	CameraObject();
	void Initialize(void);
	void SetUpCameraProjection(void);
	void SetUpCameraTransformation(void);

	void GetForwardVector(double &vx, double &vy, double &vz);
};

#endif