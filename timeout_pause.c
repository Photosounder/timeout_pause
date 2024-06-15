// \
clang timeout_pause.c -o timeout_pause.exe -Os -lwinmm && strip timeout_pause.exe

#include <stdio.h>
#include <conio.h>
#include <synchapi.h>
#include <timeapi.h>

double get_time() { return (double) timeGetTime() / 1e3; }
void sleep(double t) { Sleep(t * 1e3 + 0.5); }
void blank_line() { printf("\r                                            \r"); }

int main(int argc, char *argv[])
{
	double dur, slice = 0.02;
	if (argc == 2)
		dur = atof(argv[1]);
	else
	{
		fprintf(stderr, "Usage: timeout_pause <timeout in seconds>\nExample: timeout_pause 2.5\n");
		return EXIT_FAILURE;
	}
	printf("\n");

	double end_time = get_time() + dur;

	while (get_time() < end_time)
	{
		blank_line();
		printf("Press any key to avoid exiting (in %.1f sec)", end_time - get_time());

		// Sleep
		if (end_time - get_time() < slice)
			slice = end_time - get_time();
		sleep(slice);

		// See if any key was pressed
		if (_kbhit())
		{
			// Pop any key continuously for 0.125 seconds
			end_time = get_time() + 0.125;
			while (get_time() < end_time)
			{
				if (_kbhit())
					_getch();
				else
					sleep(0.01);
			}

			blank_line();
			printf("Press any key to exit.");

			// Wait for the next key to exit
			_getch();
			break;
		}
	}

	blank_line();

	return 0;
}
