#pragma once
namespace BearCore
{
	class BEARTOOL_API  BearMatrix
	{
	public:
		BearMatrix();
		
		BearMatrix(BearMatrix&&mat);
		BearMatrix(const BearMatrix&mat);
		
		void Swap(BearMatrix&mat);
		void Copy(const BearMatrix&mat);
		BearMatrix &operator=(const BearMatrix&mat);
		BearMatrix &operator=( BearMatrix&&mat);
		
		
		BearMatrix& BuildIdentity();
		BearMatrix& BuildOrtho(float width, float height, float screenNear, float screenDepth);
		BearMatrix& BuildOrthoOffCenter(float width, float height, float screenNear, float screenDepth);
		BearMatrix operator*(const BearMatrix&matrix)const;

		BearMatrix& Translation(float x, float y, float z);
		inline BearMatrix& Translation(BearCore::BearVector3<float> position)
		{
			return Translation(position.x, position.y, position.z);
		}
		BearMatrix& Scale(float x, float y, float z);
		inline BearMatrix& Scale(BearCore::BearVector3<float> size)
		{
			return Scale(size.x, size.y, size.z);
		}

		BearMatrix& RotateX(float x);
		BearMatrix& RotateY(float y);
		BearMatrix& RotateZ(float z);

		const float*operator*() const;
	private:
		union
		{
			float m_matrix[16];
			float m_matrix_4x4[4][4];
		};
	};
}