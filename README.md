Current modes for main.o
BIG NOTE FOR ENEMY ATTACKING SECTOR:
I don't know where exactly sector ownership is being handled, but wherever it is
the AI should recalculate a new attack/target sector when one is taken over. These 3 lines
in the demo change the attack/target sector, place them wherever it is being done.
	int targetSector=galaxy.findTarget();
        ai.setTargetSector(sectors.at(targetSector));
        ai.setAttackSector(sectors.at(galaxy.findNeighbor(targetSector)));


a (AI), p (physics), l (level gen), c (credits)

entering nothing shows the demo

HOW TO PLAY:
 
WASD: move
Space: shoot
0: allow allies to freeform
1: order follow
2: order defend
3: order attack
E: open/close space station menu (must be close enough)
R: spawn an ally ship nearby
T: upgrade ship (50, 100)
R: heal 10 (5)
U: heal to full (5)
