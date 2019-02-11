#pragma once
#include "Hitable.h"
#include <vector>
namespace StellarTrace {
	class HitableList:public Hitable {
	public :
		HitableList() {}
		virtual bool Hit(const Ray &r, float tmin, float tmax,
			HitRecord &rec) const;
		void Add(Hitable* h) { m_List.push_back(h); }
	private :
		std::vector<Hitable*> m_List;
	};


	
}