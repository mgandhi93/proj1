#include "stdafx.h"
#include "BRDF.h"


BRDF::BRDF() {
	kd = Color(0, 0, 0);
	ka = Color(0, 0, 0);
	ks = Color(0, 0, 0);
	kr = Color(0, 0, 0);
	ksp = 0;
}

BRDF::BRDF(float kar, float kag, float kab, float kdr, float kdg, float kdb, float ksr, float ksg, float ksb, float ksp, float krr, float krg, float krb){
	kd = Color(kdr, kdg, kdb);
	ks = Color(ksr, ksg, ksb);
	ka = Color(kar, kag, kab);
	kr = Color(krr, krg, krb);
	this->ksp = ksp;
}