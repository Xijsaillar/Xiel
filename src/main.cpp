#include "XEngine.h"

int main() {
	try {
		g_XEngine.Go();
	}
	catch (char *e) {
		throw e;
	}
	return 0;
}