#include "d_cpp_interface.h"

#include "bulletmlparser.h"
#include "bulletmlparser-tinyxml.h"
#include "bulletmlrunner.h"

// BulletMLParserTinyXML
extern "C" {
	D_CPP_CLASS(BulletMLParserTinyXML, BulletMLParserTinyXML)
	__declspec(dllexport) D_CPP_NEW_1(BulletMLParserTinyXML, BulletMLParserTinyXML_new, const char*)
	__declspec(dllexport) D_CPP_METHOD_0(BulletMLParserTinyXML, parse, BulletMLParserTinyXML_parse, void)
	__declspec(dllexport) D_CPP_DELETE(BulletMLParserTinyXML, BulletMLParserTinyXML_delete)
}

// BulletMLParser
extern "C" {
	D_CPP_CLASS(BulletMLParser, BulletMLParser)
}

// BulletMLState
extern "C" {
	D_CPP_CLASS(BulletMLState, BulletMLState)
}

// BulletMLRunner virtual functions
D_CPP_BASE_CLASS_OPEN(BulletMLRunner, BulletMLRunnerD)

BulletMLRunnerD(BulletMLParser* p) : BulletMLRunner(p), D_getRand_fp(0) {}
BulletMLRunnerD(BulletMLState* s) : BulletMLRunner(s), D_getRand_fp(0) {}

D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, getBulletDirection, double)
D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, getAimDirection, double)
D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, getBulletSpeed, double)
D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, getDefaultSpeed, double)
D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, getRank, double)
D_CPP_VIRTUAL_METHOD_2(BulletMLRunnerD, createSimpleBullet, void, double, double)
D_CPP_VIRTUAL_METHOD_3(BulletMLRunnerD, createBullet, void, BulletMLState*, double, double)
D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, getTurn, int)
D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, doVanish, void)

D_CPP_VIRTUAL_METHOD_1(BulletMLRunnerD, doChangeDirection, void, double)
D_CPP_VIRTUAL_METHOD_1(BulletMLRunnerD, doChangeSpeed, void, double)
D_CPP_VIRTUAL_METHOD_1(BulletMLRunnerD, doAccelX, void, double)
D_CPP_VIRTUAL_METHOD_1(BulletMLRunnerD, doAccelY, void, double)
D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, getBulletSpeedX, double)
D_CPP_VIRTUAL_METHOD_0(BulletMLRunnerD, getBulletSpeedY, double)

double (*D_getRand_fp) (BulletMLRunnerD*);
virtual double getRand() {
	if (D_getRand_fp) {
		return D_getRand_fp(this);
	}
	else {
		return BulletMLRunner::getRand();
	}
}
void D_set_getRand(double (*fp) (BulletMLRunnerD*)) {
	D_getRand_fp = fp;
}

D_CPP_BASE_CLASS_CLOSE()

// BulletMLRunner
extern "C" {
	D_CPP_CLASS(BulletMLRunner, BulletMLRunner)
	D_CPP_CLASS(BulletMLRunnerD, BulletMLRunnerD)
	__declspec(dllexport) D_CPP_NEW_1(BulletMLRunnerD, BulletMLRunner_new_parser, BulletMLParser*)
	__declspec(dllexport) D_CPP_NEW_1(BulletMLRunnerD, BulletMLRunner_new_state, BulletMLState*)
	__declspec(dllexport) D_CPP_DELETE(BulletMLRunnerD, BulletMLRunner_delete)
	__declspec(dllexport) D_CPP_METHOD_0(BulletMLRunnerD, run, BulletMLRunner_run, void)
	__declspec(dllexport) D_CPP_METHOD_0(BulletMLRunnerD, isEnd, BulletMLRunner_isEnd, bool)

	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getBulletDirection, BulletMLRunner_set_getBulletDirection, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getAimDirection, BulletMLRunner_set_getAimDirection, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getBulletSpeed, BulletMLRunner_set_getBulletSpeed, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getDefaultSpeed, BulletMLRunner_set_getDefaultSpeed, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getRank, BulletMLRunner_set_getRank, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_2(BulletMLRunnerD, createSimpleBullet, BulletMLRunner_set_createSimpleBullet, void, double, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_3(BulletMLRunnerD, createBullet, BulletMLRunner_set_createBullet, void, BulletMLState*, double, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getTurn, BulletMLRunner_set_getTurn, int)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, doVanish, BulletMLRunner_set_doVanish, void)

	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_1(BulletMLRunnerD, doChangeDirection, BulletMLRunner_set_doChangeDirection, void, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_1(BulletMLRunnerD, doChangeSpeed, BulletMLRunner_set_doChangeSpeed, void, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_1(BulletMLRunnerD, doAccelX, BulletMLRunner_set_doAccelX, void, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_1(BulletMLRunnerD, doAccelY, BulletMLRunner_set_doAccelY, void, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getBulletSpeedX, BulletMLRunner_set_getBulletSpeedX, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getBulletSpeedY, BulletMLRunner_set_getBulletSpeedY, double)
	__declspec(dllexport) D_CPP_VIRTUAL_METHOD_SETTER_0(BulletMLRunnerD, getRand, BulletMLRunner_set_getRand, double)

}

