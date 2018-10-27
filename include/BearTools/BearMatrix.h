#pragma once
namespace BearCore
{
	class BEARTOOL_API  BearMatrix
	{
	public:
		BearMatrix();
		
		BearMatrix(BearMatrix&&mat);
		BearMatrix(const BearMatrix&mat);
		
		void swap(BearMatrix&mat);
		void copy(const BearMatrix&mat);
		BearMatrix &operator=(const BearMatrix&mat);
		BearMatrix &operator=( BearMatrix&&mat);
		
		
		BearMatrix& buildIdentity();
		BearMatrix& buildOrtho(float width, float height, float screenNear, float screenDepth);
		BearMatrix& buildOrthoOffCenter(float width, float height, float screenNear, float screenDepth);
		BearMatrix operator*(const BearMatrix&matrix)const;

		BearMatrix& translation(float x, float y, float z);
		inline BearMatrix& translation(BearCore::BearVector3<float> position)
		{
			return translation(position.x, position.y, position.z);
		}
		BearMatrix& scale(float x, float y, float z);
		inline BearMatrix& scale(BearCore::BearVector3<float> size)
		{
			return scale(size.x, size.y, size.z);
		}

		BearMatrix& rotateX(float x);
		BearMatrix& rotateY(float y);
		BearMatrix& rotateZ(float z);

		const float*operator*() const;
	private:
		union
		{
			float m_matrix[16];
			float m_matrix_4x4[4][4];
		};
	};
}