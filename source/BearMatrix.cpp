#include "BearCore.hpp"
#include <math.h>
static void multiply (float* result, const float* matrix1, const float* matrix2)
{
	result[0] = (matrix1[0] * matrix2[0]) + (matrix1[1] * matrix2[4]) + (matrix1[2] * matrix2[8]) + (matrix1[3] * matrix2[12]);
	result[1] = (matrix1[0] * matrix2[1]) + (matrix1[1] * matrix2[5]) + (matrix1[2] * matrix2[9]) + (matrix1[3] * matrix2[13]);
	result[2] = (matrix1[0] * matrix2[2]) + (matrix1[1] * matrix2[6]) + (matrix1[2] * matrix2[10]) + (matrix1[3] * matrix2[14]);
	result[3] = (matrix1[0] * matrix2[3]) + (matrix1[1] * matrix2[7]) + (matrix1[2] * matrix2[11]) + (matrix1[3] * matrix2[15]);

	result[4] = (matrix1[4] * matrix2[0]) + (matrix1[5] * matrix2[4]) + (matrix1[6] * matrix2[8]) + (matrix1[7] * matrix2[12]);
	result[5] = (matrix1[4] * matrix2[1]) + (matrix1[5] * matrix2[5]) + (matrix1[6] * matrix2[9]) + (matrix1[7] * matrix2[13]);
	result[6] = (matrix1[4] * matrix2[2]) + (matrix1[5] * matrix2[6]) + (matrix1[6] * matrix2[10]) + (matrix1[7] * matrix2[14]);
	result[7] = (matrix1[4] * matrix2[3]) + (matrix1[5] * matrix2[7]) + (matrix1[6] * matrix2[11]) + (matrix1[7] * matrix2[15]);

	result[8] = (matrix1[8] * matrix2[0]) + (matrix1[9] * matrix2[4]) + (matrix1[10] * matrix2[8]) + (matrix1[11] * matrix2[12]);
	result[9] = (matrix1[8] * matrix2[1]) + (matrix1[9] * matrix2[5]) + (matrix1[10] * matrix2[9]) + (matrix1[11] * matrix2[13]);
	result[10] = (matrix1[8] * matrix2[2]) + (matrix1[9] * matrix2[6]) + (matrix1[10] * matrix2[10]) + (matrix1[11] * matrix2[14]);
	result[11] = (matrix1[8] * matrix2[3]) + (matrix1[9] * matrix2[7]) + (matrix1[10] * matrix2[11]) + (matrix1[11] * matrix2[15]);

	result[12] = (matrix1[12] * matrix2[0]) + (matrix1[13] * matrix2[4]) + (matrix1[14] * matrix2[8]) + (matrix1[15] * matrix2[12]);
	result[13] = (matrix1[12] * matrix2[1]) + (matrix1[13] * matrix2[5]) + (matrix1[14] * matrix2[9]) + (matrix1[15] * matrix2[13]);
	result[14] = (matrix1[12] * matrix2[2]) + (matrix1[13] * matrix2[6]) + (matrix1[14] * matrix2[10]) + (matrix1[15] * matrix2[14]);
	result[15] = (matrix1[12] * matrix2[3]) + (matrix1[13] * matrix2[7]) + (matrix1[14] * matrix2[11]) + (matrix1[15] * matrix2[15]);

	return;
}
BearCore::BearMatrix::BearMatrix()
{
	//BearCore::bear_fill(m_matrix, 16, 0);

}

BearCore::BearMatrix::BearMatrix(BearMatrix && mat)
{
	Copy(mat);
}

BearCore::BearMatrix::BearMatrix(const BearMatrix & mat)
{
	Copy(mat);
}

void BearCore::BearMatrix::Swap(BearMatrix & mat)
{
	BearCore::bear_swap(m_matrix, mat.m_matrix);
}

void BearCore::BearMatrix::Copy(const BearMatrix & mat)
{
	BearCore::bear_copy(reinterpret_cast<float*>( m_matrix), const_cast<float*>(mat.m_matrix),16);
}

BearCore::BearMatrix & BearCore::BearMatrix::operator=(const BearMatrix & mat)
{
	Copy(mat);
	return *this;
}

BearCore::BearMatrix & BearCore::BearMatrix::operator=(BearMatrix && mat)
{
	Copy(mat);
	return *this;
}

BearCore::BearMatrix & BearCore::BearMatrix::BuildIdentity()
{
	//BearCore::bear_fill(m_matrix, 16, 0);
	m_matrix[0] = 1.0f;
	m_matrix[1] = 0.0f;
	m_matrix[2] = 0.0f;
	m_matrix[3] = 0.0f;

	m_matrix[4] = 0.0f;
	m_matrix[5] = 1.0f;
	m_matrix[6] = 0.0f;
	m_matrix[7] = 0.0f;

	m_matrix[8] = 0.0f;
	m_matrix[9] = 0.0f;
	m_matrix[10] = 1.0f;
	m_matrix[11] = 0.0f;

	m_matrix[12] = 0.0f;
	m_matrix[13] = 0.0f;
	m_matrix[14] = 0.0f;
	m_matrix[15] = 1.0f;
	return *this;
}
BearCore::BearMatrix & BearCore::BearMatrix::BuildPerspectiveFovLH(float fieldOfView, float screenAspect, float screenNear, float screenDepth)
{
	BearCore::bear_fill(m_matrix, 16, 0);
	m_matrix[0] = 1.0f / (screenAspect * static_cast<float>(tan(fieldOfView * 0.5f)));
	m_matrix[5] = 1.0f / static_cast<float>(tan(fieldOfView * 0.5f));
	m_matrix[10] = screenDepth / (screenDepth - screenNear);
	m_matrix[11] = 1.0f;
	m_matrix[14] = -(screenNear * screenDepth) / (screenDepth - screenNear);
	return  *this;
}
BearCore::BearMatrix & BearCore::BearMatrix::BuildPerspectiveFovRH(float fieldOfView, float screenAspect, float screenNear, float screenDepth)
{
	BearCore::bear_fill(m_matrix, 16, 0);
	m_matrix[0] = 1.0f / (screenAspect * static_cast<float>(tan(fieldOfView * 0.5f)));
	m_matrix[5] = 1.0f / static_cast<float>(tan(fieldOfView * 0.5f));
	m_matrix[10] = screenDepth / (screenDepth - screenNear);
	m_matrix[11] = -1.0f;
	m_matrix[14] = (screenNear * screenDepth) / (screenDepth - screenNear);
	return  *this;
}
BearCore::BearMatrix & BearCore::BearMatrix::BuildOrtho(float width, float height, float screenNear, float screenDepth)
{
	BearCore::bear_fill(m_matrix, 16, 0);
	m_matrix[0] = float(2) / width;
	m_matrix[5] = float(2) / height;
	m_matrix[10] = 1.f / (screenDepth - screenNear);
	m_matrix[14] = screenNear / (screenNear - screenDepth);
	m_matrix[15] = 1;
	return *this;
}

BearCore::BearMatrix & BearCore::BearMatrix::BuildOrthoOffCenter(float width, float height, float screenNear, float screenDepth)
{
	BearCore::bear_fill(m_matrix, 16, 0);
	m_matrix[0] =float(2) / width;
	m_matrix[5] =-float(2) / height;
	m_matrix[10] =( 1.f / (screenDepth - screenNear));
	m_matrix[12] = -1;
	m_matrix[13] = 1;
	m_matrix[14] = screenNear / (screenNear - screenDepth);
	m_matrix[15] = 1;
	return *this;
}
void normalize(BearCore::BearVector3<float>&n)
{
	float mag = static_cast<float>(sqrt((float)1 / (n.x*n.x + n.y*n.y + n.z*n.z)));
	n.x *= mag;
	n.y *= mag;
	n.z *= mag;
}
BearCore::BearMatrix & BearCore::BearMatrix::BuildView(BearCore::BearVector3<float> position, BearCore::BearVector3<float> lookAt, BearCore::BearVector3<float> up)
{
	BearVector3<float> vView = lookAt;
	vView -= position;
	normalize(vView);
	float t = up.x*vView.x + up.y*vView.y + up.z*vView.z;
	BearVector3<float> vUp;
	vUp.x = (vView.x*-t) + up.x;
	vUp.y = (vView.y*-t) + up.y;
	vUp.z = (vView.z*-t) + up.z;
	normalize(vUp);
	BearVector3<float> vRight;
	vRight.x = (vUp.y  * vView.z) - vUp.z  * vView.y;
	vRight.y = (vUp.z  * vView.x) - vUp.x  * vView.z;
	vRight.z = (vUp.x  * vView.y) - vUp.y  * vView.x;

	// Set the computed values in the view matrix.
	m_matrix[0] = vRight.x; //11
	m_matrix[1] = vUp.x;//12
	m_matrix[2] = vView.x;//13
	m_matrix[3] = 0.0f;//14

	m_matrix[4] = vRight.y;//21
	m_matrix[5] = vUp.y;//22
	m_matrix[6] = vView.y;//23
	m_matrix[7] = 0.0f;   //24

	m_matrix[8] = vRight.z;//31
	m_matrix[9] = vUp.z;//32
	m_matrix[10] = vView.z;//33
	m_matrix[11] = 0.0f;   //34

	m_matrix[12] = -(position.x*vRight.x + position.y*vRight.y + position.z*vRight.z);//41
	m_matrix[13] = -(position.x*vUp.x + position.y*vUp.y + position.z*vUp.z);;//42
	m_matrix[14] = -(position.x*vView.x + position.y*vView.y + position.z*vView.z);;//43
	m_matrix[15] = 1.0f;   //44}
	return *this;
}

BearCore::BearMatrix BearCore::BearMatrix::operator*(const BearMatrix & matrix) const
{
	BearMatrix result;
	multiply(result.m_matrix, m_matrix, matrix.m_matrix);
	return result;
}

BearCore::BearMatrix & BearCore::BearMatrix::Translation(float x, float y, float z)
{
	BuildIdentity();
	m_matrix[12] = x;
	m_matrix[13] = y;
	m_matrix[14] = z;
	return*this;
}

BearCore::BearMatrix & BearCore::BearMatrix::Scale(float x, float y, float z)
{
	BuildIdentity();
	m_matrix_4x4[0][0] = x;
	m_matrix_4x4[1][1] = y;
	m_matrix_4x4[2][2] = z;
	return*this;
}


BearCore::BearMatrix & BearCore::BearMatrix::RotateX(float x)
{
	BuildIdentity();
	float cosa = static_cast<float>(cosf(x));
	float sina = static_cast<float>(sinf(x));
	m_matrix[5] = cosa;
	m_matrix[6] = sina;
	m_matrix[9] = -sina;
	m_matrix[10] = cosa;
	return*this;
}

BearCore::BearMatrix & BearCore::BearMatrix::RotateY(float y)
{
	BuildIdentity();
	float cosa = static_cast<float>(cosf(y));
	float sina = static_cast<float>(sinf(y));
	m_matrix[0] = cosa;
	m_matrix[2] = -sina;
	m_matrix[8] = sina;
	m_matrix[10] = cosa;
	return*this;
}

BearCore::BearMatrix & BearCore::BearMatrix::RotateZ(float z)
{
	BuildIdentity();
	float cosa = static_cast<float>(cosf(z));
	float sina = static_cast<float>(sinf(z));
	m_matrix[0] = cosa;
	m_matrix[1] = sina;
	m_matrix[4] = -sina;
	m_matrix[5] = cosa;
	return *this;
}

const float * BearCore::BearMatrix::operator*() const
{
	return m_matrix;
}
