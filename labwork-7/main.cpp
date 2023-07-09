#include "ParseMP3.h"
#include "ParseCommand.h"
int main (int argc, char* argv[]) {
    ParseCommand parse = ParseCommand(argc, argv);
    ParseMP3 parse_mp3 = ParseMP3(parse.getPathToFiles(), parse.getFrameCheck());
}