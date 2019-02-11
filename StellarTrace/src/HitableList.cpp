#include "HitableList.h"

namespace StellarTrace {
	bool HitableList::Hit(const Ray &r, float tmin, float tmax,
		HitRecord &rec) const {
		HitRecord trec;
		bool hitAnything = false;
		double closestObjectSoFar = tmax;
		for (int i = 0; i < m_List.size(); i++) {
			if (m_List[i]->Hit(r, tmin, closestObjectSoFar, trec)) {
				hitAnything = true;
				closestObjectSoFar = trec.t;
				rec = trec;
			}
		}
		return hitAnything;
	}
}