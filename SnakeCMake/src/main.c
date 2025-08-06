#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "state.h"
#include "screen.h"
#include "globals.h"



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//int main(int argc, char* argv[]) {
//	Screen_reset();
//	Screen_print();
//	return 0;
//}


#include <stdio.h>
#include <conio.h>

int main() {
    printf("Press any key (q to quit):\n");

    while (1) {
        if (_kbhit()) {
            char c = _getch();
            printf("You pressed: %c\n", c);
            if (c == 'q') break;
        }
        // Do other non-blocking stuff here
        Sleep(10); // sleep for 10ms
    }

    return 0;
}