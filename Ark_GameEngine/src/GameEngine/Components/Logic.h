#pragma once

namespace Ark {

	enum ObjectType {
		Player = 0,
		Hazard = 1,
		Goal = 2
	};

	class Logic
	{
	public:
		Logic();
		Logic(ObjectType type, float collisionRadius);

		void SetType(ObjectType newType);
		ObjectType GetType();

		void SetRadius(float newRadius);
		float GetRadius();
		

	private:
		ObjectType m_type;
		float m_collisionRadius;
	};
}


