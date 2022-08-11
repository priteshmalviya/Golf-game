#include"include/menu.cpp"
#include"include/game.cpp"
using namespace std;

int main(int argc,char* argv[]) {
	my_Init();
	create_window();
	loadMedia();
	int stat=start();
	while (stat>1) {
		if (stat == 2) {
			loadgMedia();
			stat = g_start();
		}
		if (stat == 3) {
			loadMedia();
			stat = start();
		}
	}
	close();
	return 0;
}