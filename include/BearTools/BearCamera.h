#pragma once
namespace BearCore
{
	class BEARTOOL_API  BearCamera
	{
	public:
		BearCamera();
		void SetPosition(BearCore::BearVector3<float> pox);
		void SetRotation(BearCore::BearVector3<float> rot);
		void SetPosition(float x,float y,float z);
		void SetRotation(float x, float y, float z);
		void AddPosition(BearCore::BearVector3<float> pox);
		void AddRotation(BearCore::BearVector3<float> rot);
		void AddPosition(float x, float y, float z);
		void AddRotation(float x, float y, float z);
		BearCore::BearVector3<float>&GetRotation();
		const BearCore::BearVector3<float>&GetRotation()const;

		const BearMatrix&GetMatrix();
		void Render();

		void Copy(const BearCamera&right);
		void Swap(BearCamera&right);

		BearCamera(const BearCamera&right);
		BearCamera&operator=(const BearCamera&right);
		BearCamera( BearCamera&&right);
		BearCamera&operator=( BearCamera&&right);
	private:
		BearMatrix matrix;
		BearCore::BearVector3<float> m_position;
		BearCore::BearVector3<float> m_rotation;
	};
}
