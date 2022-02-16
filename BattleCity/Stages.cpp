#include <string>
#include "Config.h"

/*
*   - air (nothing)
* b - brick
* w - wall
* B - bush
* i - ice
* W - water
* p - "protection"
* e - eagle (upper left corner)
*/

const std::string stages[36][26] = {
{ // STAGE 1
	"                          ",
	"                          ",
	"  bb  bb  bb  bb  bb  bb  ",
	"  bb  bb  bb  bb  bb  bb  ",
	"  bb  bb  bb  bb  bb  bb  ",
	"  bb  bb  bb  bb  bb  bb  ",
	"  bb  bb  bbwwbb  bb  bb  ",
	"  bb  bb  bbwwbb  bb  bb  ",
	"  bb  bb  bb  bb  bb  bb  ",
	"  bb  bb          bb  bb  ",
	"  bb  bb          bb  bb  ",
	"          bb  bb          ",
	"          bb  bb          ",
	"bb  bbbb          bbbb  bb",
	"ww  bbbb          bbbb  ww",
	"          bb  bb          ",
	"          bbbbbb          ",
	"  bb  bb  bbbbbb  bb  bb  ",
	"  bb  bb  bb  bb  bb  bb  ",
	"  bb  bb  bb  bb  bb  bb  ",
	"  bb  bb  bb  bb  bb  bb  ",
	"  bb  bb          bb  bb  ",
	"  bb  bb          bb  bb  ",
	"  bb  bb   pppp   bb  bb  ",
	"           pe p           ",
	"           p  p           "
},
{ // STAGE 2
	"      ww      ww          ",
	"      ww      ww          ",
	"  bb  ww      bb  bb  bb  ",
	"  bb  ww      bb  bb  bb  ",
	"  bb        bbbb  bbwwbb  ",
	"  bb        bbbb  bbwwbb  ",
	"      bb          ww      ",
	"      bb          ww      ",
	"BB    bb    ww    bbBBbbww",
	"BB    bb    ww    bbBBbbww",
	"BBBB      bb    ww  BB    ",
	"BBBB      bb    ww  BB    ",
	"  bbbbbbBBBBBBww    BBbb  ",
	"  bbbbbbBBBBBBww    BBbb  ",
	"      wwBBbb  bb  bb  bb  ",
	"      wwBBbb  bb  bb  bb  ",
	"wwbb  ww  bb  bb      bb  ",
	"wwbb  ww  bb  bb      bb  ",
	"  bb  bb  bbbbbb  bbwwbb  ",
	"  bb  bb  bbbbbb  bbwwbb  ",
	"  bb  bb  bbbbbb          ",
	"  bb  bb  bbbbbb          ",
	"  bb              bb  bb  ",
	"  bb       pppp   bb  bb  ",
	"  bb  bb   pe p   bbbbbb  ",
	"  bb  bb   p  p   bbbbbb  "
},
{ // STAGE 3
	"        bb      bb        ",
	"        bb      bb        ",
	"  BBBBBBbb                ",
	"  BBBBBBbb          wwwwww",
	"bbBBBBBB                  ",
	"bbBBBBBB                  ",
	"BBBBBBBB      bb  bbbbbbb ",
	"BBBBBBBB      bb  bbbbbbb ",
	"BBBBBBBBbbbbbbbb  bb   b  ",
	"BBBBBBBBbbbbbb    bb   b  ",
	"BBBBBBBB    bb         b  ",
	"BBBBBBBB    bb         b  ",
	"  BB        wwwwww    BB  ",
	"  BB        wwwwww    BB  ",
	"                  BBBBBBBB",
	"  bb  bb          BBBBBBBB",
	"bbb  bbbb  bbbbbbbBBBBBBBB",
	"bbb  bbbb  b      BBBBBBBB",
	"          bb      BBBBBBBB",
	"          bb  bbbbBBBBBBBB",
	"bb    w       bbbbBBBBBB  ",
	"bb    w           BBBBBB  ",
	"bbbb  w           BBBBBB  ",
	"bbbb  w    pppp   BBBBBB  ",
	"wwbbbb     pe p   bb      ",
	"wwbbbb     p  p   bb      "
},
{ // EMPTY STAGE
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          ",
	"                          "
}
};

const uint8_t tanks[36][20] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{3, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3, 3}
};